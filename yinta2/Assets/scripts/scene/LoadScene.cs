using UnityEngine;
using System.Collections;
using UnityEngine.SceneManagement;
public class LoadScene //: MonoBehaviour
{
    static AsyncOperation scene;

    public delegate void loadover();
    public static event loadover loadoverEvent;


    public static void loadScene(string name)
    {
        GameplayUI.ChangeScene(); 
        scene = SceneManager.LoadSceneAsync(name);
        scene.allowSceneActivation = false;
        // StartCoroutine(load());
        if (UIcommon.loadsceneName == "00")
        { UI_load.startCoroutine(load()); }
        else
        {
            UI_game.startCoroutine(load());
        }
    }

    public static void Loadin()
    {
        scene.allowSceneActivation = true;
    }

    static IEnumerator load()
    {
        while (scene.progress < 0.88){
            yield return 0;
        }
        loadoverEvent();
    }
}

