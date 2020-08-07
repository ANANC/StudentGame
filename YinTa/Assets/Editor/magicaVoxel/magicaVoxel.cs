using UnityEngine;
using System.Collections;
using UnityEditor;
using System.IO;
using System.Xml;
using System;
using System.Text;
using System.Collections.Generic;

[Serializable]
public class colorlistJson
{
    public List<ColorList> list;
    public colorlistJson(int index)
    {
        list = new List<ColorList>(index);
    }
 

    public void NewList(int index)
    {
        if (index <= 0)
            return;

        if(index > list.Count)
        {
            int number = index - list.Count;
            for(int i =0;i<number;i++)
            {
                list.Add(new ColorList("", 0, new Color()));
                //list.Add(new ColorList("", 0, 0, 0, 0, 0));
            }
        }
        if (index < list.Count)
        {
            int number = list.Count - index;
            list.RemoveRange(0, number);
        }
    }

    public void clear()
    {
        if (list == null)
            return;
        list.Clear();
    }
}

[Serializable]
public class ColorList
{
    public string MaterialName;
    public int id;
    //public float color_r;
    //public float color_g;
    //public float color_b;
    //public float color_a;
    public Color color;

   // public ColorList(string name,int Id, float r, float g, float b, float a)
    public ColorList(string name, int Id, Color COLOR)
    {
        ChangeColor(name, Id, COLOR);
    }

    public void ChangeColor(string name, int Id, Color COLOR)
    {
        MaterialName = name;
        id = Id;
        //color_r = r;
        //color_g = g;
        //color_b = b;
        //color_a = a;
        color = COLOR;
    }
}

public class magicaVoxel : EditorWindow
{
    static string DataPath = "Assets/magicVoxel/Resources/Materials";
    static string XmlPath = "Assets/magicVoxel/Resources/xml";
    static string PrefabPath = "Assets/magicVoxel/Resources/Prafab";
    static string AssetbundlePath = "Assets/magicVoxel/Resources/Assetbundle";
    static string jsonNormalPath = XmlPath + "/normal.json";

    static GUIContent[] TitleContent = new GUIContent[]{new GUIContent("修改颜色"),new GUIContent("添加方块"),new GUIContent("方块对齐"), new GUIContent("保存数据") };

static colorlistJson colorlist_normal = new colorlistJson(1);

    //static ArrayList Materials = new ArrayList();
    static ArrayList MatColors = new ArrayList();
    static ArrayList EditorColors = new ArrayList();
    static ArrayList SelectGOs = new ArrayList();
    static ArrayList SelectColors = new ArrayList();
    static Vector2 ScrollView = new Vector2(0, 0);
    static int SelectTarIndex = -1;
    static int toolBar = 0;

    static ArrayList SelectDir_Y = new ArrayList();
    static ArrayList SelectDir_Z = new ArrayList();
    static ArrayList AddNumberSelect = new ArrayList();
    static ArrayList AddCube_F = new ArrayList();
    static ArrayList AddCube_F_Dir = new ArrayList();
    static string[] DirName = { "左上", "中上", "右上", "中左", "中间", "中右", "左下", "中下", "右下" };
    static string[] DirName_Z = { "前方","平行","后方"};
    static string[] AddNumberName = { "单个", "多个" };
    static string[] AddCube_F_dirname = { "前", "后", "左", "右", "上", "下" };
    static int[,] AddCube_F_dirname_index = new int[6,2] { {4,0 }, { 4,2}, { 3,1}, { 5,1}, { 1,1}, { 7,1} };


    static int[] DirIndex = new int[3];
    static int AddNumber = 1;
    static int AddCube_F_dir_index;

    static ArrayList ModelDelectCube = new ArrayList();

    static GameObject[] AlignGO = new GameObject[2];
    static ArrayList AlignSelectDir_0 = new ArrayList();
    static ArrayList AlignSelectDir_1 = new ArrayList();
    static string[] AlignName = { "前上左", "前上右", "后上左", "后上右", "前下左", "前下右" , "后下左", "后下右" };
    static int[] AlignIndex = new int[2];

    //[MenuItem("magicaVoxel/创建环境")]
    static void Init()
    {
        if (!Directory.Exists(DataPath))
        {
            Directory.CreateDirectory(DataPath);
        }
        if (!Directory.Exists(XmlPath))
        {
            Directory.CreateDirectory(XmlPath);
        }
        if (!Directory.Exists(PrefabPath))
        {
            Directory.CreateDirectory(PrefabPath);
        }
        if (!Directory.Exists(AssetbundlePath))
        {
            Directory.CreateDirectory(AssetbundlePath);
        }

        LoadColor();

        for (int i =0;i<9;i++)
        {
            SelectDir_Y.Add(false);
            AlignSelectDir_0.Add(false);
            AlignSelectDir_1.Add(false);
        }

        for(int i =0;i<2;i++)
        {
            AddNumberSelect.Add(false);
        }

        for(int i = 0;i<3;i++)
        {
            SelectDir_Z.Add(false);
        }

        for(int i=0;i<6;i++)
        {
            AddCube_F_Dir.Add(false);
        }

        DirIndex[0] = -1;
        DirIndex[1] = -1;
        DirIndex[2] = -1;

        AlignIndex[0] = -1;
        AlignIndex[1] = -1;

        AddCube_F_dir_index = -1;

        AssetDatabase.Refresh();

        //Debug.Log("环境创建完成！");
    }

    [MenuItem("magicaVoxel/打开面板")]
    static void ShowPlane()
    {
        Rect rect = new Rect(200, 0, 300, 500);
        magicaVoxel window = (magicaVoxel)EditorWindow.GetWindowWithRect(typeof(magicaVoxel), rect, true, "magicVoxel面板");
        window.Show();
    }

    [MenuItem("magicaVoxel/创建一个新项目")]
    static void CreatCube()
    {
        Init();

        GameObject GoNull = new GameObject();


        GameObject obj = AddCube();
        obj.transform.position = new Vector3(0, 0, 0);
        obj.GetComponent<MeshRenderer>().material = LoadMaterial(colorlist_normal.list[0].MaterialName + ".mat");//(Material)Materials[0];
        obj.transform.parent = GoNull.transform;

        //if (!Directory.Exists(Application.dataPath + "/magicVoxel/Resources/Materials"))
        //{
        //    Directory.CreateDirectory(Application.dataPath + "/magicVoxel/Resources/Materials");
        //}

        //string name = Random.Range(10000, 99999).ToString();
        //string path = "Assets/magicVoxel/Resources/Materials/" + name + ".prefab";

        //PrefabUtility.CreatePrefab(path, obj);

        ShowPlane();
    }


