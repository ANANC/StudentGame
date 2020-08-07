using UnityEngine;
using System.Collections;

public class StandHandle : SimpleHandle
{
    public bool IsDown(out Vector3 pos)
    {
        //RaycastHit hit;
        pos = Vector3.zero;
        bool b = true;
        if (MoveMessage.IsMoveout)
        {
            b = IsDownofOut();
        }
        else
            b = false;
        //else
        //{
        //    if (moveCommon.IsTouchRoad(out hit))
        //    {
        //        if (moveCommon.IsMoveOutRance(MoveMessage.Standobject, MoveMessage.StandobjectRance, false))
        //        {
        //            Transform checkBroad = hit.collider.gameObject.transform;
        //            Vector3 dir = gameCommon.Right * moveCommon.GetPlayerAndTargetDistance(checkBroad, DirectionState.right);

        //            if (moveCommon.Abs(dir.x) > 0 || moveCommon.Abs(dir.z) > 0)//往左
        //            {
        //                pos = -gameCommon.Right * 0.25f;
        //            }
        //            else
        //            {
        //                pos = gameCommon.Right * 0.25f;
        //            }
        //        }
        //        else
        //        {
        //            b = false;
        //        }
        //    }
            
        //}

        if(b)
            MoveMessage.IsMoveout = false;

        return b;
    }

    bool IsDownofOut()
    {
        bool b = false;

        if (moveCommon.IshasobstructofStand())
            b = true;

        return b;
    }

    public bool StandIsmoving()
    {
        Transform Standobject = MoveMessage.Standobject;
        if (Standobject.tag == gameCommon.moveStandTag)
        {
            if(Standobject.GetComponent<MoveStand>().IsReturn)
                return true;
        }
        return false;
    }
}
