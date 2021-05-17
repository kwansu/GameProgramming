using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SingleGameMacro
{
    public partial class GameItem
    {
        public string Name { get; set; } = "Unnamed";
        public List<GameItemComponent> Components { get; } = new List<GameItemComponent>();

    }
}
