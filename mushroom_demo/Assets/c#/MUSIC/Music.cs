using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class Music_Manager
{
    static Music_Manager music_manager;
    private List<Music_pai> list;


    static public Music_Manager GetInstance()
    {
        if(music_manager == null)
        {
            music_manager = new Music_Manager();
        }
        return music_manager;
    }

    private Music_Manager()
    {
        list = new List<Music_pai>();

        list.Add(new MusicPai_0());
    }

    public void SelectMusicPai(int i,out Music_pai mp)
    {
        if(i>=list.Count)
        {
            Debug.Log("超过List的容量！");
            mp = null;
            return;
        }
        mp = list[i];
    }
}

public enum Music_state
{
    sleep,//未开始
    play_init,//开始-初始化
    play_ing,//游戏进行中
    over,//游戏结束
   // death//死亡
};

public enum GradeState
{
    S,
    A,
    B,
    C
}
public class Music : MonoBehaviour
{
    Music_state State;
    int SelectNumber;
    public GameObject Circle;

    Music_Manager musicManager;
    Music_pai list;

    Dictionary<int, GameObject> PaiRender;
    List<int> CheckNumber;

    float Circlewight;
    float Paiwight;
    Vector3 CirclePos;
    Vector3 Speed;
    int Start_render;

    float RenderTipTime;
    public GameObject CheckGradeGameObejct;
    public GameObject comboGameObject;
    public GameObject GradeGameObject;
    public GameObject CookContentGameObject;

    bool IsRenderTipAndCombo;

    Dictionary<PaiQuality, int> PaiQualityscore;
    int combo;
    float score;
    float time_clear;
    int IsActivetrueNumber;
    int LastNeedCheckNumber;


    //死亡喷泉
   // public GameObject Deathwater;
    //bool isDie;

    static Music instance;

    public static Music GetInstance()
    {
        return instance;
    }

    public int Selectnumber
    {
        set
        {
            SelectNumber = value;
        }
    }

    void Start()
    {
        Circle.SetActive(false);
        CheckGradeGameObejct.SetActive(false);
        comboGameObject.SetActive(false);
        GradeGameObject.SetActive(false);

        SelectNumber = 0;
        CirclePos = Circle.transform.localPosition;
        musicManager = Music_Manager.GetInstance();

        State = Music_state.sleep;
        Start_render = 0;
        IsRenderTipAndCombo = false;
        RenderTipTime = 0;

        PaiRender = new Dictionary<int, GameObject>();
        CheckNumber = new List<int>();

        PaiQualityscore = new Dictionary<PaiQuality, int>();
        PaiQualityscore.Add(PaiQuality.perfect, 0);
        PaiQualityscore.Add(PaiQuality.good, 0);
        PaiQualityscore.Add(PaiQuality.bad, 0);
        PaiQualityscore.Add(PaiQuality.miss, 0);
        score = 0;

        time_clear = 0;
        //isDie = false;
        IsActivetrueNumber = -1;
        LastNeedCheckNumber = -1;

        instance = this;
    }

  
    public Music_state STATE
    {
        get
        {
            return State;
        }
        set
        {
            State = value;
        }
    }

