using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using UnityEngine.SceneManagement;
public class chipUI {
    
    Transform chipuiTra;

    private static chipUI ChipUIInstance;
    public static chipUI chipUIInstance(Transform father)
    {
        if (ChipUIInstance == null)
            ChipUIInstance = new chipUI(father);
        return ChipUIInstance;
    }
    
    private Transform sphereNumber_now_text;
    private GameObject[] chips;
   // private static string[] Names;
    private static Dictionary<string, string[]> GetChipNames;
        public void Distroy()
    {
        ChipUIInstance = null;
    }
    chipUI(Transform tra) {
        chipuiTra = tra;
        sphereNumber_now_text = tra.FindChild("Text");

        if(GetChipNames == null)
        {
            GetChipNames = new Dictionary<string, string[]>();
            for(int i=0;i<UIcommon.LayerIndex;i++)
            {
                if(UIcommon.Layer[i].IsOpen)
                {
                    for(int j=0;j<4;j++)
                    {
                        if(UIcommon.Layer[i].SceneChipIndex[j]!=0)
                        {
                            GetChipNames.Add(i.ToString()+j.ToString(), new string[UIcommon.Layer[i].SceneChipIndex[j]]);
                        }
                    }
                }
            }
        }

        init();
    }

    public void init()
    {
        chips = GameObject.FindGameObjectsWithTag("chip");
        //if (Names == null)
        //{
        //    Names = new string[chips.Length];
        //}
        //else
        //{
        //    for (int i = 0; i < Names.Length; i++)
        //    {
        //        if (Names[i] != null)
        //        {
        //            for (int j = 0; j < chips.Length; j++)
        //            {
        //                if (chips[j].name == Names[i])
        //                {
        //                    chips[j].SetActive(false);
        //                }
        //            }
        //        }
        //    }
        //}

        string NowSceneName = UIcommon.GetNowSceneName(); 
        for (int i = 0; i < GetChipNames[NowSceneName].Length; i++)
        {
            if (GetChipNames[NowSceneName][i] != null)
            {
                for (int j = 0; j < chips.Length; j++)
                {
                    if (chips[j].name == GetChipNames[NowSceneName][i])
                        chips[j].SetActive(false);
                }
            }
        }
        

        Updatechipindex();
    }
    

    public void OnCollisionEnter(string name)
    {
        //for(int i=0;i<Names.Length;i++)
        //{
        //    if(Names[i] == null)
        //    {
        //        Names[i] = name;
        //        break;
        //    }
        //}

        string NowSceneName = UIcommon.GetNowSceneName();
        for (int i = 0; i < GetChipNames[NowSceneName].Length; i++)
        {
            if (GetChipNames[NowSceneName][i] == null)
            {
                GetChipNames[NowSceneName][i] = name;
                break;
            }
        }

        chipuiTra.GetComponent<AudioSource>().volume = UIcommon.MusiceffectPower;
        chipuiTra.GetComponent<AudioSource>().Play();
        UIcommon.Addnowchipindex();
        Updatechipindex();
    }
    
   void Updatechipindex()
    {
        UIcommon.setText(sphereNumber_now_text, UIcommon.nowchipindex.ToString());
    }




}
