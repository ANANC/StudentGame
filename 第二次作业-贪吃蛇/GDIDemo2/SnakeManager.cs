using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;

using GameFramework2D;

namespace GDIDemo2
{

    class SnakeManager
    {
        private LinkedList<Snake> Snakes = new LinkedList<Snake>();
        private Direction Keydown;
        private Snake Food;
        private Point[] Box = new Point[13*13];

        public Direction KEYdown
        {
            set{
                Keydown = value;
            }
        }

        public SnakeManager()
        {
            for(int i = 0;i<13;i++)
            {
                for(int j = 0;j<13;j++)
                {
                    Box[j + 13 * i] = new Point((j-1)*50,(i-1)*50);
                }
            }

            Random rand = new Random();

            int nn = rand.Next(55, 59);
            Snake s = new Snake("身体", Box[nn], Direction.dUp, nn);
            Snakes.AddLast(s);

            nn = rand.Next(108, 115);
            Food = new Snake("心", Box[nn], Direction.dNothing, nn);

            Keydown = Direction.dNothing;
        }

        public int IsTouch()
        {
            /*----------身体-----------------------------*/
            int s = Snakes.ElementAtOrDefault(0).Number;
            if (Snakes.Count() != 1)
            {
                for (int i = 1; i < Snakes.Count(); i++)
                {
                    if (s == Snakes.ElementAtOrDefault(i).Number)
                        return -1;
                }
            }
            
            /*---------------------------------------*/

            /*----------墙-----------------------------*/
            for (int i = 0; i < 12;i++ )
            {
                if (s == i ||s == i*13 ||s == i*13+13)
                    return -1;
            }
            for (int i = 13 * 11 + 1; i < 13 * 13;i++ )
            {
                if (s == i)
                    return -1;
            }
            /*---------------------------------------*/

            /*----------食物-----------------------------*/
            if (Food.SnakeSprite.CollideWith(Snakes.ElementAtOrDefault(0).SnakeSprite))
            {
                Random rand = new Random();
                int nn = rand.Next(1,13*13-1);
                bool kk =false;
                while (kk == false)
                {
                    for (int i = 0; i < 13; i++)
                    {
                        if (nn == i || nn == i * 13 || nn == i * 13 + 13)
                            nn = rand.Next(1, 13 * 13 - 1);
                        else
                            kk = true;
                    }
                    for (int i = 13 * 11 + 1; i < 13 * 13; i++)
                    {
                        if (nn == i)
                            nn = rand.Next(1, 13 * 13 - 1);
                        else
                            kk = true;
                    }
                }
                Food.ReInitSnake(Box[nn], Direction.dNothing, nn);

                AddBody();
                return 1;
            }
            /*---------------------------------------*/

            return 0;
        }

        private void AddBody()
        {
            int n = Snakes.ElementAtOrDefault(0).Number;
            Direction d = Snakes.ElementAtOrDefault(0).DIRECTION;
            n += KeyNextPos(d);
            Snake s = new Snake("身体", Box[n], d, n);
            Snakes.AddFirst(s);
        }


        private int TimeMove = 0;
        public void Update(float dt)
        {
            TimeMove++;
            if (TimeMove < 5)
                return;
            else
            {
                TimeMove = 0;
            }

            int s = Snakes.ElementAtOrDefault(0).Number;
            Direction d= Keydown;

            if(Keydown == Direction.dNothing)
            {
                d = Snakes.ElementAtOrDefault(0).DIRECTION;
            }

            s += KeyNextPos(d);

            Snakes.ElementAtOrDefault(Snakes.Count() - 1).ReInitSnake(Box[s], d, s);
            Snake ss = Snakes.ElementAtOrDefault(Snakes.Count() - 1);
            Snakes.RemoveLast();
            Snakes.AddFirst(ss);
        }
       
        private int KeyNextPos(Direction d)
        {
            if(d == Direction.dUp)
            {
                return -13;
            }

            if (d == Direction.dDown)
            {
                return 13;
            }

            if (d == Direction.dLeft)
            {
                return -1;
            }

            if (d == Direction.dRight)
            {
                return 1;
            }

            return 0;
        }

    }
}
