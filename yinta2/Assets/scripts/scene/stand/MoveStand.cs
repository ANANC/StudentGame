using UnityEngine;
using System.Collections;

public class MoveStand : MonoBehaviour
{
    public bool IsReturn;
    public Vector3[] positions;
    public bool IsSureSpeed;
    public float SureSpeed;
    float speed ;

    private Transform myTransform;
    private Vector3 targetPos;
    private int NowtargetposIndex;
    private Vector3 pos;
    private int direction;
    private bool IsRotate;
    void Start()
    {
        myTransform = this.transform;
        pos = Vector3.zero;
        NowtargetposIndex = 1;
        targetPos = positions[NowtargetposIndex];
        direction = 1;
        IsRotate = gameCommon.IsRotate;

        if (IsSureSpeed && SureSpeed!=0)
            speed = SureSpeed;
        else
            speed = Random.Range(0.1f, 0.2f);
    }

    void Update()
    {
        IsRotate = gameCommon.IsRotate;
        if (IsRotate)
            return;

        pos = targetPos - myTransform.localPosition;
        if (pos.magnitude < 0.1f)
        {
            if (!IsReturn)
            {
                myTransform.localPosition = positions[0];
                pos = targetPos - myTransform.localPosition;
            }

            else
            {
                NowtargetposIndex += 1 * direction;
                int length = positions.Length;
                if (NowtargetposIndex == length || NowtargetposIndex == -1)
                {
                    direction *= -1;
                    NowtargetposIndex += 1 * direction;
                }
                targetPos = positions[NowtargetposIndex];
                pos = targetPos - myTransform.localPosition;
            }
        }

        pos = pos.normalized * speed;
        myTransform.localPosition += pos;
    }

    public bool GetSpeed(out Vector3 speed)
    {
        speed = pos;
        return IsReturn;
    }

    //void OnCollisionEnter(Collision collision)
    //{
    //    if(collision.collider.transform == gameCommon.playerTransform)
    //    {
    //        gameCommon.playerStateControllorGetInstance.StateCommunicate(PlayerState.StandMoveStand);
    //    }
    //}
}
