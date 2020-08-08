using UnityEngine;
using System.Collections;

public class seek : MonoBehaviour
{
    public GameObject target;
    Animator a;
    float MaxDistance;
    float slowDownDistance;
    float NowDistance;
    Vector3 vector;
    float speed;
    float MaxSpeed;
    float time;
    int direction;

    // Use this for initialization
    void Start()
    {
        MaxDistance = 0.5f;
        slowDownDistance = 1f;
        NowDistance = (target.transform.position - transform.position).magnitude;
        vector = new Vector3();
        MaxSpeed = 0.42f;
        speed = 0.1f;
        time = 0;
        a = gameObject.GetComponent<Animator>();
        direction = -1;
    }
    Vector3 Force()
    {
        Vector3 force;
        force = (target.transform.position - transform.position).normalized * speed;
        if ((int)(NowDistance - MaxDistance) <= (int)slowDownDistance)
            force = force * (NowDistance - MaxDistance) / slowDownDistance;
        return force - vector;
    }
    void SetAnimator(Vector3 F)
    {
        if (NowDistance - MaxDistance > 0.5f)
        {
            if (System.Math.Abs(F.y) - System.Math.Abs(F.x)>0.0005f)
            {
                if (F.y > 0)
                {
                    if (direction != 0)
                    {
                        if (a.GetBool("IsChange") == false)
                        {
                            a.SetBool("IsChange", true);
                            a.SetBool("IsUp", false);
                            a.SetBool("IsLeft", false);
                            a.SetBool("IsRight", false);
                            a.SetBool("IsDown", false);
                            a.SetBool("IsStop", false);
                            return;
                        }
                        a.SetBool("IsChange", false);
                        a.SetBool("IsUp", true);
                        direction = 0;
                        return;
                    }
                }
                else
                {
                    if (direction != 1)
                    {
                        if (a.GetBool("IsChange") == false)
                        {
                            a.SetBool("IsChange", true);
                            a.SetBool("IsUp", false);
                            a.SetBool("IsLeft", false);
                            a.SetBool("IsRight", false);
                            a.SetBool("IsDown", false);
                            a.SetBool("IsStop", false);
                            return;
                        }
                        a.SetBool("IsChange", false);
                        a.SetBool("IsDown", true);
                        direction = 1;
                        return;
                    }
                }

            }
            else
            {
                if (F.x > 0)
                {
                    if (direction != 2)
                    {
                        if (a.GetBool("IsChange") == false)
                        {
                            a.SetBool("IsChange", true);
                            a.SetBool("IsUp", false);
                            a.SetBool("IsLeft", false);
                            a.SetBool("IsRight", false);
                            a.SetBool("IsDown", false);
                            a.SetBool("IsStop", false);
                            return;
                        }
                        a.SetBool("IsChange", false);
                        a.SetBool("IsRight", true);
                        direction = 2;
                        return;
                    }
                }
                else
                {
                    if (direction != 3)
                    {
                        if (a.GetBool("IsChange") == false)
                        {
                            a.SetBool("IsChange", true);
                            a.SetBool("IsUp", false);
                            a.SetBool("IsLeft", false);
                            a.SetBool("IsRight", false);
                            a.SetBool("IsDown", false);
                            a.SetBool("IsStop", false);
                            return;
                        }
                        a.SetBool("IsChange", false);
                        a.SetBool("IsLeft", true);
                        direction = 3;
                        return;
                    }

                }
            }
        }
        else
        {
            if(direction!=-1)
            {
                if (a.GetBool("IsStop") == false)
                {
                    a.SetBool("IsUp", true);
                    a.SetBool("IsChange", false);
                    a.SetBool("IsLeft", false);
                    a.SetBool("IsRight", false);
                    a.SetBool("IsDown", false);
                    a.SetBool("IsStop", true);
                    return;
                }
                direction = -1;
            }
           
        }
    }


    void Teleport()
    {
        Vector3 v = -vector;
        v = target.transform.position + v.normalized * 2f;
        transform.position = v;
    }

    // Update is called once per frame
    void Update()
    {
        time += Time.deltaTime;
        if (time > 0.1f)
        {

            NowDistance = (target.transform.position - transform.position).magnitude;
            if (NowDistance - MaxDistance > 0.5f)
            {
                vector += Force();
                if (vector.magnitude > MaxSpeed)
                    vector = vector.normalized * MaxSpeed;
                GetComponent<CharacterController>().Move(vector);
            }

            SetAnimator(vector);

            if (NowDistance - MaxDistance > 7f)
            {
                Teleport();
            }
            
            time = 0;

        }
    }
}

