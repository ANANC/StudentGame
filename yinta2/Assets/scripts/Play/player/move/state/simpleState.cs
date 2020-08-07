using UnityEngine;
using System.Collections;

public class simpleState
{

    protected playerStateControllor stateInstance;
    protected PlayerState myState;
    protected bool IsStop;
    protected Vector3 Right;
    protected Vector3 Forward;
    protected Vector3 Up;
    protected bool IsRotate;
    protected bool IsRoteteDir_Right;

    public simpleState() {
        stateInstance = gameCommon.playerStateControllorGetInstance;
        IsRotate = false;
        gameCommon.directionupdateEvent += UpdateDir;
        UpdateDir();
        
    }

    public virtual void GetInput(PlayerState state, KeyCode key, bool IsKeyup = false) {}

    public virtual void GetInput(PlayerState state) {
        if (!IsThisState(state))
            return;

        manage();
    }

    protected virtual void manage() { Do(); }
    protected void  Do() {
        IsStop = false;
        IsRotate = false;
        stateInstance.IsSureState(true);
        stateInstance.ToStartCoroutine(DoMove());
    }

    public virtual IEnumerator DoMove() {
        yield break; }

    public void Stop() {
        IsStop = true;
    }

    protected void GetStopevent(PlayerState state)
    {
        if (!IsThisState(state))
            return;
        Stop();
    }

    protected bool IsThisState(PlayerState state)
    {
        bool b = myState == state ? true:false;
        return b;
    }

    protected virtual void UpdateDir()
    {
        Right = gameCommon.Right;
        Forward = gameCommon.Forward;
        Up = gameCommon.Up;
    }
    
    public void RotateInit(bool IsRight)
    {
        IsRotate = true;
        IsRoteteDir_Right = IsRight;
    }

    
}