    [MenuItem("magicaVoxel/删除全部材质球")]
    static void Clean()
    {
        DirectoryInfo direction = new DirectoryInfo(DataPath);
        FileInfo[] files = direction.GetFiles("*.mat", SearchOption.AllDirectories);
        

        if(files.Length ==0)
        {
            Debug.Log("没有材质球可清理！");
            return;
        }
        
        for (int i = 0; i < files.Length; i++)
        {
            AssetDatabase.DeleteAsset(DataPath +"/"+files[i].Name );
            Debug.Log(files[i].Name);
        }

        Debug.Log("全部材质球清理完毕！");

       // Materials.Clear();
        MatColors.Clear();
        EditorColors.Clear();
        SelectColors.Clear();
        SelectDir_Y.Clear();
        SelectDir_Z.Clear();
        AlignSelectDir_0.Clear();
        AlignSelectDir_1.Clear();
        AddCube_F_Dir.Clear();

        DirIndex[0] = -1;
        DirIndex[1] = -1;
        
        AlignIndex[0] = -1;
        AlignIndex[1] = -1;

        AssetDatabase.Refresh();
    }

    Vector2 scrowllView;

    void OnGUI () 
	{
        if (MatColors.Count == 0)
        {
            Init();
        }

        toolBar=GUILayout.Toolbar(toolBar, TitleContent);

        switch (toolBar)
        {
            case 0:
                Color();
                break;
            case 1:
                Cubes();
                break;
            case 2:
                Align();
                break;
            case 3:
                DataManage();
                break;
        }
    }

    #region 颜色    
    static void Color()
    {
        //EditorGUILayout.BeginHorizontal();
        //if (GUILayout.Button("保存颜色表"))
        //{
        //    KeepColorXML();
        //}
        //if (GUILayout.Button("读取颜色表"))
        //{
        //    ReadColorXML();
        //}
        //EditorGUILayout.EndHorizontal();

        //EditorGUILayout.LabelField("-------------------------------------------------------");

        EditorGUILayout.BeginHorizontal();
        if (GUILayout.Button("  新增颜色  "))
        {
            AddColor(new Color(1, 1, 1, 1));
        }

        //if (GUILayout.Button("删除相同颜色"))
        //{
        //    CleanColor();
        //}
        EditorGUILayout.EndHorizontal();

        EditorGUILayout.LabelField("-------------------------------------------------------");

        if (MatColors.Count == 0)
            return;

        ScrollView = EditorGUILayout.BeginScrollView(ScrollView);
        for (int i = 0; i < MatColors.Count; i++)
        {
            EditorGUILayout.BeginHorizontal();

            EditorColors[i] = EditorGUILayout.ColorField((Color)EditorColors[i]);

            SelectColors[i] = EditorGUILayout.Toggle((bool)SelectColors[i]);


            EditorGUILayout.EndHorizontal();


           // ((Material)Materials[i]).color = (Color)EditorColors[i];
            if ((Color)EditorColors[i] != (Color)MatColors[i])
            {
                //EditorUtility.SetDirty((Object)EditorColors[i]);
                MatColors[i] = (Color)EditorColors[i];
                // ((Material)Materials[i]).color = (Color)MatColors[i];
                LoadMaterial(colorlist_normal.list[i].MaterialName + ".mat").color = (Color)MatColors[i];
                AssetDatabase.SaveAssets();
            }

            if ((bool)SelectColors[i])
            {
                SelectTarIndex = SelectTarIndex == -1 ? i : SelectTarIndex;
                if (SelectTarIndex != i)
                {
                    SelectColors[SelectTarIndex] = false;
                    SelectTarIndex = i;
                }
                if (GUILayout.Button("赋值"))
                {
                    if(SelectGOs.Count == 0)
                    {
                        GetSelectTransforms();
                        if (SelectGOs.Count == 0)
                            return;
                    }

                    for (int j = 0; j < SelectGOs.Count; j++)
                    {
                        ((Transform)SelectGOs[j]).GetComponent<MeshRenderer>().material = LoadMaterial(colorlist_normal.list[i].MaterialName + ".mat");//(Material)Materials[i];
                    }
                    AssetDatabase.SaveAssets();
                }
            }
        }

        EditorGUILayout.EndScrollView();
    }

    static void KeepColorList()
    {
        colorlist_normal.NewList(MatColors.Count);
        for (int i = 0; i < MatColors.Count; i++)
        {
           // Color color = (Color)MatColors[i];
            colorlist_normal.list[i].ChangeColor("matColor" + i, i, (Color)MatColors[i]);
            //colorlist_normal.list[i] = new ColorList("matColor" + i, i, color.r, color.g, color.b, color.a);
        }
        WriteJson();
    }

    static void WriteJson()
    {
        string path = XmlPath + "/normal.json";
        string str = JsonUtility.ToJson(colorlist_normal);
        File.WriteAllText(path, str, Encoding.UTF8);

        //FileInfo file = new FileInfo(path);
        //StreamWriter sw = file.CreateText();
        //sw.WriteLine(str);
        //sw.Close();
        //sw.Dispose();
    }

    static Material AddColor(Color color)
    {
        Material mat = new Material(Shader.Find("Standard"));
        mat.color = color;
        string name = "matColor" + MatColors.Count;
        AssetDatabase.CreateAsset(mat, DataPath + "/" + name + ".mat");

        //Materials.Add(mat);
        MatColors.Add(mat.color);
        EditorColors.Add(mat.color);
        SelectColors.Add(false);

         //colorlist_normal.list.Add(new ColorList(name, MatColors.Count - 1, color));
        //colorlist_normal.list.Add(new ColorList(name, MatColors.Count - 1, color.r, color.g, color.b, color.a));
        

        return mat;
    }

