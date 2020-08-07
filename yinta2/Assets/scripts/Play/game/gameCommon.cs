using UnityEngine;
using System.Collections;

public class gameCommon : MonoBehaviour {

    private static playerMove playerMoveInstance;
    public static playerMove playerMoveGetInstance
    {
        get
        {
            if(playerMoveInstance == null)
                playerMoveInstance = GameObject.FindObjectOfType<playerMove>();
            return playerMoveInstance;
        }
    }
    
    public static moveMessage moveMessageGetInstance
    {
        get
        {
            return moveMessage.GetInstance;
        }
    }
    
    public static playerStateControllor playerStateControllorGetInstance
    {
        get
        {
            return playerStateControllor.GetInstance;
        }
    }

    public static playerAnimator playerAnimatorGetInstance
    {
        get
        {
            return playerAnimator.GetInstance;
        }
    }

    private static followcamera followcameraInstance;
    public static followcamera FollowcameraInstance
    {
        get
        {
            if (followcameraInstance == null)
                followcameraInstance = GameObject.FindObjectOfType<followcamera>();
            return followcameraInstance;
        }
    }


    public static Transform playertransform;
    public static Transform playerTransform
    {
        get
        {
            if (playertransform == null)
                playertransform = playerMoveGetInstance.transform;
            return playertransform;
        }
    }

    static Transform mainCamera;
    public static Transform MainCamera
    {
        get
        {
            if (mainCamera == null)
                mainCamera = Camera.main.transform;
            return mainCamera;
        }
    }

    static float PlayerSize_X = playerTransform.GetComponent<Renderer>().bounds.size.x;
    static float PlayerSize_Y = playerTransform.GetComponent<Renderer>().bounds.size.y;
    static float PlayerSize_Z = playerTransform.GetComponent<Renderer>().bounds.size.z;

    public static float Playersize_right = PlayerSize_X;
    public static float Playersize_forward = PlayerSize_Z;
    public static float Playersize_Up = PlayerSize_Y;

    public static Vector3 Right = playerTransform.right;
    public static Vector3 Forward = playerTransform.forward;
    public static Vector3 Up = playerTransform.up;

    public delegate void playerDirectionUpdete();
    public static event playerDirectionUpdete directionupdateEvent;
    public static void DirectionUpdete()
    {
        Right = playerTransform.right;
        Forward = playerTransform.forward;
        Up = playerTransform.up;

        if (moveCommon.IsPlayerFaceX(DirectionState.right))
        {
            Playersize_right = PlayerSize_X;
            Playersize_forward = PlayerSize_Z;
        }
        else
        {
            Playersize_right = PlayerSize_Z;
            Playersize_forward = PlayerSize_X;
        }

        checkExcursionPosition_up = Vector3.up * (PlayerSize_Y / 2f + 0.23f);
        checkExcursionPosition_right = Right * (Playersize_right / 2f + 0.23f);
        checkExcursionPosition_forward = Forward * (Playersize_forward / 2f + 0.23f);

        directionupdateEvent();
    }

    public const  float speed = 0.2f;
    public const float jumpspeed = 0.28f;
    public const float G = 0.32f;
    public const float downspeed = 0.32f;
    public const float jumpXspeed = 0.18f;
    public const float downXspeed = 0.18f;
    public const float canDownTime = 1.5f;
    public const float shinspeed = 0.14f;
    public const float hangspeed = 0.14f;
    public const float rotateSpeed = 3f;
    public const float cameraDistance =800f;

    public static Vector3 checkExcursionPosition_up = Vector3.up * (PlayerSize_Y / 2f + 0.15f);
    public static Vector3 checkExcursionPosition_right = Right * (Playersize_right / 2f + 0.3f);
    public static Vector3 checkExcursionPosition_forward = Forward * (Playersize_forward / 2f + 0.3f);
    
    public const string musicTag = "music";
    public const string musicEffectTag = "musicEffect";
    public const string dailyTag = "Default";
    public const string shinTag = "green";
    public const string standTag = "stand";
    public const string moveStandTag = "movestand";
    public const string wallTag = "wall";
    public const string chipTag = "chip";
    public const string loadTag = "load";
    public const string transmitTag = "Transmit";
    
    public static bool IsRotate = false;
    
    public static void Distroy()
    {
        mainCamera = null;
        playertransform = null;
        playerMoveInstance = null;
        moveMessage.Distroy();
        playerStateControllor.Distroy();
        playerAnimator.Distroy();
        followcameraInstance = null;
    }
}



public enum PlayerState
{
    //基本状态
    Standing,//不动
    Moving,//左右移动
    Jump,//跳起
    hanging,//悬挂
    shinning,//攀爬
    Dowing,//落下
    Rotate,//旋转
    Death,//死亡

    //游戏特有状态
    StandMoveStand//站到移动版的状态
}

public enum MoveChangeState
{
    Keyup,
    NoTouchRoad,
    Jump
}

public enum JumpState
{
    NotJump,
    JumpUp,
    JumpDown
}

public enum StandChangState
{
    LeftMove,
    RightMove,
    hang,
    shin
}

public enum DirectionState
{
    up,
    forward,
    right
}


public enum RaycastLay
{
    dailyTag,
    shinTag,
    standTag,
    wallTag,
    allLay,
    Notthing
}
