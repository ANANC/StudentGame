using UnityEngine;
using System.Collections;

public class control : MonoBehaviour {

    public float speed = 1;
    public float JumpSpeed =1;
    public float JumpTime = 1;
    public float DownSpeed = 1;
    public float CanDownTime = 1;
    bool IsClick;
    CharacterController CharacterController;
    Vector3 force;
    bool IsJump;
    float Jumping;
    bool IsRotate;
    Vector3 JumpForce;
    float width;
    float high;
    public GameObject CheckGameObject;
    Vector3 AgainPos;
    Vector3 position;
    Vector3 offsetPos;
    Vector3 RayPos;
    Vector2 CheckPos;
    RaycastHit Checkhit;
    bool IsInBirth;
    public GameObject BirthPlath;
    Vector3 MovePassPos;
    bool IsInMovePass;
    bool IsDowing;

	void Start () {
        CharacterController = GetComponent<CharacterController>();
        force = Vector3.zero;
        JumpForce = Vector3.zero;
        Jumping = 0;
        IsJump = false;
        width = GetComponent<BoxCollider>().bounds.size.x;
        high = GetComponent<BoxCollider>().bounds.size.y;
        IsRotate = false;
        AgainPos = transform.position;
        offsetPos = new Vector3(0, -high / 2 - 0.05f, 5);
        IsInBirth = false;
        IsInMovePass = false; 
        IsDowing = false;

        
	}
    void GetDirectionPos(GameObject GO)
    {
        Vector3 directionPos = Vector3.zero ;
        if(!IsInBirth)
            directionPos = GO.GetComponent<banPass>().GetDirectionPos(transform);
        else
            directionPos = BirthPlath.GetComponent<BirthPass>().GetDirectionPos(transform);
        transform.position = directionPos;
        if(GO.GetComponent<banPass>().IsMove)
        {
            InMovePass(GO.transform.position);
        }
    }
    IEnumerator Downing()
    {
        yield return new WaitForSeconds(CanDownTime);
        transform.position = AgainPos;
        IsDowing = false;
        Debug.Log("!!");
    }

    void Update()
    {
        position = transform.position;
        force = Vector3.zero;


        if (CharacterController.isGrounded)
        {
            AgainPos = position;

            if (IsDowing)
                StopCoroutine("Downing");

            if (IsRotate)
            {
                GetDirectionPos(CheckGameObject);
                IsRotate = false;
            }

            if (IsInMovePass)
            {
                Vector3 pos = Vector3.zero;
                if ((int)(transform.forward.x) != 0)
                    pos.x += CheckGameObject.transform.position.x - transform.position.x;
                else
                    pos.z += CheckGameObject.transform.position.z - transform.position.z;
                transform.position += pos;
            }
        }
        else
        {
            RayPos = position + offsetPos;

            if (Physics.Raycast(RayPos, -transform.forward, out Checkhit, 5))
            {
                CheckGameObject = Checkhit.collider.gameObject;
                if (CheckGameObject.tag == "ban")
                    GetDirectionPos(CheckGameObject);
            }

            if (!IsJump &&! IsDowing)
            {
                IsDowing = true;
                StartCoroutine("Downing");
            }
        }



        if (Input.GetKey(KeyCode.LeftArrow))
        {
            force += transform.right * speed;
        }
        if (Input.GetKey(KeyCode.RightArrow))
        {
            force += -transform.right * speed;
        }
        if (Input.GetKey(KeyCode.Space))
        {
            if (!IsJump)
            {
                JumpForce = transform.up * JumpSpeed * 2;
                IsJump = true;
            }
        }
        if (Input.GetKeyDown(KeyCode.A))
        {
            transform.Rotate(new Vector3(0, -90, 0));
            IsRotate = true;
        }
        if (Input.GetKeyDown(KeyCode.D))
        {
            transform.Rotate(new Vector3(0, 90, 0));
            IsRotate = true;
        }

        if (IsJump)
        {
            if (Jumping < JumpTime)
            {
                Jumping += 0.1f;
                JumpForce = JumpForce + transform.up * JumpSpeed * JumpTime;
                JumpForce += transform.up * DownSpeed;
                force += JumpForce;
            }
            else
            {
                if(!IsDowing)
                {
                    IsDowing = true;
                    StartCoroutine("Downing");
                }

            }
        }

        force += -transform.up * DownSpeed;
        CharacterController.Move(force);
    }

    void OnControllerColliderHit(ControllerColliderHit hit)
    {
        if (IsJump)
        {
            IsJump = false;
            Jumping = 0;
        }
        if (hit.collider.gameObject.tag == "birthSphere")
        {
            BirthPlath.GetComponent<BirthPass>().TouchSphere(hit.collider.gameObject.name);
        }
        if(IsInMovePass && hit.collider.gameObject.transform != transform.parent)
        {
            IsInMovePass = false;
            //transform.parent = partent;
        }
    }

    public void SetIsInbirth(bool b)
    {
        IsInBirth = b;
    }
    void InMovePass(Vector3 pos)
    {
        //transform.parent = t;
        IsInMovePass = true;
        MovePassPos = pos;
    }
}
