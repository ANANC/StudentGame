using UnityEngine;
using System.Collections;

public class HangState : simpleState {

    HangHandle handle;
    Vector3 initPos;
    Vector3 dir;
    bool IsRight;
    bool IsDoMove;
    bool IsDoOut;


    public HangState():base()
    {
        myState = PlayerState.hanging;
        handle = new HangHandle();
        IsDoMove = false;
        IsDoOut = false;
    }

    public override void GetInput(PlayerState state, KeyCode key, bool IsKeyup = false)
    {
        if (!IsThisState(state))
            return;

        PlayerState newState = myState;

        switch (key)
        {
            case KeyCode.LeftArrow:
                dir = -Right;
                IsRight = false;
                IsDoMove = true;
                break;

            case KeyCode.RightArrow:
                dir = Right;
                IsRight = true;
                IsDoMove = true;
                break;

            case KeyCode.DownArrow:
                newState = PlayerState.Dowing;
                stateInstance.StateCommunicate(newState);
                break;

            case KeyCode.UpArrow:
                IsDoOut = true;
                newState = PlayerState.Standing;
                stateInstance.StateCommunicate(newState);
                break;

            case KeyCode.Space:
                newState = PlayerState.Dowing;
                stateInstance.StateCommunicate(newState);
                break;
        }

    }

    public override void GetInput(PlayerState state)
    {
        if (!IsThisState(state))
            return;

        handle.GetNowstate(stateInstance.GetState());
        if (handle.IsCando(out initPos))
            manage();
        else
            stateInstance.IsSureState(false);
    }

    protected override void manage()
    {
        IsDoMove = false;
        IsDoOut = false;
        Do();
    }

    public override IEnumerator DoMove()
    {
        stateInstance.Move(initPos);
        yield return 0;
        while (true)
        {
            if (IsRotate)
            {
                yield return handle.Rotating(IsRoteteDir_Right);
                IsRotate = false;
            }

            if (IsStop)
            {
                if (IsDoOut)
                {
                    Vector3 speed = handle.DoOut();
                    stateInstance.Move(speed);
                   // break;
                }
                break;
            }

            if (IsDoMove)
            {
                
                    Vector3 pos = handle.Move(dir, IsRight);
                    stateInstance.Move(pos);
                    IsDoMove = false;
                    dir = Vector3.zero;
                
            }

            yield return 0;
        }
    }
    
}
