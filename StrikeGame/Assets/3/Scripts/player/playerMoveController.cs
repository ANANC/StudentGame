using UnityEngine;
using System.Collections;

public class playerMoveController : MonoBehaviour {
    private Transform myTransform;
    private Transform cameraTransform;
    private CharacterController characterController;
    private playerStateController PlayerStateContorllor;

    private PlayerState playerState;

    private float commonXSpeed = 0.3f;
    private float FixedXSpeed_High = 0.23f;
    private float FixedXSpeed_Low = 0.08f;
    private float JumpYSpeed = 0.32f;
    private float DownYSpeed = 0.31f;
    private float CanJumpTime = 1.8f;
    private float CanDownTime = 4.5f;
    private float CanRotateSpeed = 5f;
    private float offsets_Forward = 20f;

    
    private Vector3 lastTransform_Right;
    private bool IsMoveX;
    private bool IsMoveY;
    private bool IsRotate;
    private bool IsFace;
    private GameObject Standboard;
    private Vector3 againPos;
    private Quaternion lastRotationAngle;
    private bool IsGround;
    private float width;
    private float high;
    private float downTime;
    private bool IsCheckNewStandboard;

    //左右移动
    DirectionState MovedirectionState;
    private Vector3 XSpeed;
    private Vector3 YSpeed;

    //跳跃
    JumpState jumpState;
    float jumpTime;

    //旋转
    DirectionState RotatedirectionState;
    Vector3 rotationSpeed;
    RotationState rotationState;
    float Angle;
    float currentRotationAngle;

    void Awake () {
        myTransform = this.transform;
        cameraTransform = Camera.main.transform;
        characterController = GetComponent<CharacterController>();
        width = GetComponent<Renderer>().bounds.size.x;
        high = GetComponent<Renderer>().bounds.size.y;
        PlayerStateContorllor = playerStateController.GetInstance();
        Init();
    }
    

    void Init()
    {
        lastTransform_Right = myTransform.right;
        XSpeed = Vector3.zero;
        IsMoveX = false;
        IsMoveY = false;
        jumpState = JumpState.NotJumping;
        jumpTime = 0;
        YSpeed = Vector3.zero;
        IsFace = false;
        IsGround = false;
        downTime = 0;
        IsCheckNewStandboard = false;
        rotationState = RotationState.Dont;
        RotatedirectionState = DirectionState.Not;
        IsRotate = false;
        MovedirectionState = DirectionState.Not;
    }
	
	void Update () {
        if(IsRotate)
        {
            //Rotation();
            return;
        }

        if (IsMoveX)
        {
            characterController.Move(XSpeed);
            CheckMoveDowning();
        }
        if(IsMoveY)
        {
            Jump();
            characterController.Move(YSpeed);
            Check();
        }
    }

    public void MovePrepare(PlayerState plaState, DirectionState dirState)
    {
        switch (plaState)
        {
            case PlayerState.Standing:
                    StopXMove();
                break;

            case PlayerState.Moving:
                if (playerState == PlayerState.Standing)
                {
                    SetPlayerState(plaState);
                    IsFrontMove();
                    XMove(commonXSpeed, dirState);
                }
                if (playerState == PlayerState.Moving)
                {
                    XMove(commonXSpeed, dirState);
                }

                if (playerState == PlayerState.Jump)
                {
                    if (MovedirectionState == DirectionState.Not)
                    {
                        MovedirectionState = dirState;
                        XMove_Fixed(FixedXSpeed_Low, MovedirectionState);
                    }
                }
                break;

            case PlayerState.Jump:
                if (jumpState == JumpState.NotJumping)
                {
                    SetPlayerState(PlayerState.Jump);
                    JumpPrepare();
                }
                break;

            case PlayerState.Dowing:
                SetPlayerState(plaState);
                Dowing();
                if (jumpState != JumpState.JumpDown)
                {
                    if (MovedirectionState != DirectionState.Not)
                        XMove_Fixed(FixedXSpeed_Low, MovedirectionState);
                }
                break;

            case PlayerState.Death:
                Revive();
                break;

            case PlayerState.Rotate:
                RotatePrepare(dirState);

                //旋转是发送但不改变这个类的playerState
                break;

            case PlayerState.PrepareDown:
                if (playerState == PlayerState.Moving || playerState == PlayerState.Standing)
                {
                    IsFrontMove();
                    SetPlayerState(PlayerState.PrepareDown);
                    characterController.Move(-myTransform.up * 0.5f);
                    SetPlayStateChangeEvent(PlayerState.Dowing);
                }
                break;

        }
    }

