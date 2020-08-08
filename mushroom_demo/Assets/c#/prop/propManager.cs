using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class shortcutProp
{
    public shortcutProp(GameObject g,string n)
    {
        gameobject = g;
        name = n;
    }
    GameObject gameobject;
    string name;
    public GameObject Gameobject
    {
        get
        {
            return gameobject;
        }
    }
    public string Name
    {
        get
        {
            return name;
        }
    }
}

public class propManager : MonoBehaviour
{
    Dictionary<string,prop> list;
    //快捷键的物体
    Dictionary<string, shortcutProp> shortcutList;

    int lineRight;//列
    int lineDown;//行
    float width;
    float height;
    Vector3 initPos;
    Vector3 ShortpropDeviationPos;
    bool IsDrag;

    //GameObject
    public GameObject substance;//物体栏
    public GameObject SubstanceTipContent;//框-tip
    public GameObject SubstanceTipContenttext;//文字-tip
    public GameObject substancecontentEmpty;//空-管理物体
    Dictionary<string,GameObject> substanceContent;//物体
    public GameObject shortcutAllGameObeject;//快捷键位的管理物体
    List<GameObject> shortcutKey;//快捷键位

    

    static propManager instance;


    public static propManager GetInstance()
    {
        return instance;
    }

    void Awake()
    {
        instance = this;
    }

    void Start()
    {
        list = new Dictionary<string, prop>();
        shortcutList = new Dictionary<string, shortcutProp>();
        substanceContent = new Dictionary<string, GameObject>();

        lineDown = 6;
        lineRight = 5;
        width = 38;
        height = 41;

        IsDrag = false;

        SubstanceTipContent.SetActive(false);
        substance.SetActive(false);
        
        initAdd();

        UIRoot root = GameObject.FindObjectOfType<UIRoot>();
        if (root != null)
        {
            float s = (float)root.activeHeight / Screen.height;
            float ScreenHeight = Mathf.CeilToInt(Screen.height * s);
            float ScreenWidth = Mathf.CeilToInt(Screen.width * s);

            ShortpropDeviationPos.x = (ScreenWidth / 2f );//+ substance.transform.localPosition.x);// * ScreenWidth / ScreenHeight;
            ShortpropDeviationPos.y = (ScreenHeight / 2f );//+ substance.transform.localPosition.y);//* ScreenWidth / ScreenHeight;
            
        }

        initPos = new Vector3(-76.8f, 87.3f, 0);

        shortcutKey = new List<GameObject>();
        for (int i = 0; i < shortcutAllGameObeject.transform.childCount; i++)
            shortcutKey.Add(shortcutAllGameObeject.transform.GetChild(i).gameObject);
        
	}

    void onHover(GameObject go, bool isOver)
    {
        if (isOver)
            SetTipOpen(go.name,go.transform.position);
        else
            SetTipClose();
    }

    void onPress(GameObject go, bool isPressed)
    {
        if(isPressed)
        {
            if (Input.GetMouseButtonDown(0))
            {
                if (go.tag == "prop")
                {
                    MarkClone(go.name, go.transform.localPosition);
                    SetTipClose();

                }
            }
            if (Input.GetMouseButtonDown(1))
            {
                property p = UsedProp(go.name, go.tag);
                attribute.GetInstance().SetProp(p);
            }
        }
        else
        {
            if(go.tag =="shortcutProp" && IsDrag == true)
            {
                RaycastHit hit;
                //Ray ray = new Ray(go.transform.position, new Vector3(0, 0, 1));//不知道为什么这样不可以成功
                Ray ray = new Ray(UICamera.lastWorldPosition, new Vector3(0, 0, 1));
                if(Physics.Raycast(ray,out hit,20f))
                {
                    if(hit.collider.gameObject.tag =="shortcutKey")
                    {
                        DragDown(go.name, true, hit.collider.gameObject.transform.position);
                    }
                }
                else
                    DragDown(go.name, false);
                IsDrag = false;
                
            }
        }
    }

    void onDrag(GameObject go, Vector2 delta)
    {
        IsDrag = true;

        Vector3 pos = UICamera.lastTouchPosition;

        pos -= ShortpropDeviationPos;
        Drag(go.name, pos);
    }


