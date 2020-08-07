using UnityEngine;
using System.Collections;

public class DownHandle : SimpleHandle
{
    private float DownXSpeed;
    private float downSpeed;
    private float G;
    private float JumpSpeed;

    public DownHandle():base()
    {
        DownXSpeed = gameCommon.downXspeed;
        downSpeed = gameCommon.downspeed;
        JumpSpeed = gameCommon.jumpspeed;
        G = gameCommon.G;

        MoveMessage.updateStandobjectEvent += UpdateObject;
        //UpdateObject(MoveMessage.Standobject);
        
    }

    public override void Init()
    {
        RaycastHit hit;
        if (!moveCommon.IshasobstructInforward(out hit))
        {
            MoveMessage.IsCanmoveinforward = true;
        }
        else
        {
            MoveMessage.IsCanmoveinforward = false;
            MoveMessage.FaceWall = hit.collider.transform;
        }
    }


    Vector3 JumpDown(float time)
    {
        Vector3 Speed = Vector3.zero;
        
        float y = JumpSpeed  + G * time;
        Speed = -Vector3.up * y;
 
        return Speed;
    }

    Vector3 Down(float time)
    {
        Vector3 Speed = Vector3.zero;

        float y = 0.13f +downSpeed * time;
        Speed = -Vector3.up * y;

        return Speed;
    }

 


    public Vector3 Move(float time,out bool IsStand,out bool IsHang)
    {
        Vector3 Speed;
        RaycastHit hit;
        IsHang = moveCommon.IsTouchStandofside(out hit);
        if (moveCommon.IsTouchRoad(out hit))
        {
            IsStand = true;
            Transform tra = hit.collider.transform;

            Vector3 reallyPos = Vector3.zero;
            if (tra != Standobject)
            {
                reallyPos += moveCommon.MoveToReallyPos(DirectionState.forward, -1, tra, 0.5f, -0.5f, -0.8f);
                //Speed = reallyPos;
                MoveMessage.UpdateStandobject(tra);
            }

            reallyPos += moveCommon.MoveToReallyPos(DirectionState.up, 1, tra, 0.5f, 0.5f, 0);
            Speed = reallyPos;
            
        }
        else
        {
            Speed = IsJump() ? JumpDown(time) : Down(time);
            IsStand = false;

            Speed += moveCommon.CheckIsNeeddodge(Standobject, DirectionState.up, -1, downSpeed, true, false);

            if (MoveMessage.IsJumpX)
            {
                Speed += moveCommon.MoveJumpX();
            }
            else if (MoveMessage.IsDownX)
            {
                Speed += moveCommon.MoveDownX(DownXSpeed);
            }

            if (!moveCommon.IshasobstructInforward(out hit))
            {
                Vector3 checkPos = -gameCommon.checkExcursionPosition_up + Speed*2;

                if (moveCommon.CameraRaycast(checkPos, out hit, 1000) == RaycastLay.standTag)
                {
                    Transform tra = hit.collider.gameObject.transform;
                    Speed += moveCommon.MoveToReallyPos(DirectionState.forward, -1, tra, 0.5f, -0.5f, -0.8f);
                }
            }

        }

        SceneCommon.IsTouchChip();

        return Speed;
    }

    protected override void UpdateObject(Transform tra)
    {
        Standobject = tra;
        //StandobjectRance = moveCommon.GetRance(Standobject, DirectionState.right, true);
        StandobjectRance = MoveMessage.StandobjectRance;
    }


    public bool IsJump()
    {
        bool b = false;
        if (MoveMessage.jumpState != JumpState.NotJump)
            b = true;
        return b;
    }
}
