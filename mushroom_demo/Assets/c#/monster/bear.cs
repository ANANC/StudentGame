using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class bear : monster {

    public bear(GameObject g,int i,string s):base()
    {
        MaxSpeed = 4f;
        name = s;

        monst = GameObject.Instantiate((GameObject)Resources.Load("Prefab/monster/bear"));
        monst.name = s;
        monst.transform.parent = g.transform;
        center = g;

        substanceName = "石螺";

        Init();

    }

}

public class bearManager
{
    GameObject center;
    GameObject player;
    static List<bear> list;
    float productionNumber;
    static bearManager instance;
    bool IsUpdate;
    float MaxDistance_player;
    float MaxDistance_center;
    public static bearManager GetInstance()
    {
        if(instance == null)
            instance = new bearManager();
        return instance;
    }

    bearManager()
    {
        productionNumber = 30;
        IsUpdate = false;
        MaxDistance_player = 17f;

        center = GameObject.Find("bearCenter");
        player = GameObject.Find("player");

        list = new List<bear>();
        for(int i=0;i<productionNumber;i++)
        {
            list.Add(new bear(center, 0,"bear" + i.ToString()));
            Vector3 v = new Vector3();
            v = center.transform.position;
            v += new Vector3((float)(Random.value - 0.5) * 2 * 10f, (float)(Random.value - 0.5) * 2 * 10f, 0);
            list[i].SetPos(v);
        }
    }

    public void Check()
    {
        if ((center.transform.position - player.transform.position).magnitude < MaxDistance_player )
        {
            IsUpdate = true;
            return;
        }
        else
        {
            IsUpdate = false;
        }
    }
    public void Upda()
    {
        if (IsUpdate == false)
            return;

        foreach (bear b in list)
            b.Update();
    }

    public string FindSubstanceName(string s)
    {
        string ss = null;
        foreach (bear b in list)
        {
            if (b.NAME == s)
                return b.SubstanceName;
        }
        return ss;
    }
}
