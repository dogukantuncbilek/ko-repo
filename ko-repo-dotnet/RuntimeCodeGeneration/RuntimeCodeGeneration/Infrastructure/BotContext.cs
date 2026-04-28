using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace RuntimeCodeGeneration.Infrastructure
{
    public interface IBotContext
    {
        void UseSkill(uint skillId);
        void WalkTo(float x, float z);
        void Attack(uint targetId);
        uint GetHP();
        uint GetMP();
        void Log(string msg);
    }
    public class MockBotContext : IBotContext
    {
        public uint HP = 5000;
        public uint MP = 3000;
        public float X = 500f, Z = 300f;

        private readonly Action<string> _logger;
        public readonly List<string> ActionLog = new List<string>();

        public MockBotContext(Action<string> logger = null)
        {
            _logger = logger ?? Console.WriteLine;
        }

        public uint GetHP() => HP;
        public uint GetMP() => MP;

        public void UseSkill(uint skillId)
        {
            string action = $"UseSkill({skillId})";
            ActionLog.Add(action);
            _logger?.Invoke($"  >> {action}");
            MP = (uint)Math.Max(0, (int)MP - 100);
        }

        public void Attack(uint targetId)
        {
            string action = $"Attack({targetId})";
            ActionLog.Add(action);
            _logger?.Invoke($"  >> {action}");
        }

        public void WalkTo(float x, float z)
        {
            string action = $"WalkTo({x}, {z})";
            ActionLog.Add(action);
            _logger?.Invoke($"  >> {action}");
            X = x; Z = z;
        }

        public void Log(string message) => _logger?.Invoke($"  [Script] {message}");

    }
}
