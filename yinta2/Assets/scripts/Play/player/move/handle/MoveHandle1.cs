using UnityEngine;
using System.Collections;

public class MoveHandle1 : SimpleHandle
{
    private  float speed;

    public MoveHandle1():base()
    {
        MoveMessage.updateStandobjectEvent += UpdateObject;
        speed = gameCommon.speed;
    }

    public override Vector3 Init(Transform tra)
    {
        Vector3 reallyPos = Vector3.zero;
        reallyPos += moveCommon.MoveToReallyPos(DirectionState.forward, -1, tra, 0.5f, -0.5f, -0.8f);
        reallyPos += moveCommon.MoveToReallyPos(DirectionState.up, 1, tra, 0.5f, 0.5f, 0);

        MoveMessage.UpdateStandobject(tra);
        return reallyPos;
    }

    //public override bool IsCando(out Vector3 pos)
    //{
    //    pos = Vector3.zero;
    //    bool b = false;
    //    if (moveCommon.IsMoveOutRance(Standobject, StandobjectRance, false))
    //    {
    //        RaycastHit hit;
    //        Vector3 excursion = -gameCommon.checkExcursionPosition_up;
    //        if (moveCommon.DoubleRaycast(false, false, RaycastLay.standTag, excursion, DirectionState.forward, 1, out hit, 1000))
    //        {
    //            Transform checkBroad = hit.collider.gameObject.transform;

    //            if (Standobject != checkBroad)
    //            {
    //                pos = Init(checkBroad);
    //                b = true;
    //            }
    //            else
    //            {
    //                for (int i = 0; i < 5;i++)
    //                    MoveMessage.UpdatedownxPower();
    //            }
    //        }
    //    }
    //    else
    //        b = true;


    //    if(!b)
    //    {
    //        MoveMessage.UpdatedownxPower();
    //    }

    //    return b;
    //}

    public Vector3 Move(Vector3 dir, bool IsRight, out bool IsDown)
    {
        IsDown = false;
        RaycastHit hit;
        Vector3 Speed = Vector3.zero;
        Speed = dir * speed;
        float coe = IsRight ? 1 : -1;

        if (MoveMessage.IsMoveout)
        {
            if (moveCommon.DoubleRaycast(true, true, RaycastLay.Notthing, Vector3.zero, DirectionState.forward, 1, out hit, 8))
            {
                Speed = dir * speed + moveCommon.MoveToReallyPos(DirectionState.forward, -1, Standobject, 0.5f, -0.5f, -0.8f);
                MoveMessage.IsMoveout = false;
            }
        }
        
        //躲避前方的物体而移动
        Vector3 DodgePos = moveCommon.CheckIsNeeddodge(Standobject, DirectionState.right, coe, speed, true, true,true);
        Speed += DodgePos;
        if(DodgePos!= Vector3.zero)
        {
            //if(!moveCommon.IsTouchRoad(out hit,true))
            if(moveCommon.PlayerRaycast(DodgePos,DirectionState.up,-1,out hit,5) != RaycastLay.standTag)
            {
                MoveMessage.IsMoveout = true;
            }
        }

        //当移动到后面去时，返回到前面
        Vector3 movetoForward = moveCommon.StandtoForward(dir);
        if (movetoForward != Vector3.zero)
        {
            Speed = movetoForward + dir * speed;
        }

        Speed += moveCommon.MoveToReallyPos(DirectionState.up, 1, Standobject, 0.5f, 0.5f, 0);

        MoveMessage.UpdatedownxPower();

        if (moveCommon.IsMoveOutRance(Standobject, StandobjectRance, false))
        {
            Vector3 checkPos = -gameCommon.checkExcursionPosition_up;
            bool IsNeedDown = true;

            if (moveCommon.DoubleRaycast(false, false, RaycastLay.standTag, checkPos, DirectionState.forward, 1, out hit, 1000))
            {
                Transform tra = hit.collider.transform;
                if (tra != Standobject)
                {
                    Vector3 reallyPos = Vector3.zero;
                    reallyPos += moveCommon.MoveToReallyPos(DirectionState.forward, -1, tra, 0.5f, -0.5f, -0.8f);
                    reallyPos += moveCommon.MoveToReallyPos(DirectionState.up, 1, tra, 0.5f, 0.5f, 0);
                    Speed = reallyPos;

                    MoveMessage.UpdateStandobject(tra);
                    IsNeedDown = false;
                }
            }


            if (IsNeedDown)
            {
                IsDown = true;
            }
        }

        SceneCommon.IsTouchChip();

        return Speed;
    }

    protected override void UpdateObject(Transform tra)
    {
        Standobject = tra;
        StandobjectRance = MoveMessage.StandobjectRance;
    }
    
}
