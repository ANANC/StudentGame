using UnityEngine;
using System.Collections;

public class playerSence : MonoBehaviour {

    float time;//沙漠，仙人掌倒计时

    void Start()
    {
        time = 0;
    }

    void Update()
    {
        time += Time.deltaTime;
        if(time>1)
        {
            time = 0;
            PropControllor.GetInstance().CactusTime -= 1;
            PropControllor.GetInstance().propChangeEvent(PropType.cactus);
        }

        if(Input.GetKeyDown(KeyCode.LeftControl))
        {
            Collider[] colliders = Physics.OverlapSphere(transform.position, 3f, 1 << LayerMask.NameToLayer("cactus"));

            if(colliders.Length>0)
            {
                PropControllor.GetInstance().CactusTime = 80;
                PropControllor.GetInstance().propChangeEvent(PropType.cactus);
            }
        }
    }

    void OnTriggerEnter(Collider Target)
    {
        if (Target.gameObject.tag == tags.fragment)
        {
            Target.gameObject.SetActive(false);
            PropControllor.GetInstance().FragmentNumber += 1;
            PropControllor.GetInstance().propChangeEvent(PropType.fragment);
        }
    }

}
