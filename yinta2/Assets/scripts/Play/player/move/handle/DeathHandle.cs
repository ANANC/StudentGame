using UnityEngine;
using System.Collections;

public class DeathHandle : SimpleHandle {
    private Vector3 repeatPos;
    private Quaternion quaternion;

    public DeathHandle():base()
    {
        MoveMessage.updateQuaternionEvent += UpdatePos;
    }

    public Vector3 Move()
    {
        Vector3 pos = Vector3.zero;
        pos = repeatPos;
        pos += Vector3.up * gameCommon.Playersize_Up;
        pos = moveCommon.GetPlayerAndTargetDistance(pos);
        return pos;
    }

    public void SetRotateToReallyPos()
    {
        gameCommon.FollowcameraInstance.setSpecificQuaternion(quaternion);
    }

    public void UpdatePos()
    {
        if (MoveMessage.Standobject.tag == gameCommon.moveStandTag)
            return;

        repeatPos = gameCommon.playerTransform.position;
        quaternion = gameCommon.playerTransform.rotation;

    }
}