    static void CleanColor()
    {
        ArrayList clean = new ArrayList();
        for (int i = 0; i < MatColors.Count - 1; i++)
        {
            if (clean.Contains(i))
                continue;
            for (int j = i + 1; j < MatColors.Count; j++)
            {
                if (clean.Contains(j))
                    continue;

                if ((Color)MatColors[i] == (Color)MatColors[j])
                {
                    clean.Add(j);
                }
            }
        }

        //for (int i=0;i<clean.Count;i++)
        //{
        //    AssetDatabase.DeleteAsset(DataPath + "/" + ((Material)Materials[(int)clean[i]]).name + ".mat");
        //}

         if (clean.Count > 0)
        {
            Clear();
        }

       

        Debug.Log("删除完毕！");
    }

    static void LoadColor()
    {
        DirectoryInfo direction = new DirectoryInfo(DataPath);
        FileInfo[] files = direction.GetFiles("*.mat", SearchOption.AllDirectories);

        if (files.Length == 0)
        {
            for (int i = 0; i < 10; i++)
            {
                AddColor(new Color(1, 1, 1, 1));
            }
            KeepColorList();
        }
        else
        {
            // for (int i = 0; i < files.Length; i++)
            // {
            //     AssetDatabase.RenameAsset(DataPath + "/" + files[i].Name, i.ToString());
            // }

            // files = direction.GetFiles("*.mat", SearchOption.AllDirectories);
            //for (int i = 0; i < files.Length; i++)
            //{
            //    Material Mats = LoadMaterial(files[i].Name);
            //    Materials.Add(Mats);
            //    MatColors.Add(Mats.color);
            //    EditorColors.Add(Mats.color);
            //    SelectColors.Add(false);
            //}

            //if (!File.Exists(jsonNormalPath))
            //{
            //    KeepColorList();
            //}

            StreamReader sr = new StreamReader(jsonNormalPath);
            string json = sr.ReadToEnd();
            sr.Close();
            sr.Dispose();

            if (json.Length > 0)
            {
                colorlistJson list = JsonUtility.FromJson<colorlistJson>(json);
                for (int i = 0; i < list.list.Count; i++)
                {
                    if (i != list.list[i].id)
                        Debug.LogError("出错！");

                    Color color = list.list[i].color;
                    //Color color = new Color(list.list[i].color_r, list.list[i].color_g, list.list[i].color_b, list.list[i].color_a);

                    MatColors.Add(color);
                    EditorColors.Add(color);
                    SelectColors.Add(false);
                }
            }

            KeepColorList();
        }
    }

    static Material LoadMaterial(string name)
    {
        return AssetDatabase.LoadAssetAtPath(DataPath + "/" + name, typeof(Material)) as Material;
    }
    /*
    static void KeepColorXML()
    {
        string path = EditorUtility.SaveFilePanel("", XmlPath, "", "xml");

        if (path == null)
            return;

        XmlDocument xmlDoc = new XmlDocument();
        if (File.Exists(path))
        {
            AssetDatabase.DeleteAsset(path);
        }

        XmlElement root = xmlDoc.CreateElement("Data");

        ArrayList colors = new ArrayList();
        for (int i = 0; i < Materials.Count; i++)
        {
            colors.Add(WriteColorXML(xmlDoc, ((Material)Materials[i]).name,i, (Color)MatColors[i]));
        }
        
        for (int i = 0; i<colors.Count; i++)
        {
            root.AppendChild(((XmlElement)colors[i]));
        }
        xmlDoc.AppendChild(root);

        xmlDoc.Save(path);
    }

    static XmlElement WriteColorXML(XmlDocument xmlDoc,string name,int id,Color MatColors)
    {
        XmlElement color = xmlDoc.CreateElement("ColorList");

        color.SetAttribute("name", name);
        color.SetAttribute("id", id.ToString());
        color.SetAttribute("color_r", MatColors.r.ToString());
        color.SetAttribute("color_g", MatColors.g.ToString());
        color.SetAttribute("color_b", MatColors.b.ToString());
        color.SetAttribute("color_a", MatColors.a.ToString());

        return color;
    }

    static void ReadColorXML()
    {
        string path = EditorUtility.OpenFilePanel("保存颜色表", XmlPath, "xml");

        if (path == null)
            return;

        if (File.Exists(path))
        {
            XmlDocument xmlDoc = new XmlDocument();
            xmlDoc.Load(path);

            XmlNodeList nodeList = xmlDoc.SelectSingleNode("Data").ChildNodes;

            int MatCount = Materials.Count;

            if (nodeList.Count < MatCount)
            {
                Materials.RemoveRange(0, MatCount - nodeList.Count);
                MatColors.RemoveRange(0, MatCount - nodeList.Count);
                EditorColors.RemoveRange(0, MatCount - nodeList.Count);
                SelectColors.RemoveRange(0, MatCount - nodeList.Count);
            }
            if (nodeList.Count > MatCount)
            {
                foreach (XmlElement node in nodeList)
                {
                    string name = node.GetAttribute("name");//从这里开始要改
                    int id = int.Parse(node.GetAttribute("id"));
                    float r = float.Parse(node.GetAttribute("color_r"));
                    float g = float.Parse(node.GetAttribute("color_g"));
                    float b = float.Parse(node.GetAttribute("color_b"));
                    float a = float.Parse(node.GetAttribute("color_a"));
                    Color color = new Color(r, g, b, a);

                    if (id >= MatCount)
                    {
                        AddColor(color);
                    }
                }
            }

            for (int i = 0; i < Materials.Count; i++)
            {
                Resources.UnloadAsset((Material)Materials[i]);
            }

            foreach (XmlElement node in nodeList)
            {
                string name = node.GetAttribute("name");//从这里开始要改
                int id = int.Parse(node.GetAttribute("id"));
                float r = float.Parse(node.GetAttribute("color_r"));
                float g = float.Parse(node.GetAttribute("color_g"));
                float b = float.Parse(node.GetAttribute("color_b"));
                float a = float.Parse(node.GetAttribute("color_a"));
                Color color = new Color(r, g, b, a);

                Materials[id] = LoadMaterial(name + ".mat");
                MatColors[id] = color;
                EditorColors[id] = color;
                SelectColors[id] = false; 
            }

        }
    }
    */

    #endregion

