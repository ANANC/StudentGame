using UnityEngine;
using System.Collections;
using UnityEngine.UI;
using DG.Tweening;

public class UImove : MonoBehaviour
{
    public Transform ContentBg;
    private static UImove _instance;
    public static UImove GetInstance()
    {
        if (_instance == null)
            _instance = GameObject.Find("Canvas").GetComponent<UImove>();
        return _instance;
    }
    
    public void ChangeContentToTarget(Transform nowTarget,Transform wanttoTarget,float distance,float time,bool IsYmove = true)
    {
        if (IsYmove)
        {
            ContentBg.DOLocalMoveY(ContentBg.localPosition.y - distance, time);
            nowTarget.DOLocalMoveY(nowTarget.localPosition.y - distance, time);
        }
        else
        {
            ContentBg.DOLocalMoveX(ContentBg.localPosition.x - distance, time);
            nowTarget.DOLocalMoveX(nowTarget.localPosition.x - distance, time);
        }

        StartCoroutine(Move(nowTarget, wanttoTarget, distance, time, IsYmove));
    }

    IEnumerator Move(Transform nowTarget, Transform wanttoTarget, float distance, float time, bool IsYmove = true)
    {
        yield return new WaitForSeconds(time);
        nowTarget.gameObject.SetActive(false);
        wanttoTarget.gameObject.SetActive(true);
        if (IsYmove)
        {
            ContentBg.DOLocalMoveY(ContentBg.localPosition.y + distance, time);
            wanttoTarget.DOLocalMoveY(wanttoTarget.localPosition.y + distance, time);
        }
        else
        {
            ContentBg.DOLocalMoveX(ContentBg.localPosition.x + distance, time);
            wanttoTarget.DOLocalMoveX(wanttoTarget.localPosition.x + distance, time);
        }
        
        yield break;
    }

    public void singleMove(Transform target, float endValue, float time, bool IsMoveY, bool IsActive, bool IsWait = false, float WaitTime = 0)
    {
        StartCoroutine(SingleMove(target,endValue,time,IsMoveY,IsActive, IsWait,WaitTime));
    }

    IEnumerator SingleMove(Transform target,float endValue,float time,bool IsMoveY,bool IsActive,bool IsWait = false,float WaitTime = 0)
    {
        if(IsWait)
            yield return new WaitForSeconds(WaitTime);

        if (IsActive)
            target.gameObject.SetActive(true);

        if (IsMoveY)
            target.DOLocalMoveY(target.localPosition.y + endValue, time);
        else
            target.DOLocalMoveX(target.localPosition.x + endValue, time);

        if (!IsActive)
        {
            yield return new WaitForSeconds(time);
            target.gameObject.SetActive(IsActive);
        }
    }
}
