using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class RotationWall : MonoBehaviour {

    public float speed;
    public GameObject target;
    public Camera camera;

    public GameObject Seeker;
    public Shader Seeker_CollisionShader;
    public Shader Target_CollisionShader;
    Shader Seeker_DailyShader;
    Shader Target_DailyShader;

    Vector3 TranfromPos;
	void Start () {
        Seeker_DailyShader = Seeker.GetComponent<Renderer>().material.shader;
        Target_DailyShader = target.GetComponent<Renderer>().material.shader;
	}
	

    void OnCollisionEnter(Collision collision)
    {
        //target.GetComponent<Rigidbody>().AddForce(-collision.relativeVelocity* 3f);
        string ColliderTag = collision.collider.gameObject.tag;
        if(collision.collider.gameObject == Seeker)
        {
            Vector3 force = collision.relativeVelocity*40;

            force.y = 0;
            Seeker.GetComponent<Renderer>().material.shader = Seeker_CollisionShader;
            Seeker.GetComponent<Rigidbody>().AddForce(-force);

            target.GetComponent<Renderer>().material.shader = Target_CollisionShader;
            target.GetComponent<Rigidbody>().AddForce(force*2);

            StartCoroutine(ShaderBegin());
        }
        if (ColliderTag == "reflexWall")
        {
            GetComponent<Rigidbody>().AddForce(collision.relativeVelocity * 90);
        }
        //Debug.Log(collision.collider.name);
    }

    IEnumerator ShaderBegin()
    {
        yield return 30;
        Seeker.GetComponent<Renderer>().material.shader = Seeker_DailyShader;
        target.GetComponent<Renderer>().material.shader = Target_DailyShader;
        yield break;
    }
    void Update()
    {

        if (Input.GetKey(KeyCode.A))
            target.GetComponent<Rigidbody>().AddForce(Vector3.left * speed);
        if (Input.GetKey(KeyCode.D))
            target.GetComponent<Rigidbody>().AddForce(Vector3.right * speed);
        if (Input.GetKey(KeyCode.S))
            target.GetComponent<Rigidbody>().AddForce(Vector3.back * speed);
        if (Input.GetKey(KeyCode.W))
            target.GetComponent<Rigidbody>().AddForce(Vector3.forward * speed);

        TranfromPos = transform.position;
        TranfromPos.y = 3;
        camera.transform.position = TranfromPos;
    }

}
