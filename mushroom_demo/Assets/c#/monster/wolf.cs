using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class wolf : monster
{

    public wolf(GameObject g, int i, string s)
        : base()
    {
        MaxSpeed = 4f;
        name = s;

        monst = GameObject.Instantiate((GameObject)Resources.Load("Prefab/monster/wolf"));
        monst.name = s;
        monst.transform.parent = g.transform;
        center = g;

        substanceName = "萎蜜";

        Init();

    }

}

public class wolfManager
{
    GameObject center;
    GameObject player;
    static List<wolf> list;
    float productionNumber;
    static wolfManager instance;
    bool IsUpdate;
    float MaxDistance_player;
    float MaxDistance_center;
    public static wolfManager GetInstance()
    {
        if (instance == null)
            instance = new wolfManager();
        return instance;
    }

    wolfManager()
    {
        productionNumber = 30;
        IsUpdate = false;
        MaxDistance_player = 17f;

        center = GameObject.Find("wolfCenter");
        player = GameObject.Find("player");

        list = new List<wolf>();
        for (int i = 0; i < productionNumber; i++)
        {
            list.Add(new wolf(center, 0, "wolf" + i.ToString()));
            Vector3 v = new Vector3();
            v = center.transform.position;
            v += new Vector3((float)(Random.value - 0.5) * 2 * 10f, (float)(Random.value - 0.5) * 2 * 10f, 0);
            list[i].SetPos(v);
        }
    }


    public void Check()
    {
        if ((center.transform.position - player.transform.position).magnitude < MaxDistance_player)
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

        foreach (wolf b in list)
            b.Update();
    }

    public string FindSubstanceName(string s)
    {
        string ss = null;
        foreach (wolf b in list)
        {
            if (b.NAME == s)
                return b.SubstanceName;
        }
        return ss;
    }
}
