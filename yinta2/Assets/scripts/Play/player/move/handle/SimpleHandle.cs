using UnityEngine;
using System.Collections;

public class SimpleHandle //: MonoBehaviour {
{ 
    protected Transform Standobject;
    protected float StandobjectRance;
    protected moveMessage MoveMessage;
    
    public SimpleHandle()
    {
        MoveMessage = gameCommon.moveMessageGetInstance;
    }

    public virtual void Init(){}
    public virtual Vector3 Init(Transform tra) { return Vector3.zero; }
    protected virtual void UpdateObject(Transform tra) { }

    public virtual bool IsCando(out Vector3 pos)
    {
        pos = Vector3.zero;
        return false;
    }

    public virtual Vector3 DoOut()
    {
        return Vector3.zero;
    }
    public virtual bool DoOut(Vector3 v,out Vector3 ov)
    {
        ov = Vector3.zero;
        return false;
    }

    public void SetJumpXTrue(Vector3 dir)
    {
        MoveMessage.JumpXTrue(dir);
    }

    public void SetDownXTrue(Vector3 dir)
    {
        MoveMessage.DownXTrue(dir);
    }

    public void SetJumpX(Vector3 dir)
    {
        MoveMessage.SetJumpAngle(dir);
    }

    public void DownXInit()
    {
        MoveMessage.DownXInit();
    }

    public void JumpXInit()
    {
        MoveMessage.JumpXInit();
    }

    public void downxpowerInit()
    {
        MoveMessage.downxPowerInit();
    }

    public void ChangeJumpstate(PlayerState state)
    {
        MoveMessage.ChangJumpstate(state);
        
    }

    public IEnumerator Rotating(bool IsRight)
    {
        yield return gameCommon.FollowcameraInstance.SetRotate(IsRight);
    }

    public bool IsCanMove_Direction(Vector3 dir)
    {
        bool b = false;
        RaycastHit hit;
        if (moveCommon.PlayerRaycast(Vector3.zero,dir, out hit, 1) == RaycastLay.Notthing)
            if (moveCommon.PlayerRaycast(Vector3.zero,-dir, out hit, 1) == RaycastLay.Notthing)
                b = true;
        return b;
    }

    public Vector3 StandOn()
    {
        return moveCommon.StandOn();
    }
}
