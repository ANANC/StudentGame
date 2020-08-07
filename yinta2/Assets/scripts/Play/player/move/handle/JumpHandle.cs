using UnityEngine;
using System.Collections;

public class JumpHandle : SimpleHandle
{
    private float JumpSpeed;
    private float G;

    public JumpHandle() : base()
    {
        JumpSpeed = gameCommon.jumpspeed;
        G = gameCommon.G;
    }

    public override Vector3 Init(Transform tra)
    {
        Vector3 pos = Vector3.zero;
        RaycastHit hit;

        if (!moveCommon.IshasobstructInforward(out hit))
        {
            Vector3 excursion = -gameCommon.checkExcursionPosition_up * 1.3f;

            if (moveCommon.CameraRaycast(excursion, out hit, 1000) == RaycastLay.standTag)
            {
                Transform hitTra = hit.collider.transform;
                if (hitTra != MoveMessage.Standobject)
                {
                    pos += moveCommon.MoveToReallyPos(DirectionState.forward, -1, hitTra, 0.5f, 0.5f, 10);
                }
            }

            MoveMessage.IsCanmoveinforward = true;
        }
        else
        {
            MoveMessage.IsCanmoveinforward = false;
            MoveMessage.FaceWall = hit.collider.transform;
        }

        return pos;
    }

    public Vector3 move(float time,out bool IsDown,out bool IsHang)
    {
        Vector3 Speed = Vector3.zero;
        float y = JumpSpeed - G * time;
        Speed = Vector3.up * y;

        IsDown = y > 0.12 ? false : true;

        RaycastHit hit;
        IsHang = moveCommon.IsTouchStandofside(out hit);
        
        if (MoveMessage.IsJumpX)
        {
            Speed += moveCommon.MoveJumpX();
        }
        
        Speed += moveCommon.CheckIsNeeddodge(MoveMessage.Standobject, DirectionState.up, 1, JumpSpeed, true,true);

        SceneCommon.IsTouchChip();

        return Speed;
    }

}
