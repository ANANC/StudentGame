using UnityEngine;
using System.Collections;


public class npc_1 : npc
{
    static npc instance;
    void Awake()
    {
        instance = this;
    }
    void Start()
    {
        sleepTell = "可怜哒我";
        withPlayerTell = "人生无常。谁会知道，你下一秒会成为什么。";
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
