using UnityEngine;
using System.Collections;

public class npc_3 : npc
{
    static npc instance;
    void Awake()
    {
        instance = this;
    }
    void Start()
    {
        sleepTell = "今朝有酒今朝醉，哈哈哈";
        withPlayerTell = "何必多说！有酒喝就足够了！";
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
