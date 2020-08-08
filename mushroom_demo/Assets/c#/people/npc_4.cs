using UnityEngine;
using System.Collections;

public class npc_4 : npc
{
    static npc instance;

    void Awake()
    {
        instance = this;
    }

    void Start()
    {
        sleepTell = "我哒老婆真可爱。>////<";
        withPlayerTell = "两个人走到现在不容易。在一起不是只要你爱我我爱你就够了，相互理解很重要哒。";
        Init();
        IsNeedShop = false;
    }
    public static npc Instance
    {
        get
        {
            return instance;
        }
    }

    protected override void TextInit()
    {
        string SelectText;
        if (Task != null && Task.State == task_state.Remove)
        {
            Task = null;
        }
        if (Task != null)
            SelectText = "任务：" + Task.Name;
        else
            SelectText = "对话";
        DialogBox.GetInstance().TextOpen(SelectText, sleepTell, IsNeedShop);
        DialogBox.GetInstance().SelectNpc(instance);
    }

}