    void SetPlayerState(PlayerState state)
    {
        PlayerStateContorllor.SetPlayerState(state);
        playerState = state;
    }

    void SetPlayStateChangeEvent(PlayerState state)
    {
        PlayerStateContorllor.GetKeyControl(state);
    }

    #region X位移

    void XMove(float speed, DirectionState dirState)
    {
        MovedirectionState = dirState;

        if (MovedirectionState == DirectionState.Right)
        {
                XSpeed = myTransform.right * speed;
        }
        else if (MovedirectionState == DirectionState.Left)
        {
                XSpeed = -myTransform.right * speed;
        }

        IsMoveX = true;
    }

    void XMove_Fixed(float speed,DirectionState dirState)
    {
        MovedirectionState = dirState;
        if (MovedirectionState == DirectionState.Right)
        {
            XSpeed = lastTransform_Right * speed;
        }
        else if (MovedirectionState == DirectionState.Left)
        {
            XSpeed = -lastTransform_Right * speed;
        }

        IsMoveX = true;
    }
    
    
    
    #endregion

    #region Y位移

    void Dowing()
    {
        YSpeed = -myTransform.up * DownYSpeed;
        IsMoveY = true;
    }
    
    void Revive()
    {
        SetPlayerState(PlayerState.Death);

        Init();

        Vector3 v = againPos;
        v.y += 2f;
        myTransform.position = v;
        myTransform.position -= myTransform.forward * 20;

        myTransform.rotation = lastRotationAngle;

        SetPlayStateChangeEvent(PlayerState.Dowing);
    }

    void JumpPrepare()
    {
        jumpState = JumpState.JumpUp;
        if (MovedirectionState != DirectionState.Not)
        {
            lastTransform_Right = myTransform.right;
            XMove_Fixed(FixedXSpeed_High, MovedirectionState);
        }
        else
            IsFrontMove();

        jumpTime = 0;
        IsMoveY = true;
        
    }

    void Jump()
    {
        //Debug.Log("跳跃状态：" + jumpState);
        if (jumpState == JumpState.JumpUp)
        {
            jumpUp();
        }
    }

    void jumpUp()
    {
        jumpTime += 0.1f;
        if (jumpTime < CanJumpTime)
        {
            YSpeed = myTransform.up * JumpYSpeed * Mathf.Sin(jumpTime % CanJumpTime);
        }
        else
        {
            jumpState = JumpState.JumpDown;
            SetPlayStateChangeEvent(PlayerState.Dowing);
        }
    }

    #endregion

    #region 旋转
    
    void RotatePrepare(DirectionState dirState)
    {
        if (playerState != PlayerState.Standing)
            SetFrontMove(false);

        IsRotate = true;
        RotatedirectionState = dirState;
        float IsLeft = -1;
        if (RotatedirectionState == DirectionState.Left)
            IsLeft = 1;
        Angle = myTransform.eulerAngles.y + IsLeft * 90;
        if (Angle < 0)
            Angle = 270;
        if (Angle >= 360)
            Angle = 0;
        RotatedirectionState = DirectionState.Not;
        rotationState = RotationState.Rotating;
        PlayerStateContorllor.SetPlayerState(PlayerState.Rotate);
        currentRotationAngle = myTransform.eulerAngles.y;
        StartCoroutine(Rotation());
    }

    IEnumerator Rotation()
    {
        yield return 3;
         while (Mathf.Abs(currentRotationAngle - Angle) > 0.1f)
         {
            currentRotationAngle = Mathf.LerpAngle(currentRotationAngle, Angle, CanRotateSpeed * Time.deltaTime);
            Quaternion currentRotation = Quaternion.Euler(0, currentRotationAngle, 0);
            myTransform.rotation = currentRotation;

            currentRotationAngle = myTransform.eulerAngles.y;
            yield return 0;
        }
        myTransform.Rotate(new Vector3(0, Angle - myTransform.eulerAngles.y, 0));
        yield return 3;
        EndRotate();
    }

    void EndRotate()
    {
        rotationState = RotationState.Dont;
        rotationSpeed = Vector3.zero;
        if (playerState != PlayerState.Standing)
            IsFrontMove();
        rotationState = RotationState.Dont;
        IsRotate = false;
        if(playerState!= PlayerState.Jump)
            lastTransform_Right = myTransform.right;
        PlayerStateContorllor.SetPlayerState(playerState);
    }
       

