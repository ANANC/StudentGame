using UnityEngine;
using System.Collections;
using UnityEngine.SceneManagement;

public class LoadUI : MonoBehaviour
{
    static  LoadUI _instance;
    public static LoadUI GetInstance
    {
        get
        {
            if (_instance == null)
                _instance = GameObject.FindObjectOfType<LoadUI>();
            return _instance;
        }
    }

    Transform interludeTra;
    Transform[] sphere;
    Transform[] cubes;
    public static string loadname;

    void Awake()
    {
        sphere = new Transform[4];
        cubes = new Transform[70];
    }

    public void Distroy()
    {
        _instance = null;
        //if(!UIcommon.IsStart)
         //   GameplayUI.Distroy();
    }
    
    public void LoadTransform(Transform Interlude)
    {
        interludeTra = Interlude;

        for (int i = 0; i <4; i++)
        {
            sphere[i] = interludeTra.FindChild("sphere/"+i.ToString());

        }

        Transform newTra = interludeTra.FindChild("new/cubes");

        for (int i = 0; i < newTra.childCount; i++)
        {
            cubes[i] = newTra.GetChild(i);
            cubes[i].gameObject.SetActive(false);
        }
    }

    public static void LoadName(string name)
    {
        loadname = name;
    }
	
    public void StartLoad()
    {
        interludeTra.gameObject.SetActive(true);
        StartCoroutine(Load());
    }

    IEnumerator Load()
    {
        AsyncOperation scene = SceneManager.LoadSceneAsync(loadname);
        scene.allowSceneActivation = false;

        int index = 1;
        int AllIndex = cubes.Length;
        float toProgress = 0;
        while (toProgress < 0.9f)
        {
            toProgress = scene.progress;
            //while (toProgress> index *0.2f && index <4)
            //{
            //    sphere[index].gameObject.SetActive(true);
            //    index += 1;
            //    yield return 10;
            //}

            if(index!=AllIndex)
            {
                index += 1;
                cubes[index-1].gameObject.SetActive(true);
            }
            yield return 0;
        }
        
        while(index!= AllIndex)
        {
            cubes[index - 1].gameObject.SetActive(true);
            index += 1;
            yield return 0;
        }

        Distroy();
        scene.allowSceneActivation = true;

        yield return 0;
    }

    public void LoadOver()
    {
        StartCoroutine(Over());
    }

    IEnumerator Over()
    {
        int AllIndex = cubes.Length;
        int index = AllIndex;

        for (int i = 0; i < AllIndex; i++)
        {
            cubes[i].gameObject.SetActive(true);
        }

        while (index != 1)
        {
            cubes[index - 1].gameObject.SetActive(false);
            index -= 1;
            
            yield return 0;
        }
        interludeTra.gameObject.SetActive(false);
    }
}
