using UnityEngine;
using System.Collections;
using UnityEngine.UI;
public class UIInstall : MonoBehaviour {
    Transform ButtonTra;
    Transform FunctionTra;
    UImove moveEvent;
    UIReturnButton Return;

    void Start () {
        ButtonTra = transform.FindChild("Button");
        FunctionTra = transform.FindChild("Function");

        ButtonTra.gameObject.SetActive(true);
        FunctionTra.gameObject.SetActive(true);

        Return = UIReturnButton.GetInstance();
        moveEvent = UImove.GetInstance();

        for(int i =0;i< ButtonTra.childCount;i++)
        {
            Transform go = ButtonTra.GetChild(i);
            Transform target = FunctionTra.FindChild(go.name.ToString()).transform;
            go.GetComponent<Button>().onClick.AddListener(delegate () { ChangeContentToFunction(target); });
            moveEvent.singleMove(target, -UICommon.ContentMoveDistance, 0.1f, false, false);
        }
    }

    void ChangeContentToFunction(Transform wangtoTarget)
    {
        moveEvent.ChangeContentToTarget(ButtonTra, wangtoTarget, UICommon.ContentMoveDistance, UICommon.MoveTime, false);
        Return.AddOnClikEvent(delegate () { ChangeContentToTarget(wangtoTarget); });   
    }

    void ChangeContentToTarget(Transform nowTarget)
    {
        moveEvent.ChangeContentToTarget(nowTarget, ButtonTra, UICommon.ContentMoveDistance, UICommon.MoveTime, false);
    }
    
}
