using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class inform
{
    public inform(bool b,task t)
    {
        isInform = b;
        TASK = t;
    }
    bool isInform;
    task TASK;
    public bool Isinform
    {
        get
        {
            return isInform;
        }
        set
        {
            isInform = value;
        }
    }
    public task Task
    {
        get
        {
            return TASK;
        }
        set
        {
            TASK = value;
        }
    }
}

public class taskManager : MonoBehaviour
{
    Dictionary<task, npc> Task;
    Dictionary<task, npc> AccpectGradeTask;
    Dictionary<npc, inform> CanAcceptTask;
    List<npc> RemoveTask;

    float time;

    //npc
    npc drugstore;//药店老板娘
    npc pig;//猪
    npc girl;//女
    npc man;//流浪汉
    npc man2;//男

    static taskManager instance;

    void Awake()
    {
        instance = this;
    }

    void Start()
    {
        time = 0;

        Task = new Dictionary<task, npc>();
        RemoveTask = new List<npc>();
        CanAcceptTask = new Dictionary<npc, inform>();
        AccpectGradeTask = new Dictionary<task, npc>();

        drugstore = npc_0.Instance;
        pig = npc_1.Instance;
        girl = npc_2.Instance;
        man = npc_3.Instance;
        man2 = npc_4.Instance;

        InitTask();
        UpdateAccpectGradeTask();
    }

    public static taskManager GetInstance()
    {
        return instance;
    }


    void InitTask()
    {
        task t = new task_0();
        Task.Add(t, drugstore);
        t = new task_1();
        Task.Add(t, drugstore);
        t = new task_2();
        Task.Add(t, pig);
        t = new task_3();
        Task.Add(t, pig);
        t = new task_4();
        Task.Add(t, girl);
        t = new task_5();
        Task.Add(t, man);
        t = new task_6();
        Task.Add(t, man2);
    }

    public task_state FindState(string s)
    {
        foreach(KeyValuePair<task,npc> k in Task)
        {
            if (k.Key.Name == s)
                return k.Key.State;
        }
        return task_state.CanNotAccept;
    }

    public void UpdateTasktip()
    {
        if (CanAcceptTask.Count != 0)
        {
            foreach (KeyValuePair<npc, inform> k in CanAcceptTask)
            {
                if (k.Value.Task.State == task_state.Accept)
                    k.Value.Task.RenderTip();
            }
        }
    }

    public void UpdateAccpectGradeTask()
    {
        int grade = attribute.GetInstance().Grade;
        foreach (KeyValuePair<task, npc> k in Task)
        {
            if (k.Key.State == task_state.Remove)
                continue;
            if (k.Key.accpectGrade > grade)
                continue;
            if (AccpectGradeTask.ContainsKey(k.Key))
                continue;
            AccpectGradeTask.Add(k.Key, k.Value);
        }
    }

    void Update()
    {
        time += Time.deltaTime;
        if (time < 1)
            return;
        time = 0;

        foreach (KeyValuePair<task, npc> k in AccpectGradeTask)
        {
            if (CanAcceptTask.ContainsKey(k.Value) == true)
                continue;
            if( k.Key.TaskJudge(k.Key.State)== task_state.NotAccept)
            {
                CanAcceptTask.Add(k.Value, new inform(false, k.Key));
            }
        }


        if(CanAcceptTask.Count!=0)
        {
            foreach(KeyValuePair<npc,inform> k in CanAcceptTask)
            {
                if (k.Value.Isinform == true)
                {
                    //k.Value.Task.RenderTip();
                    if (k.Value.Task.State == task_state.Remove)
                    {
                        k.Value.Task.StopRenderTip();
                        RemoveTask.Add(k.Key);
                    }
                    continue;
                }
                else
                {
                    k.Key.CanGetNowTask(k.Value.Task);
                    k.Value.Isinform = true;
                }
            }
        }

        if(RemoveTask.Count!=0)
        {
            foreach(npc n in RemoveTask)
            {
                AccpectGradeTask.Remove(CanAcceptTask[n].Task);
                CanAcceptTask.Remove(n);
            }
        }
        RemoveTask.Clear();


    }
}
