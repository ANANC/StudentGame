using UnityEngine;
using System.Collections;


public class npc_0 : npc {

    static  npc instance;

    void Awake()
    {
        instance = this;
    }

    void Start()
    {
        sleepTell = "买不买点药屯着啊？";
        withPlayerTell = "生活真的不简单。一不小心可能就会磕伤什么的，所以常备点药是很重要的。";
        Init();
        IsNeedShop = true;
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

    public override void ShopButtonClick()
    {
        shop.GetInstance().AddContent("郁米");
        shop.GetInstance().AddContent("阳玉");
        shop.GetInstance().AddContent("红瓶");
        shop.GetInstance().AddContent("羽桦");
        shop.GetInstance().AddContent("蓝瓶");
        shop.GetInstance().AddContent("桂玫");

        shop.GetInstance().Open();
        LeftButtonClick();
    }
}
