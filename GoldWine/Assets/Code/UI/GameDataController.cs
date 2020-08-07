using UnityEngine;
using System.Collections;

public class GameDataController: MonoBehaviour
{

    private int CurPass;

    private int CurValue;
    private int TargetValue;

    private int second;
    private float GameTime;

    private bool GameRunning =false;
    private bool InitGame = false;

    public UILabel timeLabel;
    public UILabel curLabel;
    public UILabel targetLabel;

    public UILabel tipLabel;

    public GameObject Win_Go;
    public GameObject Fail_Go;

    public delegate void InitViewEvent();
    public static InitViewEvent initViewEvent;

    private readonly int PassTime = 20;

    void Awake()
    {
        Screen.SetResolution(584, 684,false);
    }

    void Start () {

        CurPass = 1;
        InitPassData();
        GameRunning = false;
        RodBoxController.eatEvent += EatEvent;

        SetTip("请点击空格开始");
    }

    // Update is called once per frame
    void Update()
    {
        if (InitGame)
        {
            InitGame = false;
            GameRunning = true;
            InitPassData();
            curLabel.text = CurValue.ToString();
            targetLabel.text = TargetValue.ToString();
            if (initViewEvent != null) initViewEvent();
        }

        if (GameRunning)
        {
            timeLabel.text = GameTime.ToString();

            if (GameTime == 0)
            {
                GameTime = -1;
                GameRunning = false;
                RadishManager.Instance.GamePlaying = false;
                if (CurValue >= TargetValue) Win();
                else Fail();

                SetTip("请点击空格继续");
            }

            second += 1;

            if (second == 60)
            {
                GameTime -= 1;
                second = 0;
            }
        }
        else
        {
            if (Input.GetKeyDown(KeyCode.Space))
            {
                InitGame = true;
            }
        }
    }

    private void Win()
    {
        Win_Go.SetActive(true);
        CurPass += 1;
    }

    private void Fail()
    {
        Fail_Go.SetActive(true);
        CurPass = 1;
    }

    private void EatEvent()
    {
        CurValue += 1;
        curLabel.text = CurValue.ToString();
    }

    private void InitPassData()
    {
        second = 0;
        GameTime = PassTime;
        CurValue = 0;
        TargetValue = CurPass * CurPass + CurPass*5;
        Win_Go.SetActive(false);
        Fail_Go.SetActive(false);
        SetTip("");
    }

    private void SetTip(string content)
    {
        if (string.IsNullOrEmpty(content))
        {
            tipLabel.gameObject.SetActive(false);
            return;
        }

        tipLabel.text = content;
        tipLabel.gameObject.SetActive(true);

    }
}
