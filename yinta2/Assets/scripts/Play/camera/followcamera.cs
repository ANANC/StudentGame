using UnityEngine;
using System.Collections;

public class followcamera : MonoBehaviour {

    Transform cameraTransform;
    Transform playerTransform;
    bool IsRotate;
    bool IsRight;
    bool IsFaceX;
    Quaternion playerQuaternion;

    float height = 30.0f;
    float heightDamping = 3.0f;
    float offsetheight = 1f;

    float widthDamping = 1.4f;
    float offsetwidth = 0f;

    Vector3 RotatePoint;

    float angle = 0;
    float AngleDirindex = 0;

    Vector3 currentPosition;
    float wantedHeight;
    float currentHeight;
    float distanceHeight;
    float wantedWidth;
    float currentWidth;
    float distanceWidth;
    float wantedForward;
    float currentForward;
    float distanceForward;

    void Start () {
        cameraTransform = gameObject.transform;
        playerTransform = gameCommon.playerTransform;
        playerQuaternion = playerTransform.rotation;
        distanceForward = gameCommon.cameraDistance;
    }

    //void Update () {
    void FixedUpdate() { 
        if (IsRotate)
            return;

        IsFaceX = false;
        if (moveCommon.IsPlayerFaceX(DirectionState.right))
            IsFaceX = true;

         wantedHeight = playerTransform.position.y + height;
         currentHeight = cameraTransform.position.y;
         distanceHeight =wantedHeight - currentHeight;
        distanceHeight= moveCommon.Abs(distanceHeight);
        
        if (IsFaceX)
        {
            wantedWidth = playerTransform.position.x;
            currentWidth = cameraTransform.position.x;
            wantedForward = playerTransform.position.z;
            currentForward = cameraTransform.position.z;
        }
        else
        {
            wantedWidth = playerTransform.position.z;
            currentWidth = cameraTransform.position.z;
            wantedForward = playerTransform.position.x;
            currentForward = cameraTransform.position.x;
        }
        distanceWidth = wantedWidth - currentWidth;
        distanceWidth=moveCommon.Abs(distanceWidth);
        distanceWidth -= height;

        currentHeight = Mathf.Lerp(currentHeight, wantedHeight, heightDamping * Time.deltaTime);
        currentWidth = Mathf.Lerp(currentWidth, wantedWidth, widthDamping * Time.deltaTime);

        currentPosition = cameraTransform.position;
        if(distanceHeight>offsetheight || currentHeight>0.1f)
            currentPosition.y = currentHeight;
        if(distanceWidth > offsetwidth || currentWidth > 0.01f)
        {
            if (IsFaceX)
            {
                currentPosition.x = currentWidth;
               // currentPosition.z = wantedForward + distanceForward;
            }
            else
            { currentPosition.z = currentWidth;
              //  currentPosition.x = wantedForward +distanceForward;
            }
        }
        currentPosition += playerTransform.forward *(moveCommon.Abs(wantedForward - currentForward) - distanceForward);

        cameraTransform.position = currentPosition;
        playerTransform.rotation = playerQuaternion;
    }

    public IEnumerator SetRotate(bool isRight)
    {
        IsRotate = true;
        gameCommon.IsRotate = true;
        IsRight = isRight;
        setAngleDirindex(isRight);
        angle = 0;

        Vector3 offsetHeight = (cameraTransform.position.y - playerTransform.position.y) * Vector3.up;
        Vector3 offsetWidth;
        if(moveCommon.IsPlayerFaceX(DirectionState.right))
            offsetWidth =(cameraTransform.position.x - playerTransform.position.x) *playerTransform.right;
        else
            offsetWidth = (cameraTransform.position.z - playerTransform.position.z) * playerTransform.right;

        RotatePoint = playerTransform.position + offsetWidth + offsetHeight;

        yield return Rotation();
    }

    IEnumerator Rotation()
    {
        while (true)
        {
            if (!IsRotation(IsRight, angle, out angle))
            {
                angle = 0;
                IsRotate = false;
                gameCommon.IsRotate = false;
                break;
            }
            yield return 0;
        }
    }

    public bool IsRotation(bool IsRight, float newAngle, out float changAngle)
    {
        bool b = false;
        changAngle = newAngle;

        float speed = gameCommon.rotateSpeed;
        float angle = IsRight ? -speed : speed;
        
        if (newAngle - 90 < 0)
        {
            changAngle = newAngle += speed;

            float currentRotationAngle = cameraTransform.eulerAngles.y;
            currentRotationAngle += angle;
            Quaternion currentRotation = Quaternion.Euler(0, currentRotationAngle, 0);
            cameraTransform.position = RotatePoint;
            cameraTransform.position -= currentRotation * Vector3.forward * gameCommon.cameraDistance;

            cameraTransform.LookAt(RotatePoint);
            playerTransform.LookAt(playerTransform.position + cameraTransform.forward * 100f);
            
            b = true;
        }
        else
        {
            playerQuaternion = Quaternion.Euler(0, AngleDirindex*90, 0);
            cameraTransform.rotation = playerQuaternion;
            playerTransform.rotation = playerQuaternion;

            gameCommon.DirectionUpdete();
        }

        return b;
    }

    void setAngleDirindex(bool isRight)
    {
        AngleDirindex += isRight ? -1 : 1;
        AngleDirindex = AngleDirindex < 0 ? 3 : AngleDirindex;
        AngleDirindex = AngleDirindex > 3 ? 0 : AngleDirindex;
    }

    void setAngleDirindex(Quaternion quaternion)
    {
        AngleDirindex = quaternion.eulerAngles.y / 90;
    }

    public void setSpecificQuaternion(Quaternion quaternion)
    {
        setAngleDirindex(quaternion);
        cameraTransform.rotation = quaternion;
        playerTransform.rotation = quaternion;
        playerQuaternion = playerTransform.rotation;
        cameraTransform.position = playerTransform.position;
        cameraTransform.position += -playerTransform.forward * distanceForward;

        gameCommon.DirectionUpdete();
    }
    
}
