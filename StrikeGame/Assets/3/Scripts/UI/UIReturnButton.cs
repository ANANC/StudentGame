using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class UIReturnButton : MonoBehaviour {
    Transform Return;
    UImove moveEvent;
    bool isActive;
    public bool IsActive {get{return isActive;}}

    public delegate void onClick();
    private event onClick OnClickEvent;
    private Stack OnClickStack;

    private static UIReturnButton _instance;
    public static UIReturnButton GetInstance()
    {
        if (_instance == null)
            _instance = GameObject.Find("menu").GetComponent<UIReturnButton>();
        return _instance;
    }

    void Start () {
        Return = transform.FindChild("Return");
        moveEvent = UImove.GetInstance();

        Return.GetComponent<Button>().onClick.AddListener(onclickEvent);

        OnClickStack = new Stack();
        
    }
	
    public void setActive(bool b)
    {
        if (isActive == b)
            return;

        isActive = b;
        if (b)
        {
            moveEvent.singleMove(Return, -UICommon.ButtonMoveDisece, UICommon.MoveTime, false, true, true, UICommon.MoveTime);
        }
        else
        {
            moveEvent.singleMove(Return, UICommon.ButtonMoveDisece, UICommon.MoveTime, false, false);
        }
    }

    void onclickEvent()
    {
        OnClickEvent();
        OnClickStack.Pop();
        OnClickEvent = null;
        if (OnClickStack.Count != 0)
        {
            onClick click = (onClick)OnClickStack.Pop();
            OnClickEvent += click;
            OnClickStack.Push(click);
        }
    }

    public void AddOnClikEvent(onClick click)
    {
        OnClickStack.Push(click);
        OnClickEvent = null;
        OnClickEvent += click;
    }
    
}
