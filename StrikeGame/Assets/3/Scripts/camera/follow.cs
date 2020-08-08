using UnityEngine;
using System.Collections;
using DG.Tweening;

public class follow : MonoBehaviour {

    public Transform player;
    Transform myTransform;
    float offsets_Forward;
    float offsets_Up;
    Vector3 offsets;
    float MoveDistance_x;
    float MoveDistance_y;
    float FollowLimits_y;
    float FollowLimits_x;
    float speed;
    Vector3 playerPos;
    bool IsMove;
    bool IsRota;
    float Angle;
    float RotateY;
    float RotateX;

	void Start () {
        myTransform = this.transform;
        offsets_Forward = myTransform.position.x * myTransform.forward.x + myTransform.position.z * myTransform.forward.z;
        offsets_Forward -= player.position.x * player.forward.x + player.position.z * player.forward.z;
        offsets_Up = myTransform.position.y - player.position.y;
        offsets = offsets_Forward * player.forward + player.up * offsets_Up;
        FollowLimits_y = 1+offsets_Up;
        FollowLimits_x = 2;
        speed = 0.3f;
        playerPos = player.position;
        MoveDistance_x = 0;
        MoveDistance_y = 0;
        IsMove = false;
        IsRota = false;

	}

    public void RotationPrapare()
    {
        RotateY = myTransform.position.y - player.position.y;
        IsRota = true;
    }
    

    void FixedUpdate()
    {
        if(IsRota)
        {
            myTransform.LookAt(player.forward + myTransform.position);
            offsets = offsets_Forward * player.forward +  player.position;
            offsets.y += RotateY;
            myTransform.position = offsets;
            playerPos = player.position;
            Angle += 10;
            if (Angle == 90)
            {
                IsRota = false;
                Angle = 0;
            }
            return;
        }

        if (IsMove)
        {
            myTransform.LookAt(player.forward + myTransform.position);
            offsets = offsets_Forward * player.forward + offsets_Up * player.up + player.position;
            if (playerPos == player.position)
            {
                myTransform.position = offsets;
                playerPos = player.position;
                MoveDistance_x = 0;
                MoveDistance_y = 0;
                IsMove = false;
                return;
            }

            myTransform.DOMove(offsets, speed);
            playerPos = player.position;
            return;
        }


        if(playerPos != player.position)
        {
            if((int)myTransform.right.x!= 0)
            {
                MoveDistance_x = player.position.x - myTransform.position.x;
            } 
            else
                MoveDistance_x += player.position.z - myTransform.position.z;
            if (Mathf.Abs(MoveDistance_x) > FollowLimits_x)
            {
                IsMove = true;
                return;
            }

            MoveDistance_y += myTransform.position.y - player.position.y;
            if(Mathf.Abs(MoveDistance_y)>FollowLimits_y)
            {
                IsMove = true;
                return;
            }

            playerPos = player.position;
        }
    }


}
