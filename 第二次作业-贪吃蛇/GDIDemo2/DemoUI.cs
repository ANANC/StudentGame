using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;


using GameFramework2D;
namespace GDIDemo2
{
    public partial class DemoUI : Form
    {
        public DemoUI()
        {
            InitializeComponent();
        }
       
        private Graphics graphics;
        
       
        private DemoGame demoGame;
        private void timeGameLoop_Tick(object sender, EventArgs e)
        {
            
            demoGame.GameFunc();
            
           
        }

        private void DemoUI_Load(object sender, EventArgs e)
        {
            graphics = this.CreateGraphics();
            demoGame = new DemoGame(graphics,ClientRectangle.Width, ClientRectangle.Height);
            demoGame.InitGame();
            //ResourcesPool.GetInstance().AddTexture("gear","gear.png");
            //ResourcesPool.GetInstance().AddTexture("background", "AutumnLeaves.bmp");
            //Bitmap tex = ResourcesPool.GetInstance().GetResource("gear");
            //Point vPos = new Point(150, 150);
            //gear = new Sprite(graphics, tex,   vPos, 256, 256);
            //gear.SetHotSpot(new Point(128, 128));
            //tex = ResourcesPool.GetInstance().GetResource("background");
            //vPos.X = vPos.Y = 0;
            //background = new Sprite(graphics, tex, vPos, 1024, 768);
            //background.SetDestRect(vPos, ClientRectangle.Width, ClientRectangle.Height);
            //vPos.X = 300;
            //vPos.Y = 250;
            //gear.SetPos( vPos);
            ////gear.SetScaleFactor(0.5f, 0.5f);
            //gear.IsDrawBoudingBox = true;

            timeGameLoop.Start();
        }

       

        private void DemoUI_KeyDown(object sender, KeyEventArgs e)
        {
            demoGame.HandleKeyDown(e);
        }
    }
}
