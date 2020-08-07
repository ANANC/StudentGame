using UnityEngine;
using System.Collections;

public class UI_game : UI_page
{
    int Index = 0;
    int Allindex = 2;
    static MonoBehaviour ower;
    public override void Init()
    {
        ThisTransform = this.transform;
        for (int i = 0; i < ThisTransform.childCount; i++)
        {
            UIcommon.SetGameObjectAnimator(ThisTransform.GetChild(i), false);
        }
        SpriteRenderenabled(false);
        ower = ThisTransform.GetComponent<MonoBehaviour>();
        LoadScene.loadoverEvent += loadover;
    }

    public override void LeftArrow() { }
    public override void RightArrow() { }

    public override void DownArrow()
    {
        if(Index==0)
        {
            SelectShow(Index + 1);
        }
    }

    public override void UpArrow()
    {
        if (Index ==Allindex-1)
        {
            SelectShow(Index - 1);
        }
    }

    public override void Return()
    {
        if(Index == 0)
        {
            SpriteRenderenabled(false);
        }
        else
        {
            UIcommon.loadsceneName = "start";
            LoadScene.loadScene("start");
            LoadScene.Loadin();
        }
    }

    public override void OtherKeydown()
    {
        if(Input.GetKeyDown(KeyCode.Escape))
        {
            SpriteRenderenabled(true);
            SelectShow(Index);
        }
    }

    void SelectShow(int index)
    {
        UIcommon.SetGameObjectAnimator(ThisTransform.GetChild(Index), false);
        Index = index;
        UIcommon.SetGameObjectAnimator(ThisTransform.GetChild(Index), true);
    }

    void SpriteRenderenabled(bool b)
    {
        ThisTransform.GetComponent<SpriteRenderer>().enabled = b;
        for(int i = 0;i<ThisTransform.childCount;i++)
            ThisTransform.GetChild(i).GetComponent<SpriteRenderer>().enabled = b;
    }

    public static void startCoroutine(IEnumerator ienumerator)
    {
        ower.StartCoroutine(ienumerator);
    }

    void loadover()
    {
        //并不做什么事情，不让加载完成事件为空而已。
    }
}
