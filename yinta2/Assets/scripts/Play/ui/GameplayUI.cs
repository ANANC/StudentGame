using UnityEngine;
using System.Collections;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class GameplayUI : MonoBehaviour {

    public static chipUI chip;

   // private Transform backButton;

    //static Transform Interlude;
    //static LoadUI loadui;

    void Start () {
        UIcommon.IsStart = false;

      //  if(Interlude == null)
      //      Interlude = transform.FindChild("Interlude");
      //  loadui = LoadUI.GetInstance;
      //  loadui.LoadTransform(Interlude);
      //  loadui.LoadOver();
        //Interlude.gameObject.SetActive(false);

        Transform chiptra = transform.FindChild("chipUI");
        chip = chipUI.chipUIInstance(chiptra);

      //  backButton = transform.FindChild("backbutton");
      //  backButton.GetComponent<Button>().onClick.AddListener(ChangeScene);
    }

    public  static void ChangeScene()
    {
        Distroy();
        //LoadUI.LoadName("start1");
        //loadui.LoadTransform(Interlude);
       // Interlude = null;
        //loadui.StartLoad();
    }
	
    public static void Distroy()
    {
        if (chip == null)
            return;
        chip.Distroy();
        gameCommon.Distroy();
        moveCommon.Distroy();
        TransmitEvent.Distroy();
    }
}
