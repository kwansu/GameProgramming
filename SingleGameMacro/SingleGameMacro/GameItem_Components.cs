using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SingleGameMacro
{
    public interface IComponent
    {
        string ComponentName { get; set; }
        Type ComponentType { get; }
        List<IComponent> Components { get; }
    }

    public interface IComponent_Value<T> : IComponent
    {
        T Value { get; set; }
        byte[] SearchKey { get; set; }
        int DataOffset { get; set; }
        uint DataSize { get; set; }
    }

    partial class GameItem
    {
        public class GameItemComponent : IComponent
        {
            public string ComponentName { get => throw new NotImplementedException(); set => throw new NotImplementedException(); }

            public Type ComponentType => throw new NotImplementedException();

            public List<IComponent> Components => throw new NotImplementedException();
        }

        public class GameItemComponent_NumberValue<T> : GameItemComponent, IComponent_Value<T>
        {
            public T Value { get; set; }
            public byte[] SearchKey { get; set; }
            public int DataOffset { get; set; }
            public uint DataSize { get; set; }
        }
    }
}
