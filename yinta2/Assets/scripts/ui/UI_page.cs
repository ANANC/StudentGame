using UnityEngine;
using System.Collections;

public class UI_page : MonoBehaviour
{
    protected Transform ThisTransform;
    protected bool IsChange = false;
    protected int isRight = -1;

    public void Start()
    {
        Init();
    }

    public void Update()
    {
        if (Input.GetKeyDown(KeyCode.DownArrow))
        {
            DownArrow();
        }
        if (Input.GetKeyDown(KeyCode.UpArrow))
        {
            UpArrow();
        }
        if (Input.GetKeyDown(KeyCode.LeftArrow))
        {
            LeftArrow();
        }
        if (Input.GetKeyDown(KeyCode.RightArrow))
        {
            RightArrow();
        }
        if (Input.GetKeyDown(KeyCode.Return))
        {
            Return();
        }
        OtherKeydown();
    }

    public virtual void Init() {
        isRight = UIcommon.IsMoveTorightpage ? 1 : 0;
        UIcommon.UIselectbutton(ThisTransform, isRight == 1 ? true : false);
        IsChange = true;
    }
    public virtual void UpArrow() { }
    public virtual void DownArrow() { }
    public virtual void LeftArrow()
    {
        SelectLeftbutton();
    }
    public virtual void RightArrow()
    {
        SelectRightbutton();
    }
    public void SelectLeftbutton()
    {
        if (IsChange && isRight == 1)
        {
            UIcommon.UIselectbutton(ThisTransform, false);
            isRight = 0;
        }
    }
    public void SelectRightbutton()
    {
        if (IsChange && isRight == 0)
        {
            UIcommon.UIselectbutton(ThisTransform, true);
            isRight = 1;
        }
    }
    public virtual void Return() { }
    public void Changepage(string name,bool IsMoveToRight)
    {
        if (IsChange)
        {
            UIcommon.IsMoveTorightpage = IsMoveToRight;
            UIcommon.GetPrefab(prefabType.ui, name);
            Destroy(ThisTransform.gameObject);
        }
    }

    public virtual void OtherKeydown() { }

}
