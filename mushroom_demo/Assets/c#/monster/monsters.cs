using UnityEngine;
using System.Collections;


public class monsters : MonoBehaviour
{
    float time_Check;
    bool IsUpdate;
    static monsters instance;

    bearManager bearmanager;
    wolfManager wolfmanagr;
    monkeyManager monkeymanagr;

    static public monsters GetInstance()
    {
        return instance;
    }

    void Awake()
    {
        bearmanager = bearManager.GetInstance();
        wolfmanagr = wolfManager.GetInstance();
        monkeymanagr = monkeyManager.GetInstance();
        time_Check = 0;
        IsUpdate = true;

        instance = this;
    }

    public bool ISupdate
    {
        set
        {
            IsUpdate = value;
        }
    }

    public string GetSubstanceName(string s)
    {
        string ss = null;
        ss = bearmanager.FindSubstanceName(s);
        if (ss != null)
            return ss;
        ss = wolfmanagr.FindSubstanceName(s);
        if (ss != null)
            return ss;
        ss = monkeymanagr.FindSubstanceName(s);
        if (ss != null)
            return ss;
        return ss;
    }

	public void Update () {

        time_Check += Time.deltaTime;
        if (time_Check > 1f)
        {
            bearmanager.Check();
            wolfmanagr.Check();
            monkeymanagr.Check();
            time_Check = 0;
        }

        if (IsUpdate == false)
            return;
        
        bearmanager.Upda();
        wolfmanagr.Upda();
        monkeymanagr.Upda();
	}
}
