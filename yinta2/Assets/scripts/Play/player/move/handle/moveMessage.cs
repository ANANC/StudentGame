using UnityEngine;
using System.Collections;

public class moveMessage //: MonoBehaviour {
{
    static moveMessage _instance;
    public static moveMessage GetInstance
    {
        get
        {
            if (_instance == null)
                _instance = new moveMessage();
            return _instance;
        }
    }
    moveMessage() {
        jumpstate = JumpState.NotJump;
        gameCommon.directionupdateEvent += UpdateStandobjectRances;
        gameCommon.directionupdateEvent += moveCommon.IsStandinBack;
        ismoveout = false;
    }

    public static void Distroy()
    {
        _instance = null;
        standobject = null;
    }

    public void Init()
    {
        RaycastHit hit;
        if (moveCommon.PlayerRaycast(Vector3.zero, DirectionState.up, -1, out hit, 1000) == RaycastLay.standTag)
        {
            UpdateStandobject(hit.collider.transform);
        }
    }

    static Transform standobject;
    public Transform Standobject
    {
        get
        {
            if(standobject == null)
            {
                RaycastHit hit;
                if (moveCommon.PlayerRaycast(Vector3.zero,-Vector3.up, out hit, 1000) == RaycastLay.standTag)
                    standobject = hit.collider.transform;
            }
            return standobject;
        }
    }
    float standobjectRance;
    public float StandobjectRance
    {
        get
        {
            return standobjectRance;
        }
    }


    JumpState jumpstate;
    public JumpState jumpState
    {
        get
        {
            return jumpstate;
        }
    }

    bool IsMoveToJump;
    bool isJumpX;
    public bool IsJumpX
    {
        get
        {
            return isJumpX;
        }
    }
    Vector3 jumpDir;
    public Vector3 JumpDir
    {
        get
        {
            return jumpDir;
        }
    }

    float jumpxPower;
    public float JumpxPower
    {
        get
        {
            return jumpxPower;
        }
    }
    



    bool isDownX;
    public bool IsDownX
    {
        get
        {
            return isDownX;
        }
    }
    Vector3 downDir;
    public Vector3 DownDir
    {
        get
        {
            return downDir;
        }
    }

    float downxPower;
    public float DownxPower
    {
        get
        {
            return downxPower;
        }
    }

    

    bool isStandInbace;
    public bool IsStandInbace
    {
        set
        {
            isStandInbace = value;
        }
        get
        {
            return isStandInbace;
        }
    }

    bool ismoveout;
    public bool IsMoveout
    {
        get
        {
            return ismoveout;
        }
        set
        {
            ismoveout = value;
        }
    }

    bool isCanmoveinForward;
    public bool IsCanmoveinforward
    {
        get
        {
            return isCanmoveinForward;
        }
        set
        {
            isCanmoveinForward = value;
        }
    }

    Transform facewall;
    public Transform FaceWall
    {
        get
        {
            return facewall;
        }
        set
        {
            facewall = value;
        }
    }


    public delegate void UpdateStandObject(Transform tar);
    public event UpdateStandObject updateStandobjectEvent;
    public delegate void UpdateStandinstandobjectQuaternion();
    public event UpdateStandinstandobjectQuaternion updateQuaternionEvent;
    
    public void UpdateStandobject(Transform tar)
    {
        standobject = tar;
        UpdateStandobjectRances();
        updateQuaternionEvent();
    }

    public void UpdateStandobjectRances()
    {
        standobjectRance = moveCommon.GetRance(Standobject, DirectionState.right, true);
        updateStandobjectEvent(Standobject);
    }

    public void ChangJumpstate(PlayerState state)
    {
        if (state == PlayerState.Jump)
            jumpstate = JumpState.JumpUp;
        if (state == PlayerState.Dowing)
            jumpstate = JumpState.JumpDown;
    }


    public void JumpXInit()
    {
        isJumpX = false;
        jumpDir = Vector3.zero;
        jumpxPower = 0;
        jumpstate = JumpState.NotJump;
        IsMoveToJump = false;
    }
    public void JumpXTrue(Vector3 dir)
    {
        isJumpX = true;
        IsMoveToJump = true;
        jumpDir = dir;
        jumpxPower = 1;
    }

    public void SetJumpAngle(Vector3 dir)
    {
        if (IsMoveToJump)
            return;

        if(!isJumpX)
        {
            isJumpX = true;
            jumpDir = dir;
            jumpxPower = 0.1f;
        }
        if(jumpDir == dir)
        {
            jumpxPower += 0.08f;
            jumpxPower = jumpxPower > 0.85f ? 0.85f : jumpxPower;
        }
    }

    public void DownXInit()
    {
        isDownX = false;
        downDir = Vector3.zero;
        downxPower = 0;
    }
    public void DownXTrue(Vector3 dir)
    {
        isDownX = true;
        downDir = dir;
    }
    
    public void UpdatedownxPower()
    {
        downxPower += 0.1f;
        downxPower = downxPower > 1 ? 1 : downxPower;
    }

    public void downxPowerInit()
    {
        if(!isDownX)
        {
            downxPower = 0;
        }
    }
}
