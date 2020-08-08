using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class attribute : MonoBehaviour
{
    /*人物属性*/
    //血值
    float MaxBlood;
    float nowBlood;
    public GameObject BloodGameObject;
    public GameObject BloodTextGameObject;

    //饥饿值
    float MaxHunger;
    float nowHunger;
    public GameObject HungerGameObject;
    public GameObject HungerTextGameObject;

    //经验值
    float Maxexperience;
    float nowexperience;
    public GameObject ExperienceTextGameObject;
    public GameObject ExperienceGameObject;

    //金钱
    int money_copper;
    int money_silver;
    int money_golden;
    public GameObject moneyCopperGameObejct;
    public GameObject moneySilverGameObejct;
    public GameObject moneyGoldenGameObejct;

    //等级
    int nowgrade;
    public GameObject GradeTextGameObject;


    /*系统显示文字框*/
    public GameObject SystemText;

    /*任务提示文字框*/
    public GameObject TaskText;
    Dictionary<string,string> tasktipText;

    static attribute instance;

    void Awake()
    {
        instance = this;
    }

    public static attribute GetInstance()
    {
        return instance;
    }

	void Start () {
        MaxBlood = 100;
        nowBlood = 100;
        MaxHunger = 10;
        nowHunger = 0;
        Maxexperience = 500;
        nowexperience = 0;
        nowgrade = 1;
        money_copper = 0;
        money_silver = 0;
        money_golden = 0;

        BloodGameObject = GameObject.Find("blood");
        BloodTextGameObject = GameObject.Find("bloodtext");
        HungerGameObject = GameObject.Find("hunger");
        HungerTextGameObject = GameObject.Find("hungertext");
        ExperienceTextGameObject = GameObject.Find("experiencetext");
        ExperienceGameObject = GameObject.Find("experience");
        GradeTextGameObject = GameObject.Find("gradetext");


        BloodGameObject.GetComponent<UISlider>().value = nowBlood / MaxBlood;
        BloodTextGameObject.GetComponent<UILabel>().text = nowBlood.ToString() + "/" + MaxBlood.ToString();
        HungerGameObject.GetComponent<UISlider>().value = nowHunger / MaxHunger;
        HungerTextGameObject.GetComponent<UILabel>().text = nowHunger.ToString() + "/" + MaxHunger.ToString();
        ExperienceTextGameObject.GetComponent<UILabel>().text = nowexperience.ToString() + "/" + Maxexperience.ToString();
        ExperienceGameObject.GetComponent<UISlider>().value = nowexperience / Maxexperience;
        GradeTextGameObject.GetComponent<UILabel>().text = "等级:" + nowgrade;
        moneyCopperGameObejct.GetComponent<UILabel>().text = money_copper.ToString();
        moneySilverGameObejct.GetComponent<UILabel>().text = money_silver.ToString();
        moneyGoldenGameObejct.GetComponent<UILabel>().text = money_golden.ToString();
        SetMoneyActive(false);

        TaskText.GetComponent<UITextList>().Add("任务提示:");
        TaskText.transform.GetChild(0).GetComponent<UILabel>().pivot = UIWidget.Pivot.TopLeft;
        tasktipText = new Dictionary<string, string>();
	}

    public void SetProp(property p)
    {
        if (p.key == PropertyKey.Blood)
        {
            nowBlood += p.value;
            if (nowBlood > MaxBlood)
                nowBlood = MaxBlood;
            if (nowBlood < 0)
                nowBlood = 0;
            BloodGameObject.GetComponent<UISlider>().value = nowBlood / MaxBlood;
            BloodTextGameObject.GetComponent<UILabel>().text = nowBlood.ToString() + "/" + MaxBlood.ToString();
        }
        if (p.key == PropertyKey.Hunger)
        {
            nowHunger += p.value;
            if (nowHunger < 0)
                nowHunger = 0;
            if (nowHunger > MaxHunger)
                nowHunger = MaxHunger;
            HungerGameObject.GetComponent<UISlider>().value = nowHunger / MaxHunger;
            HungerTextGameObject.GetComponent<UILabel>().text = nowHunger.ToString() + "/" + MaxHunger.ToString();
        }
    }


    public void AddExperience(int i)
    {
        nowexperience += i;
        if (nowexperience > Maxexperience)
        {
            while (nowexperience > Maxexperience)
            {
                AddMaxExperience(500*nowgrade);
                AddGrade(1);
            }
        }
        ExperienceTextGameObject.GetComponent<UILabel>().text = nowexperience.ToString() + "/" + Maxexperience.ToString();
        ExperienceGameObject.GetComponent<UISlider>().value = nowexperience / Maxexperience;

    }

    public void AddMaxExperience(int i)
    {
        Maxexperience += i;
        ExperienceTextGameObject.GetComponent<UILabel>().text = nowexperience.ToString() + "/" + Maxexperience.ToString();
        ExperienceGameObject.GetComponent<UISlider>().value = nowexperience / Maxexperience;

    }

    public void AddMaxBlood(int i)
    {
        MaxBlood += i;
        BloodGameObject.GetComponent<UISlider>().value = nowBlood / MaxBlood;
        BloodTextGameObject.GetComponent<UILabel>().text = nowBlood.ToString() + "/" + MaxBlood.ToString();

    }

    public void AddMaxHunger(int i)
    {
        MaxHunger += i;
        HungerGameObject.GetComponent<UISlider>().value = nowHunger / MaxHunger;
        HungerTextGameObject.GetComponent<UILabel>().text = nowHunger.ToString() + "/" + MaxHunger.ToString();

    }

    public void AddGrade(int i)
    {
        AddSystemtext("你升了一级！最大血值增加" + 50 * nowgrade + ",最大饥饿值增加" + 5 * nowgrade + ".");

        AddMaxBlood(50*nowgrade);
        AddMaxHunger(5 * nowgrade);
        nowgrade += i;
        GradeTextGameObject.GetComponent<UILabel>().text = "等级:" + nowgrade;

        taskManager.GetInstance().UpdateAccpectGradeTask();
    }

    public bool UseMoney(int i)
    {
        int nowMoney = money_golden * 1000 + money_silver * 100 + money_copper;
        if (i > nowMoney)
            return false;
        nowMoney -= i;
        money_golden = nowMoney / 1000;
        money_silver = (nowMoney - money_golden * 1000) / 100;
        money_copper = nowMoney % 100;
        moneyCopperGameObejct.GetComponent<UILabel>().text = money_copper.ToString();
        moneySilverGameObejct.GetComponent<UILabel>().text = money_silver.ToString();
        moneyGoldenGameObejct.GetComponent<UILabel>().text = money_golden.ToString();
        return true;
    }

    public void AddMoney(int i)
    {
        int nowMoney = money_golden * 1000 + money_silver * 100 + money_copper;
        nowMoney += i;
        money_golden = nowMoney / 1000;
        money_silver = (nowMoney - money_golden*1000) / 100;
        money_copper = nowMoney % 100;
        moneyCopperGameObejct.GetComponent<UILabel>().text = money_copper.ToString();
        moneySilverGameObejct.GetComponent<UILabel>().text = money_silver.ToString();
        moneyGoldenGameObejct.GetComponent<UILabel>().text = money_golden.ToString();
    }

    public void SetMoneyActive(bool b)
    {
        moneyCopperGameObejct.SetActive(b);
        moneySilverGameObejct.SetActive(b);
        moneyGoldenGameObejct.SetActive(b);
    }

    public int Grade
    {
        get
        {
            return nowgrade;
        }
    }

    public void AddSystemtext(string s)
    {
        SystemText.GetComponent<UITextList>().Add(s);
    }

    public float Getblood()
    {
        return nowBlood;
    }

    public float GetHungerRotio()
    {
        return nowHunger/MaxHunger;
    }

    public void AddTaskText(string task,string s,bool IsRender = true)
    {
        if (tasktipText.ContainsKey(task) == false)
            tasktipText.Add(task, s);
        else
        {
            tasktipText[task] = s;
            if (IsRender == false)
                tasktipText.Remove(task);
        }
        TaskText.GetComponent<UITextList>().Clear();
        TaskText.GetComponent<UITextList>().Add("任务提示:");
        foreach (KeyValuePair<string, string> k in tasktipText)
            TaskText.GetComponent<UITextList>().Add(k.Value);

    }
}
