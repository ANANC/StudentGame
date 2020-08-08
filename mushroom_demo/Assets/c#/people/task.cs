using UnityEngine;
using System.Collections;
using System.Collections.Generic;
public enum task_state
{
    CanNotAccept,
    NotAccept,
    Accept,
    Over,
    Remove
}
public class task  {
    protected task_state state;
    protected Dictionary<task_state, string> content;
    protected string name;
    protected int experience;
    protected int money;
    protected int AccpectGrade;

    protected task(string s)
    {
        content = new Dictionary<task_state, string>();
        name = s;
        state = task_state.CanNotAccept;
    }

    public task_state State
    {
        set
        {
            state = value;
        }
        get
        {
            return state;
        }
    }

    protected virtual void InitContent() { }
    protected virtual bool CheckCanOver() { return false; }
    protected virtual void GetReward() { }
    protected virtual bool CheckCanAccept() { return false; }

    public virtual void RenderTip() { }
    public virtual void StopRenderTip() { }

    public string GetContent(task_state t)
    {
        return content[t];
    }

    public string Name
    {
        get
        {
            return name;
        }
    }

    public int Experienct
    {
        get
        {
            return experience;
        }
    }

    public int accpectGrade
    {
        get
        {
            return AccpectGrade;
        }
    }

    public task_state TaskJudge(task_state t)
    {
        task_state b = t;
        if (state == task_state.CanNotAccept)
        {
            if (CheckCanAccept())
            {
                b = task_state.NotAccept;
                return b;
            }
        }
        if (state == task_state.NotAccept)
        {
            b = task_state.Accept;
            return b;
        }
        if (state == task_state.Accept)
        {
            if (CheckCanOver())
            {
                b = task_state.Over;
                return b;
            }
        }
        if(state == task_state.Over)
        {
            GetReward();
            b = task_state.Remove;
            return b;
        }
        if (state == task_state.Remove)
        {
            b = task_state.Remove;
            return b;
        }
        return b;
    }

}
