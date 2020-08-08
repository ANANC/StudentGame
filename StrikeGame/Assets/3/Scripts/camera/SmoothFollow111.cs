using UnityEngine;
using System.Collections;

public class SmoothFollow111 : MonoBehaviour {

    public float distance = 40.0f;
    public float height = 5.0f;
    public float moveDamping = 2.0f;
    Transform selfTransform;
    public float Offset_Width = 2f;
    public float Offset_High = 2f;
    bool IsMoveWidth = false;
    bool IsMoveHigh = false;
    public Transform Target;
    float wantedWidth ;
    float currentWidth ;
    float distanceWidth ;
    bool IsRotate;

    [AddComponentMenu("Camera-Control/Smooth Follow")]
	void Start () {
        selfTransform = GetComponent<Transform>();
	}

    //void LateUpdate()
    void Update()
    {
        if (!Target)
            return;

        float wantedRotationAngle = Target.eulerAngles.y;
        float wantedHeight = Target.position.y + height;

        float currentRotationAngle = selfTransform.eulerAngles.y;
        float currentHeight = selfTransform.position.y;

        float distanceHigh = Abs(wantedHeight - currentHeight);

        if (!IsMoveHigh)
        {
            if (distanceHigh > Offset_High)
                IsMoveHigh = true;
        }
        else
        {
            if (currentHeight == wantedHeight)
                IsMoveHigh = false;
            currentHeight = Mathf.Lerp(currentHeight, wantedHeight, moveDamping * Time.deltaTime);
        }

        bool IsX = false;
        bool IsZ = false;
        if (Abs(selfTransform.right.x) > 0.01f)
            IsX = true;
        if (Abs(selfTransform.right.z) > 0.01f)
            IsZ = true;
        if (IsX && IsZ)
        {
            Debug.Log("正在旋转");
            IsRotate = true;
        }
        else
        {
            IsRotate = false;
            if (IsX)
            {
                wantedWidth = Target.position.x;
                currentWidth = selfTransform.position.x;
                distanceWidth = currentWidth - wantedWidth;
            }
            else if (IsZ)
            {
                wantedWidth = Target.position.z;
                currentWidth = selfTransform.position.z;
                distanceWidth = currentWidth - wantedWidth;
            }

            distanceWidth = Abs(distanceWidth);
            if (!IsMoveWidth && distanceWidth > Offset_Width)
            {
                IsMoveWidth = true;
            }

            if (IsMoveWidth)
            {
                if (distanceWidth == 0)
                    IsMoveWidth = false;
                currentWidth = Mathf.Lerp(currentWidth, wantedWidth, 4f * Time.deltaTime);
            }
        }
        

        currentRotationAngle = wantedRotationAngle;
        Quaternion currentRotation = Quaternion.Euler(0, currentRotationAngle, 0);
        selfTransform.position = Target.position;
        selfTransform.position -= currentRotation * Vector3.forward * distance;

        Vector3 currentPosition = transform.position;       
        currentPosition.y = currentHeight;


        
        if (!IsRotate)
        {
            if (IsX)
                currentPosition.x = currentWidth;
            else if (IsZ)
                currentPosition.z = currentWidth;
        }


        selfTransform.position = currentPosition;

        //selfTransform.LookAt(Target.position + new Vector3(0, height, 0));
        selfTransform.LookAt(selfTransform.position + Target.forward);
    }

    float Abs(float f)
    {
        if (f < 0)
            f *= -1;
        return f;
    }
}
