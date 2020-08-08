using UnityEngine;
using System.Collections;

public enum PropType
{
    cactus,
    fragment,
    all
}

public class PropControllor : MonoBehaviour {

   static PropControllor _instance;
    public static PropControllor GetInstance()
    {
        if (_instance == null)
            _instance = GameObject.FindGameObjectWithTag(tags.gameControl).GetComponent<PropControllor>();
        return _instance;
    }
    private PropControllor() { }

    public delegate void onChange(PropType type);
    public static event onChange PropChangeEvent;

    public delegate void DesertWorld();
    public static event DesertWorld desertWorldEvent;

    int fragmentNumber;//当前获取的碎片值
    int cactusTime;//仙人掌倒数时间
    public int FragmentNumber
    {
        set
        {
            fragmentNumber = value;
        }
        get
        {
            return fragmentNumber;
        }
    }

    public int CactusTime
    {
        set
        {
            cactusTime = value;
            if(cactusTime<10)
            {
                desertWorldEvent();
            }
        }
        get
        {
            return cactusTime;
        }
    }

    void Start()
    {
        Init();
    }

    public void Init()
    {
        fragmentNumber = 0;
        cactusTime = 80;
        propChangeEvent(PropType.all);
    }

    public void propChangeEvent(PropType type)
    {
        PropChangeEvent(type);
    }
}
