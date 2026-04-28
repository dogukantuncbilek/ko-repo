using Microsoft.CodeAnalysis;
using Microsoft.CodeAnalysis.CSharp;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;

namespace RuntimeCodeGeneration.Infrastructure
{
    public class ScriptEngine
    {
        private readonly List<MetadataReference> _refs;

        public ScriptEngine()
        {
            _refs = new List<MetadataReference>();

            var runtimeDir = Path.GetDirectoryName(typeof(object).Assembly.Location);
            _refs.Add(MetadataReference.CreateFromFile(typeof(object).Assembly.Location));
            _refs.Add(MetadataReference.CreateFromFile(Path.Combine(runtimeDir, "System.Runtime.dll")));
            _refs.Add(MetadataReference.CreateFromFile(Path.Combine(runtimeDir, "System.Collections.dll")));
            _refs.Add(MetadataReference.CreateFromFile(Path.Combine(runtimeDir, "System.Threading.dll")));
            _refs.Add(MetadataReference.CreateFromFile(Path.Combine(runtimeDir, "System.Threading.Tasks.dll")));
            _refs.Add(MetadataReference.CreateFromFile(Path.Combine(runtimeDir, "System.Console.dll")));
            _refs.Add(MetadataReference.CreateFromFile(Path.Combine(runtimeDir, "System.Linq.dll")));

            // This assembly — scripts can see IScript, IBotContext
            _refs.Add(MetadataReference.CreateFromFile(typeof(IScript).Assembly.Location));
        }

        public ScriptEngine AddReference(Assembly assembly)
        {
            _refs.Add(MetadataReference.CreateFromFile(assembly.Location));
            return this;
        }

        public IScript Compile(string sourceCode)
        {
            var tree = CSharpSyntaxTree.ParseText(sourceCode);

            var compilation = CSharpCompilation.Create(
                $"Script_{Guid.NewGuid():N}",
                new[] { tree },
                _refs,
                new CSharpCompilationOptions(OutputKind.DynamicallyLinkedLibrary));

            var ms = new MemoryStream();
            var result = compilation.Emit(ms);

            if (!result.Success)
            {
                var errors = result.Diagnostics
                    .Where(d => d.Severity == DiagnosticSeverity.Error)
                    .Select(d => $"  Line {d.Location.GetLineSpan().StartLinePosition.Line + 1}: {d.GetMessage()}");
                throw new ScriptCompileException(
                    $"Compilation failed:\n{string.Join("\n", errors)}");
            }

            ms.Seek(0, SeekOrigin.Begin);
            var assembly = Assembly.Load(ms.ToArray());

            var scriptType = assembly.GetTypes()
                .FirstOrDefault(t => typeof(IScript).IsAssignableFrom(t) && !t.IsInterface);

            if (scriptType == null)
                throw new ScriptCompileException("No class implementing IScript found.");

            return (IScript)Activator.CreateInstance(scriptType);
        }
    }

    public class ScriptCompileException : Exception
    {
        public ScriptCompileException(string message) : base(message) { }
    }
}