using UnityEngine;
using System.Collections;

public class SceneCommon : MonoBehaviour {
   

   public static void IsTouchChip()
    {
        float dircoe = 1;
        RaycastHit hit;
        for (int i = 0; i < 2; i++)
        {
            if (moveCommon.DoubleRaycast(true, false, RaycastLay.dailyTag, Vector3.zero, DirectionState.forward, dircoe, out hit, 100))
            {
                GameObject gameObject = hit.collider.gameObject;
                if (gameObject.tag == gameCommon.chipTag)
                {
                    GameplayUI.chip.OnCollisionEnter(gameObject.name);
                    gameObject.SetActive(false);
                    break;
                }
            }
            dircoe *= -1;
        }
    }

    public static void IsTouchTransmit()
    {
        RaycastHit hit;
        if (moveCommon.DoubleRaycast(true,false,RaycastLay.dailyTag,Vector3.zero,DirectionState.forward,1,out hit,1000))
        {
            GameObject gameObject = hit.collider.gameObject;
            if (gameObject.tag == gameCommon.transmitTag)
            {
                TransmitEvent.GetInstance.ToTransmit();
            }
        }
    }
}
