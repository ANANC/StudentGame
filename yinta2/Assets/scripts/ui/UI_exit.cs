using UnityEngine;
using System.Collections;

public class UI_exit : UI_newGame
{
    public override void Init()
    {
        ThisTransform = this.transform;
        text = ThisTransform.FindChild("text");
        UIcommon.SetGameObjectAnimator(text, false);
        base.Init();
    }

    public override void Return()
    {
        if (isRight != -1)
        {
            IsChange = true;
            string name = isRight == 1 ? uiprefabName.newGame.ToString() : uiprefabName.about.ToString();
            Changepage(name, isRight == 0 ? false : true);
        }
    }
}
