using UnityEngine;
using System.Collections;

public class ShinHandle : SimpleHandle
{
    private float speed;
    private bool IsUp;
    Vector3 CheckDirection;

    public ShinHandle():base()
    {
        speed = gameCommon.shinspeed;
    }

    public void SetDirectionCheckInit(bool isup)
    {
        IsUp = isup;
    }

    public override Vector3 Init(Transform tra)
    {
        UpdateObject(tra);

        Vector3 pos = Vector3.zero;
        pos = moveCommon.MoveToReallyPos(DirectionState.forward, -1, Standobject, 0.5f, 0.5f, 0.003f);

        CheckDirection = gameCommon.Forward;

        return pos;
    }
    public override bool IsCando(out Vector3 pos)
    {
        bool b = false;
        pos = Vector3.zero;
        RaycastHit hit;

        Vector3 checkPos = IsUp? gameCommon.checkExcursionPosition_up:-gameCommon.checkExcursionPosition_up;

        if (moveCommon.DoubleRaycast(false, true, RaycastLay.shinTag, checkPos, DirectionState.forward, 1, out hit, 1000))
        {
            b = true;
        }
        
        if (b)
            pos = Init(hit.collider.transform);

        return b;
    }

    public Vector3 Move(Vector3 dir,bool IsVertical,bool IsRight,out bool IsDoOut)
    {
        Vector3 pos = Vector3.zero;
        IsDoOut = false;

       if(!IsCanMove_Direction(dir))
        {
            if (!IsVertical)
            {
                RaycastHit hit;
                if (moveCommon.PlayerRaycast(Vector3.zero, DirectionState.forward, -1, out hit, 2) == RaycastLay.Notthing)
                {
                    Vector3 excursion = gameCommon.checkExcursionPosition_right;
                    if (!IsRight)
                        excursion = -excursion;
                    
                    if (moveCommon.CameraRaycast(excursion, out hit, 1000) == RaycastLay.shinTag)
                    {
                        pos = Init(hit.collider.transform);
                        pos += excursion * 0.8f;
                    }
                }
            }

            return pos;
        }

        int IsMoveOut = 0;
        DirectionState directionState = IsVertical ? DirectionState.up : DirectionState.right;

        StandobjectRance = moveCommon.GetRance(Standobject, DirectionState.up, false);
        if(moveCommon.IsMoveOutRance(Standobject, StandobjectRance, IsVertical))
        {
            IsMoveOut += 1;
        }
        StandobjectRance = moveCommon.GetRance(Standobject, DirectionState.right, false);
        if (moveCommon.IsMoveOutRance(Standobject, StandobjectRance, IsVertical))
        {
            IsMoveOut += 1;
        }

        pos += dir * speed;
        if (IsMoveOut!=0)
        {
            bool IsCanmove = false;
            Vector3 length;
            float coe;

            if (directionState == DirectionState.up)
            {
                length = gameCommon.checkExcursionPosition_up;
                coe = dir.y > 0 ? 1 : -1f;
            }
            else
            {
                length = gameCommon.checkExcursionPosition_right;
                if (moveCommon.IsPlayerFaceX(directionState))
                    coe = dir.x > 0 ? 1 : -1f;
                else
                    coe = dir.z > 0 ? 1 : -1f;
            }
            length *= coe;

            RaycastHit Nexthit;
            if (moveCommon.DoubleRaycast(false, true, RaycastLay.shinTag, length, DirectionState.forward, 1, out Nexthit, 1000))
                IsCanmove = true;

            if (IsCanmove)
            {
                UpdateObject(Nexthit.collider.transform);
                pos += moveCommon.MoveToReallyPos(DirectionState.forward, -1, Standobject, 0.5f, 0.5f, 0.003f);
            }
            else
            {
                if (IsVertical)
                    IsCanmove = moveCommon.IsCanMoveinRance(Standobject, DirectionState.up, dir);
                else
                    IsCanmove = moveCommon.IsCanMoveinRance(Standobject, DirectionState.right, dir);

                if (!IsCanmove)
                {
                    pos = Vector3.zero;
                    if (DoOut(dir, out pos))
                    {
                        IsDoOut = true;
                    }
                }
            }
        }

        SceneCommon.IsTouchChip();

        return pos;
    }

    public override bool DoOut(Vector3 dir,out Vector3 pos)
    {
        bool b = false;
        pos = Vector3.zero;
        if (dir.y != 0)
        {
            if (dir.y > 0)//上面
            {
                Vector3 checkPos = gameCommon.checkExcursionPosition_up;
                RaycastHit hit;
                if(moveCommon.PlayerRaycast(checkPos, CheckDirection, out hit,1) == RaycastLay.Notthing)
                {
                    if(moveCommon.PlayerRaycast(Vector3.zero, CheckDirection, out hit,1) == RaycastLay.standTag)
                    {
                        Transform tra = hit.collider.transform;

                        if (tra != MoveMessage.Standobject)
                            MoveMessage.UpdateStandobject(tra);

                        pos = Vector3.zero;
                        pos += moveCommon.MoveToReallyPos(DirectionState.forward, -1, tra, 0.5f, -0.5f, -0.8f);
                        pos += moveCommon.MoveToReallyPos(DirectionState.up, 1,tra ,0.5f, 0.5f, 0);
                        pos += moveCommon.StandOn();

                        b = true;
                    }
                }
            }
            else//下面
            {
                RaycastHit hit;
               // if(moveCommon.PlayerRaycast(Vector3.zero,DirectionState.up,-1,out hit,1) == RaycastLay.standTag)
               if(moveCommon.CameraRaycast(-gameCommon.checkExcursionPosition_up,out hit,1000) == RaycastLay.standTag)
                {
                    Transform tra = hit.collider.transform;

                    if (tra != MoveMessage.Standobject)
                        MoveMessage.UpdateStandobject(tra);

                    pos = Vector3.zero;
                    pos += moveCommon.MoveToReallyPos(DirectionState.forward, -1, tra, 0.5f, -0.5f, -0.8f);
                    pos += moveCommon.MoveToReallyPos(DirectionState.up, 1, tra, 0.5f, 0.5f, 0);

                    b = true;
                }
            }
        }

        return b;
    }

    protected override void UpdateObject(Transform tra)
    {
        Standobject = tra;
    }
}
