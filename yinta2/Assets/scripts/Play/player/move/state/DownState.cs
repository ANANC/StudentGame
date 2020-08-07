using UnityEngine;
using System.Collections;

public class DownState : simpleState {
    DownHandle handle;
    public DownState():base()
    {
        myState = PlayerState.Dowing;
        handle = new DownHandle();
    }

    public override void GetInput(PlayerState state, KeyCode key, bool IsKeyup = false)
    {
        if (!IsThisState(state))
            return;

        PlayerState newState = myState;

        switch (key)
        {

            case KeyCode.LeftArrow:
                if(handle.IsJump())
                    handle.SetJumpX(-Right);
                break;

            case KeyCode.RightArrow:
                if (handle.IsJump())
                    handle.SetJumpX(Right);
                break;

            case KeyCode.UpArrow:
                newState = PlayerState.shinning;
                stateInstance.StateCommunicate(newState,key,IsKeyup);
                break;
        }

    }

    //protected override void manage()
    //{
    //    handle.Init();
    //    Do();
    //}

    public override IEnumerator DoMove()
    {
        float time = 0;
        float DownTime = gameCommon.canDownTime;
        bool IsStand = false;
        bool IsHang = false;
        handle.Init();
        while (time < DownTime)
        { 
            if (IsStop)
                break;

            if (IsRotate)
            {
                yield return handle.Rotating(IsRoteteDir_Right);
                IsRotate = false;
            }

            time += Time.deltaTime;
            Vector3 speed = handle.Move(time,out IsStand,out IsHang);
            stateInstance.Move(speed);
            
            if(IsStand)
            {//碰到地面
                stateInstance.StateCommunicate(PlayerState.Standing);
            }
            else if(IsHang)
            {
                stateInstance.StateCommunicate(PlayerState.hanging);
            }

            yield return 0;
        }
        if (!IsStand && time>=DownTime)
        {
            stateInstance.StateCommunicate(PlayerState.Death);
        }
        handle.DownXInit();
        handle.JumpXInit();
    }
}
