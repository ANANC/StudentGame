using UnityEngine;
using System.Collections;

public class DataMgr
{
    private DataMgr() { }
    private static DataMgr instance;
    public static DataMgr Instance()
    {
        if (instance == null)
        {
            instance = new DataMgr();
        }
        return instance;
    }

    private int woodCount = 0;
    private int warmValueA = 100;
    private int warmValueB = 100;

    private int fireValue = 100;
    private int treeSkyRound = 600;
    private int AIRound = 600;

    private readonly int woodTofireValue = 2;

    private bool AllHome = true;

    public delegate void woodUpdate();
    public delegate void warmUpdate();
    public delegate void fireUpdate();
    public delegate void treeSkyUpdate();
    public delegate void playerControUpdate();

    public woodUpdate woodUpdateEvent;
    public warmUpdate warmUpdateEvent;
    public fireUpdate fireUpdateEvent;
    public treeSkyUpdate treeSkyUpdateEvent;
    public playerControUpdate playerUpdateEvent;

    private PlayerController m_A;
    private PlayerController m_B;
    private PlayerController m_AAI;
    private PlayerController m_BAI;

    private bool m_PlayerControlA = true;

    public void AddWood()
    {
        int value = Random.Range(1, 3);
        woodCount += value;
        if (woodCount > 100)
        {
            woodCount = 100;
        }
        if(woodUpdateEvent!=null)
        {
            woodUpdateEvent();
        }
    }

    public void UseWood(int value)
    {
        if(value> woodCount)
        {
            value = woodCount;
        }

        AddFire(value * woodTofireValue);

        woodCount -= value;

        if (woodUpdateEvent != null)
        {
            woodUpdateEvent();
        }
    }

    public void UseAllWood()
    {
        AddFire(woodCount * woodTofireValue);
        woodCount = 0;
        if (woodUpdateEvent != null)
        {
            woodUpdateEvent();
        }
    }

    public void AddWarm(bool a,int value)
    {
        if (a)
        {
            warmValueA += value;
            if (warmValueA > 100)
            {
                warmValueA = 100;
            }
        }
        else
        {
            warmValueB += value;
            if (warmValueB > 100)
            {
                warmValueB = 100;
            }
        }
        if (warmUpdateEvent != null)
        {
            warmUpdateEvent();
        }
    }

    public void UesWarm(bool a, int value)
    {
        if (a)
        {
            warmValueA -= value;
            if (warmValueA < 0)
            {
                warmValueA = 0;
            }
        }
        else
        {
            warmValueB -= value;
            if (warmValueB < 0)
            {
                warmValueB = 0;
            }
        }
        if (warmUpdateEvent != null)
        {
            warmUpdateEvent();
        }
    }

    public void AddFire(int value)
    {
        fireValue += value;
        if (fireValue > 100)
        {
            fireValue = 100;
        }
        if (fireUpdateEvent != null)
        {
            fireUpdateEvent();
        }
    }

    public void UesFire(int value)
    {
        fireValue -= value;
        if (fireValue < 0)
        {
            fireValue = 0;
        }
        if (fireUpdateEvent != null)
        {
            fireUpdateEvent();
        }
    }

    public int GetWarmValue(bool a)
    {
        return a ? warmValueA : warmValueB;
    }

    public int GetWoodValue()
    {
        return woodCount;
    }
    public int GetFireValue()
    {
        return fireValue;
    }

    public void SetTreeSkyRound(int width)
    {
        treeSkyRound = width;
        if(treeSkyUpdateEvent!=null)
        {
            treeSkyUpdateEvent();
        }
    }

    public int GetTreeSkyRound()
    {
        return treeSkyRound;
    }

    public int GetAIRound()
    {
        return AIRound;
    }

    // --- Player --

    public void SetPlayerController(bool a,bool ai,PlayerController controller)
    {
        if(a )
        {
            if(ai)
            {
                m_AAI = controller;
            }
            else
            {
                m_A = controller;
            }
        }
        else
        {
            if(ai)
            {
                m_BAI = controller;
            }
            else
            {
                m_B = controller;
            }
        }
    }

    public void SetMoveCom(bool a,Vector3 pos)
    {
        PlayerController playerController = a ? m_AAI : m_BAI;
        if(playerController.transform.localPosition != pos )
        {
            playerController.MoveToTarget(pos);
        }
    }

    public void SetStopCom(bool a)
    {
        PlayerController playerController = a ? m_AAI : m_BAI;
        playerController.MoveStopAI();
    }

    public void SetTalkCom(bool a ,string text)
    {
        PlayerController playerController = a ? m_AAI : m_BAI;
        playerController.Talk(text);
    }

    public void SetActiveCom(bool a ,bool active)
    {
        PlayerController playerController = a ? m_AAI : m_BAI;
        playerController.gameObject.SetActive(active);
    }

    public void SetPlayerControl(bool a)
    {
        m_PlayerControlA = a;
        if(playerUpdateEvent != null)
        {
            playerUpdateEvent();
        }
    }

    public bool GetPlayerControl()
    {
        return m_PlayerControlA;
    }

    // --- Player --

    public void SetHome(bool home)
    {
        AllHome = home;
    }

    public bool GetAllHome()
    {
        return AllHome;
    }
}
