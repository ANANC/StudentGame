using UnityEngine;
using System.Collections;

public class shinState : simpleState {
    ShinHandle handle;
    Vector3 initPos;
    Vector3 dir;
    bool IsVertical;
    bool IsRight;
    bool IsDoMove;
    public shinState():base()
    {
        myState = PlayerState.shinning;
        handle = new ShinHandle();
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
                    dir = -Right;
                    IsVertical = false;
                    IsDoMove = true;
                    IsRight = false;
                }
                break;

            case KeyCode.RightArrow:
                if (!IsKeyup)
                {
                    dir = Right;
                    IsVertical = false;
                    IsDoMove = true;
                    IsRight = true;
                }
                break;

            case KeyCode.DownArrow:
                if (!stateInstance.IsThisState(myState))
                {
                    handle.SetDirectionCheckInit(false);
                    if (handle.IsCando(out initPos))
                        manage();
                    else
                        stateInstance.IsSureState(false);
                }
                else
                {
                    if (!IsKeyup)
                    {
                        dir = -Up;
                        IsVertical = true;
                        IsDoMove = true;
                    }
                }
                break;

            case KeyCode.UpArrow:
                if (!stateInstance.IsThisState(myState))
                {
                    handle.SetDirectionCheckInit(true);
                    if (handle.IsCando(out initPos))
                        manage();
                    else
                        stateInstance.IsSureState(false);
                }
                else
                {
                    if (!IsKeyup)
                    {
                        dir = Up;
                        IsVertical = true;
                        IsDoMove = true;
                    }
                }
                break;

            case KeyCode.Space:
                if (!IsVertical && dir != Vector3.zero)
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
        Debug.Log("shinState不接受这样的通讯！");
    }

    protected override void manage()
    {
        IsDoMove = false;
        Do();
    }

    public override IEnumerator DoMove()
    {
        Vector3 speed;
        bool IsDoOut = false;
        stateInstance.Move(initPos);
        yield return 0;
        while(true)
        {
            if (IsStop)
                break;

            if (IsRotate)
            {
                yield return handle.Rotating(IsRoteteDir_Right);
                IsRotate = false;
            }

            if (IsDoMove)
            {
                speed = handle.Move(dir, IsVertical,IsRight, out IsDoOut);
                stateInstance.Move(speed);
                IsDoMove = false;

                if (IsDoOut)
                {
                    stateInstance.StateCommunicate(PlayerState.Standing);
                    break;
                }

                dir = Vector3.zero;

            }

            yield return 0;
        }
    }
    
}