    #region 方块
    static void Cubes()
    {
        EditorGUILayout.LabelField("----------------------------------------------------------");

        EditorGUILayout.LabelField("选中的大物体的长宽高：");
        ShowSice();
        EditorGUILayout.LabelField("----------------------------------------------------------");


        EditorGUILayout.LabelField("方块化和模型化可以相互转化。");
        EditorGUILayout.LabelField("方块化是建模状态，如果没有模型化过不需要按。");
        EditorGUILayout.LabelField("模型化是优化状态。相同颜色的会合并方块。");
        EditorGUILayout.BeginHorizontal();
        if(GUILayout.Button("方块化"))
        {
            CubeMode();
        }

        if(GUILayout.Button("模型化"))
        {
            ModelMode();
        }
        EditorGUILayout.EndHorizontal();
        EditorGUILayout.LabelField("----------------------------------------------------------");

        EditorGUILayout.LabelField("添加一行同色方块");

        EditorGUILayout.BeginHorizontal();

        for (int i = 0; i < 6; i++)
        { 
            EditorGUILayout.LabelField(AddCube_F_dirname[i], GUILayout.Width(20));
            AddCube_F_Dir[i] = EditorGUILayout.Toggle((bool)AddCube_F_Dir[i]);

            if ((bool)AddCube_F_Dir[i])
            {
                if (AddCube_F_dir_index != -1 && AddCube_F_dir_index != i)
                {
                    AddCube_F_Dir[AddCube_F_dir_index] = false;
                }
                AddCube_F_dir_index = i;
            }
        }
        EditorGUILayout.EndHorizontal();

        if (AddCube_F_dir_index != -1)
        {
            if (GUILayout.Button("f键"))
            {
                AddSimpleCubes();
            }
        }
        
        EditorGUILayout.LabelField("----------------------------------------------------------");

        EditorGUILayout.LabelField("方位选择_平面");
        for (int i = 1; i < 10; i++)
        {
            int index = i-1;
            if (i % 3 == 1)
            {
                EditorGUILayout.BeginHorizontal();
            }

            EditorGUILayout.LabelField(DirName[index], GUILayout.Width(30));
            SelectDir_Y[index] = EditorGUILayout.Toggle((bool)SelectDir_Y[index]);

            if (i % 3 == 0)
            {
                EditorGUILayout.EndHorizontal();
            }

            if ((bool)SelectDir_Y[index])
            {
                if (DirIndex[0] != -1 && DirIndex[0] != index)
                { SelectDir_Y[DirIndex[0]] = false; }
                DirIndex[0] = index;
            }
        }

        EditorGUILayout.LabelField("方位选择_轴向");
        EditorGUILayout.BeginHorizontal();
        for (int i = 0; i < 3; i++)
        {
            EditorGUILayout.LabelField(DirName_Z[i], GUILayout.Width(30));
            SelectDir_Z[i] = EditorGUILayout.Toggle((bool)SelectDir_Z[i]);

            if ((bool)SelectDir_Z[i])
            {
                if (DirIndex[1] != -1 && DirIndex[1] != i)
                {
                    SelectDir_Z[DirIndex[1]] = false;
                }
                DirIndex[1] = i;
            }
        }
        EditorGUILayout.EndHorizontal();

        EditorGUILayout.LabelField("方块个数");
        EditorGUILayout.BeginHorizontal();
        for (int i = 0; i < 2; i++)
        {
            EditorGUILayout.LabelField(AddNumberName[i], GUILayout.Width(30));
            AddNumberSelect[i] = EditorGUILayout.Toggle((bool)AddNumberSelect[i]);

            if((bool)AddNumberSelect[i])
            {
                if(DirIndex[2]!=-1 && DirIndex[2]!=i)
                {
                    AddNumberSelect[DirIndex[2]] = false;
                }
                DirIndex[2] = i;

                if(i == 0)
                {
                    AddNumber = 1;
                }
                if(i==1)
                {
                    AddNumber = EditorGUILayout.IntField(AddNumber);
                }
            }
        }
        EditorGUILayout.EndHorizontal();


        if (DirIndex[0] != -1 && DirIndex[1] != -1 && DirIndex[2] != -1)
        {
            if (GUILayout.Button("添加方块"))
            {
                if (SelectGOs.Count == 0)
                {
                    GetSelectTransforms();
                    if (SelectGOs.Count == 0)
                        return;
                }

                int Count = SelectGOs.Count;
                for (int j = 0; j < Count; j++)
                {
                    Transform tra = (Transform)SelectGOs[0];
                    for (int k = 0; k < AddNumber; k++)
                    {
                        GameObject obj = AddCube();
                        Vector3 firstPos = k == 0 ? tra.position : ((Transform)SelectGOs[SelectGOs.Count - 1]).position;
                        obj.transform.position = firstPos + GetDir(DirIndex[0], DirIndex[1]);
                        GetMeshRenderer(obj.transform).material = LoadMaterial(GetMeshRenderer(tra).sharedMaterial.name + ".mat");
                        if (tra.parent == null)
                        {
                            GameObject parent = new GameObject();
                            tra.parent = parent.transform;
                            obj.transform.parent = parent.transform;
                        }
                        else
                        {
                            obj.transform.parent = tra.parent;
                        }

                        SelectGOs.Remove(tra);
                        SelectGOs.Add(obj.transform);
                    }
                }

                UnityEngine.Object[] selectionObjs = new UnityEngine.Object[SelectGOs.Count];
                for (int j = 0; j < SelectGOs.Count; j++)
                {
                    selectionObjs[j] = (UnityEngine.Object)((Transform)SelectGOs[j]).gameObject;
                }
                Selection.objects = selectionObjs;

                AssetDatabase.SaveAssets();
            }
        }
    }

