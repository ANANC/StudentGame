using UnityEngine;
using System.Collections;

enum Player_state
{
    Start,
    move,
    //play,
    Over
}
public class move : MonoBehaviour {
    Player_state state;

    //小地图显示位置
    public GameObject postextGameObject;

    //开始和结束
    public GameObject StartGameObject;
    public GameObject OverGameObject;

    //反应
    GameObject mouseLeftGameObject;//鼠标点击的物体-左键
    public GameObject LightCircleGameObject;//头环
    bool IsMouseLeftDown;//鼠标左键点击


    //行走
    Animator a;
    float speed;
    float MoveNumber;
    float HungerSpeed;

    //怪物
    monsters MonstersManager;

    //物体栏
    public GameObject knapsack;
    bool IsOpenSubstance;

    //治愈时间
    float curetime;
    

    void Start()
    {
        OverGameObject.SetActive(false);

        a = gameObject.GetComponent<Animator>();
        speed = 0.042f;
        MoveNumber = 0;

        state = new Player_state();
        state = Player_state.Start;

        MonstersManager = monsters.GetInstance();

        HungerSpeed = 1;

        IsOpenSubstance = false;

        IsMouseLeftDown = false;

        curetime = 0;

        //显示小地图的位置
        postextGameObject.GetComponent<UILabel>().text = "(" + (int)transform.position.x + "," + (int)transform.position.y + ")";

    }

    void CheckKey()
    {
        /*------------------------------移动------------------------------------------*/
        if (transform.position.z != 0)
        {
            transform.position = new Vector3(transform.position.x, transform.position.y, 0);
        }

        if (Input.GetKey(KeyCode.A))
        {
            //增加饥饿值
            if (MoveNumber > 100)
            {
                AddMoveHunger();
                MoveNumber = 0;
            }
            if (attribute.GetInstance().GetHungerRotio() >= 0.5f)
            {
                HungerSpeed = 0.5f;
                attribute.GetInstance().AddSystemtext("你的饥饿值已经达到一半了！速度减低50%！当饥饿值满了的时候，将不能移动。");
            }
            if (attribute.GetInstance().GetHungerRotio() == 1f)
            {
                HungerSpeed = 0f;
                attribute.GetInstance().AddSystemtext("你太饿了！没有力气走路了！");

            }
            if (attribute.GetInstance().GetHungerRotio() < 0.5f)
            {
                HungerSpeed = 1f;
            }

            if (a.GetBool("IsStop") == false && a.GetBool("IsLeft") == false)
            {

                a.SetBool("IsStop", true);
                a.SetBool("IsLeft", false);
                a.SetBool("IsRight", false);
                a.SetBool("IsDown", false);
                a.SetBool("IsUp", false);
                return;
            }

            a.SetBool("IsStop", false);
            a.SetBool("IsLeft", true);
            Vector3 s = new Vector3(-speed * HungerSpeed, 0, 0);
            GetComponent<CharacterController>().Move(s);
            MoveNumber++;

            //显示小地图的位置
            postextGameObject.GetComponent<UILabel>().text = "(" + (int)transform.position.x + "," + (int)transform.position.y + ")";

            return;
        }
        if (Input.GetKey(KeyCode.D))
        {
            //增加饥饿值
            if (MoveNumber > 100)
            {
                AddMoveHunger();
                MoveNumber = 0;
            }
            if (attribute.GetInstance().GetHungerRotio() >= 0.5f)
            {
                HungerSpeed = 0.5f;
                attribute.GetInstance().AddSystemtext("你的饥饿值已经达到一半了！速度减低50%！当饥饿值满了的时候，将不能移动。");
            }
            if (attribute.GetInstance().GetHungerRotio() == 1f)
            {
                HungerSpeed = 0f;
                attribute.GetInstance().AddSystemtext("你太饿了！没有力气走路了！");

            }
            if (attribute.GetInstance().GetHungerRotio() < 0.5f)
            {
                HungerSpeed = 1f;
            }

            if (a.GetBool("IsStop") == false && a.GetBool("IsRight") == false)
            {

                a.SetBool("IsStop", true);
                a.SetBool("IsLeft", false);
                a.SetBool("IsRight", false);
                a.SetBool("IsDown", false);
                a.SetBool("IsUp", false);
                return;
            }
            a.SetBool("IsStop", false);
            a.SetBool("IsRight", true);
            Vector3 s = new Vector3(speed*HungerSpeed, 0, 0);
            GetComponent<CharacterController>().Move(s);
            MoveNumber++;

            //显示小地图的位置
            postextGameObject.GetComponent<UILabel>().text = "(" + (int)transform.position.x + "," + (int)transform.position.y  + ")";

            return;
        }

        if (Input.GetKey(KeyCode.S))
        {
            //增加饥饿值
            if (MoveNumber > 100)
            {
                AddMoveHunger();
                MoveNumber = 0;
            }
            if (attribute.GetInstance().GetHungerRotio() >= 0.5f)
            {
                HungerSpeed = 0.5f;
                attribute.GetInstance().AddSystemtext("你的饥饿值已经达到一半了！速度减低50%！当饥饿值满了的时候，将不能移动。");
            }
            if (attribute.GetInstance().GetHungerRotio() == 1f)
            {
                HungerSpeed = 0f;
                attribute.GetInstance().AddSystemtext("你太饿了！没有力气走路了！");

            }
            if (attribute.GetInstance().GetHungerRotio() < 0.5f)
            {
                HungerSpeed = 1f;
            }


            if (a.GetBool("IsStop") == false && a.GetBool("IsDown") == false)
            {

                a.SetBool("IsStop", true);
                a.SetBool("IsLeft", false);
                a.SetBool("IsRight", false);
                a.SetBool("IsDown", false);
                a.SetBool("IsUp", false);
                return;
            }
            a.SetBool("IsStop", false);
            a.SetBool("IsDown", true);
            Vector3 s = new Vector3(0, -speed * HungerSpeed, 0);
            GetComponent<CharacterController>().Move(s);
            MoveNumber++;

            //显示小地图的位置
            postextGameObject.GetComponent<UILabel>().text = "(" + (int)transform.position.x + "," + (int)transform.position.y + ")";

            return;
        }

        if (Input.GetKey(KeyCode.W))
        {
            //增加饥饿值
            if (MoveNumber > 100)
            {
                AddMoveHunger();
                MoveNumber = 0;
            }
            if (attribute.GetInstance().GetHungerRotio() >= 0.5f)
            {
                HungerSpeed = 0.5f;
                attribute.GetInstance().AddSystemtext("你的饥饿值已经达到一半了！速度减低50%！当饥饿值满了的时候，将不能移动。");
            }
            if (attribute.GetInstance().GetHungerRotio() == 1f)
            {
                HungerSpeed = 0f;
                attribute.GetInstance().AddSystemtext("你太饿了！没有力气走路了！");

            }
            if (attribute.GetInstance().GetHungerRotio() < 0.5f)
            {
                HungerSpeed = 1f;
            }

            if (a.GetBool("IsStop") == false && a.GetBool("IsUp") == false)
            {

                a.SetBool("IsStop", true);
                a.SetBool("IsLeft", false);
                a.SetBool("IsRight", false);
                a.SetBool("IsDown", false);
                a.SetBool("IsUp", false);
                return;
            }
            a.SetBool("IsStop", false);
            a.SetBool("IsUp", true);
            Vector3 s = new Vector3(0, speed * HungerSpeed, 0);
            GetComponent<CharacterController>().Move(s);
            MoveNumber++;


            //显示小地图的位置
            postextGameObject.GetComponent<UILabel>().text = "(" + (int)transform.position.x + "," + (int)transform.position.y + ")";

            return;
        }
        if (Input.GetKeyUp(KeyCode.W) || Input.GetKeyUp(KeyCode.S) || Input.GetKeyUp(KeyCode.A) || Input.GetKeyUp(KeyCode.D))
        {
            a.SetBool("IsStop", true);
            a.SetBool("IsLeft", false);
            a.SetBool("IsRight", false);
            a.SetBool("IsDown", false);
            a.SetBool("IsUp", false);
            return;
        }

        
        /*------------------------------移动------------------------------------------*/


        /*------------------------------物体栏------------------------------------------*/
        if (Input.GetKeyDown(KeyCode.P))
        {
            if (IsOpenSubstance == false)
            {
                propManager.GetInstance().Open();
                IsOpenSubstance = true;
            }
            else
            {
                propManager.GetInstance().Close();
                IsOpenSubstance = false;
            }
        }
        /*------------------------------物体栏------------------------------------------*/

    }

