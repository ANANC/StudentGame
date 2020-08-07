using UnityEngine;
using System.Collections;

public class UI_about : UI_page
{
    public override void Init()
    {
        ThisTransform = this.transform;
        base.Init();
    }

    public override void DownArrow() { }
    public override void UpArrow() { }

    public override void Return()
    {
        bool Isright = isRight == 1 ? true : false;
        string name = Isright ? uiprefabName.exit.ToString() : uiprefabName.set.ToString();
        Changepage(name, isRight == 0 ? false : true);
    }
}