    #endregion

    #region 直视检查射线

    bool IsFrontMove()
    {
        IsFace = IsFacetoFace();
        if (IsFace)
        {
            SetFrontMove(true);
            return true;
        }
        return false;
    }

    bool IsFacetoFace()
    {
        Vector3 rayPos = myTransform.position;
        if ((int)myTransform.forward.x != 0)
            rayPos.x = cameraTransform.position.x;
        else
            rayPos.z = cameraTransform.position.z;
        Ray ray = new Ray(rayPos, myTransform.forward);
        Debug.DrawRay(rayPos, myTransform.forward * 200, Color.red);
        RaycastHit hit;
        if (Physics.Raycast(ray, out hit, 200))
        {
            if (hit.collider.gameObject == gameObject)
            {
                return true;
            }
        }
        return false;
    }

    void SetFrontMove(bool b)
    {
        if (b)
        {
            myTransform.position += -myTransform.forward * offsets_Forward;
        }
        else
        {
            myTransform.position += myTransform.forward * offsets_Forward;
        }
    }
    #endregion

    #region 板子相关
    bool CheckStandBroad()
    {
        Vector3 rayPos = cameraTransform.position;
        rayPos.y = myTransform.position.y - 0.7f;
        Ray ray = new Ray(rayPos, myTransform.forward);
        Debug.DrawRay(rayPos, myTransform.forward * 200, Color.blue);
        RaycastHit hit;
        if (Physics.Raycast(ray, out hit, 200))
        {
            if (hit.collider.gameObject.tag == "ban")
            {
                if (Standboard != hit.collider.gameObject)
                {
                    Standboard = hit.collider.gameObject;
                    IsCheckNewStandboard = true;
                }
                againPos = Standboard.transform.position;
                lastRotationAngle = myTransform.rotation;
                return true;
            }
        }
        return false;
    }

    void GetStandboard(Vector3 pos)
    {
        Vector3 ver = myTransform.position;
        if ((int)(myTransform.forward.x) != 0)
            ver.x = pos.x;
        else
            ver.z = pos.z;
        myTransform.position = ver;
    }
    #endregion

    #region 相关检测
    void Check()
    {
        if (jumpState == JumpState.JumpUp)
            return;

        bool b = CheckStandBroad();
        if(IsCheckNewStandboard)
            GetStandboard(Standboard.transform.position);

        IsDown();
        if (IsGround)
        {
            characterController.Move(-myTransform.up * 10);
            SetPlayStateChangeEvent(PlayerState.Standing);
            return;
        }
        KeepingTime();
    }

    void CheckMoveDowning()
    {
        if (playerState != PlayerState.Moving)
            return;

        bool b = CheckStandBroad();
        if (!b)
        {
            SetPlayStateChangeEvent(PlayerState.Dowing);
        }
    }

    void StopXMove()
    {
        if (playerState == PlayerState.Moving)
        {
            CheckStandBroad();
            if (IsCheckNewStandboard)
                GetStandboard(Standboard.transform.position);
            else
            {
                if (IsFace)
                    SetFrontMove(false);
            }
        }
        IsDown();
        if (IsGround)
        {
            downTime = 0;
            if (jumpState == JumpState.JumpDown)
                jumpState = JumpState.NotJumping;
            SetPlayerState(PlayerState.Standing);
            lastTransform_Right = myTransform.right;
            MovedirectionState = DirectionState.Not;
            IsMoveX = false;
            IsMoveY = false;
        }
        else
            SetPlayStateChangeEvent(PlayerState.Dowing);
    }

    void IsDown()
    {
        IsGround = false;
        Vector3 vec = myTransform.position;
        vec += high / 2 * -myTransform.up;

        vec -= width / 2 * myTransform.right;
        if (Physics.Raycast(vec, -transform.up, 0.5f))
        {
            IsGround = true;
        }

        vec += width * myTransform.right;
        if (Physics.Raycast(vec, -transform.up, 0.5f))
        {
            IsGround = true;
        }
    }

    void KeepingTime()
    {
        downTime += 0.1f;
        if (downTime > CanDownTime)
        {
            IsMoveX = false;
            IsMoveY = false;
            SetPlayStateChangeEvent(PlayerState.Death);
        }
    }
    #endregion

   
}
