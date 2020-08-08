using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class Run : MonoBehaviour
{
    enum state
    {
        patrolling,
        chasing
    }
    state SeekerState;
    float angle;
    Vector3 rayDirection;
    RaycastHit hit;
    GameObject patrolPoint;
    float patrolDistance;
    float memoryTime;
    float lastMemoryTime;
    bool IsSeeingTarget;
    Vector3 desPos;
    Vector3 nextpathPoint;

    public Transform TargetObject = null;
    public GameObject[] patrolPoints;
    public float fieldOfView = 45f;
    public float distanceOfView = 1;
    public float ChasingSpeed;

    public GameObject textObject;

    void Start()
    {
        SeekerState = state.patrolling;
        patrolPoints = GameObject.FindGameObjectsWithTag("patrolPoint");

        int index = Random.Range(0, patrolPoints.Length);
        patrolPoint = patrolPoints[index];
        GetComponent<NavMeshAgent>().destination = patrolPoint.transform.position;
        IsSeeingTarget = false;
        memoryTime = 10;
        lastMemoryTime = 0;
        
    }
    void Update()
    {
        //onDraw();
        CheckView();
        switch(SeekerState)
        {
            case state.patrolling:
                PatrolState();

                break;
            case state.chasing:
                ChasingState();
                break;
        }
        transform.LookAt(patrolPoint.transform);
    }

    void CheckView()
    {
        transform.LookAt(TargetObject.transform);
        desPos = TargetObject.transform.position;
        rayDirection = desPos - transform.position;
        rayDirection.y = 0;
        angle = Vector3.Angle(rayDirection, transform.forward);
        if (angle < fieldOfView)
        {
            if (Physics.Raycast(transform.position, rayDirection.normalized, out hit, distanceOfView))
            {
                if (hit.collider.gameObject.name == TargetObject.name)
                {
                    IsSeeingTarget = true;
                    return;
                }
            }
        }
        IsSeeingTarget = false;
    }

    void OnCollisionEnter(Collision collision)
    {
        string ColliderName = collision.collider.gameObject.name;
        string ColliderTag = collision.collider.gameObject.tag;
        if ( ColliderName == TargetObject.name)
        {
            SeekerState = state.chasing;
            textObject.GetComponent<Text>().text = "追逐你！";
        }
        if(ColliderTag == "reflexWall")
        {
            GetComponent<Rigidbody>().AddForce(collision.relativeVelocity * 90);
        }
    }

    void onDraw()
    {
        Vector3 front = transform.position + (transform.forward * distanceOfView);
        float radians = fieldOfView*3.14f/180.0f;
        Vector3 left = transform.TransformPoint(new Vector3(-distanceOfView*Mathf.Sin(radians),0,distanceOfView*Mathf.Cos(radians)));
        Vector3 right = transform.TransformPoint(new Vector3(distanceOfView * Mathf.Sin(radians), 0, distanceOfView * Mathf.Cos(radians)));

        Debug.DrawLine(transform.position, front, Color.black);
        Debug.DrawLine(transform.position , left, Color.green);
        Debug.DrawLine(transform.position, right, Color.blue);
    }

    void PatrolState()
    {
        if (IsSeeingTarget == true)
        {
            SeekerState = state.chasing;
            textObject.GetComponent<Text>().text = "追逐你！";
        }

        patrolDistance = Vector3.Distance(transform.position, patrolPoint.transform.position);
        if(patrolDistance < 2)
        {
            int index = Random.Range(0, patrolPoints.Length);
            patrolPoint = patrolPoints[index];
            GetComponent<NavMeshAgent>().destination = patrolPoint.transform.position;
        }
    }

    void ChasingState()
    {
        //Debug.Log("111111111");
        if (IsSeeingTarget == true)
        {
            Quaternion targetRotation = Quaternion.LookRotation(desPos - transform.position);
            transform.rotation = Quaternion.Slerp(transform.rotation, targetRotation, Time.deltaTime * 6);

            if (rayDirection.magnitude < 5)
                GetComponent<Rigidbody>().AddForce(rayDirection.normalized * ChasingSpeed * 1.8f);
            else
                GetComponent<Rigidbody>().AddForce(rayDirection.normalized * ChasingSpeed);

            lastMemoryTime = 0;
        }
        else
        {
            lastMemoryTime += Time.deltaTime;
            if (lastMemoryTime > memoryTime)
            {
                SeekerState = state.patrolling;

                int index = Random.Range(0, patrolPoints.Length);
                patrolPoint = patrolPoints[index];
                GetComponent<NavMeshAgent>().destination = patrolPoint.transform.position;

                textObject.GetComponent<Text>().text = "巡逻";

                lastMemoryTime = 0;
                return;
            }
            GetComponent<NavMeshAgent>().destination = desPos;
           
        }
    }
}
