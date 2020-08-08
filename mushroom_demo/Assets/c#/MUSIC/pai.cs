using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public enum DIRECTION
{
    up = 0,
    down,
    left,
    right,
    space,
    error,
    Toggle
}
public enum PaiQuality
{
    perfect,
    good,
    bad,
    miss
}
public class pai 
{

    protected Vector3 pos;//位置
    protected DIRECTION direction;//方向
    protected float distance;//距离

    public pai(DIRECTION d, float di, Vector3 v)
    {
        direction = d;
        distance = di;
        pos = v;
    }

    public Vector3 Pos
    {
        get
        {
            return pos;
        }
        set
        {
            pos = value;
        }
    }
    public void SetPosX(float x)
    {
        pos.x = x;
    }
    public float Distance
    {
        get
        {
            return distance;
        }
    }
    public DIRECTION DIRECTION
    {
        get
        {
            return direction;
        }
    }
}

public class Music_pai
{
    protected List<pai> list;
    protected float speed;
    protected GameObject sourcePrefab;

    protected Music_pai()
    {
        Init();
    }
    protected virtual void Init() { }
    protected virtual void Init_pai() { }
    public virtual Music_pai Clone()
    {
        Music_pai A = new Music_pai();
        return A;
    }
    public  void SelectThis_Init(Vector3 InitPos)
    {
        list[0].Pos = InitPos;
        list[0].SetPosX(list[0].Pos.x - list[0].Distance);
        for (int i = 1; i < list.Count; i++)
        {
            list[i].Pos = list[i - 1].Pos;
            list[i].SetPosX(list[i - 1].Pos.x - list[i].Distance );
        }

        sourcePrefab.GetComponent<AudioSource>().Play();
    }
    public void SelectThis_Over()
    {
        sourcePrefab.GetComponent<AudioSource>().Stop();
    }
    public List<pai>List
    {
        get
        {
            return list;
        }
    }
    public float Speed
    {
        get
        {
            return speed;
        }
    }


    public GameObject SourcePrefab
    {
        get
        {
            return sourcePrefab;
        }
    }
}

