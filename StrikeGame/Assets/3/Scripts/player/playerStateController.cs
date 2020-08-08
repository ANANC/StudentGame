using UnityEngine;
using System.Collections;
using DG.Tweening;

public enum RotationState
{
    Rotating,
    Over,
    Dont
}

public enum DirectionState
{
    Right,
    Left,
    Not
}

public enum PlayerState
{
    Moving,
    Jump,
    Standing,
    PrepareDown,
    Dowing,
    Rotate,
    Death
}

public enum JumpState
{
    JumpUp,
    JumpDown,
    NotJumping
}


public class playerStateController : MonoBehaviour {

    //单例模式
    static playerStateController _instance;
    public static playerStateController GetInstance()
    {
        if(_instance == null)
            _instance = GameObject.FindGameObjectWithTag(tags.gameControl).GetComponent<playerStateController>();
        return _instance;
    }
    //玩家类
    playerMoveController MoveControl;
    PlayerState playerstate;
    
    //仙人掌
    float SlowPercent;

    void Start()
    {
        PropControllor.desertWorldEvent += DesertWorldEvent;
        MoveControl = GameObject.FindGameObjectWithTag("Player").GetComponent<playerMoveController>();
        GetKeyControl( PlayerState.Dowing);
    }
    

    #region 切换状态
    public void GetKeyControl(PlayerState plaState, DirectionState dirState = DirectionState.Not,bool IsInput = false)
    {
        if (playerstate == PlayerState.Rotate)
            return;

        if (playerstate == plaState)
            return;

        if (plaState == PlayerState.Standing && IsInput)
        {
            if(playerstate != PlayerState.Moving)
                return;
        }
            
        MoveControl.MovePrepare(plaState, dirState);
    }
 
    
    public void SetPlayerState(PlayerState state)
    {
        playerstate = state;
    }
   #endregion
    void DesertWorldEvent()//沙漠世界特有玩法-仙人掌倒计时
    {
        int i = PropControllor.GetInstance().CactusTime;
        SlowPercent = i * 0.1f;
        if (i == 0)
        {
            SlowPercent = 1;
            playerstate = PlayerState.Death;
            PropControllor.GetInstance().Init();
        }
    }
}
