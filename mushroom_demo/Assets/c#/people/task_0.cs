using UnityEngine;
using System.Collections;

/*--------------------基础任务0-------------------------*/
public class task_0 : task {
    public task_0() : base("基础任务0")
    {
        experience = 50;
        money = 100;
        AccpectGrade = 1;
        InitContent();
    }

    protected override void InitContent()
    {
        string notaccepte = "HI~好久不见啊。现在世界不安全啊。快把背包里的药放到快捷键吧~\n（左键按着拉动到快捷键即可）";
        string accepte = "快放吧。";
        string over = "真不错呢！\n(获得红瓶*5，红菇*5，经验值*"+experience+"，金钱*"+money+")";

        content.Add(task_state.NotAccept,notaccepte);
        content.Add(task_state.Accept,accepte);
        content.Add(task_state.Over,over);
    }

    protected override bool CheckCanAccept()
    {
        if (attribute.GetInstance().Grade >= 1)
        {
            return true;
        }
        return false;
    }

    protected override bool CheckCanOver()
    {
        if (true)
        {
            return true;
        }
            
        return false;
    }

    protected override void GetReward()
    {
        for (int i = 0; i < 5; i++)
        {
            propManager.GetInstance().AddProp("红瓶");
            propManager.GetInstance().AddProp("红菇");
        }
        attribute.GetInstance().AddExperience(experience);
        attribute.GetInstance().AddMoney(money);
    }
}
/*--------------------基础任务0-------------------------*/


/*--------------------基础任务1-------------------------*/
public class task_1 : task
{
    public task_1()
        : base("基础任务1")
    {
        experience = 80;
        money = 500;
        AccpectGrade = 1;
        InitContent();
    }

    protected override void InitContent()
    {
        string notaccepte = "能不能帮我去找点石螺回来？请说熊会掉落。记得是要先点击对象，有了黑圈后按R喔！\n(提交：1个石螺)";
        string accepte = "拜托你了！";
        string over = "谢谢你！\n(获得红瓶*3，蓝瓶*3，阳玉*1，经验值*" + experience + "，金钱*" + money + ")";

        content.Add(task_state.NotAccept, notaccepte);
        content.Add(task_state.Accept, accepte);
        content.Add(task_state.Over, over);
    }

    protected override bool CheckCanAccept()
    {
        if (taskManager.GetInstance().FindState("基础任务0")== task_state.Remove)
        {
            return true;
        }
        return false;
    }

    protected override bool CheckCanOver()
    {
        if (propManager.GetInstance().GetPossesstionNunber("石螺")>=1)
        {
            propManager.GetInstance().UsedProp("石螺", "prop");
            return true;
        }

        return false;
    }

    protected override void GetReward()
    {
        for (int i = 0; i < 3; i++)
        {
            propManager.GetInstance().AddProp("红瓶");
            propManager.GetInstance().AddProp("蓝瓶");
        }
        propManager.GetInstance().AddProp("阳玉");
        attribute.GetInstance().AddExperience(experience);
        attribute.GetInstance().AddMoney(money);
    }

    public override void RenderTip()
    {
        int munber = propManager.GetInstance().GetPossesstionNunber("石螺");
        string tip = "基础任务1：提交"+munber+"/1个石螺";
        attribute.GetInstance().AddTaskText("基础任务1", tip);
    }
    public override void StopRenderTip()
    {
        string tip = "";
        attribute.GetInstance().AddTaskText("基础任务1", tip, false);
    }
}
/*--------------------基础任务1-------------------------*/



/*--------------------基础任务2-------------------------*/
public class task_2 : task
{
    public task_2()
        : base("基础任务2")
    {
        experience = 10;
        money = 50;
        AccpectGrade = 1;
        InitContent();
    }

    protected override void InitContent()
    {
        string notaccepte = "你是谁！不要靠近我！\n（提供一个红瓶）";
        string accepte = "走开！";
        string over = "好吧。。我告诉你吧。。我是吃错东西了！\n(获得星钩*3，肥祥*3，丽菊*1，经验值*" + experience + "，金钱*" + money + ")";

        content.Add(task_state.NotAccept, notaccepte);
        content.Add(task_state.Accept, accepte);
        content.Add(task_state.Over, over);
    }

