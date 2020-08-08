using UnityEngine;
using System.Collections;
using DG.Tweening;
using UnityEngine.UI;
using UnityEngine.Events;
public class UIMenu : MonoBehaviour
{
    Transform mainMenu;
    Transform MenuContent;
    
    UImove moveEvent;
    UIReturnButton Return;
    void Start () {
        mainMenu = transform.FindChild("MainMenu");
        MenuContent = transform.FindChild("MenuContent");

        mainMenu.gameObject.SetActive(true);
        for(int i = 0;i<MenuContent.childCount;i++)
        {
            MenuContent.GetChild(i).gameObject.SetActive(false);
        }

        //继续游戏和开始界面加载文件页面，所以要跳过
        for (int i = 0; i < mainMenu.childCount; i++)
        {
            GameObject go = mainMenu.GetChild(i).gameObject;
            if (go.name == "ContinnueGame")
                continue;
            if (go.name == "NewGame")
                continue;
            Transform target = MenuContent.FindChild(go.name.ToString()).transform;
            go.GetComponent<Button>().onClick.AddListener(delegate () { ChangeContentToTarget(target);});
        }

        moveEvent = UImove.GetInstance();
        Return = UIReturnButton.GetInstance();
        moveEvent.singleMove(MenuContent, -UICommon.ContentMoveDistance, 0.1f,true, true);
    }
    

    public void ChangeContentToMune(Transform target)
    {
        moveEvent.ChangeContentToTarget(target, mainMenu, UICommon.ContentMoveDistance, UICommon.MoveTime);
        Return.setActive(false);
    }

    public void ChangeContentToTarget(Transform target)
    {
        moveEvent.ChangeContentToTarget(mainMenu, target, UICommon.ContentMoveDistance, UICommon.MoveTime);

        Return.AddOnClikEvent(delegate () { ChangeContentToMune(target); });
        Return.setActive(true);
    }
    
}