    static void ShowSice()
    {
        if (SelectGOs.Count == 0)
        {
            EditorGUILayout.LabelField("没有选中物体");
            return;
        }

        if(GetMeshRenderer((Transform)SelectGOs[0]) == null)
        {
            EditorGUILayout.LabelField("请选择实物，谢谢。");
            return;
        }

        float x = 0, y = 0, z = 0;

        Transform target = ((Transform)SelectGOs[0]).parent;
        float[] pos = new float[6] { target.position.x, target.position.x, target.position.y, target.position.y, target.position.z, target.position.z };
        int[] index = new int[6] { 0, 0, 0, 0, 0, 0 };

        for(int i=0;i<target.childCount;i++)
        {
            Transform nowTra = target.GetChild(i);

            if (nowTra.position.x > pos[0])//right
            {
                pos[0] = nowTra.position.x;
                index[0] = i;
            }

            if (nowTra.position.x < pos[1])//left
            {
                pos[1] = nowTra.position.x;
                index[1] = i;
            }

            if (nowTra.position.y > pos[2])//up
            {
                pos[2] = nowTra.position.y;
                index[2] = i;
            }

            if (nowTra.position.y < pos[3])//down
            {
                pos[3] = nowTra.position.y;
                index[3] = i;
            }

            if (nowTra.position.z > pos[4])//forward
            {
                pos[4] = nowTra.position.z;
                index[4] = i;
            }

            if (nowTra.position.z < pos[5])//back
            {
                pos[5] = nowTra.position.z;
                index[5] = i;
            }
        }
        
        pos[0] = pos[0] >= 0 ? pos[0] + GetSize_X(target.GetChild(index[0]))/2: pos[0] - GetSize_X(target.GetChild(index[0]))/2;
        pos[1] = pos[1] >= 0? pos[1] - GetSize_X(target.GetChild(index[1]))/2 : pos[1] - GetSize_X(target.GetChild(index[1]))/2;
        x =  pos[0] -  pos[1];

        pos[2] = pos[2] >= 0 ? pos[2] + GetSize_Y(target.GetChild(index[2]))/2 : pos[2] - GetSize_Y(target.GetChild(index[2]))/2;
        pos[3] = pos[3] >= 0 ? pos[3] - GetSize_Y(target.GetChild(index[3]))/2 : pos[3] - GetSize_Y(target.GetChild(index[3]))/2;
        y = pos[2] - pos[3];

        pos[4] = pos[4] >= 0 ? pos[4] + GetSize_Z(target.GetChild(index[4]))/2 : pos[4] - GetSize_Z(target.GetChild(index[4]))/2;
        pos[5] = pos[5] >= 0 ? pos[5] - GetSize_Z(target.GetChild(index[5]))/2 : pos[5] - GetSize_Z(target.GetChild(index[5]))/2;
        z = pos[4] - pos[5];

        EditorGUILayout.LabelField("长(x)：" + (int)(x+0.5f) + "个,宽(z)：" + (int)(z+0.5f) + "个,高(y)："+ (int)(y+0.5f) +"个");
    }

    static GameObject AddCube()
    {
        GameObject obj = GameObject.CreatePrimitive(PrimitiveType.Cube);
        obj.transform.localScale = new Vector3(1, 1, 1);
        return obj;
    }
    static Vector3 GetDir(int index,int Zindex)
    {
        Vector3 dir = Vector3.zero;
        switch (index)
        {
            case 0:
                dir.x = - 1;dir.y = 1;
                break;
            case 1:
                dir.y = 1;
                break;
            case 2:
                dir.x = 1;dir.y = 1;
                break;
            case 3:
                dir.x = -1;
                break;
            case 4:
                //中间 不需要改变
                break;
            case 5:
                dir.x = 1;
                break;
            case 6:
                dir.x = -1;dir.y = -1;
                break;
            case 7:
                dir.y = -1;
                break;
            case 8:
                dir.x = 1;dir.y = -1;
                break;
        }
        return setDirZ(dir,Zindex);
    }
    
    static Vector3 setDirZ(Vector3 dir,int Zindex)
    {
        switch (Zindex)
        {
            case 0:
                dir.z = 1;
                break;
            case 1:
                dir.z = 0;
                break;
            case 2:
                dir.z = -1;
                break;
        }
        return dir;

    }

    static void CubeMode()
    {
        Debug.Log("方块化进行中，请稍等。");
        if (SelectGOs.Count == 0)
        {
            Debug.Log("并没有选中物体，方块化结束！");
            return;
        }
        Transform parent = ((Transform)SelectGOs[0]).parent;
        if (parent == null)
        {
            GameObject GOnull = GameObject.CreatePrimitive(PrimitiveType.Cube);
            DestroyImmediate(GOnull.GetComponent<MeshFilter>());
            DestroyImmediate(GOnull.GetComponent<BoxCollider>());
            DestroyImmediate(GOnull.GetComponent<MeshRenderer>());
            GOnull.name = "New Game Object";

            ((Transform)SelectGOs[0]).parent = GOnull.transform;
            parent = GOnull.transform;
        }
        Transform Target;
        string materialName;

        ArrayList DelectCube = new ArrayList();
        float x, y, z,Ax, Ay, Az;
        for (int i = 0; i < parent.childCount; i++)
        {
            Target = parent.GetChild(i);

            x = GetSize_X(Target);
            y = GetSize_Y(Target);
            z = GetSize_Z(Target);

            Ax = x > 1 ? (int)(x / 2 + 0.5f) : 1;
            Ay = y > 1 ? (int)(y / 2 + 0.5f) : 1;
            Az = z > 1 ? (int)(z / 2 + 0.5f) : 1;

            if (x != 1 || y!=1 || z!=1)
            {
                materialName = GetMeshRenderer(Target).sharedMaterial.name;

                Vector3 firstPos = Target.position;
                firstPos.x = x != 1 ? firstPos.x - Ax * 0.5f : Target.position.x;
                firstPos.y = y != 1 ? firstPos.y - (Ay - 0.5f) : Target.position.y;
                firstPos.z = z != 1 ? firstPos.z - Az * 0.5f: Target.position.z;

                DelectCube.Add(parent.GetChild(i));

                for(int iy = 0;iy <(int)(y+0.5f);iy ++)
                {
                    for(int ix = 0;ix<(int)(x+0.5f);ix ++)
                    {
                        for(int iz = 0;iz<(int)(z+0.5f); iz++)
                        {
                            GameObject obj = AddCube();
                            obj.transform.parent = parent;
                            obj.transform.position = firstPos + new Vector3(ix, iy, iz);
                            GetMeshRenderer(obj.transform).material =  LoadMaterial(materialName + ".mat");
                        }
                    }
                }
            }
        }

        while(DelectCube.Count!=0)
        {
            GameObject obj = ((Transform)DelectCube[0]).gameObject;
            DelectCube.RemoveAt(0);
            DestroyImmediate(obj);
        }
        Debug.Log("方块化完毕！");
    }

