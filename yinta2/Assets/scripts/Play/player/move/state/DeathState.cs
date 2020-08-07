using UnityEngine;
using System.Collections;

public class DeathState : simpleState {

    DeathHandle handle;

    public DeathState() : base()
    {
        myState = PlayerState.Death;
        handle = new DeathHandle();
    }

    public override IEnumerator DoMove()
    {
        Vector3 pos = handle.Move();
        stateInstance.Move(pos);
        handle.SetRotateToReallyPos();
        stateInstance.StateCommunicate(PlayerState.Dowing);
        yield break;
    }

}
