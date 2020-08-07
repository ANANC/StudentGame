using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Drawing.Imaging;



/*******************************************************************************
	建立精灵类,用于管理精灵自身的行为,包括将图片渲染到指定的地方,
	并且能检查是否与其它精灵碰撞

*******************************************************************************/





namespace GameFramework2D
{
    class Sprite
    {

        protected string name;
        protected Bitmap texture;
        public Bitmap Texture
        {
            set
            {
                texture = value;
            }
            get
            {
                return texture;
            }
        }

        protected Point vPos;                   //位置向量

        public Point Pos															//设置精灵的位置
        {
            set
            {
                this.vPos = value;
                matTranslation.Reset();
                matTranslation.Translate(vPos.X - vHotSpot.X, vPos.Y - vHotSpot.Y);
                CalculateBoundingBox();
            }
            get
            {
                return vPos;
            }
        }
        
        protected int tx;																		//纹理图x
        protected int ty;																		//纹理图y									


        protected int width;																	//精灵宽度
        protected int height;																	//精灵高度			

        protected bool bVisible;
        protected bool bEnabled;

        protected Point vHotSpot;

        public Point HotSpot													//设置热点		
        {
            set
            {
                this.vHotSpot = value;
                matTranslation.Reset();
                matTranslation.Translate(vPos.X - vHotSpot.X, vPos.Y - vHotSpot.Y);
                CalculateBoundingBox();
            }
            get
            {
                return vHotSpot;
            }
        }
       

        protected Matrix matWorld;
        protected Matrix matScale;
        protected Matrix matRotation;
        protected Matrix matTranslation;



        protected float fRotationAngle;
        protected float fsx;
        protected float fsy;



        protected Point[] spriteBoundingBox;
        protected RectangleF calcBoundingBox;

        protected Pen boundingBoxPen;

        public Sprite(	Bitmap texture,														//纹理
                        Point vPos, 														//位置向量
                        int w = 0,																//精灵宽度
                        int h = 0,																//精灵高度
                        int tx = 0,															//纹理x
                        int ty = 0,															//纹理y
                        string name = "")
        {
           
            this.name = name;
            if (w == 0 || h == 0)
            {
                this.width = texture.Width;
                this.height = texture.Height;
            }
            else
            {
                this.width = w;
                  this.height = h;
            }
            this.tx = tx;
            this.ty = ty;
            this.texture = texture;
            spriteBoundingBox = new Point[4];
            this.bVisible = this.bEnabled = true;
            fRotationAngle = 0.0f;
            fsx = fsy = 0.0f;
            
           
            spriteBoundingBox[0].X = 0;
            spriteBoundingBox[0].Y = 0;
            spriteBoundingBox[1].X = 0;
            spriteBoundingBox[1].Y = h;
            spriteBoundingBox[2].X = w;
            spriteBoundingBox[2].Y = 0;
            spriteBoundingBox[3].X = w;
            spriteBoundingBox[3].Y = h;

            matTranslation = new Matrix();
            matRotation = new Matrix();
            matScale = new Matrix();
            matWorld = new Matrix();

            boundingBoxPen = new Pen(Color.Blue);
            Pos = vPos;
        }
       
