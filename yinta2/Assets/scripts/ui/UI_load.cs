using UnityEngine;
using System.Collections;

public class UI_load : MonoBehaviour {
    Transform title;
    Transform ThisTransform;
    static MonoBehaviour ower;
    //LoadScene loadScene;
    void Start()
    {
        ThisTransform = this.transform;
        title = ThisTransform.FindChild("loadTitle");
        //loadScene = new LoadScene();
        LoadScene.loadoverEvent += loadover;
        StartCoroutine(load());
    }
	
    IEnumerator load()
    {
        ower = ThisTransform.GetComponent<MonoBehaviour>();
        yield return new WaitForSeconds(0.5f);
        SetAnimatorRun(false);
        LoadScene.loadScene(UIcommon.loadsceneName);
    }

    void loadover()
    {
        if (ThisTransform == null)
            return;

        SetAnimatorRun(true);
        StartCoroutine(runover());
    }

    IEnumerator runover()
    {
        yield return new WaitForSeconds(1.8f);
        LoadScene.Loadin();
    }

    void SetAnimatorRun(bool b)
    {
        for (int i = 0; i < title.childCount; i++)
        {
            title.GetChild(i).GetComponent<Animator>().enabled = b;
        }
    }

    public static void startCoroutine(IEnumerator ienumerator)
    {
        ower.StartCoroutine(ienumerator);
    }


}