    void CheckMouse()
    {
        IsMouseLeftDown = Input.GetMouseButtonDown(0);

        //鼠标左键点击，打开背包
        if (IsMouseLeftDown || IsOpenSubstance)
        {
            //主摄像机
            Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition);
            RaycastHit hit;
            if (Physics.Raycast(ray, out hit, 100))
            {
                mouseLeftGameObject = hit.collider.gameObject;

                
            }
        }

    }


    void AddMoveHunger()
    {
        property p;
        p.key = PropertyKey.Hunger;
        p.value = 1;
        attribute.GetInstance().SetProp(p);
    }

    void ClickStartGameObject(GameObject button)
    {
        StartGameObject.SetActive(false);
        attribute.GetInstance().AddSystemtext("欢迎回来！><");
        attribute.GetInstance().AddSystemtext("使用WASD移动。当npc头上有小灯泡时，记得去接任务喔~");
        state = Player_state.move;
    }

    //点击背包
    void ClickknapsackGameObejct(GameObject button)
    {
        if (IsOpenSubstance == false)
        {
            propManager.GetInstance().Open();
            IsOpenSubstance = true;
            attribute.GetInstance().AddSystemtext("点击右键使用喔");
        }
        else
        {
            propManager.GetInstance().Close();
            IsOpenSubstance = false;
        }
        return;
    }

    void Update()
    {
        switch (state)
        {
            case Player_state.Start:
                UIEventListener.Get(StartGameObject).onClick = ClickStartGameObject;
                UIEventListener.Get(knapsack).onClick = ClickknapsackGameObejct;
                return;
            case Player_state.Over://设置结束的方式还没写
                OverGameObject.SetActive(true);
                return;
            case Player_state.move:
                CheckKey();
                CheckMouse();
                MonstersManager.Update();

                if (taskManager.GetInstance().FindState("基础任务6") == task_state.Remove)
                {
                    float time = 0;
                    while(time>250)
                        time += Time.deltaTime;
                    state = Player_state.Over;
                }
                return;
        }
    }
}
