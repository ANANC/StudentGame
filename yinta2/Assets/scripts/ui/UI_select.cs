using UnityEngine;
using System.Collections;

public class UI_select : UI_page
{
    protected Transform content;
    protected int Index ;
    protected int AllInex;
	public override void Init () {
        ThisTransform = this.transform;
        content = ThisTransform.FindChild("content");
        AllInex = 4;
        if (UIcommon.loadsceneName == "start")
        {
            Index = 0;
            UIcommon.UIinit(ThisTransform);
            SelectShow(Index);
        }
        else
        {
            Index = AllInex - 1;
            base.Init();
        }
    }

    public override void DownArrow()
    {
        if (Index == AllInex - 1 && IsChange == false)
        {
            IsChange = true;
            UIcommon.UIselectbutton(ThisTransform, false);
            isRight = 0;
        }
        if (Index < AllInex)
        {
            SelectShow(Index + 1);
        }
    }

    public override void UpArrow()
    {
        if (Index > 0)
        {
            SelectShow(Index - 1);
        }
        if (Index == AllInex-1 && IsChange == true)
        {
            bool Isright = isRight == 1 ? true : false;
            UIcommon.UINotselectbutton(ThisTransform, Isright);
            IsChange = false;
            isRight = -1;
        }
    }

    public override void Return()
    {
        if (IsChange)
        {
            string name = isRight == 1 ? uiprefabName.set.ToString() : uiprefabName.newGame.ToString();
            Changepage(name, isRight == 0 ? false : true);
        }
    }

    void SelectShow(int index)
    {
        UIcommon.SetGameObjectAnimator(content.FindChild(Index.ToString()), false);
        if (index == AllInex)
            return;
        Index = IsChange? Index: index;
        UIcommon.SetGameObjectAnimator(content.FindChild(Index.ToString()), true);
    }
}
