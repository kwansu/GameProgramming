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
    public partial class Main : AutoScalingForm
    {
        GameItemManager GameItemManager = new GameItemManager();

        public Main()
        {
            InitializeComponent();
            MinimumSize = Size;
            base.InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            GameItemManager.ShowDialog();
        }
    }
}