    static void ModelMode()
    {
        Debug.Log("模型化进行中，请稍等。");
        if (SelectGOs.Count == 0)
        {
            Debug.Log("并没有选中物体，模型化结束！");
            return;
        }
        Transform parent = ((Transform)SelectGOs[0]).parent;
        if (parent == null)
        {
            GameObject GOnull = GameObject.CreatePrimitive(PrimitiveType.Cube);
            DestroyImmediate(GOnull.GetComponent<MeshFilter>());
            DestroyImmediate(GOnull.GetComponent<BoxCollider>());
            DestroyImmediate(GOnull.GetComponent<MeshRenderer>());
            GOnull.name = "New Game Object";

            ((Transform)SelectGOs[0]).parent = GOnull.transform;
            parent = GOnull.transform;
        }

        ModelDelectCube.Clear();
        bool IsDoing = true;

        while (IsDoing)
        {
            IsDoing = false;
            int count = parent.childCount;
            for (int i = 0; i < count; i++)
            {
                Transform target = parent.GetChild(i);

                if (ModelDelectCube.Contains(target))
                {
                    continue;
                }

                for (int j = 0; j < 6; j++)
                {
                    int index = GetSameIndex(target, j);

                    if (index == 0)
                    {
                        continue;
                    }

                    if (index > 1)
                    {
                        IsDoing = true;

                        if (!ModelDelectCube.Contains(target))
                        {
                            ModelDelectCube.Add(parent.GetChild(i));
                        }

                        Vector3 pos = target.position + (index -1) * GetSamecubeLenth(target, j)/2 * GetSamecubeDir(j);

                        Vector3 dir = GetSamecubeDir(j);
                        dir.x = dir.x < 0 ? -dir.x : dir.x;
                        dir.y = dir.y < 0 ? -dir.y : dir.y;
                        dir.z = dir.z < 0 ? -dir.z : dir.z;
                        Vector3 scale = target.localScale + (index-1) * GetSamecubeLenth(target, j) * dir;

                        GameObject obj = AddCube();
                        obj.transform.position = pos;
                        obj.transform.localScale = scale;
                        obj.transform.parent = parent;
                        string name = GetMeshRenderer(target).sharedMaterial.name;
                        if (!name.Contains("matColor"))
                        {
                            Color color = GetMeshRenderer(target).sharedMaterial.color;
                            bool IsExist = false;
                            for (int c = 0; c < MatColors.Count; c++)
                            {
                                if ((Color)MatColors[c] == color)
                                {
                                    GetMeshRenderer(obj.transform).material = LoadMaterial(colorlist_normal.list[c].MaterialName + ".mat"); ;
                                    IsExist = true;
                                }
                            }

                            if (!IsExist)
                            {
                                GetMeshRenderer(obj.transform).material = AddColor(color);
                                AssetDatabase.SaveAssets();
                            }
                        }
                        else
                        {
                            GetMeshRenderer(obj.transform).material = LoadMaterial(name + ".mat");
                        }

                    }
                }
            }

            while (ModelDelectCube.Count != 0)
            {
                GameObject obj = ((Transform)ModelDelectCube[0]).gameObject;
                ModelDelectCube.RemoveAt(0);
                DestroyImmediate(obj);
            }
        }

        
        Debug.Log("模型化完毕！");
    }

    static int GetSameIndex(Transform target, int dirIndex)
    {
        if (ModelDelectCube.Contains(target))
            return 0;

        RaycastHit hit;
        int Index = 1;
        if (Physics.Raycast(target.position, GetSamecubeDir(dirIndex), out hit, GetSamecubeLenth(target, dirIndex)/2 +1))
        {
            Transform next = hit.collider.transform;

            if (GetMeshRenderer(target).sharedMaterial.color == GetMeshRenderer(next).sharedMaterial.color)
            {
                if (GetSize_X(target) == GetSize_X(next) && GetSize_Y(target) == GetSize_Y(next) && GetSize_Z(target) == GetSize_Z(next))
                {
                    Index += GetSameIndex(next, dirIndex);
                    if (!ModelDelectCube.Contains(next))
                    {
                        ModelDelectCube.Add(hit.collider.transform);
                    }
                    return Index;
                }
            }
        }
        
        return Index;
    }
    
    static Vector3 GetSamecubeDir(int index)
    {
        Vector3 dir = Vector3.zero;
        switch(index)
        {
            case 0:
                dir = Vector3.left;
                break;
            case 1:
                dir = Vector3.forward;
                break;
            case 2:
                dir = Vector3.right;
                break;
            case 3:
                dir = Vector3.back;
                break;
            case 4:
                dir = Vector3.up;
                break;
            case 5:
                dir = Vector3.down;
                break;
        }
        return dir;
    }

    static float GetSamecubeLenth(Transform target, int index)
    {
        float length = index == 0 || index == 2 ? GetSize_X(target) : index == 1 || index == 3 ? GetSize_Z(target) : GetSize_Y(target);
        return length;
    }

    static void AddSimpleCubes()
    {
        AddCube_F.Clear();

        if(SelectGOs.Count == 0)
        {
            Debug.Log("没有选中物体！");
            return;
        }

        AddCube_F.Add((Transform)SelectGOs[0]);
        GetSimpleCube_plane((Transform)SelectGOs[0]);
        SelectGOs.Clear();
        Transform target;

        for(int i = 0;i<AddCube_F.Count;i++)
        {
            target = (Transform)AddCube_F[i];
            Transform tra = AddCube().transform;
            tra.transform.parent = target.parent;
            tra.transform.localScale = target.localScale;
            tra.transform.position = target.position + GetDir(AddCube_F_dirname_index[AddCube_F_dir_index, 0], AddCube_F_dirname_index[AddCube_F_dir_index, 1]);
            GetMeshRenderer(tra).material = LoadMaterial(GetMeshRenderer(target).sharedMaterial.name + ".mat");

            SelectGOs.Add(tra);
        }

        UnityEngine.Object[] selectionObjs = new UnityEngine.Object[SelectGOs.Count];
        for (int j = 0; j < SelectGOs.Count; j++)
        {
            selectionObjs[j] = (UnityEngine.Object)((Transform)SelectGOs[j]).gameObject;
        }
        Selection.objects = selectionObjs;

        AssetDatabase.SaveAssets();
    }