    public void initAdd()
    {
        prop f0 = new food_0(substance.transform);
        list.Add(f0.Name, f0);
        f0 = new food_1(substance.transform);
        list.Add(f0.Name, f0);
        f0 = new food_2(substance.transform);
        list.Add(f0.Name, f0);
        f0 = new food_3(substance.transform);
        list.Add(f0.Name, f0);
        f0 = new food_4(substance.transform);
        list.Add(f0.Name, f0);
        f0 = new food_5(substance.transform);
        list.Add(f0.Name, f0);
        f0 = new food_6(substance.transform);
        list.Add(f0.Name, f0);
        f0 = new food_7(substance.transform);
        list.Add(f0.Name, f0);

        f0 = new sundires_0(substance.transform);
        list.Add(f0.Name, f0);
        f0 = new sundires_1(substance.transform);
        list.Add(f0.Name, f0);
        f0 = new sundires_2(substance.transform);
        list.Add(f0.Name, f0);
        f0 = new sundires_3(substance.transform);
        list.Add(f0.Name, f0);
        f0 = new sundires_4(substance.transform);
        list.Add(f0.Name, f0);
        f0 = new sundires_5(substance.transform);
        list.Add(f0.Name, f0);
    }

    public void Open()
    {
        substance.SetActive(true);
        attribute.GetInstance().SetMoneyActive(true);
        UpdateSubstanceContent();
    }

    void UpdateSubstanceContent()
    {
        int nowLineRight = 0;
        int nowLineDown = 0;

        bool IsNeedAgain = false;
         foreach(KeyValuePair<string,prop> k in list)
         {
             if (nowLineDown == lineDown)
                 return;
             if(k.Value.PossesstionNunber > 0)
             {
                 if (substanceContent.ContainsKey(k.Value.Name) == false)
                 {
                     Vector3 pos = initPos;

                     nowLineRight = substanceContent.Count % lineRight;
                     nowLineDown = substanceContent.Count / lineDown;
                     pos.x += nowLineRight * width;
                     pos.y -= nowLineDown * height;

                     GameObject g = GameObject.Instantiate((GameObject)Resources.Load("Prefab/shop/substance"));
                     g.transform.parent = substancecontentEmpty.transform;
                     g.transform.localPosition = pos;
                     g.transform.localScale = Vector3.one;
                     g.transform.FindChild("sprite").GetComponent<UISprite>().spriteName = k.Value.Name;
                     g.transform.FindChild("number").GetComponent<UILabel>().text = k.Value.PossesstionNunber.ToString();
                     g.name = k.Value.Name;
                     substanceContent.Add(k.Value.Name, g);

                     UIEventListener.Get(g).onHover = onHover;
                     UIEventListener.Get(g).onPress = onPress;
                     UIEventListener.Get(g).onDrag = onDrag;
                 }
                 else
                 {
                     substanceContent[k.Value.Name].transform.FindChild("number").GetComponent<UILabel>().text = k.Value.PossesstionNunber.ToString();
                 }
             }
             else
             {
                 if (substanceContent.ContainsKey(k.Value.Name) == true)
                 {
                     Object.Destroy(substanceContent[k.Value.Name]);
                     substanceContent.Remove(k.Value.Name);
                     IsNeedAgain = true;
                 }
             }
         }

        foreach(KeyValuePair<string, shortcutProp> shortProp in shortcutList)
        {
            shortProp.Value.Gameobject.transform.FindChild("number").GetComponent<UILabel>().text = GetPossesstionNunber(shortProp.Value.Name).ToString();
        }
        
        if(IsNeedAgain)
        {
            int number = 0;
            foreach(KeyValuePair<string, GameObject> k in substanceContent)
            {
                Vector3 pos = initPos;
                
                nowLineRight = number % lineRight;
                nowLineDown = number / lineDown;
                pos.x += nowLineRight * width;
                pos.y -= nowLineDown * height;
                number++;

                k.Value.transform.localPosition = pos;
            }
        }
    }

    public void Close()
    {
        substance.SetActive(false);
        attribute.GetInstance().SetMoneyActive(false);
    }

    public void SetTipOpen(string String,Vector3 pos)
    {
        string s = "名称：";
        s += String;
        s += "\n介绍：" + list[String].Content;
        //s += "\n数量：" + list[String].PossesstionNunber.ToString();

        SubstanceTipContent.SetActive(true);
        SubstanceTipContenttext.GetComponent<UILabel>().text = s;

        SubstanceTipContent.transform.position = new Vector3(pos.x - 0.46f, pos.y, 0);
    }
	
    public void SetTipClose()
    {
        SubstanceTipContent.SetActive(false);
        
    }

    public bool ContainsKey(string s)
    {
        return list.ContainsKey(s);
    }

