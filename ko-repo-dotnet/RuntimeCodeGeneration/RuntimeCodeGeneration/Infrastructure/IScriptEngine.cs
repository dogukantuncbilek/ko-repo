using System.Threading.Tasks;

namespace RuntimeCodeGeneration.Infrastructure
{
    public interface IScript
    {
        Task Execute(IBotContext ctx);
    }

    public class a
    {
        public Task Execute(IBotContext ctx)
        {
            if (ctx.GetMP() < 500)
            {
                ctx.Log("MP low, waiting...");
                return Task.CompletedTask;
            }
            
            ctx.UseSkill(112211);
            ctx.UseSkill(332211);
            ctx.UseSkill(412312);

            return Task.CompletedTask;
        }
    }
}
