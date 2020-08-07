using UnityEngine;
using System.Collections;

public class MoveState : simpleState {

    MoveHandle1 handle;
    Vector3 dir;
    bool IsRight;
    bool IsMove;
   // Vector3 initPos;
    public MoveState():base()
    {
        myState = PlayerState.Moving;
        handle = new MoveHandle1();
        dir = Vector3.zero;
        IsStop = false;
        IsMove = false;
    }

    public override void GetInput(PlayerState state, KeyCode key, bool IsKeyup = false)
    {
        if (!IsThisState(state))
            return;
        PlayerState newState = myState;

        switch (key)
        {
            case KeyCode.LeftArrow:
                IsRight = false;
                if (!IsMove)
                {
                    //if(handle.IsCando(out initPos))
                    //    manage();
                    //else
                    //{
                    //    newState = PlayerState.Dowing;
                    //    stateInstance.StateCommunicate(newState);
                    //}
                    manage();
                }
                if (IsKeyup)
                {
                    newState = PlayerState.Standing;
                    stateInstance.StateCommunicate(newState);
                }
                break;

            case KeyCode.RightArrow:
                IsRight = true;
                if (!IsMove)
                {
                    //Vector3 pos;
                    //if (handle.IsCando(out pos))
                    //    manage();
                    //else
                    //{
                    //    newState = PlayerState.Dowing;
                    //    stateInstance.StateCommunicate(newState);
                    //}
                    manage();
                }
                if (IsKeyup)
                {
                    newState = PlayerState.Standing;
                    stateInstance.StateCommunicate(newState);
                }
                break;

            case KeyCode.Space:
                handle.SetJumpXTrue(dir);
                newState = PlayerState.Jump;
                stateInstance.StateCommunicate(newState);
                break;
        }
    }

    public override void GetInput(PlayerState state)
    {
        if (!IsThisState(state))
            return;

        stateInstance.IsSureState(false);
        Debug.Log("moveState不接受这样的通讯！");

    }

    protected override void manage()
    {
        IsMove = true;
        base.manage();
    }

    public override IEnumerator DoMove()
    {
        bool IsDown;
        Vector3 speed;
        //stateInstance.Move(initPos);
        while (true)
        {
            if (IsRotate)
            {
                stateInstance.Move(handle.StandOn());
                yield return handle.Rotating(IsRoteteDir_Right);
                IsRotate = false;
            }

            dir = IsRight ? Right : -Right;
            speed = handle.Move(dir,IsRight, out IsDown);
            stateInstance.Move(speed);

            if (IsDown)
            {
                handle.SetDownXTrue(dir);
                stateInstance.StateCommunicate(PlayerState.Dowing);
            }

            if (IsStop)
                break;

            yield return 0;
        }
        IsMove = false;
        handle.downxpowerInit();
    }
    
}
