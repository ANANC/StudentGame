 using UnityEngine;
using System.Collections;

public class UI_start : MonoBehaviour {

    void Start()
    {
        Screen.SetResolution(1024, 624, false);
        if(UIcommon.loadsceneName == "start")
        {
            load(false);
        }
    }

	void Update () {
    if(Input.anyKeyDown)
        {
            load(true);
        }	
	}

    void load(bool IsFirst)
    {
        if (IsFirst)
        {
            UIcommon.GetPrefab(prefabType.ui, uiprefabName.newGame.ToString());
        }
        else
        {
            UIcommon.GetPrefab(prefabType.ui, uiprefabName.select.ToString());
        }
        Destroy(this.gameObject);
    }
}
