using UnityEngine;
using System.Collections;

public class UI_newGame : UI_page
{
    protected Transform text;
    static bool IsFirst = true;
    public override void Init()
    {
        ThisTransform = this.transform;
        text = ThisTransform.FindChild("text");
        if (IsFirst)
        {
            UIcommon.UIinit(ThisTransform);
            IsFirst = false;
        }
        else
        {
            UIcommon.SetGameObjectAnimator(text, false);
            base.Init();
        }
    }

    public override void LeftArrow()
    {
        if(isRight == -1)
        {
            UIcommon.SetGameObjectAnimator(text, false);
            UIcommon.UIselectbutton(ThisTransform, false);
            isRight = 0;
        }
        if(isRight == 1)
        {
            UIcommon.SetGameObjectAnimator(text, true);
            UIcommon.UINotselectbutton(ThisTransform, true);
            isRight = -1;
        }
    }

    public override void RightArrow()
    {
        if (isRight == -1)
        {
            UIcommon.SetGameObjectAnimator(text, false);
            UIcommon.UIselectbutton(ThisTransform, true);
            isRight = 1;
        }
        if (isRight == 0)
        {
            UIcommon.SetGameObjectAnimator(text, true);
            UIcommon.UINotselectbutton(ThisTransform,false);
            isRight = -1;
        }
    }

    public override void Return()
    {
        if (isRight != -1)
        {
            IsChange = true;
            string name = isRight == 1 ? uiprefabName.select.ToString() : uiprefabName.exit.ToString();
            Changepage(name, isRight == 0 ? false : true);
        }
        else
        {
            UIcommon.loadsceneName = "00";
            UIcommon.GetPrefab(prefabType.ui, uiprefabName.load.ToString());
            Destroy(ThisTransform.gameObject);
        }
    }

}
