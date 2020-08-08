using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public enum PropertyKey
{
    Blood,
    Hunger,
    Nothing
}

public struct property
{
    public int value;
    public PropertyKey key;
}

public class prop  {
    protected string name;
    protected string content;
    protected int possesstionNumber;
    protected property Property;//属性-对人物的属性进行加减
    protected int sellMoney;//买入的价格
    protected Dictionary<string, int> MarkNeedGoods;//制作这个道具所需要的道具

    protected prop(string s)
    {
        name = s;
        MarkNeedGoods = new Dictionary<string, int>();
    }

    public int PossesstionNunber
    {
        set
        {
            possesstionNumber = value;
        }
        get
        {
            return possesstionNumber;
        }
    }
    
    public string Name
    {
        get
        {
            return name;
        }
    }

    public string Content { 
        get
        {
            return content;
        }
    }

    public property PropertyValue
    {
        get
        {
            return Property;
        }
    }

    public int SellMoney
    {
        get
        {
            return sellMoney;
        }
    }

    public Dictionary<string,int>MarkneedGoods
    {
        get
        {
            return MarkNeedGoods;
        }
    }

}