    protected override bool CheckCanAccept()
    {

        if (attribute.GetInstance().Grade >= 1)
        {
            return true;
        }
        return false;
    }

    protected override bool CheckCanOver()
    {
        if (propManager.GetInstance().GetPossesstionNunber("红瓶") >= 1)
        {
            propManager.GetInstance().UsedProp("红瓶", "prop");
            return true;
        }

        return false;
    }

    protected override void GetReward()
    {
        for (int i = 0; i < 3; i++)
        {
            propManager.GetInstance().AddProp("星钩");
            propManager.GetInstance().AddProp("肥祥");
        }
        propManager.GetInstance().AddProp("丽菊");
        attribute.GetInstance().AddExperience(experience);
        attribute.GetInstance().AddMoney(money);
    }

    public override void RenderTip()
    {
        int munber = propManager.GetInstance().GetPossesstionNunber("红瓶");
        string tip = "基础任务2：提交" + munber + "/1个红瓶";
        attribute.GetInstance().AddTaskText("基础任务2", tip);
    }
    public override void StopRenderTip()
    {
        string tip = "";
        attribute.GetInstance().AddTaskText("基础任务2", tip,false);
    }
}
/*--------------------基础任务2-------------------------*/

/*--------------------基础任务3-------------------------*/
public class task_3 : task
{
    GameObject pig;

    public task_3()
        : base("基础任务3")
    {
        experience = 10;
        money = 1000;
        AccpectGrade = 1;
        InitContent();

        pig = GameObject.Find("pig");
        pig.SetActive(false);
    }

    protected override void InitContent()
    {
        string notaccepte = "我本来是个人，吃错蘑菇变成猪了。。能不能拜托你帮我变回人啊？";
        string accepte = "走开！";
        string over = "你真是太好了！谢谢你！但你不会是骗我哒，然后带走我吃掉我吧。。\n(获得郁米*2，桂玫*1，经验值*" + experience + "，金钱*" + money + ")";

        content.Add(task_state.NotAccept, notaccepte);
        content.Add(task_state.Accept, accepte);
        content.Add(task_state.Over, over);
    }

    protected override bool CheckCanAccept()
    {
        if (taskManager.GetInstance().FindState("基础任务2") == task_state.Remove)
        {
            return true;
        }
        return false;
    }

    protected override bool CheckCanOver()
    {
        if (true)
        {
            return true;
        }

        return false;
    }

    protected override void GetReward()
    {

        propManager.GetInstance().AddProp("桂玫");
        for (int i = 0; i < 2;i++ )
            propManager.GetInstance().AddProp("郁米");
        attribute.GetInstance().AddExperience(experience);
        attribute.GetInstance().AddMoney(money);

        pig.SetActive(true);
    }
}
/*--------------------基础任务3-------------------------*/

/*--------------------基础任务4-------------------------*/
public class task_4 : task
{
    public task_4()
        : base("基础任务4")
    {
        experience = 10;
        money = 300;
        AccpectGrade = 2;
        InitContent();

    }

    protected override void InitContent()
    {
        string notaccepte = "额。。为什么有只猪跟着你啊？好吧，你想要知道些什么的话，你就去找后面屋子的流浪汉吧。他会知道些什么的";
        string accepte = "？";
        string over = "没事没事。去吧。这些给你，希望能帮到你。\n(获得羽桦*4，蓝瓶*4，石之十*1，萎蜜*1，经验值*" + experience + "，金钱*" + money + ")";

        content.Add(task_state.NotAccept, notaccepte);
        content.Add(task_state.Accept, accepte);
        content.Add(task_state.Over, over);
    }

    protected override bool CheckCanAccept()
    {
        if (taskManager.GetInstance().FindState("基础任务3") == task_state.Remove)
        {
            return true;
        }
        return false;
    }

    protected override bool CheckCanOver()
    {
        if (true)
        {
            return true;
        }

        return false;
    }