    static void GetSimpleCube_plane(Transform target)
    {
        RaycastHit hit;
        for (int i = 0; i < 6; i++)//修改这里！
        {
            Vector3 dir = GetDir(AddCube_F_dirname_index[i, 0], AddCube_F_dirname_index[i, 1]);

            Vector3 selectdir = GetDir(AddCube_F_dirname_index[AddCube_F_dir_index, 0], AddCube_F_dirname_index[AddCube_F_dir_index, 1]);

            if (dir == selectdir || dir == -selectdir)
            {
                continue;
            }

            if(Physics.Raycast(target.position,dir,out hit,1))
            {
                Transform next = hit.collider.transform;
                if(GetMeshRenderer(next).sharedMaterial.color == GetMeshRenderer(target).sharedMaterial.color)
                {
                    if(!AddCube_F.Contains(next))
                    {
                        AddCube_F.Add(next);
                        GetSimpleCube_plane(next);
                    }
                }
            }
        }
    }

    #endregion

    #region 对齐
    static void Align()
    {
        EditorGUILayout.LabelField("对齐对象");
        // AlignGO[0] = (GameObject)EditorGUI.ObjectField(new Rect(10, 40, 300,20),AlignGO[0],typeof(GameObject),true);
        // AlignGO[1] = (GameObject)EditorGUI.ObjectField(new Rect(10, 65, 300, 20), AlignGO[1], typeof(GameObject), true);

        AlignGO[0] = (GameObject)EditorGUILayout.ObjectField("主体", AlignGO[0], typeof(GameObject), true);
        EditorGUILayout.LabelField("对齐点");
        for (int i = 1; i < 9; i++)
        {
            if (i % 4 == 1)
            {
                EditorGUILayout.BeginHorizontal();
            }
            
            EditorGUILayout.LabelField(AlignName[i - 1], GUILayout.Width(40));
            AlignSelectDir_0[i - 1] = EditorGUILayout.Toggle( (bool)AlignSelectDir_0[i - 1], GUILayout.Width(20));

            if (i % 4 == 0)
            {
                EditorGUILayout.EndHorizontal();
            }

            if((bool)AlignSelectDir_0[i-1])
            {
                if(AlignIndex[0]!=-1 && AlignIndex[0]!=i-1)
                {
                    AlignSelectDir_0[AlignIndex[0]] = false;
                }
                AlignIndex[0] = i - 1;
            }
        }

        AlignGO[1] = (GameObject)EditorGUILayout.ObjectField("移动者", AlignGO[1], typeof(GameObject), true);
        EditorGUILayout.LabelField("对齐点");
        for (int i = 1; i < 9; i++)
        {
            if (i % 4 == 1)
            {
                EditorGUILayout.BeginHorizontal();
            }

            EditorGUILayout.LabelField(AlignName[i - 1], GUILayout.Width(40));
            AlignSelectDir_1[i - 1] = EditorGUILayout.Toggle((bool)AlignSelectDir_1[i - 1], GUILayout.Width(20));

            if (i % 4 == 0)
            {
                EditorGUILayout.EndHorizontal();
            }

            if ((bool)AlignSelectDir_1[i - 1])
            {
                if (AlignIndex[1] != -1 && AlignIndex[1] != i - 1)
                {
                    AlignSelectDir_1[AlignIndex[1]] = false;
                }
                AlignIndex[1] = i - 1;
            }
        }

        if(AlignGO[0]!=null && AlignGO[1]!=null && AlignIndex[0]!=-1 && AlignIndex[1]!=-1 )
        {
            if (GUILayout.Button("对齐"))
            {
                AlignGO[1].transform.position = GetAlignPos(AlignIndex[0], AlignIndex[1], AlignGO[0].transform, AlignGO[1].transform);
            }
        }
    }
    static Vector3 GetAlignPos(int PointIndex,int MoverIndex,Transform Point,Transform Mover)
    {
        Vector3 pos = Vector3.zero;
        
        //float Mover_length_X = Mover.GetComponent<MeshRenderer>().bounds.size.x;
        //float Mover_length_Y = Mover.GetComponent<MeshRenderer>().bounds.size.y;
        //float Mover_length_Z = Mover.GetComponent<MeshRenderer>().bounds.size.z;

        if (PointIndex == MoverIndex)
        {
            pos = Point.position;
        }
        else
        {
            pos = Point.position + GetAlignDir(PointIndex, Point);
            pos -= GetAlignDir(MoverIndex, Mover);
        }
        return pos;
    }

    static Vector3 GetAlignDir(int Index, Transform target)
    {
        Vector3 dir = Vector3.zero;
        float Point_length_X = target.GetComponent<MeshRenderer>().bounds.size.x/2;
        float Point_length_Y = target.GetComponent<MeshRenderer>().bounds.size.y/2;
        float Point_length_Z = target.GetComponent<MeshRenderer>().bounds.size.z/2;

        switch (Index)
        {
            case 0:
                dir.x = -Point_length_X;
                dir.y = Point_length_Y;
                dir.z = -Point_length_Z;
                break;

            case 1:
                dir.x = Point_length_X;
                dir.y = Point_length_Y;
                dir.z = -Point_length_Z;
                break;

            case 2:
                dir.x = -Point_length_X;
                dir.y = -Point_length_Y;
                dir.z = -Point_length_Z;
                break;

            case 3:
                dir.x = Point_length_X;
                dir.y = -Point_length_Y;
                dir.z = -Point_length_Z;
                break;

            case 4:
                dir.x = -Point_length_X;
                dir.y = Point_length_Y;
                dir.z = Point_length_Z;
                break;

            case 5:
                dir.x = Point_length_X;
                dir.y = Point_length_Y;
                dir.z = Point_length_Z;
                break;

            case 6:
                dir.x = -Point_length_X;
                dir.y = -Point_length_Y;
                dir.z = Point_length_Z;
                break;

            case 7:
                dir.x = Point_length_X;
                dir.y = -Point_length_Y;
                dir.z = Point_length_Z;
                break;
        }

        return dir;
    }
    #endregion

    #region 保存读取数据

