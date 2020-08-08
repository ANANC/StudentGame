using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class MusicPai_0 : Music_pai
{
    public MusicPai_0():base()
    {
        list = new List<pai>();
        speed = 2f;
        sourcePrefab =  GameObject.Instantiate((GameObject)Resources.Load("Prefab/music/musicSource_0"));
        
        Init_pai();
    }

    public override Music_pai Clone()
    {
        MusicPai_0 m = new MusicPai_0();
        m.list = list;
        m.speed = speed;
        m.sourcePrefab = sourcePrefab;
        return m;
    }
    protected override void Init_pai()
    {
        float L0 = 40f;
        float L1 = 50f;
        float L2 = 70f;
        list.Add(new pai(DIRECTION.up, 340, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.right, L0, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.space, L2, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.left, L1, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.space, L1, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.left, L1, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.right, L1, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.right, L2, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.space, L0, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.up, L0, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.down, L0, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.up, L0, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.space, L2, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.up, L0, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.right, L1, new Vector3(0, 0, 0)));

        list.Add(new pai(DIRECTION.right, L1, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.down, L2, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.down, L0, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.left, L0, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.right, L1, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.up, L0, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.space, L2, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.down, L1, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.left, L0, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.up, L0, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.space, L2, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.left, L0, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.up, L0, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.space, L2, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.up, L0, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.down, L1, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.left, L1, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.space, L2, new Vector3(0, 0, 0)));

        list.Add(new pai(DIRECTION.down, L0, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.left, L1, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.up, L0, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.space, L2, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.right, L1, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.left, L1, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.down, L1, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.up, L0, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.space, L2, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.up, L0, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.down, L1, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.down, L1, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.space, L2, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.left, L0, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.down, L0, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.left, L0, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.left, L1, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.right, L2, new Vector3(0, 0, 0)));

        list.Add(new pai(DIRECTION.up, L1, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.right, L2, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.up, L1, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.space, L1, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.down, L0, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.left, L1, new Vector3(0, 0, 0)));

        list.Add(new pai(DIRECTION.left, L2, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.right, L0, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.down, L0, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.down, L0, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.left, L1, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.space, L2, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.right, L1, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.down, L2, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.right, L0, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.right, L1, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.down, L0, new Vector3(0, 0, 0)));

        list.Add(new pai(DIRECTION.left, L1, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.right, L2, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.left, L0, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.down, L1, new Vector3(0, 0, 0)));

        list.Add(new pai(DIRECTION.up, L1, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.right, L2, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.space, L0, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.right, L1, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.space, L2, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.left, L0, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.right, L1, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.space, L1, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.left, L0, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.right, L1, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.space, L2, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.space, L2, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.left, L0, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.left, L1, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.space, L2, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.right, L1, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.space, L2, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.space, L2, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.down, L0, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.down, L0, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.right, L1, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.space, L2, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.left, L1, new Vector3(0, 0, 0)));

        list.Add(new pai(DIRECTION.space, L1, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.down, L0, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.right, L2, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.down, L1, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.right, L1, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.left, L2, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.left, L1, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.up, L1, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.up, L1, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.up, L2, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.right, L1, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.down, L1, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.space, L2, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.space, L2, new Vector3(0, 0, 0)));
        list.Add(new pai(DIRECTION.space, L2, new Vector3(0, 0, 0)));
    }
}
