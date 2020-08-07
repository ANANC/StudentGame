using UnityEngine;
using System.Collections;
using System.Collections.Generic;
public class playerStateControllor// : MonoBehaviour {
{ 

   static playerStateControllor _instance;
    public static playerStateControllor GetInstance
    {
        get
        {
            if (_instance == null)
                _instance = new playerStateControllor();
            return _instance;
        }
    }


    PlayerState playerState;
    Stack traPlayerState;
    playerMove playerMoveControllor;
    playerAnimator playeranimator;
    Dictionary<PlayerState, simpleState> States;

    #region states
    StandState standstate;
    MoveState movestate;
    JumpingState jumpstate;
    DownState downstate;
    HangState hangstate;
    shinState shinstate;
    DeathState deathstate;

    StandMoveStandState standMovestandstate;
    #endregion
    playerStateControllor() {
        traPlayerState = new Stack();
        //stateInit();
    }

    public static void Distroy()
    {
        _instance = null;
    }

    public void stateInit()
    {
        playerMoveControllor = gameCommon.playerMoveGetInstance;
        playeranimator = gameCommon.playerAnimatorGetInstance;

        standstate = new StandState();
        movestate = new MoveState();
        jumpstate = new JumpingState();
        downstate = new DownState();
        hangstate = new HangState();
        shinstate = new shinState();
        deathstate = new DeathState();
        standMovestandstate = new StandMoveStandState();

        States = new Dictionary<PlayerState, simpleState>();
        States.Add(PlayerState.Standing, standstate);
        States.Add(PlayerState.Moving, movestate);
        States.Add(PlayerState.Jump, jumpstate);
        States.Add(PlayerState.Dowing, downstate);
        States.Add(PlayerState.hanging, hangstate);
        States.Add(PlayerState.shinning, shinstate);
        States.Add(PlayerState.Death, deathstate);
        States.Add(PlayerState.StandMoveStand, standMovestandstate);

        gameCommon.moveMessageGetInstance.Init();
        gameCommon.DirectionUpdete();

        //SetState(PlayerState.Standing);
        StateCommunicate(PlayerState.Dowing);
        
    }
    
    void SetState(PlayerState state)
    {
        playerState = state;
        playeranimator.SetState(state);
    }
    public PlayerState GetState()
    {
        return playerState;
    }
    
    public void Input(KeyCode key, bool IsKeyUp = false)//按键信息
    {
        InputStateControl(playerState, key, IsKeyUp);
    }

    //处理按键信息
    void InputStateControl(PlayerState state, KeyCode key, bool IsKeyUp = false)
    {
        if(key == KeyCode.A)
        {
            States[state].RotateInit(false);
            return;
        }
        else if(key == KeyCode.D)
        {
            States[state].RotateInit(true);
            return;
        }

        if (key == KeyCode.LeftArrow)
        { SetDireceiton(DirectionState.right, -1); }
        if (key == KeyCode.RightArrow)
        { SetDireceiton(DirectionState.right, 1); }
        if (key == KeyCode.UpArrow)
        { SetDireceiton(DirectionState.up, 1); }
        if (key == KeyCode.DownArrow)
        { SetDireceiton(DirectionState.up, -1); }

        traPlayerState.Push(state);
        //InputevetManage(state, key, IsKeyUp);
        States[state].GetInput(state, key, IsKeyUp);
    }

    //处理通讯信息-非按键
    void TransformStateControl(PlayerState state)
    {
        traPlayerState.Push(state);
        //transfromeventManage(state);
        States[state].GetInput(state);
    }

    //通讯状态-非按键
    public void StateCommunicate(PlayerState state) {
        TransformStateControl(state);
    }


    //通讯状态-按键
    public void StateCommunicate(PlayerState state,KeyCode key,bool IsKeyUp = false)
    {
        TransformStateControl(state,key,IsKeyUp);

    } 
    //处理通讯信息-按键
    void TransformStateControl(PlayerState state, KeyCode key, bool IsKeyUp = false)
    {
        traPlayerState.Push(state);
        InputStateControl(state, key, IsKeyUp);
    }

    //是否确定状态
    public void IsSureState(bool IsSure)
    {
        if (IsSure)
        {
            //StopeventManag(playerState);
            States[playerState].Stop();
            PlayerState state = (PlayerState)traPlayerState.Pop();
            SetState(state);
        }
        traPlayerState.Clear();
    }

    //判断当前状态是否参数状态
    public bool IsThisState(PlayerState state)
    {
        bool b = playerState == state ? true : false;
        return b;
    }
    
    public void Move(Vector3 speed)
    {
        playerMoveControllor.Move(speed);
    }
    
    //开启线程
    public void ToStartCoroutine(IEnumerator ienumberator)
    {
        playerMoveControllor.ToStartCoroutine(ienumberator);
    }

    //设置方向
    public void SetDireceiton(DirectionState state,float coe)
    {
        playeranimator.SetDirection(state, coe);
    }



}