    static void DataManage()
    {
        EditorGUILayout.LabelField("保存前务必查看父物体的名字！");
        EditorGUILayout.LabelField("预制体名字就是父物体名字！如果重复会被覆盖。");
        if(GUILayout.Button("保存成预制体"))
        {
            KeepPrefab();
        }
        EditorGUILayout.LabelField("----------下面这两个还没做好，勿按-----------------------------------");
        if (GUILayout.Button("保存Assetbundle"))
        {
            KeepAssetbundle();
        }

        if (GUILayout.Button("读取Assetbundle"))
        {
            ReadAssetbundle();
        }
        EditorGUILayout.LabelField("---------------------------------------------------------------------");
    }

    static void KeepPrefab()
    {
        if(SelectGOs.Count==0)
        {
            Debug.Log("没有选中物体，无法保存！");
            return;
        }

        Transform targer = ((Transform)SelectGOs[0]).parent;
        PrefabUtility.CreatePrefab(PrefabPath + "/" + targer.name + ".prefab", targer.gameObject);

        Debug.Log("预制体"+targer.name+"保存完毕。");
    }

    static void KeepAssetbundle()
    {
        /*
        DirectoryInfo direction = new DirectoryInfo(PrefabPath);
        FileInfo[] files = direction.GetFiles("*.*", SearchOption.AllDirectories);
        //Object[] selects = new Object[files.Length];
        //for(int i =0;i<files.Length;i++)
        //{
        //    selects[i] = AssetDatabase.LoadAssetAtPath(PrefabPath + "/" + files[i].Name, typeof(PrefabType));
        //}

        AssetBundleBuild[] buildMap = new AssetBundleBuild[1];

        buildMap[0].assetBundleName = "resources";//打包的资源包名称 随便命名
        string[] resourcesAssets = new string[files.Length];//此资源包下面有多少文件
        for (int i = 0; i < files.Length; i++)
        {
            resourcesAssets[i] = PrefabPath + "/" + files[i].Name;
            Debug.Log(PrefabPath + "/" + files[i].Name);
        }
        buildMap[0].assetNames = resourcesAssets;

        BuildPipeline.BuildAssetBundles(AssetbundlePath, buildMap);

        // BuildPipeline.BuildAssetBundles(AssetbundlePath, BuildAssetBundleOptions.DeterministicAssetBundle, BuildTarget.StandaloneOSXIntel);//这里还不懂
        Debug.Log("AssetBundle保存完毕。");
        */


        //foreach (Object o in Selection.GetFiltered(typeof(Object), SelectionMode.DeepAssets))
        DirectoryInfo direction = new DirectoryInfo(PrefabPath);
        FileInfo[] files = direction.GetFiles("*.prefab", SearchOption.AllDirectories);
        string name = "Prefab";
        for(int i=0;i<files.Length;i++)
        {
            string path = PrefabPath + files[i].Name;
            Debug.Log(path);
            AssetImporter ai = AssetImporter.GetAtPath(path);
            ai.assetBundleName = name;
        }


        ////生成bundle包的路径  
        //if (!Directory.Exists(outputPath))
        //    Directory.CreateDirectory(outputPath);
        ////把已经赋值AssetBundleName的Object全部打包到指定目录中  
        //BuildPipeline.BuildAssetBundles(outputPath);
        //AssetDatabase.Refresh();
        //Debug.Log("Build AssetBundle Success");
    }

    static void ReadAssetbundle()
    {
        string path = EditorUtility.OpenFilePanel("保存颜色表", AssetbundlePath, "assetbundle");

        if (path == null)
            return;

        WWW bundle = WWW.LoadFromCacheOrDownload(path, 1);
        
        //加载到游戏中
        Instantiate(bundle.assetBundle.mainAsset);

        bundle.assetBundle.Unload(false);
    }
    
    #endregion

    #region 通用方法

    static FileInfo[] GetMaterialFiles()
    {
        DirectoryInfo direction = new DirectoryInfo(DataPath);
        FileInfo[] files = direction.GetFiles("*.mat", SearchOption.AllDirectories);
        return files;
    }

    static MeshRenderer GetMeshRenderer(Transform target)
    {
        return target.GetComponent<MeshRenderer>();
    }

    static float GetSize_X(Transform target)
    {
        return GetMeshRenderer(target).bounds.size.x;
    }
    static float GetSize_Y(Transform target)
    {
        return GetMeshRenderer(target).bounds.size.y;
    }
    static float GetSize_Z(Transform target)
    {
        return GetMeshRenderer(target).bounds.size.z;
    }

    #endregion

    void OnFocus()
	{
		//Debug.Log("当窗口获得焦点时调用一次");
	}
 
	void OnLostFocus()
	{
		//Debug.Log("当窗口丢失焦点时调用一次");
	}
 
	void OnHierarchyChange()
	{
		//Debug.Log("当Hierarchy视图中的任何对象发生改变时调用一次");
	}
 
	void OnProjectChange()
	{

		//Debug.Log("当Project视图中的资源发生改变时调用一次");
	}
 
	void OnInspectorUpdate()
	{
	   //Debug.Log("窗口面板的更新");
	   //这里开启窗口的重绘，不然窗口信息不会刷新
	   this.Repaint();
	}
 
	void OnSelectionChange()
	{
        //当窗口出去开启状态，并且在Hierarchy视图中选择某游戏对象时调用
        GetSelectTransforms();
    }

    static void GetSelectTransforms()
    {
        SelectGOs.Clear();
        foreach (Transform t in Selection.transforms)
        {
            SelectGOs.Add(t);
        }
    }
 
	void OnDestroy()
	{
        KeepColorList();

        Clear();
        // Debug.Log("当窗口关闭时调用");
    }

    static void Clear()
    {
        //for (int i = 0; i < Materials.Count; i++)
        //{
        //    Resources.UnloadAsset((Material)Materials[i]);
        //}

        SelectGOs.Clear();
        SelectDir_Y.Clear();
       // Materials.Clear();
        MatColors.Clear();
        EditorColors.Clear();
        AlignSelectDir_0.Clear();
        AlignSelectDir_1.Clear();
        AddNumberSelect.Clear();
        AddCube_F.Clear();
        AddCube_F_Dir.Clear();
        SelectDir_Z.Clear();

    }
}
