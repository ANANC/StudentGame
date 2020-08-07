using UnityEngine;
using System.Collections;

public class JumpingState : simpleState {

    JumpHandle handle;

    public JumpingState():base()
    {
        myState = PlayerState.Jump;
        handle = new JumpHandle();
        handle.JumpXInit();
    }
    public override void GetInput(PlayerState state, KeyCode key, bool IsKeyup = false)
    {
        if (!IsThisState(state))
            return;

        PlayerState newState = myState;

        switch (key)
        {
            case KeyCode.LeftArrow:
                handle.SetJumpX(-Right);
                break;

            case KeyCode.RightArrow:
                handle.SetJumpX(Right);
                break;

            case KeyCode.UpArrow:
                newState = PlayerState.shinning;
                stateInstance.StateCommunicate(newState,key,IsKeyup);

                newState = PlayerState.hanging;
                stateInstance.StateCommunicate(newState);
                break;
                
            case KeyCode.Space:
                if (!stateInstance.IsThisState(myState))
                    manage();
                break;
        }

    }

  

    protected override void manage()
    {
        handle.ChangeJumpstate(myState);
        Do();
    }


    public override IEnumerator DoMove()
    {
        float time = 0;
        bool IsDown;
        bool IsHang;
        Transform tra = gameCommon.playerTransform;
        stateInstance.Move(handle.Init(tra));
        while (true)
        {
            if (IsStop)
                break;

            time += Time.deltaTime;
            Vector3 speed = handle.move(time,out IsDown,out IsHang);
            if (!IsDown)
            {
                stateInstance.Move(speed);
            }

            if(IsDown)
            {
                break;
            }
            else if (IsHang)
            {
                stateInstance.StateCommunicate(PlayerState.hanging);
            }

            yield return 0;
        }
        if (!IsStop)
        {
            stateInstance.StateCommunicate(PlayerState.Dowing);
            handle.ChangeJumpstate(PlayerState.Dowing);
        }
        else
        {
            handle.JumpXInit();
        }
        
    }

}
