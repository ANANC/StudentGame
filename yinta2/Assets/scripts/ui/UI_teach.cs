using UnityEngine;
using System.Collections;

public class UI_teach : UI_about {
    Transform content;
    int Index = 0;
    int Allindex = 5;
    bool IsMoving = false;
    float distance = 22;
    public override void Init()
    {
        ThisTransform = this.transform;
        content = ThisTransform.FindChild("content");
        isRight = 0;
        IsChange = true;
        UIcommon.UIselectbutton(ThisTransform, false);
    }

    public override void Return()
    {
        if(!IsMoving)
        {
            StartCoroutine(Domove(isRight==0? false:true));
        }
    }

    IEnumerator Domove(bool IsRight)
    {
        IsMoving = true;

        UIcommon.UINotselectbutton(ThisTransform, IsRight);

        int nextIndex = IsRight ? Index + 1:Index - 1;
        nextIndex = nextIndex < 0 ? Allindex - 1 : nextIndex == Allindex ? 0 : nextIndex;
        Vector3 pos = IsRight ? new Vector3(-distance, 0, 0) : new Vector3(distance, 0, 0);

        Transform Now = content.GetChild(Index);
        Transform Next = content.GetChild(nextIndex);
        Next.localPosition = Now.localPosition + pos;

        float move = 0;
        Vector3 speed = IsRight? Vector3.right:-Vector3.right;
        while(move<distance)
        {
            Now.localPosition += speed;
            Next.localPosition += speed;
            move += 1;
            yield return new WaitForSeconds(0.1f);
        }
        Index = nextIndex;
        IsMoving = false;

        UIcommon.UIselectbutton(ThisTransform, IsRight);
    }

    public override void OtherKeydown()
    {
        if(Input.GetKeyDown(KeyCode.A))
        {
            StartCoroutine(loadover());
        }
    }

    IEnumerator loadover()
    {
        yield return new WaitForSeconds(0.1f);
        playerMove.IsDomove = true;
        ThisTransform.gameObject.SetActive(false);
    }

}
