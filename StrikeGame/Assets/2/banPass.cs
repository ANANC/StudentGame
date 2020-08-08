using UnityEngine;
using System.Collections;

public class banPass : MonoBehaviour {
    public bool IsMove;
    Vector3[] DirectionPos;
    float offset_xAz;
    float offset_y;
	// Use this for initialization
	void Start () {
        transform.tag = "ban";

        /*
          0  3  
          1  2
         */

        DirectionPos = new Vector3[4];
        float w = transform.GetComponent<BoxCollider>().bounds.size.x;
        float k = transform.GetComponent<BoxCollider>().bounds.size.z;
        Vector3 PlayerScale = GameObject.FindGameObjectWithTag("Player").transform.localScale;
        offset_xAz = w / 2 - PlayerScale.x / 2;
        offset_y = k / 2 + 0.001f;
	}
	
	// Update is called once per frame
	void Update () {
	
	}

    public Vector3 GetDirectionPos(Transform target)
    {
        for (int i = 0; i < 4; i++)
        {
            DirectionPos[i] = transform.position;
            DirectionPos[i].y += offset_y;
        }

        DirectionPos[0].x -= offset_xAz;
        DirectionPos[0].z += offset_xAz;

        DirectionPos[1].x -= offset_xAz;
        DirectionPos[1].z -= offset_xAz;

        DirectionPos[2].x += offset_xAz;
        DirectionPos[2].z -= offset_xAz;

        DirectionPos[3].x += offset_xAz;
        DirectionPos[3].z += offset_xAz;

        int index = -1;
        Vector3 direction = target.forward;
        float distance = 100;
        bool IsX;
        bool IsLeft = false;
        bool IsForward = false;
        Vector3 forwardPoint = DirectionPos[0];

        if ((int)(direction.x) != 0)
        {
            IsX = true;
            if (direction.x > 0)
                IsLeft = false;
            else
                IsLeft = true;
        }
        else
        {
            IsX = false;
            if (direction.z > 0)
                IsForward = true;
            else
                IsForward = false;
        }

        for (int i = 0; i < 4; i++)
        {
            if (IsX)
            {
                float AbsD = Mathf.Abs(DirectionPos[i].z - target.position.z);
                if (IsLeft && DirectionPos[i].x > forwardPoint.x)
                    continue;
                if (!IsLeft && DirectionPos[i].x < forwardPoint.x)
                    continue;
                if (AbsD > distance)
                    continue;

                distance = AbsD;
                forwardPoint = DirectionPos[i];
                index = i;

            }
            else
            {
                float AbsD = Mathf.Abs(DirectionPos[i].x - target.position.x);
                if (IsForward && DirectionPos[i].z < forwardPoint.z)
                    continue;
                if (!IsForward && DirectionPos[i].z > forwardPoint.z)
                    continue;
                if (AbsD > distance)
                    continue;

                distance = AbsD;
                forwardPoint = DirectionPos[i];
                index = i;
            }
        }

        Vector3 pos = target.position;
        if (IsX)
            pos.x = DirectionPos[index].x;
        else
            pos.z = DirectionPos[index].z;
        return pos;
    }
}
