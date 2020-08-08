using UnityEngine;
using System.Collections;

public class movePass : MonoBehaviour {

    public float speed = 0.03f;
    public Vector3[] targets;
    public bool IsRotate;
    Vector3 diretion;
    Vector3 force;
    int AllTargetsNumber;
    int nowNumber;
    int nextNumber;
    bool IsAdd;
    float StaticRange;
    Vector3 Rotation;
    int Y;
    void Start()
    {
        AllTargetsNumber = targets.Length;
        nowNumber = 0;
        nextNumber = GetNextNumber(nowNumber);
        IsAdd = true;
        diretion = targets[nowNumber] - transform.localPosition;
        force = diretion.normalized * speed;
        StaticRange = Vector3.Distance(targets[nowNumber], targets[nextNumber]) * 0.45f;
        Rotation = new Vector3(0, 1, 0);
        Y = 0;
    }
	
	// Update is called once per frame
    void Update()
    {
        diretion = targets[nowNumber] - transform.localPosition;

        if (IsRotate)
        {
            Y = (int)transform.rotation.eulerAngles.y;
            if (diretion.magnitude < StaticRange)
            {
                //Debug.Log(transform.name + StaticRange);
                if (Y % 90 != 0)
                    transform.Rotate(Rotation);
            }
            else
            {
                transform.Rotate(Rotation);
            }

            if(Y == 359)
            {
                transform.Rotate(new Vector3(0, -360, 0));
            }
        }

        if (diretion.magnitude<0.05f)
        {
            nextNumber = GetNextNumber(nowNumber);
            StaticRange = Vector3.Distance(targets[nowNumber], targets[nextNumber]) * 0.45f;
            nowNumber = nextNumber;
            diretion = targets[nowNumber] - transform.localPosition;
            force = diretion.normalized * speed;
        }
        transform.position += force;
    }

    int GetNextNumber(int Number)
    {
        if (IsAdd)
            Number++;
        else
            Number--;
        if (Number == AllTargetsNumber)
        {
            IsAdd = false;
            Number -= 2;
        }
        if (Number == -1)
        {
            IsAdd = true;
            Number += 2;
        }
        return Number;
    }

}
