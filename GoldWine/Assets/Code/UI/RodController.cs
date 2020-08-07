using UnityEngine;
using System.Collections;

public class RodController : MonoBehaviour {

    private readonly int MinLength = 50;
    private readonly int MaxLength = 530;

    private readonly int MinRotateValue = -45;
    private readonly int MaxRotateValue = 45;

    private Transform root;
    private UISprite Rod_Sprite;
    private RodBoxController RodBox;

    private bool ToCatch = false;

    private int Direction = 1;
    private int Speed = 5;

    private int RotateDirection = 1;
    private int RotateValue =0;
	void Start () {
        root = this.transform;

        Rod_Sprite = root.FindChild("Rod").GetComponent<UISprite>();
        RodBox = root.FindChild("RodBox").gameObject.AddComponent< RodBoxController>();

        GameDataController.initViewEvent += InitState;
        RodBoxController.catchEvent += CatchEvent;
    }

    void Update()
    {
        if (!RadishManager.Instance.GamePlaying) return;

        if (Input.GetKeyDown(KeyCode.Space))
        {
            if (!ToCatch) { ToCatch = true; Direction = 1; RodBox.SetBoxEnable(true); }
        }

        if(ToCatch)
        {
            Rod_Sprite.height += Direction* Speed;
            if (Rod_Sprite.height >= MaxLength)
            {
                Direction *= -1;
                RodBox.SetBoxEnable(false);
            }
            if (Rod_Sprite.height <= MinLength)
            {
                ToCatch = false;
                RodBox.EatRadish();
            }
        }
        else
        {
            Rod_Sprite.transform.Rotate(0, 0, RotateDirection);
            RotateValue += RotateDirection;
            if ((RotateValue >= MaxRotateValue) ||
                (RotateValue <= MinRotateValue))
                RotateDirection *= -1;
        }

        RodBox.UpdatePos(Rod_Sprite.height, RotateValue);
    }

    private void CatchEvent(Transform Rod,int Index)
    {
        if (Direction == 1) Direction *= -1;
    }

    public void InitState()
    {
        ToCatch = false;
        Direction = 1;
        Rod_Sprite.height = MinLength;
        RotateValue = 0;
        Rod_Sprite.transform.Rotate(0, 0, 0);
        RodBox.InitState();
        RodBox.UpdatePos(Rod_Sprite.height, RotateValue);
    }
}