    // Update is called once per frame
    void Update()
    {
        switch (State)
        {
            case Music_state.sleep:
                break;
            case Music_state.play_init:
                Circle.SetActive(true);
                CheckGradeGameObejct.SetActive(true);
                comboGameObject.SetActive(true);

                Circlewight = Circle.GetComponent<Renderer>().bounds.size.x * Circle.transform.localScale.x*2;
                
                musicManager.SelectMusicPai(SelectNumber, out list);
                list.SelectThis_Init(CirclePos);
                Speed = new Vector3(list.Speed, 0f, 0f);

                CheckGradeGameObejct.GetComponent<UILabel>().text = "";
                comboGameObject.GetComponent<UILabel>().text = "";
                GradeGameObject.GetComponent<UILabel>().text = "";

                for (int i = 0; i < list.List.Count;i++)
                {
                    GameObject g = GameObject.Instantiate((GameObject)Resources.Load("Prefab/music/" + list.List[i].DIRECTION.ToString()));
                    g.transform.parent = CookContentGameObject.transform;
                    g.transform.localPosition = list.List[i].Pos;
                    g.transform.localScale =new Vector3(95,95,1);
                    g.layer = 5;//UI
                    g.SetActive(false);
                    PaiRender.Add(i, g);
                }

                State = Music_state.play_ing;

                break;
            case Music_state.play_ing:
                Render();
                //OnGUI();
                Check();
                //StartCoroutine(Check());

                if (IsRenderTipAndCombo)
                    RenderTipandCombo();
                break;
            case Music_state.over:
                GameOver();

                time_clear += Time.deltaTime;
                if (time_clear > 2f)
                {
                    Clear();

                    cook.GetInstance().GetProp();
                    State = Music_state.sleep;
                }
                break;

            //case Music_state.death:
            //        if (attribute.GetInstance().Getblood() < 50)
            //            break;
            //        attribute.GetInstance().AddSystemtext("下次注意喔！你可以走啦~");
            //        State = Music_state.sleep;
            //    break;
            default:
                Debug.Log("出现异常状态！");
                break;
        }
    }
    void FixedUpdate()
    {
        if (State == Music_state.play_ing)
        {
            Check();
        }
        
    }
    void Render()
    {
        for (int i = Start_render; i < list.List.Count; i++)
        {
            if (PaiRender[i].transform.localPosition.x < CirclePos.x + Circlewight)
            {
                PaiRender[i].transform.localPosition += Speed;
                if (IsActivetrueNumber < i && PaiRender[i].transform.localPosition.x >= -194 )
                {
                    PaiRender[i].SetActive(true);
                    IsActivetrueNumber++;
                }
                if (LastNeedCheckNumber < i && PaiRender[i].transform.localPosition.x >= CirclePos.x - Circlewight / 2 - 5f)
                {
                    LastNeedCheckNumber++;
                    CheckNumber.Add(i);
                }
            }
            
        }

        if (list.SourcePrefab.GetComponent<AudioSource>().isPlaying == false && IsRenderTipAndCombo == false )//&& IsDie==false)
        {
            list.SelectThis_Over();
            State = Music_state.over;
        }
    }

   // void OnGUI()
    //IEnumerator Check()
    void Check()
    {
        if (CheckNumber.Count != 0)
        {
            float time = 0;
            while (time > 20f)
                time += 1;

            pai m_pai = list.List[CheckNumber[0]];
            int number = CheckNumber[0];
            Vector3 p = PaiRender[number].transform.localPosition;

            DIRECTION deciton = DIRECTION.error;
            //if (Event.current != null && Event.current.isKey == true)
            //{
            //    Event e = Event.current;
            //    Debug.Log(e.pressure);
            //    p = PaiRender[number].transform.localPosition;
            //    if (e.keyCode == KeyCode.UpArrow)
            //        deciton = DIRECTION.up;

            //    if (e.keyCode == KeyCode.DownArrow)
            //        deciton = DIRECTION.down;

            //    if (e.keyCode == KeyCode.LeftArrow)
            //        deciton = DIRECTION.left;

            //    if (e.keyCode == KeyCode.RightArrow)
            //        deciton = DIRECTION.right;

            //    if (e.keyCode == KeyCode.Space)
            //        deciton = DIRECTION.space;
            //}

            

            if (Input.anyKeyDown)
            {
                if (Input.GetKeyDown(KeyCode.UpArrow))
                    deciton = DIRECTION.up;
                else if (Input.GetKeyDown(KeyCode.DownArrow))
                    deciton = DIRECTION.down;
                else if (Input.GetKeyDown(KeyCode.LeftArrow))
                    deciton = DIRECTION.left;
                else if (Input.GetKeyDown(KeyCode.RightArrow))
                    deciton = DIRECTION.right;
                else if (Input.GetKeyDown(KeyCode.Space))
                    deciton = DIRECTION.space;
                p = PaiRender[number].transform.localPosition;
            }

            if ((deciton != m_pai.DIRECTION && deciton != DIRECTION.error) || (p.x > CirclePos.x + Circlewight / 2))
            {//miss
                Start_render += 1;

                PaiQualityscore[PaiQuality.miss] += 1;
                DestroyRender(number);
                SetRenderTip(PaiQuality.miss);
                SetRenderCombo(false);
                CheckNumber.Remove(number);
                return;
            }
            if (deciton == m_pai.DIRECTION)
            {
                if ((p.x <= CirclePos.x - Circlewight / 4 && p.x >= CirclePos.x) || (p.x <= CirclePos.x && p.x >= CirclePos.x + Circlewight / 4))
                {//bad
                    Start_render += 1;

                    PaiQualityscore[PaiQuality.bad] += 1;
                    DestroyRender(number);
                    SetRenderTip(PaiQuality.bad);
                    SetRenderCombo(false);
                    CheckNumber.Remove(number);

                    score += 100;
                    return;
                }
                else if ((p.x <= CirclePos.x - Circlewight / 20 && p.x > CirclePos.x - Circlewight / 4) || (p.x < CirclePos.x + Circlewight / 4 && p.x >= CirclePos.x + Circlewight / 20))
                {//good
                    Start_render += 1;

                    PaiQualityscore[PaiQuality.good] += 1;
                    DestroyRender(number);
                    SetRenderTip(PaiQuality.good);
                    SetRenderCombo(true);
                    CheckNumber.Remove(number);

                    score += 400 + 400 * combo * 0.2f;
                    return;
                }
                else if (p.x < CirclePos.x + Circlewight / 20 && p.x > CirclePos.x - Circlewight / 20)
                {//perfect
                    Start_render += 1;

                    PaiQualityscore[PaiQuality.perfect] += 1;
                    DestroyRender(number);
                    SetRenderTip(PaiQuality.perfect);
                    SetRenderCombo(true);
                    CheckNumber.Remove(number);

                    score += 700 + 700 * combo * 0.2f;
                    return;
                }
            }
        }
    }

