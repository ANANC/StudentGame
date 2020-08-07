namespace GDIDemo2
{
    partial class DemoUI
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.timeGameLoop = new System.Windows.Forms.Timer(this.components);
            this.SuspendLayout();
            // 
            // timeGameLoop
            // 
            this.timeGameLoop.Interval = 50;
            this.timeGameLoop.Tick += new System.EventHandler(this.timeGameLoop_Tick);
            // 
            // DemoUI
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(700, 549);
            this.Margin = new System.Windows.Forms.Padding(2);
            this.Name = "DemoUI";
            this.SizeGripStyle = System.Windows.Forms.SizeGripStyle.Hide;
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.DemoUI_Load);
            this.KeyDown += new System.Windows.Forms.KeyEventHandler(this.DemoUI_KeyDown);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Timer timeGameLoop;
    }
}

