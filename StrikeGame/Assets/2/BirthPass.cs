using UnityEngine;
using System.Collections;

public class BirthPass : MonoBehaviour {
    public float speed =1;
    public GameObject[] ban;
    public GameObject[] Sphere;
    public float MoveTime;
    int index;
    Vector3 force;
    Vector3 direction;
    bool IsForward;
	void Start () {
        gameObject.tag = "ban";
        IsForward = true;
	}
	
	// Update is called once per frame
    void Update()
    {
    }

    public Vector3 GetDirectionPos(Transform transform)
    {
        Vector3 direction = transform.forward;
        bool IsX;

        if ((int)(direction.x) != 0)
            IsX = true;
        else
            IsX = false;

        Vector3 pos = transform.position;
        if (IsX)
            pos.x = this.transform.position.x;
        else
            pos.z = this.transform.position.z;

        return pos;

    }

    public void TouchSphere(string name)
    {
        index = int.Parse(name);
        if (Sphere[index].activeInHierarchy == false)
            return;
        Sphere[index].SetActive(false);

        int dir = 0;
        if (IsForward)
            dir = 1;
        else
            dir = -1;

        if (index == 0)
            direction = -ban[0].transform.forward*dir;
        if (index == 1)
            direction = -ban[1].transform.forward * dir;
        if (index == 2)
            direction = -ban[2].transform.forward * dir;
        if (index == 3)
            direction = -ban[3].transform.forward * dir;

        force = direction.normalized * speed;

        StartCoroutine(UpdateBan(index, force));
    }

    IEnumerator UpdateBan(int index,Vector3 force)
    {
        float time = 0;
        while(time<MoveTime)
        {
            time += Time.deltaTime;
            ban[index].transform.position += force;
            yield return 0;
        }
    }
}
