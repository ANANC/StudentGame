using UnityEngine;
using System.Collections;

public class StandState : simpleState {

    StandHandle handle;

    public StandState():base()
    {
        myState = PlayerState.Standing;
        handle = new StandHandle();
    }

    public override void GetInput(PlayerState state, KeyCode key, bool IsKeyup = false)
    {
        if (!IsThisState(state))
            return;
        PlayerState newState = myState;

        switch (key)
        {
            case KeyCode.LeftArrow:
                if (!IsKeyup)
                {
                    newState = PlayerState.Moving;
                    stateInstance.StateCommunicate(newState, key, IsKeyup);
                }
                break;

            case KeyCode.RightArrow:
                if (!IsKeyup)
                {
                    newState = PlayerState.Moving;
                    stateInstance.StateCommunicate(newState, key, IsKeyup);
                }
                break;

            case KeyCode.UpArrow:
                newState = PlayerState.shinning;
                stateInstance.StateCommunicate(newState,key,IsKeyup);
                break;

            case KeyCode.DownArrow:
                newState = PlayerState.shinning;
                stateInstance.StateCommunicate(newState, key, IsKeyup);
                break;

            case KeyCode.Space:
                SceneCommon.IsTouchTransmit();
                newState = PlayerState.Jump;
                stateInstance.StateCommunicate(newState);
                break;

            case KeyCode.LeftControl:
                newState = PlayerState.hanging;
                stateInstance.StateCommunicate(newState);
                break;
        }
    }

    public override void GetInput(PlayerState state)
    {
        if (!IsThisState(state))
            return;
        
        if (!handle.StandIsmoving())
            manage();
        else
            stateInstance.StateCommunicate(PlayerState.StandMoveStand);
    }

    public override IEnumerator DoMove()
    {
        Vector3 pos;
        bool IsDown;

        while (true)
        {
            if (IsRotate)
            {
                stateInstance.Move(handle.StandOn());
                yield return handle.Rotating(IsRoteteDir_Right);
                IsRotate = false;
            }

            if (IsStop)
                break;

            IsDown = handle.IsDown(out pos);
            if (IsDown)
            {
                stateInstance.Move(pos);
                stateInstance.StateCommunicate(PlayerState.Dowing);
                break;
            }

            yield return 0;
        }
    }
}
