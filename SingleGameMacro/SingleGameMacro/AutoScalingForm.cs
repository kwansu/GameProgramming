using System;
using System.Windows.Forms;
using System.Collections.Generic;

namespace SingleGameMacro
{
    public class AutoScalingForm : Form
    {
        struct ControlLocationSize
        {
            public float ratioX;
            public float ratioY;
            public float ratioWidth;
            public float ratioHeight;
        }

        Dictionary<Control, ControlLocationSize> controlsRectRatio = new Dictionary<Control, ControlLocationSize>();

        protected void InitializeComponent()
        {
            foreach (Control control in Controls)
            {
                ControlLocationSize info = new ControlLocationSize();
                info.ratioX = control.Location.X / (float)ClientSize.Width;
                info.ratioY = control.Location.Y / (float)ClientSize.Height;
                info.ratioWidth = control.Width / (float)ClientSize.Width;
                info.ratioHeight = control.Height / (float)ClientSize.Height;

                controlsRectRatio.Add(control, info);
            }

            this.ResizeEnd += new System.EventHandler(Auto_ResizeEnd);
        }

        private void Auto_ResizeEnd(object sender, EventArgs e)
        {
            foreach (Control control in Controls)
            {
                ControlLocationSize info = controlsRectRatio[control];

                control.SetBounds((int)(info.ratioX * ClientSize.Width), (int)(info.ratioY * ClientSize.Height),
                    (int)(info.ratioWidth * ClientSize.Width), (int)(info.ratioHeight * ClientSize.Height));
            }
        }
    }
}
