using UnityEngine;
using System.Collections;

public class HangHandle : SimpleHandle
{
    PlayerState Nowstate;
    float hangdistance;

    public HangHandle():base()
    {
        MoveMessage.updateStandobjectEvent += UpdateObject;
        hangdistance = 0.01f;
        //UpdateObject(MoveMessage.Standobject);
    }

    public override Vector3 Init(Transform tra)
    {
        //MoveMessage.UpdateStandobject(tar);
        Vector3 Pos = Vector3.zero;
        Pos += moveCommon.MoveToReallyPos(DirectionState.forward, -1,tra, 0.5f, 0.5f, hangdistance);
        Pos += moveCommon.MoveToReallyPos(DirectionState.up, 1,tra, 0.5f, -0.002f, 0);

        return Pos;
    }


    public void GetNowstate(PlayerState state)
    {
        Nowstate = state;
    }

    public override bool IsCando(out Vector3 pos)
    {
        bool b = false;
        pos = Vector3.zero;
        Transform CheckTra = null;
        Vector3 excursion;
        RaycastHit hit;

        if(MoveMessage.Standobject.tag == gameCommon.moveStandTag)
        {
            return b;
        }

        if (!moveCommon.IshasobstructInforward(out hit))
        {
            //stand状态
            if (Nowstate == PlayerState.Standing)
            {
                excursion = -gameCommon.checkExcursionPosition_up;

                if (moveCommon.CameraRaycast(excursion, out hit, 1000) == RaycastLay.standTag)
                {
                    CheckTra = hit.collider.transform;
                    b = true;
                }
            }

            //jump/down状态
            if (Nowstate == PlayerState.Jump || Nowstate == PlayerState.Dowing)
            {
                bool IsCheck = false;
                if (moveCommon.DoubleRaycast(true, false, RaycastLay.standTag, Vector3.zero, DirectionState.forward, 1, out hit, 1000))
                {
                    IsCheck = true;
                    CheckTra = hit.collider.transform;
                }

                if (moveCommon.IsTouchStandofside(out hit))
                {
                    IsCheck = true;
                    CheckTra = hit.collider.transform;
                }

                if(IsCheck)
                {
                    if (CheckTra != Standobject)
                    {
                        b = true;
                    }
                }
            }
        }
        

        if(b)
        {
            if (CheckTra != MoveMessage.Standobject)
            {
                MoveMessage.UpdateStandobject(CheckTra);
            }
            pos = Init(MoveMessage.Standobject);
        }

        return b;
    }

    public Vector3 Move(Vector3 dir,bool IsRight)
    {
        Vector3 Speed = Vector3.zero;
        float speed = gameCommon.hangspeed;

        if (!IsCanMove_Direction(dir))
        {
            RaycastHit hit;
            if (moveCommon.PlayerRaycast(Vector3.zero, DirectionState.forward, -1, out hit, 2) == RaycastLay.Notthing)
            {
                Vector3 excursion = gameCommon.checkExcursionPosition_right*2;
                if (!IsRight)
                    excursion = -excursion;
                excursion += -Vector3.up * hangdistance * 20;

                if (moveCommon.CameraRaycast(excursion, out hit, 1000) == RaycastLay.standTag)
                {
                    Speed = Init(hit.collider.transform);
                    Speed += excursion.normalized * speed;
                }
            }

            return Speed;
        }

        
        Speed = dir * speed;

        if (moveCommon.IsMoveOutRance(Standobject, StandobjectRance, false))
        {
            float coe = IsRight == true ? 1 : -1;
            Vector3 checkPos = gameCommon.checkExcursionPosition_right*coe* 2 -Vector3.up * hangdistance * 20; 
            RaycastHit hit;

            //检测到下一个位置在z轴其他位置而移动
            if (moveCommon.CameraRaycast(checkPos, out hit, 1000) == RaycastLay.standTag)
            {
                Transform tra = hit.collider.transform;
                if (Standobject != tra)
                {
                    Speed += moveCommon.MoveToReallyPos(DirectionState.forward, -1,tra, 0.5f, 0.5f, 0.01f);
                    MoveMessage.UpdateStandobject(tra);
                }
            }
            else
            {
                if (!moveCommon.IsCanMoveinRance(Standobject, DirectionState.right, dir))
                    Speed = Vector3.zero;
            }
        }
        return Speed;
    }


    public override Vector3 DoOut()
    {
        Vector3 pos = Vector3.zero;

        pos += moveCommon.MoveToReallyPos(DirectionState.forward, -1, Standobject, 0.5f, -0.5f, -0.8f);
        pos += moveCommon.MoveToReallyPos(DirectionState.up, 1, Standobject, 0.5f, 0.5f, 0);

        //pos.x = pos.z = 0;
        //pos += gameCommon.checkExcursionPosition_forward*1.3f;

        pos += moveCommon.StandOn();
        return pos;
    }

    protected override void UpdateObject(Transform tra)
    {
        Standobject = tra;
        StandobjectRance = moveCommon.GetRance(tra, DirectionState.right, false);
    }
}
