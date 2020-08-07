using UnityEngine;
using System.Collections;

public class StandMovestandHandle : SimpleHandle
{
    MoveStand movestandObject;
    public StandMovestandHandle():base()
    {

    }

    public override void Init()
    {
        movestandObject = MoveMessage.Standobject.GetComponent<MoveStand>();
    }



    public Vector3 Move()
    {
        Vector3 pos = Vector3.zero;
        movestandObject.GetSpeed(out pos);
        return pos;
    }
}
