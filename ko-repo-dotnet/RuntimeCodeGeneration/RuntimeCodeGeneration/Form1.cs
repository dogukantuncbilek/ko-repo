using RuntimeCodeGeneration.Infrastructure;
using System;
using System.Net.Http;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace RuntimeCodeGeneration
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }
        private ScriptEngine _engine = new ScriptEngine();

        private async void button2_Click(object sender, EventArgs e)
        {
            var code = await FetchScript();

            try
            {
                var ctx = new MockBotContext(msg =>
                {
                    if (lstLog.InvokeRequired)
                    {
                        lstLog.Invoke(new Action(() =>
                        {
                            lstLog.Items.Add(msg);
                            lstLog.TopIndex = lstLog.Items.Count - 1;
                        }));
                    }
                    else
                    {
                        lstLog.Items.Add(msg);
                        lstLog.TopIndex = lstLog.Items.Count - 1;
                    }
                });
                var script = _engine.Compile(code);

                lblStatus.Text = "Running...";

                await script.Execute(ctx);
                await Task.Delay(2500);
            }
            catch (Exception ex)
            {
                lblStatus.Text = $"Error: {ex.Message}";
            }
        }

        private async Task<string> FetchScript()
        {
            var http = new HttpClient();
            return await http.GetStringAsync(textBox1.Text);
        }
    }
}
