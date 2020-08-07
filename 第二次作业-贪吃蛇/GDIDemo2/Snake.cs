using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;

using GameFramework2D;


namespace GDIDemo2
{
    enum Direction
    {
        dUp,
        dDown,
        dLeft,
        dRight,
        dNothing
    };

    class Snake
    {
        private Sprite snakeSprite;
        public Sprite SnakeSprite
        {
            get
            {
                return snakeSprite;
            }
        }
        private Point pos;
        private Direction direction;
        private int number;

        public Point Pos
        {
            get
            {
                return pos;
            }
        }

        public Direction DIRECTION
        {
            get
            {
                return direction;
            }
        }

        public int Number
        {
            get
            {
                return number;
            }
        }

        public Snake(string resName, Point p, Direction d, int n,int w= 0,int h = 0,int tx=0,int ty=0)
        {
            pos = p;
            direction = d;
            number = n;

            snakeSprite = SpriteManager.instance.CreateSprite(resName, pos,w,h,tx,ty);
        }
        public void ReInitSnake(Point p, Direction d,int n )
        {
            pos = p;
            direction = d;
            number = n;

            snakeSprite.Pos = pos;
        }

    }
}
