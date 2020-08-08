using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class UIFileContronllor : MonoBehaviour
{
    public Transform File;
    public Transform fileManage;
    public Transform ContinnueGame;
    public Transform NewGame;

    UImove moveEvent;
    UIReturnButton Return;

    void Start()
    {
        for (int i = 0; i < fileManage.childCount; i++)
        {
            Transform go = fileManage.GetChild(i);
            go.GetComponent<Button>().onClick.AddListener(delegate () { ChangeContentToFile(go); });
        }
        ContinnueGame.GetComponent<Button>().onClick.AddListener(delegate () { ChangeContentToFile(ContinnueGame); });
        NewGame.GetComponent<Button>().onClick.AddListener(delegate () { ChangeContentToFile(NewGame); });

        moveEvent = UImove.GetInstance();
        Return = UIReturnButton.GetInstance();

        moveEvent.singleMove(File, UICommon.ContentMoveDistance, 0.1f,true,false);

    }

    void ChangeContentToFile(Transform target)
    {
        moveEvent.ChangeContentToTarget(target.parent, File, -UICommon.ContentMoveDistance, UICommon.MoveTime);
        Return.AddOnClikEvent(delegate () { ChangeContentToTarget(target.parent); });
        if (target.parent.name == "MainMenu")
            Return.setActive(true);
    }

    void ChangeContentToTarget(Transform target)
    {
        moveEvent.ChangeContentToTarget(File, target, -UICommon.ContentMoveDistance, UICommon.MoveTime);
        if (target.name == "MainMenu")
            Return.setActive(false);
    }

}