        protected bool isDrawBoundingBox;
        public bool IsDrawBoudingBox
        {
            set
            {
                isDrawBoundingBox = value;
            }
            get
            {
                return isDrawBoundingBox;
            }
        }
   

        
        protected void ApplayTransform()
        {
            matWorld.Reset();

            matWorld.Multiply(matScale);
            matWorld.Multiply(matRotation, MatrixOrder.Append);
            matWorld.Multiply(matTranslation, MatrixOrder.Append);
            
        }
        protected void CalculateBoundingBox()
        {

            ApplayTransform();
        
            PointF[] ptTmp = new PointF[4];

            for (int i = 0; i < 4; ++i)
            {
                ptTmp[i] = spriteBoundingBox[i];
            }
            matWorld.TransformPoints(ptTmp);

            float fMinX = ptTmp[0].X;
            float fMaxX = ptTmp[0].X;
            float fMinY = ptTmp[0].Y;
            float fMaxY = ptTmp[0].Y;
            for (int i = 1; i < 4; ++i)
            {
                if (fMinX > ptTmp[i].X)
                {
                    fMinX = ptTmp[i].X;
                }
                if (fMaxX < ptTmp[i].X)
                {
                    fMaxX = ptTmp[i].X;
                }

                if (fMinY > ptTmp[i].Y)
                {
                    fMinY = ptTmp[i].Y;
                }
                if (fMaxY < ptTmp[i].Y)
                {
                    fMaxY = ptTmp[i].Y;
                }

            }
            calcBoundingBox.X = fMinX;
            calcBoundingBox.Y = fMinY;
            calcBoundingBox.Width = fMaxX - fMinX;
            calcBoundingBox.Height = fMaxY - fMinY;

        }

        public virtual void Update(float fDeltaTime) { }	//更新


        

        public bool IsSelected(int x, int y)
        {
            bool bRet = false;
            if (x >= calcBoundingBox.Left && x <= calcBoundingBox.Right && y >= calcBoundingBox.Top && y <= calcBoundingBox.Bottom)
            {
                return true;
            }
            return bRet;
        }
        public bool CollideWith(Sprite sprite)															//是否碰撞
        {
            return calcBoundingBox.IntersectsWith(sprite.calcBoundingBox);
        }
        public bool CollideWith(RectangleF rect)																//是否和某个矩形碰撞
        {
            return calcBoundingBox.IntersectsWith(rect);
        }

        public void SetScaleFactor(float sx, float sy)														//设置缩放系数 
        {
            fsx = sx;
            fsy = sy;
            matScale.Reset();
            matScale.Scale(fsx, fsy);

            CalculateBoundingBox();

        }

        public void SetDestRect( Point vPos, float w, float h)					//设置渲染的目的矩形
        {
            Pos = vPos;
            float sx = w / width;
            float sy = h / height;
            SetScaleFactor(sx, sy);
        }

        public void SetTexPos(int x, int y)																//设置精灵在纹理上截取的左上角坐标	
        {
            GraphicsUnit units = GraphicsUnit.Pixel;
            RectangleF rect = texture.GetBounds(ref units);

            if (x < 0 || x >= rect.Width || y < 0 || y >= rect.Height)
            {
                return;
            }
           
            tx = x;
            ty = y;
            
        }
        
        public void SetRotationAngle(float fAngle)														//设置旋转角度	
        {
            fRotationAngle = fAngle;
            matRotation.Reset();
            matRotation.RotateAt(fRotationAngle,vHotSpot);//, vHotSpot);
            CalculateBoundingBox();
        }
        public  float GetRotationAngle()
        {
            return fRotationAngle;
        }

      
        public bool IsVisible
        {
            set 
            {
                bVisible = value;
            }
            get
            {
                return bVisible;
            }
        }

        public bool IsEnable
        {
            set
            {
                bEnabled = value;
            }
            get
            {
                return bEnabled;
            }
        }

       

        public int GetWidth()																				//得到精灵宽度
        {
            return width;
        }
        public int GetHeight()																		//得到精灵高度
        {
            return height;
        }



        public string GetSpriteName()
        {
            return name;
        }
        public RectangleF GetBoundingBox()																//得到精灵矩形范围	
        {
            return calcBoundingBox;
        }

        public void Render(Graphics g)
        {
            g.Transform = matWorld;
            
            g.DrawImage(texture, tx, ty, width, height);
            if (isDrawBoundingBox)
            {
                g.ResetTransform();
                g.DrawRectangle(boundingBoxPen, Rectangle.Round(calcBoundingBox));
            }
            
        }
        public void Render(Graphics g,Point vPos)
        {
            Pos = vPos;
            Render(g);
        }
        
    }
}
