using UnityEngine;
using System.Collections;

public class FireController : MonoBehaviour
{

    public int[] rangeValue;
    public Transform[] fires;
    public int roundValue;

    private Vector3[] initPos;
    private int[] waitTime;
    private int[] updateTime;
    private int fireValue;


    // Use this for initialization
    void Start()
    {
        waitTime = new int[fires.Length];
        updateTime = new int[fires.Length];
        initPos = new Vector3[fires.Length];
        for (int index = 0; index < waitTime.Length; index++)
        {
            waitTime[index] = Random.Range(rangeValue[0], rangeValue[1]);
            initPos[index] = fires[index].localPosition;
        }
        fireValue = DataMgr.Instance().GetFireValue();
        DataMgr.Instance().fireUpdateEvent += fireValueUpdateEvent;
    }

    // Update is called once per frame
    void Update()
    {
        Transform target;
        Vector3 pos;
        for (int index = 0; index < fires.Length; index++)
        {
            updateTime[index] += 1;

            if (updateTime[index] < waitTime[index])
            {
                continue;
            }
            waitTime[index] = Random.Range(10, 30);
            updateTime[index] = 0;

            target = fires[index];
            pos = target.localPosition + new Vector3(Random.Range(-2, 2), Random.Range(-2, 2), 0);
            if (pos.x - initPos[index].x > roundValue || pos.x - initPos[index].x < -roundValue)
            {
                pos.x = initPos[index].x;
            }
            if (pos.y - initPos[index].y > roundValue || pos.y - initPos[index].y < -roundValue)
            {
                pos.y = initPos[index].y;
            }
            target.localPosition = pos;
        }

    }

    private void fireValueUpdateEvent()
    {
        fireValue = DataMgr.Instance().GetFireValue();
        Vector3 scale = Vector3.one * (fireValue / 100f);
        for (int index = 0; index < fires.Length; index++)
        {
            fires[index].localScale = scale;
        }
    }
}
