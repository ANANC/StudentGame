using UnityEngine;
using System.Collections;

public class StandMoveStandState : simpleState
{
    StandMovestandHandle handle;
    public  StandMoveStandState():base()
    {
        myState = PlayerState.StandMoveStand;
        handle = new StandMovestandHandle();
    }

    public override void GetInput(PlayerState state, KeyCode key, bool IsKeyup = false)
    {
        if (!IsThisState(state))
            return;

        stateInstance.StateCommunicate(PlayerState.Standing, key, IsKeyup);
    }

    protected override void manage()
    {
        handle.Init();
        base.manage();
    }

    public override IEnumerator DoMove()
    {
        Vector3 speed;
        while (true)
        {
            if (IsRotate)
            {
                yield return handle.Rotating(IsRoteteDir_Right);
                IsRotate = false;
            }

            if (IsStop)
                break;

            speed = handle.Move();
            stateInstance.Move(speed);

            yield return 0;
        }
    }
}