    protected override void GetReward()
    {
        propManager.GetInstance().AddProp("萎蜜");
        propManager.GetInstance().AddProp("石之十");
        for (int i = 0; i < 4; i++)
        {
            propManager.GetInstance().AddProp("羽桦");
            propManager.GetInstance().AddProp("蓝瓶");
        }
        for (int i = 0; i < 10; i++)
        {
            propManager.GetInstance().AddProp("决角");
        }
        attribute.GetInstance().AddExperience(experience);
        attribute.GetInstance().AddMoney(money);

    }
}
/*--------------------基础任务4-------------------------*/


/*--------------------基础任务4-------------------------*/
public class task_5 : task
{
    public task_5()
        : base("基础任务5")
    {
        experience = 100;
        AccpectGrade = 2;
        InitContent();

    }

    protected override void InitContent()
    {
        string notaccepte = "哈哈哈，这猪好蠢的感觉。我知道他是人啦。去吧，帮我找点决角，我就告诉你。（提交5个决角，决角会在猴子身上掉落）";
        string accepte = "这么少不行啊！";
        string over = "拿着我给的东西去找后面那对情侣就好了。\n(获得红菇*10，星钩*1，经验值*" + experience + ")";

        content.Add(task_state.NotAccept, notaccepte);
        content.Add(task_state.Accept, accepte);
        content.Add(task_state.Over, over);
    }

    protected override bool CheckCanAccept()
    {
        if (taskManager.GetInstance().FindState("基础任务4") == task_state.Remove)
        {
            return true;
        }
        return false;
    }

    protected override bool CheckCanOver()
    {
        if (propManager.GetInstance().GetPossesstionNunber("决角") >= 5)
        {
            propManager.GetInstance().UsedProp("决角", "prop");
            return true;
        }

        return false;
    }

    protected override void GetReward()
    {
        propManager.GetInstance().AddProp("星钩");
        for (int i = 0; i < 10; i++)
        {
            propManager.GetInstance().AddProp("红菇");
        }
        attribute.GetInstance().AddExperience(experience);

    }

    public override void RenderTip()
    {
        int munber = propManager.GetInstance().GetPossesstionNunber("决角");
        string tip = "基础任务5：提交" + munber + "/5个决角";
        attribute.GetInstance().AddTaskText("基础任务5", tip);
    }
    public override void StopRenderTip()
    {
        string tip = "";
        attribute.GetInstance().AddTaskText("基础任务5", tip, false);
    }
}
/*--------------------基础任务5-------------------------*/


/*--------------------基础任务6-------------------------*/
public class task_6 : task
{
    public task_6()
        : base("基础任务6")
    {
        experience = 100;
        AccpectGrade = 2;
        InitContent();

    }

    protected override void InitContent()
    {
        string notaccepte = "他会帮你真是少见。来吧，把红菇给我吧。";
        string accepte = "要多点才行！";
        string over = "恭喜你和你的猪！可以了。";

        content.Add(task_state.NotAccept, notaccepte);
        content.Add(task_state.Accept, accepte);
        content.Add(task_state.Over, over);
    }

    protected override bool CheckCanAccept()
    {
        if (taskManager.GetInstance().FindState("基础任务5") == task_state.Remove)
        {
            return true;
        }
        return false;
    }

    protected override bool CheckCanOver()
    {
        if (propManager.GetInstance().GetPossesstionNunber("红菇") >= 10)
        {
            propManager.GetInstance().UsedProp("红菇", "prop");
            return true;
        }

        return false;
    }

    protected override void GetReward()
    {
        attribute.GetInstance().AddExperience(experience);
    }

    public override void RenderTip()
    {
        int munber = propManager.GetInstance().GetPossesstionNunber("红菇");
        string tip = "基础任务6：提交" + munber + "/10个红菇";
        attribute.GetInstance().AddTaskText("基础任务6", tip);
    }
    public override void StopRenderTip()
    {
        string tip = "";
        attribute.GetInstance().AddTaskText("基础任务6", tip, false);
    }
}
/*--------------------基础任务6-------------------------*/