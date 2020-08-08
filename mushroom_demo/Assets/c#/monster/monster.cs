using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public  class monster{
    protected GameObject center;
    protected GameObject monst;
    Animator a;
    Vector3 vector;
    Vector3 circle;
    protected string name;
    protected string substanceName;

    
    //徘徊
    float distance_center;
    float MaxDistance_center;
    float distance_circle;
    float radius;
    protected float MaxSpeed;
    float time;

    //检测附近AI
    RaycastHit[] colliders;
    List<GameObject> neighbors;//邻居列表
    float detectRadius;

    //分离
    float comfortDistance;
    float multiplierInsideComfortDistance;
    
    protected monster(){}
    
    protected void Init()
    {
        MaxDistance_center = 13;
        distance_center = (center.transform.position - monst.transform.position).magnitude;
        vector = new Vector3(((float)(Random.value - 0.5) * 2f),(float)(Random.value - 0.5) * 2f, 0);
        distance_circle = 3f;
        circle = vector.normalized * distance_circle;
        radius = 0.4f;

        a = monst.GetComponent<Animator>();
        time = 0;

        neighbors = new List<GameObject>();
        detectRadius = 5f;

        comfortDistance = 1.2f;
        multiplierInsideComfortDistance = 5f;
    }

    void  CheckNeighbors()
    {
        neighbors.Clear();
        colliders = Physics.RaycastAll(monst.transform.position,monst.transform.forward,detectRadius);//使用射线，得到RaycastHit[]结构 里面有gameobject
        for(int i =0;i<colliders.Length;i++)
        {
            neighbors.Add(colliders[i].collider.gameObject);
        }
    }

    Vector3 Force_Separation()
    {
        Vector3 steeringForce = new Vector3(0, 0, 0);
        foreach(GameObject g in neighbors)
        {
            Vector3 toNeighbor = g.transform.position - monst.transform.position;
            float length = toNeighbor.magnitude;
            steeringForce += toNeighbor.normalized / length;
            if (length < comfortDistance)
                steeringForce *= multiplierInsideComfortDistance;
        }
        
        return steeringForce;
    }

	Vector3 Force_wander()
    {
        Vector3 force;
        distance_center = (center.transform.position - monst.transform.position).magnitude;
        if (distance_center> MaxDistance_center)
        {
            force = (center.transform.position - monst.transform.position).normalized * 1f;
            return force;
        }
        Vector3 circle_rander = new Vector3((float)((Random.value - 0.5) * 2f), (float)((Random.value - 0.5) * 2f), 0f).normalized * radius;
        circle = vector.normalized * distance_circle;
        force = circle_rander + circle;

        return force - vector;
    }

    void SetAnimator(Vector3 F)
    {
        if (System.Math.Abs(F.y) - System.Math.Abs(F.x) > 2.6f)
        {
            if (F.y > 0)
            {
                if (a.GetBool("IsUp"))
                    return;
                a.SetBool("IsLeft", false);
                a.SetBool("IsRight", false);
                a.SetBool("IsDown", false);
                a.SetBool("IsUp", true);
                return;
            }
            else
            {
                if (a.GetBool("IsDown"))
                    return;
                a.SetBool("IsLeft", false);
                a.SetBool("IsRight", false);
                a.SetBool("IsUp", false);
                a.SetBool("IsDown", true);
                return;
            }
        }
        else
        {
            if (F.x > 0)
            {
                if (a.GetBool("IsRight"))
                    return;
                a.SetBool("IsLeft", false);
                a.SetBool("IsDown", false);
                a.SetBool("IsUp", false);
                a.SetBool("IsRight", true);
                return;
            }
            else
            {
                if (a.GetBool("IsLeft"))
                    return;
                a.SetBool("IsRight", false);
                a.SetBool("IsDown", false);
                a.SetBool("IsUp", false);
                a.SetBool("IsLeft", true);
                return;
            }
        }
    }

	public void Update () {
        time += Time.deltaTime;
        if (time > 0.05f)
        {
            if (monst.transform.position.z != 0)
                monst.transform.position = new Vector3(monst.transform.position.x, monst.transform.position.y, 0);

            vector += Force_wander();
            
            vector += Force_Separation();
            if (vector.magnitude > MaxSpeed)
                vector = vector.normalized * MaxSpeed;
            
            monst.GetComponent<CharacterController>().Move(vector * Time.deltaTime);
            SetAnimator(vector);

            time = 0;
        }
	}

    public void SetPos(Vector3 v)
    {
        monst.transform.position = v;
    }

    public float MAXSpeed
    {
        set
        {
            MaxSpeed = value;
        }
    }


    public string NAME
    {
        get
        {
            return name;
        }
    }

    public void SetActive(bool b)
    {
        monst.isStatic = b;
    }

    public string SubstanceName
    {
        get
        {
            return substanceName;
        }
    }
}
