using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class food_0 : prop {

	public food_0(Transform parent):base("红瓶")
    {
        possesstionNumber = 5;
        content = "常见的补血药水。\n属性：加10的血。" ;
        Property.value = 10;
        Property.key = PropertyKey.Blood;
        sellMoney = 5;

        MarkNeedGoods.Add("红菇", 1);
    }
}

public class food_1 : prop
{
    public food_1(Transform parent)
        : base("红菇")
    {
        possesstionNumber = 0;
        content = "野外好多小蘑菇。但是不要随便吃喔。\n属性：加18的血。" ;
        Property.value = 18;
        Property.key = PropertyKey.Blood;
        sellMoney = 8;

        MarkNeedGoods.Add("石之十", 3);
        MarkNeedGoods.Add("石螺", 1);
    }

}

public class food_2 : prop
{
    public food_2(Transform parent)
        : base("丽菊")
    {
        possesstionNumber = 0;
        content = "漂亮的小菊花让人心情愉快。\n属性：加25的血。";
        Property.value = 25;
        Property.key = PropertyKey.Blood;
        sellMoney = 12;
    }

}

public class food_3 : prop
{
    public food_3(Transform parent)
        : base("桂玫")
    {
        possesstionNumber = 0;
        content = "桂玫很娇嫩哒，不要碰坏了。\n属性：加30的血。";
        Property.value = 30;
        Property.key = PropertyKey.Blood;
        sellMoney = 16;
    }
}

public class food_4 : prop
{
    public food_4(Transform parent)
        : base("羽桦")
    {
        possesstionNumber = 0;
        content = "轻飘飘的，好像羽毛一样。\n属性：加37的血。";
        Property.value = 37;
        Property.key = PropertyKey.Blood;
        sellMoney = 37;
    }
}


//饥饿食品
public class food_5 : prop
{
    public food_5(Transform parent)
        : base("蓝瓶")
    {
        possesstionNumber = 5;
        content = "蓝瓶的钙，补饥饿的钙。\n属性：减5饥饿值。";
        Property.value = -5;
        Property.key = PropertyKey.Hunger;
        sellMoney = 5;
    }

}

public class food_6 : prop
{
    public food_6(Transform parent)
        : base("阳玉")
    {
        possesstionNumber = 0;
        content = "绿色世界，高亮之心。\n属性：减8饥饿值。" ;
        Property.value = -8;
        Property.key = PropertyKey.Hunger;
        sellMoney = 8;
    }

}

public class food_7 : prop
{
    public food_7(Transform parent)
        : base("郁米")
    {
        possesstionNumber = 0;
        content = "蓝色让你忧郁，可食物会带给你开心。\n属性：减10饥饿值。";
        Property.value = -10;
        Property.key = PropertyKey.Hunger;
        sellMoney = 10;
    }

}

//掉落道具
public class sundires_0 : prop
{
    public sundires_0(Transform parent)
        : base("石之十")
    {
        possesstionNumber = 0;
        content = "怪物为什么会收集奇怪的石头呢？\n属性：不可用。" ;
        Property.value = 0;
        Property.key = PropertyKey.Nothing;
    }

}

public class sundires_1 : prop
{
    public sundires_1(Transform parent)
        : base("星钩")
    {
        possesstionNumber = 0;
        content = "貌似能把天上的星星抓到手里。\n属性：不可用。";
        Property.value = 0;
        Property.key = PropertyKey.Nothing;
    }

}

public class sundires_2 : prop
{
    public sundires_2(Transform parent)
        : base("决角")
    {
        possesstionNumber = 0;
        content = "懂的人才会知道用途，不然就扔了吧。\n属性：不可用。" ;
        Property.value = 0;
        Property.key = PropertyKey.Nothing;
    }
}

public class sundires_3 : prop
{
    public sundires_3(Transform parent)
        : base("萎蜜")
    {
        possesstionNumber = 0;
        content = "看起来有点像尾巴，但其实不是的喔。\n属性：不可用。" ;
        Property.value = 0;
        Property.key = PropertyKey.Nothing;
    }

}

public class sundires_4 : prop
{
    public sundires_4(Transform parent)
        : base("肥祥")
    {
        possesstionNumber = 0;
        content = "要是能减肥成功，这玩意还是能飞起来的。\n属性：不可用。" ;
        Property.value = 0;
        Property.key = PropertyKey.Nothing;
    }
    
}

public class sundires_5 : prop
{
    public sundires_5(Transform parent)
        : base("石螺")
    {
        possesstionNumber = 0;
        content = "它在你看不到的时候偷偷地移动，是个好螺。\n属性：不可用。" ;
        Property.value = 0;
        Property.key = PropertyKey.Nothing;
    }
}