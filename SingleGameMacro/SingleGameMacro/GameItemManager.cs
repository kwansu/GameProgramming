using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace SingleGameMacro
{
    public partial class GameItemManager : Form
    {
        GameItem targetGameItem;

        public GameItemManager()
        {
            InitializeComponent();
        }

        public void Setup()
        {
            //textBox_itemName.DataBindings.Add("Text", TargetGameItem.Name, "AA");
        }

        private void btn_AddGameItem_Click(object sender, EventArgs e)
        {
            GameItem newGameItem = new GameItem();

            targetGameItem = newGameItem;
            textBox_itemName.DataBindings.Add("Text", targetGameItem, "Name");

            DataStorage.Singleton.AddGameItem(newGameItem);
        }

        private void ListGameItemComponents()
        {
            foreach (GameItemComponentInfoBox control in flowLayoutPanel_attribute.Controls)
            {
                ControlPool<GameItemComponentInfoBox>.Singleton.ReturnControl(control);
            }
            flowLayoutPanel_attribute.Controls.Clear();

            foreach(var component in targetGameItem.Components)
            {
                var componentBox = ControlPool<GameItemComponentInfoBox>.Singleton.GetControl();

                componentBox.Setup(component);
            }
        }
    }
}
