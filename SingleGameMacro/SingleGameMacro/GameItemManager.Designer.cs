
namespace SingleGameMacro
{
    partial class GameItemManager
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.btn_AddGameItem = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.textBox_itemName = new System.Windows.Forms.TextBox();
            this.flowLayoutPanel_attribute = new System.Windows.Forms.FlowLayoutPanel();
            this.button1 = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // btn_AddGameItem
            // 
            this.btn_AddGameItem.Location = new System.Drawing.Point(626, 408);
            this.btn_AddGameItem.Name = "btn_AddGameItem";
            this.btn_AddGameItem.Size = new System.Drawing.Size(114, 23);
            this.btn_AddGameItem.TabIndex = 0;
            this.btn_AddGameItem.Text = "아이템 추가";
            this.btn_AddGameItem.UseVisualStyleBackColor = true;
            this.btn_AddGameItem.Click += new System.EventHandler(this.btn_AddGameItem_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(82, 77);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(73, 12);
            this.label1.TabIndex = 1;
            this.label1.Text = "아이템 이름:";
            // 
            // textBox_itemName
            // 
            this.textBox_itemName.Location = new System.Drawing.Point(161, 74);
            this.textBox_itemName.Name = "textBox_itemName";
            this.textBox_itemName.Size = new System.Drawing.Size(132, 21);
            this.textBox_itemName.TabIndex = 2;
            // 
            // flowLayoutPanel_attribute
            // 
            this.flowLayoutPanel_attribute.AutoScroll = true;
            this.flowLayoutPanel_attribute.BackColor = System.Drawing.SystemColors.ControlLight;
            this.flowLayoutPanel_attribute.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.flowLayoutPanel_attribute.Location = new System.Drawing.Point(480, 37);
            this.flowLayoutPanel_attribute.Name = "flowLayoutPanel_attribute";
            this.flowLayoutPanel_attribute.Size = new System.Drawing.Size(243, 259);
            this.flowLayoutPanel_attribute.TabIndex = 4;
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(626, 331);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(114, 23);
            this.button1.TabIndex = 5;
            this.button1.Text = "아이템 추가";
            this.button1.UseVisualStyleBackColor = true;
            // 
            // GameItemManager
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackgroundImageLayout = System.Windows.Forms.ImageLayout.None;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.flowLayoutPanel_attribute);
            this.Controls.Add(this.textBox_itemName);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.btn_AddGameItem);
            this.Name = "GameItemManager";
            this.Text = "GameItemManager";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btn_AddGameItem;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox textBox_itemName;
        private System.Windows.Forms.FlowLayoutPanel flowLayoutPanel_attribute;
        private System.Windows.Forms.Button button1;
    }
}