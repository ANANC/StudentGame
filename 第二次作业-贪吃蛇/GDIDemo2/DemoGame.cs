using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;

using GameFramework2D;
namespace GDIDemo2
{
    class DemoGame: Game
    {
       
        public DemoGame(Graphics graphics, int w, int h)
            : base(graphics,w, h)
        { }
       
        private Snake Food;
        private SnakeManager snakeManager;
        private Sprite Tip_Add;
        private Sprite Tip_Die;
        private Sprite Stop;
        private Sprite Again;
        public override void InitGame()
        {
            ResourcesPool.GetInstance().AddTexture("background", "背景.jpg");
            ResourcesPool.GetInstance().AddTexture("身体", "身体.png");
            ResourcesPool.GetInstance().AddTexture("心", "心.png");
            ResourcesPool.GetInstance().AddTexture("游戏死亡", "游戏死亡.png");
            ResourcesPool.GetInstance().AddTexture("暂停", "暂停.png");
            ResourcesPool.GetInstance().AddTexture("增加长度", "增加长度.png");
            ResourcesPool.GetInstance().AddTexture("重新", "重新.png");
            ResourcesPool.GetInstance().AddTexture("开始", "开始.png");

            Point pos = new Point(0, 0);
            Sprite background = SpriteManager.instance.CreateSprite("background", pos, width, height);
           // background.SetDestRect(pos, width, height);

            snakeManager = new SnakeManager();
            /*
            pos = new Point(546, 280);
            Tip = SpriteManager.instance.CreateSprite("道具", pos, 49*2, 49,49*2,49);
           // Tip.IsVisible =false;
            Tip.IsDrawBoudingBox = true;

            pos = new Point(546, 380);
            Stop = SpriteManager.instance.CreateSprite("道具", pos, 49 * 2, 49, 0, 49*3);
            Stop.IsDrawBoudingBox = true;

            pos = new Point(546, 440);
            Again = SpriteManager.instance.CreateSprite("道具", pos, 49 * 2, 49, 49 * 4, 49*3);
            Again.IsDrawBoudingBox = true;*/

            pos = new Point(569, 320);
            Tip_Add = SpriteManager.instance.CreateSprite("增加长度", pos);
            Tip_Die = SpriteManager.instance.CreateSprite("游戏死亡", pos);
            Tip_Add.IsVisible = false;
            Tip_Die.IsVisible = false;

            pos = new Point(580, 473);
            Stop = SpriteManager.instance.CreateSprite("暂停", pos);

            pos = new Point(580, 500);
            Again = SpriteManager.instance.CreateSprite("重新", pos);


        }

        private bool IsGameOver = false;
        protected override void Update(float fDeltatime)
        {
            if (IsGameOver)
                return;

            IsTouch();
            snakeManager.Update(fDeltatime);
           
        }

        //private String s;
        //private Font f = new Font(new FontFamily("幼圆"), 25);
        //private SolidBrush myBrush = new SolidBrush(Color.Red);
        //private Point p = new Point(10, 10);
        protected override void Render()		//渲染	
        {
            SpriteManager.instance.Render(bufferGraphics);
            //bufferGraphics.ResetTransform();
            //s = "当前的存活时间是："+ATime;
            //bufferGraphics.DrawString(s, f, myBrush, p);
            graphics.DrawImage(buffer, 0, 0);

            if(IsShowTip)
            {
                timeTip++;
                if(timeTip==20)
                {
                    timeTip = 0;
                    IsShowTip = false;
                    Tip_Add.IsVisible = false;
                }
            }
            
        }

        private int timeTip = 0;
        private bool IsShowTip = false;
        private void IsTouch()
        {
            if(snakeManager.IsTouch()==-1)
            {
               // Tip.SetTexPos(49 * 4, 49);
                Tip_Die.IsVisible = true;
                IsShowTip = true;
                IsGameOver = true;
            }
            if(snakeManager.IsTouch() == 1)
            {

                //Tip.SetTexPos(49 * 2, 49);
                Tip_Add.IsVisible = true;
                IsShowTip = true;
            }

        }

        public override void HandleKeyDown(System.Windows.Forms.KeyEventArgs e)
        {
            base.HandleKeyDown(e);
            if (e.KeyCode == System.Windows.Forms.Keys.Left)
            {
                snakeManager.KEYdown = Direction.dLeft;
            }
            else if  (e.KeyCode == System.Windows.Forms.Keys.Right)
            {
                snakeManager.KEYdown = Direction.dRight;
            }
            else if (e.KeyCode == System.Windows.Forms.Keys.Up)
            {
                snakeManager.KEYdown = Direction.dUp;
            }
            else if (e.KeyCode == System.Windows.Forms.Keys.Down)
            {
                snakeManager.KEYdown = Direction.dDown;
            }
        }
    }
}
