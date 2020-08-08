using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class shop : MonoBehaviour {

    public GameObject ShopBackGround_GameObject;
    public GameObject ShopBar_GameObject;
    public GameObject ShopCamera;
    public GameObject ShopContent_EmptyGameObject;
    public GameObject ShopLeftButton;
    List<GameObject> ShopContent;
    int ShopContentCount;
    Vector3 nowPos;
    bool IsNeedMove;
    Vector3 CameraMovePos;
    Vector3 CameraTopPos;

    static shop instance;

    void Awake()
    {
        instance = this;
    }

    public static shop GetInstance()
    {
        return instance;
    }

	void Start () {
        ShopCamera.SetActive(false);
        ShopBackGround_GameObject.SetActive(false);

        ShopContent = new List<GameObject>();
        ShopContentCount = 0;
        nowPos = Vector3.zero;
        IsNeedMove = false;
        CameraMovePos = Vector3.zero;
        CameraTopPos = ShopCamera.transform.localPosition;

        EventDelegate.Add(ShopBar_GameObject.GetComponent<UIScrollBar>().onChange, Move);
        UIEventListener.Get(ShopLeftButton).onClick = Close;

        
	}
	
	public void Open()
    {
        ShopCamera.SetActive(true);
        ShopBackGround_GameObject.SetActive(true);

        if(IsNeedMove)
            ShopBar_GameObject.SetActive(true);
        else
            ShopBar_GameObject.SetActive(false);

    }

    public void Close(GameObject g)
    {
        ShopCamera.SetActive(false);
        ShopBackGround_GameObject.SetActive(false);

        nowPos = Vector3.zero;
        ShopContentCount = 0;
        IsNeedMove = false;
        CameraMovePos = Vector3.zero;
        for (int i = 0; i < ShopContent.Count; i++)
        {
            UIEventListener.Get(ShopContent[i]).onClick = null;
            Object.Destroy(ShopContent[i]);
        }
        ShopContent.Clear();
        ShopBar_GameObject.GetComponent<UIScrollBar>().barSize = 1;
    }

    public void AddContent(string name)
    {
        GameObject g = GameObject.Instantiate((GameObject)Resources.Load("Prefab/shop/commodity"));
        g.transform.parent = ShopContent_EmptyGameObject.transform;
        g.transform.localScale = Vector3.one;
        g.transform.localPosition= nowPos;
        g.name = name;

        GameObject textContent = g.transform.FindChild("textContent").gameObject;
        GameObject textMoney = g.transform.FindChild("textMoney").gameObject;
        GameObject sprite = g.transform.FindChild("sprite").gameObject;

        int money = propManager.GetInstance().GetSellMoney(name);
        int money_golden = money / 1000;
        int money_silver = (money - money_golden * 1000) / 100;
        int money_copper = money % 100;
        textContent.GetComponent<UILabel>().text = "<"+name+"> "+propManager.GetInstance().GetContent(name);
        textMoney.GetComponent<UILabel>().text = "出售金额：" + money_golden + "金" + money_silver + "银" + money_copper + "铜";

        sprite.GetComponent<UISprite>().spriteName = name;

        ShopContent.Add(g);
        UIEventListener.Get(ShopContent[ShopContentCount]).onClick = ShopContentClick;
        ShopContentCount += 1;
        nowPos.y -= 60;

        if(ShopContentCount>5)
        {
            IsNeedMove = true;
            ShopBar_GameObject.GetComponent<UIScrollBar>().barSize = 5f / (float)ShopContentCount;
            CameraMovePos.y = 60f * (ShopContentCount - 5)/100f;
        }
    }


    public void Move()
    {
        if(IsNeedMove)
        {
            Vector3 CameraPos = CameraMovePos;
            CameraPos.y = ShopBar_GameObject.GetComponent<UIScrollBar>().value * CameraMovePos.y*100f;
            ShopCamera.transform.localPosition = CameraTopPos-CameraPos;
        }
    }

    public void ShopContentClick(GameObject g)
    {
        Sell(g.name);

    }

    public void Sell(string name)
    {
        int money = propManager.GetInstance().GetSellMoney(name);
        if (attribute.GetInstance().UseMoney(money) == false)
        {
            attribute.GetInstance().AddSystemtext("不够钱购买该商品！");
            return;
        }
        propManager.GetInstance().AddProp(name);
    }

  
}
