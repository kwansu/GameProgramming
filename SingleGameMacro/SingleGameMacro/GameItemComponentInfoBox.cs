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
    public partial class GameItemComponentInfoBox : UserControl
    {
        IComponent targetComponent;

        public void Setup(IComponent component)
        {
            
        }

        public GameItemComponentInfoBox()
        {
            InitializeComponent();
        }
    }
}
