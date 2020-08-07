using UnityEngine;
using System.Collections;

public class RodBoxController : MonoBehaviour {

    private int RadishIndex = -1;

    private Transform root;
    private BoxCollider RodBox;
    private float PosOffectY;

    public delegate void CatchEvent(Transform Rod, int Index);
    public delegate void EatEvent();

    public static CatchEvent catchEvent;
    public static EatEvent eatEvent;

    void Start () {
        root = this.transform;
        RodBox = root.GetComponent<BoxCollider>();
        PosOffectY = RodBox.size.y / 2f;
        RadishIndex = -1;
    }

    public void UpdatePos(float Height, float RotateValue)
    {
        Vector3 pos = Vector3.zero;
        if (RotateValue == 0)
        {
            pos.y = -Height + PosOffectY;
        }
        else
        {
            int DirX = RotateValue >= 0 ? 1 : -1;
            RotateValue = Mathf.Abs(RotateValue);
            float f = (RotateValue * 3.14f) / 180;
            float Sin = Mathf.Sin(f);
            float Cos = Mathf.Cos(f);
            pos.x = DirX * Height * Sin;
            pos.y = -1 * (Height - PosOffectY) * Cos;
        }

        root.transform.localPosition = pos;
    }

    public void SetBoxEnable(bool enable)
    {
        RodBox.enabled = enable;
    }

    void OnTriggerEnter(Collider other)
    {
        SetBoxEnable(false);

        GameObject Radish = other.gameObject;

        RadishIndex = System.Convert.ToInt32(Radish.name);

        if (catchEvent != null) catchEvent(root, RadishIndex);

         Vector3 RadishPos = Radish.transform.localPosition;
        RadishPos.y += PosOffectY;

        Radish.transform.localPosition = RadishPos;
    }

    public void EatRadish()
    {
        SetBoxEnable(true);

        if (RadishIndex == -1) return;

        int Value = RadishManager.Instance.EatRadish(RadishIndex);

        if (eatEvent != null) eatEvent();

        RadishIndex = -1;
    }

    public void InitState()
    {
        RadishIndex = -1;
    }
}
