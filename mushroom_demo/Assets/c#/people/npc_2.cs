using UnityEngine;
using System.Collections;


public class npc_2 : npc
{
    static npc instance;

    void Awake()
    {
        instance = this;
    }

    void Start()
    {
        sleepTell = "你好。";
        withPlayerTell = "见到喜欢的东西就买了吧。你现在不买，以后没机会买的时候，那种失望感会远比你现在的吃土感来得强烈。";
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
