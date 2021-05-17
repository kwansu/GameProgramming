using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SingleGameMacro
{
    public interface IControlPool<T> where T : System.Windows.Forms.Control
    {
        T GetControl();
        void ReturnControl(T control);
    }

    public partial class ControlPool<T> : IControlPool<T> where T : System.Windows.Forms.Control
    {
        public T GetControl()
        {
            throw new NotImplementedException();
        }

        public void ReturnControl(T control)
        {
            throw new NotImplementedException();
        }
    }

    // singleton
    sealed partial class ControlPool<T>
    {
        public static IControlPool<T> Singleton => throw new NotImplementedException();

        private ControlPool() { }
    }
}
