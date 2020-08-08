using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public enum npc_state
{
    sleep
}

public abstract class npc : MonoBehaviour
{
    public GameObject npcGameObject;

    protected bool IsClickDialogSelectTextButton;
    protected GameObject TipGameObject;

    protected task Task;

    protected npc_state npcState;
    protected string sleepTell;
    protected string withPlayerTell;

    protected bool IsNeedShop;

    protected void Init()
    {
        IsClickDialogSelectTextButton = false;
        
        npcState = npc_state.sleep;
        TipGameObject = GameObject.Instantiate((GameObject)Resources.Load("Prefab/task/question"));
        TipGameObject.transform.position = transform.position + new Vector3(0.12f, 0.5f, 0);
        IsTipGameObjectRender(false);
    }


    protected void IsTipGameObjectRender(bool b)
    {
        TipGameObject.SetActive(b);
    }


    protected virtual void TextInit(){}

    public void CanGetNowTask(task t )
    {
        Task = t;
        Task.State = Task.TaskJudge(Task.State);
        IsTipGameObjectRender(true);
    }

    public void LeftButtonClick()
    {
        DialogBox.GetInstance().LeftButtonClick(IsClickDialogSelectTextButton);

        IsClickDialogSelectTextButton = false;
        if (Task == null || Task.State != task_state.NotAccept)
            IsTipGameObjectRender(false);
    }

    public void TextButtonClick()
    {
        string TextButton;
        if (Task == null)
        {
            TextButton = withPlayerTell;
        }
        else
        {
            if (Task.State == task_state.Accept)
                Task.State = Task.TaskJudge(Task.State);
            TextButton = Task.GetContent(Task.State);
            if (Task.State == task_state.NotAccept || Task.State == task_state.Over)
                Task.State = Task.TaskJudge(Task.State);
            
            Task.RenderTip();
        }
        DialogBox.GetInstance().TextButtonClick(TextButton);

        IsClickDialogSelectTextButton = true;
        
    }

    public virtual void ShopButtonClick() { }

    protected void Update()
    {
        switch (npcState)
        {
            case npc_state.sleep:
                if (Input.GetMouseButtonDown(0))
                {
                    Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition);
                    RaycastHit hit;
                    if (Physics.Raycast(ray, out hit, 100))
                    {
                        if (hit.collider.gameObject == this.gameObject)
                        {
                            TextInit();
                            return;
                        }
                    }
                }
                return;
        }

    }

}
