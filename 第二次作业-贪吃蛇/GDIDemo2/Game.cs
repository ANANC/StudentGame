using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using System.Diagnostics;

using System.Windows.Forms;
namespace GameFramework2D
{
    abstract class Game
    {
        private int lastTime = 0;
        protected int width;
        protected int height;
        protected Graphics graphics;
        private Stopwatch sw = new Stopwatch();
        public Game(Graphics graphics, int w, int h)	//构造函数
        {
            this.graphics = graphics;
            width = w;
            height = h;
            CreateBuffer(width, height);
            lastTime = System.Environment.TickCount;


        }


        //-----处理相应的鼠标和键盘事件，这里设置为虚函数，其子类可以根据程序需要加以重写---------
        public virtual void HandleMouseUp(MouseEventArgs e) { }
        public virtual void HandleMouseDown(MouseEventArgs e) { }
        public virtual void HandleMouseMove(MouseEventArgs e) { }
        public virtual void HandleDoubleClick(MouseEventArgs e) { }
        public virtual void HandleKeyUp(KeyEventArgs e) { }
        public virtual void HandleKeyDown(KeyEventArgs e) { }



        //-----------------------------------------------------------------------------------------
        public abstract void InitGame();										//纯虚函数，创建资源		


        public void GameFunc()//执行游戏帧函数
        {
            int val = System.Environment.TickCount - lastTime;
            float dt = val / 1000.0f;
            Update(dt);
            Render();
            lastTime = System.Environment.TickCount;
        }
        protected Bitmap buffer;
        protected Graphics bufferGraphics;
        public void CreateBuffer(int w, int h)
        {
            if (buffer != null)
            {
                buffer.Dispose();
            }
            buffer = new Bitmap(w, h);
            bufferGraphics = Graphics.FromImage(buffer);
        }


        protected virtual void Update(float fDeltaTime)//帧函数	
        {
            SpriteManager.instance.Update(fDeltaTime);
        }

        protected virtual void Render()		//渲染	
        {
            SpriteManager.instance.Render(bufferGraphics);
            
            graphics.DrawImage(buffer, 0, 0);
        }





    }
}