    public string MarkClone(string s,Vector3 pos)
    {
        if (list.ContainsKey(s))
        {

            string Name = s + shortcutList.Count.ToString();

            GameObject g = GameObject.Instantiate((GameObject)Resources.Load("Prefab/shop/substance"));
            g.transform.parent = substancecontentEmpty.transform;
            g.transform.localPosition = pos;
            g.transform.localScale = Vector3.one;
            g.transform.FindChild("sprite").GetComponent<UISprite>().spriteName = s;
            g.transform.FindChild("number").GetComponent<UILabel>().text = list[s].PossesstionNunber.ToString();
            g.name = s;

            UIEventListener.Get(g).onHover = onHover;
            UIEventListener.Get(g).onPress = onPress;
            UIEventListener.Get(g).onDrag = onDrag;

            shortcutList.Add(Name, new shortcutProp(substanceContent[s], s));
            substanceContent[s] = g;

            shortcutList[Name].Gameobject.name = Name;
            shortcutList[Name].Gameobject.tag = "shortcutProp";
            shortcutList[Name].Gameobject.transform.parent = substance.transform.parent;
            shortcutList[Name].Gameobject.transform.FindChild("number").gameObject.SetActive(false);
            UIEventListener.Get(shortcutList[Name].Gameobject).onHover = null;

            return Name;
        }

        
        return null;
    }

    public void MarkDrag(string s)
    {
        if(shortcutList.ContainsKey(s))
        {
            shortcutList[s].Gameobject.GetComponent<BoxCollider>().enabled = false;
        }
    }

    public void Drag(string s,Vector3 pos)
    {
        shortcutList[s].Gameobject.transform.localPosition = pos;
    }

    public void DragDown(string s, bool IsLeave, Vector3 pos = new Vector3())
    {
        if (IsLeave == false)
        {
            UIEventListener.Get(shortcutList[s].Gameobject).onPress = null;
            UIEventListener.Get(shortcutList[s].Gameobject).onDrag = null;

            Object.Destroy(shortcutList[s].Gameobject);
            shortcutList.Remove(s);
            return;
        }

        pos.z = 0.1f;
        shortcutList[s].Gameobject.transform.position = pos;
        shortcutList[s].Gameobject.transform.FindChild("number").GetComponent<UILabel>().text = GetPossesstionNunber(shortcutList[s].Name).ToString();
        shortcutList[s].Gameobject.transform.FindChild("number").gameObject.SetActive(true);
    }


    bool ShortcutContainsName(string s)
    {
        foreach (shortcutProp p in shortcutList.Values)
        {
            if (p.Name == s)
                return true;
        }
        return false;
    }

    public property UsedProp(string s, string tab)
    {
        string name = null;

        if (tab == "prop")
        {
            if (list[s].PropertyValue.key == PropertyKey.Nothing)
            {
                property p;
                p.key = PropertyKey.Nothing;
                p.value = 0;
                return p;
            }

            name = s;
            list[s].PossesstionNunber -= 1;
            if (ShortcutContainsName(name) == true)
            {
                if (list[name].PossesstionNunber == 0)
                {
                    string RemoveNumber = null;
                    foreach (KeyValuePair<string, shortcutProp> k in shortcutList)
                    {
                        if (k.Value.Name == s)
                        {
                            Object.Destroy(k.Value.Gameobject);
                            RemoveNumber = k.Key;
                            break;
                        }
                    }
                    if(RemoveNumber!=null)
                        shortcutList.Remove(RemoveNumber);
                }
            }
        }
        if (tab == "shortcutProp")
        {
            name = shortcutList[s].Name;

            if (list[name].PropertyValue.key == PropertyKey.Nothing)
            {
                property p;
                p.key = PropertyKey.Nothing;
                p.value = 0;
                return p;
            }

            list[name].PossesstionNunber -= 1;
            if (list[name].PossesstionNunber == 0)
            {
                Object.Destroy(shortcutList[s].Gameobject);
                shortcutList.Remove(s);

            }
        }

        UpdateSubstanceContent();

        return list[name].PropertyValue;
    }

    public int GetPossesstionNunber(string s)
    {
        return list[s].PossesstionNunber;
    }

    public void AddProp(string s)
    {
        list[s].PossesstionNunber += 1;
        taskManager.GetInstance().UpdateTasktip();
        UpdateSubstanceContent();
    }

    public int GetSellMoney(string s)
    {
        return list[s].SellMoney;
    }

    public string GetContent(string s)
    {
        return list[s].Content;
    }

    public Dictionary<string,int> GetNeeds(string s)
    {
        return list[s].MarkneedGoods;
    }
}
