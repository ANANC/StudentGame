using UnityEngine;
using System.Collections;

public class UI_set : UI_page
{
    Transform content;
    Transform[] contentNumbers = new Transform[3];
    int Index;//1为头
    int AllIndex;
    int musicPower;
    int musiceffectPower;
    int OpenAnimatorIndex;
    Vector3 AmongPos = new Vector3(3.48f, 0, 0);
    Vector3 disPos = new Vector3(1f, 0, 0);
    public override void Init()
    {
        ThisTransform = this.transform;
        content = ThisTransform.FindChild("content");
        for (int i = 0; i < content.childCount; i++)
        { UIcommon.UIinit(content.GetChild(i));
            contentNumbers[i] = content.GetChild(i).FindChild("number");
        }
        AllIndex = 6;
        Index = AllIndex;
        OpenAnimatorIndex = 1;
        musicPower = (int)(UIcommon.MusicPower*100);
        musiceffectPower = (int)(UIcommon.MusiceffectPower * 100);
        SetMusicPower(musicPower,true);
        SetMusicPower(musiceffectPower, false);
        base.Init();
    }

    public override void LeftArrow()
    {
        if (!IsChange)
        {
            if (Index > 1)
            {
                SelectShow(Index - 1);
            }
        }
        else
        {
            if (isRight == 0)
            {
                DirButtonToSetbutton(false,AllIndex);
            }
            SelectLeftbutton();
        }
    }

    public override void RightArrow()
    {
        if (!IsChange)
        {
            if (Index == AllIndex)
            { SetbuttonToDirButton(false); }
            if (Index < AllIndex)
            {
                SelectShow(Index + 1);
            }
        }
        else
        {
            SelectRightbutton();
        }
    }

    public override void DownArrow()
    {
        if (!IsChange)
        {
            if (Index <= AllIndex - 2)
            {
                SelectShow(Index + 2);
            }
            else
            {
                bool isright = Index % 2 == 1 ? false : true;
                SetbuttonToDirButton(isright);
            }
        }
    }

    public override void UpArrow()
    {
        if(!IsChange)
        {
            if(Index>2)
            {
                SelectShow(Index - 2);
            }
        }
        else
        {
            bool isright = isRight == 1 ? true : false;
            DirButtonToSetbutton(isright,Index);
        }
    }

    public override void Return()
    {
        bool IsRight = isRight == 0 ? false:true;
        if(IsChange)
        {
            string name = IsRight ? uiprefabName.about.ToString() : uiprefabName.select.ToString();
            Changepage(name, IsRight);
        }
        else
        {
            IsRight = Index%2 == 1 ? false : true;
            if(Index<3)
            {
                SetMusicPower(IsRight ? musicPower + 1 : musicPower - 1,true);
            }
            else if(Index<5)
            {
                SetMusicPower(IsRight ? musiceffectPower + 1 : musiceffectPower - 1, false);
            }
            else
            {
                SetOpenAnimator();
            }
        }
    }

    void SetbuttonToDirButton(bool Isright)
    {
        IsChange = true;
        SelectShow(AllIndex +1);
        isRight = Isright ? 1 : 0;
        UIcommon.UIselectbutton(ThisTransform, Isright);
    }

    void DirButtonToSetbutton(bool Isright,int index)
    {
        IsChange = false;
        SelectShow(index);
        UIcommon.UINotselectbutton(ThisTransform, Isright);
        isRight = -1;
    }

    void SelectShow(int index)
    {
        bool IsRight = Index % 2 == 1 ? false : true;
        int layer = IsRight ? (Index / 2) - 1 : (Index / 2);
        UIcommon.UINotselectbutton(content.GetChild(layer), IsRight);
        if (index > AllIndex)
            return;
        Index = index;
        IsRight = Index % 2 == 1 ? false : true;
        layer = IsRight ? (Index / 2) - 1 : (Index / 2);
        UIcommon.UIselectbutton(content.GetChild(layer), IsRight);
    }

    void SetMusicPower(int power,bool IsMuscicPower)
    {
        if (power < 0 || power > 100)
            return;

        int NowPower = IsMuscicPower ? musicPower : musiceffectPower;
        Transform contentNumber = IsMuscicPower ? contentNumbers[0] : contentNumbers[1];
        GameObject[] number;
        bool IsSimple = false;
        Vector3 InitPos = IsMuscicPower ? AmongPos:AmongPos +new Vector3(0,-2,0); 
        if (power == 100)
        {
            number = new GameObject[3];
            number[0] = UIcommon.GetPrefab(prefabType.numbers, "1");
            number[1] = UIcommon.GetPrefab(prefabType.numbers, "0");
            number[2] = UIcommon.GetPrefab(prefabType.numbers, "0");
            InitPos -= disPos;
        }
        else
        {
            string[] names = new string[2] { (power / 10).ToString(), (power % 10).ToString() };
            number = new GameObject[2];

            if (names[0] == (NowPower / 10).ToString() && contentNumber.childCount != 0)
            {
                number[0] = contentNumber.GetChild(0).gameObject;
                IsSimple = true;
            }
            else
            {
                number[0] = UIcommon.GetPrefab(prefabType.numbers, names[0]);
            }
            number[1] = UIcommon.GetPrefab(prefabType.numbers, names[1]);

            InitPos -= disPos * 0.5f;
        }

        for (int i = IsSimple? 1: 0; i < contentNumber.childCount; i++)
        {
            Destroy(contentNumber.GetChild(i).gameObject);
        }

        for(int i=0;i<number.Length;i++)
        {
            number[i].transform.parent = contentNumber;
            number[i].transform.localPosition = InitPos + disPos * i;
        }

        if (IsMuscicPower)
        {
            musicPower = power;
            UIcommon.SetMusicPower(musicPower * 0.01f);
        }
        else
        {
            musiceffectPower = power;
            UIcommon.SetMusiceffectPower(musiceffectPower * 0.01f);
        }
    }

    void SetOpenAnimator()
    {
        contentNumbers[2].GetChild(OpenAnimatorIndex).gameObject.SetActive(false);
        OpenAnimatorIndex = OpenAnimatorIndex == 1 ? 0 : OpenAnimatorIndex == 0 ? 1: OpenAnimatorIndex;
        contentNumbers[2].GetChild(OpenAnimatorIndex).gameObject.SetActive(true);
        UIcommon.SetIsShowStartMoive(OpenAnimatorIndex == 1 ? true : false);
    }
}
