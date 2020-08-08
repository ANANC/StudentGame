using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class cook : MonoBehaviour {
    public GameObject SelectCookUIGameObject;
    public GameObject CookGameObject;
    public GameObject contentGameObject;
    public GameObject NameGameObject;
    public GameObject NeedGameObject;
    public GameObject StratButton;
    public GameObject GetPropGameObject;
    public GameObject numberTextGameObject;
    public GameObject numberBarGameObject;
    public GameObject barGameObject;
    public GameObject leftGameObject;
    public Camera cookUICamera;
    public GameObject SelectAllGameobject;
    List<GameObject> SelectButton;

    float MoveDistance;
    Vector3 CameraInitPos;
    Vector3 CameraMovePos;
    bool IsNeedMove;
    bool IsOpen;
    int CanMarkAllNumber;
    int NowMarkNumber;
    string nowName;

    static cook instance;


    public static cook GetInstance()
    {
        return instance;
    }

    void Awake()
    {
        instance = this;
    }


	void Start ()
    {
        SelectButton = new List<GameObject>();
        CameraInitPos = cookUICamera.transform.localPosition;
        MoveDistance = 20.5f;
        IsNeedMove = false;
        IsOpen = false;
        CameraMovePos = Vector3.zero;
        CanMarkAllNumber = 100;
        NowMarkNumber = 0;
           
        AddSelect("红瓶");
        AddSelect("红菇");

        EventDelegate.Add(barGameObject.GetComponent<UIScrollBar>().onChange, SelectButtonCameraMove);
        EventDelegate.Add(numberBarGameObject.GetComponent<UISlider>().onChange, SelectNumberChange);
        UIEventListener.Get(SelectCookUIGameObject).onClick = ClickCookUI;
        UIEventListener.Get(leftGameObject).onClick = ClickCookUI;
        UIEventListener.Get(StratButton).onClick = StartPlay;

        SelectAllGameobject.SetActive(false);
        CookGameObject.SetActive(false);
        contentGameObject.SetActive(false);

	}

    void ClickCookUI(GameObject g)
    {
        if (IsOpen == false)
        {
            Open();
            IsOpen = true;
        }
        else
        {
            Close();
            IsOpen = false;
        }
    }

    void Open()
    {
        SelectAllGameobject.SetActive(true);
        CookGameObject.SetActive(true);
    }

    void Close()
    {
        SelectAllGameobject.SetActive(false);
        CookGameObject.SetActive(false);
        contentGameObject.SetActive(false);
    }

    void onHover(GameObject go, bool isOver)
    {
        if (isOver)
            propManager.GetInstance().SetTipOpen(go.name, go.transform.position);
        else
            propManager.GetInstance().SetTipClose();
    }

    void OpenContent(GameObject g)
    {
        contentGameObject.SetActive(true);
        InitContent(g.name);
        nowName = g.name;
    }

    void StartPlay(GameObject g)
    {
        Use(nowName);
        GetPropGameObject.SetActive(false);
        StratButton.SetActive(false);
        Music.GetInstance().STATE = Music_state.play_init;
    }

    public void GetProp()
    {
        GetPropGameObject.SetActive(true);
        GetPropGameObject.GetComponent<UISprite>().spriteName = nowName;
        for (int i = 0; i < NowMarkNumber; i++)
            propManager.GetInstance().AddProp(nowName);
        SelectMarkNumber(nowName);
    }

    void AddSelect(string name)
    {
        GameObject g = GameObject.Instantiate((GameObject)Resources.Load("Prefab/cook/selectbutton"));
        g.name = name;
        g.transform.FindChild("text").GetComponent<UILabel>().text = name;
        g.transform.parent = SelectAllGameobject.transform;
        g.transform.localPosition = new Vector3(0, -SelectButton.Count * MoveDistance, 0);
        g.transform.localScale = Vector3.one;
        SelectButton.Add(g);

        UIEventListener.Get(g).onClick = OpenContent;
        
        if(SelectButton.Count>14)
        {
            IsNeedMove = true;
            barGameObject.GetComponent<UIScrollBar>().barSize = 14 / (float)SelectButton.Count;
            CameraMovePos.y = MoveDistance * (SelectButton.Count - 14) / 100f;
        }
    }

    void InitContent(string name)
    {
        propManager PropManager = propManager.GetInstance();
        NameGameObject.GetComponent<UISprite>().spriteName = name;
        NameGameObject.name = name;
        UIEventListener.Get(NameGameObject).onHover = onHover;
        SelectMarkNumber(name);

        GetPropGameObject.SetActive(false);
    }

    void SelectMarkNumber(string name)
    {
        propManager PropManager = propManager.GetInstance();
        int number = 100;
        string content = "";
        Dictionary<string, int> Need = propManager.GetInstance().GetNeeds(name);
        foreach (KeyValuePair<string, int> k in Need)
        {
            content += k.Key + PropManager.GetPossesstionNunber(k.Key) + "/" + k.Value.ToString() + " ";
            int i = PropManager.GetPossesstionNunber(k.Key) / k.Value;
            if (number > i)
                number = i;
        }
        NeedGameObject.GetComponent<UILabel>().text = content;
        CanMarkAllNumber = number;

        if (CanMarkAllNumber > 0)
        {
            StratButton.SetActive(true);
            NowMarkNumber = (int)(numberBarGameObject.GetComponent<UISlider>().value * CanMarkAllNumber % 10);
            numberBarGameObject.SetActive(true);
        }
        else
        {
            NowMarkNumber = 0;
            numberBarGameObject.SetActive(false);
            StratButton.SetActive(false);
        }
        numberTextGameObject.GetComponent<UILabel>().text = NowMarkNumber + "/" + CanMarkAllNumber;
    }

    void Use(string name)
    {
        propManager PropManager = propManager.GetInstance();
        Dictionary<string, int> Need = propManager.GetInstance().GetNeeds(name);
        foreach (KeyValuePair<string, int> k in Need)
        {
            int i = k.Value * NowMarkNumber;
            for (int j = 0; j < i; j++)
                PropManager.UsedProp(k.Key, "prop");
        }
    }

    void SelectNumberChange()
    {
        NowMarkNumber = (int)(numberBarGameObject.GetComponent<UISlider>().value * CanMarkAllNumber %10);
        numberTextGameObject.GetComponent<UILabel>().text = NowMarkNumber + "/" + CanMarkAllNumber;
        if(NowMarkNumber == 0)
            StratButton.SetActive(false);
        else
            StratButton.SetActive(true);
    }

    void SelectButtonCameraMove()
    {
        if (IsNeedMove)
        {
            Vector3 CameraPos = CameraMovePos;
            CameraPos.y = barGameObject.GetComponent<UIScrollBar>().value * CameraMovePos.y * 100f;
            cookUICamera.transform.localPosition = CameraInitPos - CameraPos;
        }
    }
}
