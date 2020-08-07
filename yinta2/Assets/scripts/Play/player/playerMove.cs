using UnityEngine;
using System.Collections;

public class playerMove : MonoBehaviour {

    Transform myTransform;
    playerStateControllor stateInit;

    public static bool IsDomove = false;
    void Start () {
        myTransform = this.transform;
        
        stateInit = gameCommon.playerStateControllorGetInstance;
        stateInit.stateInit();

        GameObject.FindGameObjectWithTag("music").GetComponent<AudioSource>().volume = UIcommon.MusiceffectPower;

    }

    public void Move(Vector3 speed)
    {
        myTransform.position += speed;
       
    }

    public void ToStartCoroutine(IEnumerator ienumberator)
    {
        StartCoroutine(ienumberator);
    }

    void Update()
    {
        if (!IsDomove)
            return;

        if (Input.GetKeyUp(KeyCode.LeftArrow))
        {
            stateInit.Input(KeyCode.LeftArrow, true);
        }
        if (Input.GetKeyUp(KeyCode.RightArrow))
        {
            stateInit.Input(KeyCode.RightArrow, true);
        }
            if (Input.GetKey(KeyCode.LeftArrow))
            {
            stateInit.Input(KeyCode.LeftArrow);
            }
            if (Input.GetKey(KeyCode.RightArrow))
            {
            stateInit.Input(KeyCode.RightArrow);
            }
            if (Input.GetKey(KeyCode.UpArrow))
            {
            stateInit.Input(KeyCode.UpArrow);
            }
            if (Input.GetKey(KeyCode.DownArrow))
            {
            stateInit.Input(KeyCode.DownArrow);
            }
            if (Input.GetKeyDown(KeyCode.A))
            {
            stateInit.Input(KeyCode.A);
            }
            if (Input.GetKeyDown(KeyCode.D))
            {
            stateInit.Input(KeyCode.D);
            }
            if (Input.GetKeyDown(KeyCode.Space))
            {
            stateInit.Input(KeyCode.Space);
            }
            if (Input.GetKeyDown(KeyCode.LeftControl))
            {
            stateInit.Input(KeyCode.LeftControl);
            }
        
    }

}
