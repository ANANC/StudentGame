using UnityEngine;
using System.Collections;

public class TransmitEvent : MonoBehaviour {

    static TransmitEvent _instance;
    public static TransmitEvent GetInstance
    {
        get
        {
            if (_instance == null)
            {
                _instance = GameObject.FindObjectOfType<TransmitEvent>();
            }
            return _instance;
        }
    }

    Transform DownTrasform;
    Transform Direction;
    void Start()
    {
        Direction = transform.FindChild("direction");
        DownTrasform = transform.FindChild("down");
    }

    public static void Distroy()
    {
        _instance = null;
    }

    public void ToTransmit()
    {
        Transform[] dir = new Transform[Direction.childCount];
        float distance = 0;
        bool IsFaceX = moveCommon.IsPlayerFaceX(DirectionState.forward) ? true : false;
        float DirAxis = IsFaceX ? gameCommon.Forward.x : gameCommon.Forward.z;
        int index = -1;
        for (int i = 0; i < Direction.childCount; i++)
        {
            dir[i] = Direction.GetChild(i);
            float dirDis = IsFaceX ? DownTrasform.position.x - dir[i].position.x : DownTrasform.position.z - dir[i].position.z;
            dirDis *= DirAxis;
            if(distance < dirDis)
            {
                if(dir[i].gameObject.name == "start1")
                {
                    GameplayUI.ChangeScene();
                    return;
                }
                index = int.Parse(dir[i].name);
                distance = dirDis;
            }
        }
        if (index != -1)
        {
            GameplayUI.Distroy();
            string name = UIcommon.nowLayerindex.ToString() + index.ToString();

            LoadUI.LoadName(name);
            LoadUI.GetInstance.StartLoad();
            
        }
    }


	
}
