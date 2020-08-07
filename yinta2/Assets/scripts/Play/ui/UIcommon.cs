using UnityEngine;
using System.Collections;
using UnityEngine.UI;
/*
public struct SceneLayer
{
    public int[] exist;
    public string[] Scenenames;
    public int[] SceneChipIndex;
    public int LayerNeedIndex;
    public string LayerName;
    public bool IsOpen;

    public SceneLayer(string layername,int NeedIndex,bool isopen,int[] Exist,int[] scenechipIndex,string[] sceneNames)
    {
        LayerName = layername;
        LayerNeedIndex = NeedIndex;
        exist = Exist;
        Scenenames = sceneNames;
        IsOpen = isopen;
        SceneChipIndex = scenechipIndex;
    }
}

    */
/*
public class UIcommon {

    static bool isShowStartMoive = true;
    public static bool IsShowStartMoive
    {
        get
        {
            return isShowStartMoive;
        }
    }
    static float musicPower = 1;
    public static float MusicPower
    {
        get
        {
            return musicPower;
        }
    }
    static float musiceffectPower = 0.5f;
    public static float MusiceffectPower
    {
        get
        {
            return musiceffectPower;
        }
    }

    public static bool IsStart = true;
    public static Vector3 GameNamePos_Final;
    public static Vector3 SelectZhuPos_Final;
    public static Vector3 uiPlane_Final;

    public static int nowchipindex = 0;
    public static int Layerchipindex = 0;
    public static int nowLayerindex = 0;
    public static int nowSceneindex = 0;
    public const int LayerIndex = 7;
    public static SceneLayer[] Layer = new SceneLayer[LayerIndex] {
        new SceneLayer("思 白",0,true,new int[4] { 1,1,0,0},new int[4] {8,8,0,0},new string[4] {"重觅繁迹","再返碧海","遍寻参木","仰观皑皑" }),
        new SceneLayer("弥 昏",30,false,new int[4] {0,0,0,0},new int[4] {0,0,0,0},new string[4] { "","","",""}),
        new SceneLayer("逐 明",60,false,new int[4] {0,0,0,0},new int[4] {0,0,0,0},new string[4] { "","","",""}),
        new SceneLayer("归 晴",90,false,new int[4] {0,0,0,0},new int[4] {0,0,0,0},new string[4] { "","","",""}),
        new SceneLayer("定 心",120,false,new int[4] {0,0,0,0},new int[4] {0,0,0,0},new string[4] { "","","",""}),
        new SceneLayer("正 目",150,false,new int[4] {0,0,0,0},new int[4] {0,0,0,0},new string[4] { "","","",""}),
        new SceneLayer("舍 得",180,false,new int[4] {0,0,0,0},new int[4] {0,0,0,0},new string[4] { "","","",""})
    };

    public static string GetNowSceneName()
    {
        string name = nowLayerindex.ToString() + nowSceneindex.ToString();
        return name;
    }

    public static void Addnowchipindex()
    {
        Debug.Log(LoadUI.loadname);
        if (LoadUI.loadname == "02")
            return;

        nowchipindex += 1;
    }
    
    public static void SetNowSceneindex(int index)
    {
        nowSceneindex += index;
        nowSceneindex = nowSceneindex < 0 ? 3 : nowSceneindex;
        nowSceneindex = nowSceneindex > 3 ? 0 : nowSceneindex;
    }

    public static void SetIsShowStartMoive(bool b)
    {
         isShowStartMoive = b;
    }

    public static void SetMusicPower(float power)
    {
        musicPower = power;
        GameObject.FindGameObjectWithTag("music").GetComponent<AudioSource>().volume = musicPower;
    }

    public static void SetMusiceffectPower(float power)
    {
        musiceffectPower = power;
        GameObject[] musiceffects = GameObject.FindGameObjectsWithTag("musicEffect");
        for (int i = 0; i < musiceffects.Length; i++)
        {
            musiceffects[i].GetComponent<AudioSource>().volume = musiceffectPower;
        }
    }

    public static void setText(Transform tra, string str)
    {
        tra.GetComponent<Text>().text = str;
    }

    public static float Abs(float infloat)
    {
        float outfloat;
        outfloat = infloat < 0 ? -infloat : infloat;
        return outfloat;
    }
    
}
*/