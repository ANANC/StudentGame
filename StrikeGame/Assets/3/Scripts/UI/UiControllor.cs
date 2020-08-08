using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class UiControllor : MonoBehaviour {

    Text fragment;
    Text cactusTime;

	void Awake () {
        fragment = transform.FindChild("FragmentNumber").GetComponent<Text>();
        cactusTime = transform.FindChild("cactusTime").GetComponent<Text>();
        
        PropControllor.PropChangeEvent += Onchange;
	}
	
    void Onchange(PropType type)
    {
        if(type == PropType.all)
        {
            fragment.text = PropControllor.GetInstance().FragmentNumber.ToString();
            cactusTimeChange();
        }
        if (type == PropType.fragment)
            fragment.text = PropControllor.GetInstance().FragmentNumber.ToString();
        if (type == PropType.cactus)
            cactusTimeChange();
    }

    void cactusTimeChange()
    {
        int cac = PropControllor.GetInstance().CactusTime;
        cactusTime.text = cac.ToString();
        if(cac<11)
            cactusTime.color = Color.red;
        
        if(cac == 80)
            cactusTime.color = Color.black;
    }
}
