using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//using System.Drawing.Imaging;
using System.Drawing;
using System.Drawing.Drawing2D;

namespace GameFramework2D
{
    class ResourcesPool
    {

        private ResourcesPool()
        {
            textures = new Dictionary<string, Bitmap>();
        }
        
        private static ResourcesPool instance = new ResourcesPool();
        public static ResourcesPool GetInstance()
        {

            return instance;
        }

        public bool AddTexture(string name, string filePath)
        {
            bool ret = true;
           
            if (!textures.ContainsKey(name))
            {
                
           
                try
                {
                    Bitmap tex = new Bitmap(filePath);
                    textures[name] = tex;
                   
                }
                catch (Exception e)
                {
                    ret = false;
                    
                }

            }
            return ret;
        }
        public  Bitmap GetResource(string resName)		//根据资源名得到资源节点
        {
            return textures[resName];
        }

        void ClearResourcesPool()
        {
            textures.Clear();
        }

        protected Dictionary<string, Bitmap> textures;






    }
}
