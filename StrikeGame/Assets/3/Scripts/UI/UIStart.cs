using UnityEngine;
using DG.Tweening;
using UnityEngine.UI;
using System.Collections;

public class UIStart : MonoBehaviour {
    public Transform StartYuan;
    public GameObject Text;
    public Transform Menu;
    UImove moveEvent;


    void Start () {
        StartYuan.GetComponent<Button>().onClick.AddListener(StartYuanOnClick);
        StartYuan.gameObject.SetActive(true);
        Text.SetActive(true);
        Menu.gameObject.SetActive(false);

        moveEvent = UImove.GetInstance();

    }

    void StartYuanOnClick()
    {
        moveEvent.singleMove(StartYuan, 180, 0.8f, false, false);
        float y =  StartYuan.localPosition.y- Menu.localPosition.y - 260;
        moveEvent.singleMove(Menu, y, 1f, true, true);
    }
}
