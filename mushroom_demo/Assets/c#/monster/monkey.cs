using UnityEngine;
using System.Collections;

using System.Collections.Generic;

public class monkey : monster
{

    public monkey(GameObject g, int i, string s)
        : base()
    {
        MaxSpeed = 4f;
        name = s;

        monst = GameObject.Instantiate((GameObject)Resources.Load("Prefab/monster/monkey"));
        monst.name = s;
        monst.transform.parent = g.transform;
        center = g;

        substanceName = "决角";

        Init();

    }

}

public class monkeyManager
{
    GameObject center;
    GameObject player;
    static List<monkey> list;
    float productionNumber;
    static monkeyManager instance;
    bool IsUpdate;
    float MaxDistance_player;
    float MaxDistance_center;
    public static monkeyManager GetInstance()
    {
        if (instance == null)
            instance = new monkeyManager();
        return instance;
    }

    monkeyManager()
    {
        productionNumber = 30;
        IsUpdate = false;
        MaxDistance_player = 17f;

        center = GameObject.Find("monkeyCenter");
        player = GameObject.Find("player");

        list = new List<monkey>();
        for (int i = 0; i < productionNumber; i++)
        {
            list.Add(new monkey(center, 0, "monkey" + i.ToString()));
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

        foreach (monkey b in list)
            b.Update();
    }

    public string FindSubstanceName(string s)
    {
        string ss = null;
        foreach (monkey b in list)
        {
            if (b.NAME == s)
                return b.SubstanceName;
        }
        return ss;
    }
}