    void SetRenderTip(PaiQuality d)//0,1.20,0
    {
        CheckGradeGameObejct.GetComponent<UILabel>().text = d.ToString();
        IsRenderTipAndCombo = true;
    }

    void SetRenderCombo(bool IsAdd)
    {
        if (IsAdd == true)
        {
            combo += 1;
            if (combo < 2)
                return;

            comboGameObject.GetComponent<UILabel>().text = "combo:" + combo;

            IsRenderTipAndCombo = true;
        }
        else if (combo != 0)
        {
            combo = 0;
            comboGameObject.GetComponent<UILabel>().text = "";
        }
    }
    void RenderTipandCombo()
    {
        RenderTipTime += Time.deltaTime;
        if (RenderTipTime >= 0.3f)
        {
            RenderTipTime = 0;
            IsRenderTipAndCombo = false;
            //SetRenderCombo(false);
        }
    }
    void DestroyRender(int i)
    {
        PaiRender[i].SetActive(false);
    }

    void GameOver()
    {
        for (int i = 0; i < PaiRender.Count; i++)
            Object.Destroy(PaiRender[i]);
        PaiRender.Clear();
        CheckNumber.Clear();

        Circle.SetActive(false);
        CheckGradeGameObejct.SetActive(false);
        comboGameObject.SetActive(false);
        GradeGameObject.SetActive(true);

        GradeState gradeState;
        if(PaiQualityscore[PaiQuality.perfect]==list.List.Count)
            gradeState = GradeState.S;
        else if(PaiQualityscore[PaiQuality.perfect]>=list.List.Count/2 || PaiQualityscore[PaiQuality.good]>list.List.Count/2f)
            gradeState = GradeState.A;
        else if (PaiQualityscore[PaiQuality.bad] >= list.List.Count / 2 || PaiQualityscore[PaiQuality.good] > list.List.Count / 3f)
            gradeState = GradeState.B;
        else 
            gradeState = GradeState.C;

        GradeGameObject.GetComponent<UILabel>().text = "等级："+gradeState.ToString();
    }

    void Clear()
    {
        list.SourcePrefab.GetComponent<AudioSource>().Stop();

        Start_render = 0;

        foreach(KeyValuePair<int, GameObject> k in PaiRender)
        {
            Object.Destroy(k.Value);
        }
        PaiRender.Clear();

        Circle.SetActive(false);

        PaiRender.Clear();
    }
}