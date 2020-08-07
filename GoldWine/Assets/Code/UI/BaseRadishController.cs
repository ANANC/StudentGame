using UnityEngine;
using System.Collections;

public class BaseRadishController : MonoBehaviour {

    public enum State
    {
        Active,//激活
        Catch,//抓住
        Disable//休眠
    }

    private State mState;

    private int Value;
    private bool Special = false;

    private Transform root;
    private UISprite Radish_Sprite;
    private GameObject Special_GO;

    private float Speed;
    private int Direction;

    private int ViewWidthRance;
    private int ViewHeightRance;


    public void InitViewComponent(Transform target)
    {
        root = target;

        Special_GO = root.FindChild("Special").gameObject;
        Radish_Sprite = root.FindChild("Radish").GetComponent<UISprite>();
    }

    public void Setup()
    {
        Value = 0;
        SetSpecial(false);
        SetPos(new Vector3(2000, 2000));
        mState = State.Disable;
    }

    public void SetData(int direction,int widthRance,int heightRance)
    {
        Direction = direction;
        Speed = Random.Range(0.2f, 2.5f) * Direction;
        Radish_Sprite.flip = direction == 1 ? UIBasicSprite.Flip.Nothing : UIBasicSprite.Flip.Horizontally;
        ViewWidthRance = widthRance;
        ViewHeightRance = heightRance;
        mState = State.Active;
    }

    public void Catch()
    {
        mState = State.Catch;
    }
    
    public void SetPos(Vector3 pos)
    {
        root.localPosition = pos;
    }

    public void UpdatePos(int ViewWidthRance)
    {
        if (mState != State.Active)
            return;

        Vector3 Pos = root.localPosition;

        SetPos(Pos + Vector3.right * Speed);

        if ((Direction == 1 && Pos.x > ViewWidthRance) || (Direction == -1 && Pos.x < -ViewWidthRance))
        {
            SetData(Direction * -1, ViewWidthRance, ViewHeightRance);
            Pos = root.localPosition;
            Pos.y = Random.Range(-ViewHeightRance, ViewHeightRance);
            SetPos(Pos);
        }
    }


    public void SetValue(int value)
    {
        Value = value; 
    }

    public void SetSpecial(bool isSpecial)
    {
        Special = isSpecial;
        Special_GO.SetActive(Special);
    }

    public int GetValue()
    {
        if (Special)
            return Value * 2;
        return Value;
    }
}
