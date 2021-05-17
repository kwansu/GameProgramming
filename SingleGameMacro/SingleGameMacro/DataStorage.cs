using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SingleGameMacro
{
    public partial class DataStorage
    {
        public ReturnInfo AddGameItem(GameItem gameItem)
        {
            if (gameItems.ContainsKey(gameItem.Name))
            {
                return ReturnInfo.containKey;
            }

            gameItems.Add(gameItem.Name, gameItem);
            return true;
        }

        public GameItem GetGameItem(string itemName)
        {
            throw new NotImplementedException();
        }
    }


    // Private
    partial class DataStorage
    {
        private Dictionary<string, GameItem> gameItems = new Dictionary<string, GameItem>();
    }


    // Singlton
    sealed partial class DataStorage
    {
        static public DataStorage Singleton { get; } = new DataStorage();
        private DataStorage() { }
    }
}
