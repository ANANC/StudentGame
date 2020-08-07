using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class RadishManager : MonoBehaviour {

    private static RadishManager instance;
    public static RadishManager Instance { get { return instance; } }

    private List<BaseRadishController> RadishPool = new List<BaseRadishController>();//萝卜资源池

    private int RadishViewMaxValue = 10;//界面萝卜最大数
    private UIWidget ViewWidget;
    private int ViewWidthRance;
    private int ViewHeightRance;

    public bool GamePlaying;

    void Awake()
    {
        instance = this;
    }

    void Start () {
        ViewWidget = this.transform.GetComponent<UIWidget>();
        ViewWidthRance = ViewWidget.width /2;
        ViewHeightRance = ViewWidget.height / 2;

        GamePlaying = false;

        GameDataController.initViewEvent += InitView;
        RodBoxController.catchEvent += CatchRadish;
    }

    void Update()
    {
        if (!GamePlaying) return;

        BaseRadishController con;
        for (int index = 0;index< RadishPool.Count;index++)
        {
            con = RadishPool[index];
            con.UpdatePos(ViewWidthRance);
        }
    }

    #region 界面

    //初始化界面
    public void InitView()
    {
        int DataCount = RadishViewMaxValue;
        int CellCount = RadishPool.Count;
        int Update = DataCount > CellCount ? DataCount : CellCount;

        BaseRadishController con;
        for (int index = 0;index< Update;index++)
        {
            if(index< DataCount)
            {
                if (index >= CellCount)
                    con = AddRadish();
                else
                    con = RadishPool[index];

                InitRadish(con);
            }
            else
            {
                con = RadishPool[index];
                con.Setup();
            }
        }

        RadishManager.Instance.GamePlaying = true;
    }

    //清理界面
    private void CleanView()
    {
        BaseRadishController con;

        for (int index = 0; index < RadishPool.Count; index++)
        {
            con = RadishPool[index];
            con.Setup();
        }
    }

    #endregion
    
    #region 萝卜资源池

    private void InitRadish(BaseRadishController controller)
    {
        int Value = 1;

        int Direction = Random.Range(0, 2) == 0? -1: 1;

        int Radio = ViewHeightRance;
        int PosY = Random.Range(-Radio, Radio);

        int PosX = (ViewWidthRance + 10) * Direction;

        controller.transform.parent = ViewWidget.transform;

        controller.SetData(Direction,ViewWidthRance,ViewHeightRance);
        controller.SetPos(new Vector3(PosX, PosY));
        controller.SetValue(Value);
    }

    private BaseRadishController AddRadish()
    {
        Object RadishObj = Resources.Load(GameSet.RadishResPath, typeof(GameObject));
        GameObject RadishGO = GameObject.Instantiate(RadishObj) as GameObject;
        BaseRadishController controller = RadishGO.AddComponent<BaseRadishController>();
        
        RadishGO.name = RadishPool.Count.ToString();
        RadishGO.transform.parent = ViewWidget.transform;
        RadishGO.transform.localScale = Vector3.one;

        controller.InitViewComponent(RadishGO.transform);
        controller.Setup();

        RadishPool.Add(controller);

        return controller;
    }

    #endregion

    #region 抓住萝卜

    public void CatchRadish(Transform Rod, int Index)
    {
        if(RadishPool.Count< Index || Index<0 )
        {
            Debug.LogError(string.Format("抓住的萝卜id{0}异常",Index));
            return;
        }

        BaseRadishController catchRadish = RadishPool[Index];
        catchRadish.Catch();
        catchRadish.transform.parent = Rod;
    }



    public int EatRadish(int Index)
    {
        BaseRadishController catchRadish = RadishPool[Index];
        int Value = catchRadish.GetValue();
        
        InitRadish(catchRadish);
        
        return Value;
    }
    #endregion
}
