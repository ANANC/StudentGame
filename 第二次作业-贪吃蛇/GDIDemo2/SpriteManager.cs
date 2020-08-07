using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;

namespace GameFramework2D
{
    class SpriteManager
    {

        private SpriteManager(){}
	
	
	    public  static readonly SpriteManager instance = new SpriteManager();

	
        public Sprite CreateSprite	(string 		resourceName,
								     Point		    vPos,
								    int					w = 0,
								    int					h=0,
								    int					tx = 0,
								    int					ty = 0,
                                    string              name = ""
								)		//创建精灵节点
        {
            Bitmap tex= ResourcesPool.GetInstance().GetResource(resourceName);
            if (w == 0 || h == 0)
            {
                w = tex.Width;
                h = tex.Height;
            }
            Sprite sprite = new Sprite(tex,vPos,w,h,tx,ty,name);
            spriteList.AddLast(sprite);
            return sprite;
        }
	
	    public void DeleteSprite(Sprite sprite)	//删除精灵节点	
        {
            spriteList.Remove(sprite);
        }
        public void Render(Graphics graphics)									//渲染	
        {
            foreach (var sprite in spriteList)
            {
                if (sprite.IsVisible)
                {
                    sprite.Render(graphics);
                }
            }
        }
        public void Update(float dt)
        {
            foreach (var sprite in spriteList)
            {
                if (sprite.IsEnable)
                {
                    sprite.Update(dt);
                }
            }
        }


        
        protected LinkedList<Sprite>	spriteList = new LinkedList<Sprite>();
	    
    }
}
