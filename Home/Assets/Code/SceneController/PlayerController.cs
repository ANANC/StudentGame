using UnityEngine;
using UnityEngine.UI;
public class PlayerController : MonoBehaviour
{

    public float speed;
    public float warmSpeed;
    public float useFireSpeed;
    public float maskSpeed;
    public Transform[] m_World;
    public Transform m_Fire;
    public Image maskImage;
    public Image warmImage;
    public AnimationController m_Animation;
    public TalkController m_Talk;
    public WoodController m_Wood;
    public TreeSkyController m_Tree;
    public StoneController m_Stone;
    public bool m_Left;
    public bool m_AI;

    public bool m_Home;

    private Transform m_Transform;
    private bool m_PlayAnimation;
    private Vector3 m_Dir;
    private float updateTime;
    private float fireUpdateTime;
    private float warmValue;
    private float moveRoundX;
    private float maskTime;
    private bool treeSkyLeft;
    private bool m_Control;

    // -- AI --
    private Vector3 m_TargetPos;
    private bool m_AIMove;
    // -- AI --
    void Start()
    {
        Screen.SetResolution(1024, 768, false);
        DataMgr.Instance().SetPlayerController(m_Left, m_AI, this);

        m_Transform = this.transform;
        m_PlayAnimation = false;
        m_Animation.SetDir(m_Left);
        m_Animation.SetOpen(false);
        m_Dir = m_Left ? Vector3.left : Vector3.right;
        updateTime = 0;
        fireUpdateTime = 0;
        maskTime = -1;
        m_AIMove = false;
        m_Control = DataMgr.Instance().GetPlayerControl() == m_Left;
        warmUpdateEvent();
        treeSkyUpdatEvent();
        DataMgr.Instance().warmUpdateEvent += warmUpdateEvent;
        DataMgr.Instance().playerUpdateEvent += playerContolUpdateEvent;
        DataMgr.Instance().treeSkyUpdateEvent += treeSkyUpdatEvent;

    }

    void Update()
    {
        UpdateMask();
        if(maskTime!= -1)
        {
            return;
        }

        KeyController();

        if(!m_AI)
        {
            if(m_Home)
            {
                if (m_Left)
                {
                    if(m_Transform.localPosition.x <= 46)
                    {
                        treeSkyLeft = true;
                        maskTime = 0;
                        StopMove();
                    }
                    if (m_Transform.localPosition.x >= 450)
                    {

                        treeSkyLeft = false;
                        maskTime = 0;
                        StopMove();
                    }
                }
            }
            else
            {
                if(m_Left )
                {
                    if( (!treeSkyLeft && m_World[0].position.x > -450) || (treeSkyLeft && m_World[0].position.x < 450))
                    {
                        maskTime = 0;
                        StopMove();
                    }
                }
            }
        }

        if (m_PlayAnimation)
        {
            if (m_Home)
            {
                if (m_AI)
                {
                    if (!(m_Transform.localPosition.x + m_Dir.x * speed > moveRoundX || m_Transform.localPosition.x + m_Dir.x * speed < -moveRoundX))
                    {
                        m_Transform.localPosition += m_Dir * speed;
                    }
                }
                else
                {
                    m_Transform.localPosition += m_Dir * speed;
                    DataMgr.Instance().SetMoveCom(m_Left, m_Transform.localPosition);
                }
            }
            else
            {
                for (int index = 0; index < m_World.Length; index++)
                {
                    if (m_World[index].localPosition.x + m_Dir.x * speed > moveRoundX || m_World[index].localPosition.x + m_Dir.x * speed < -moveRoundX)
                    {
                        continue;
                    }
                    m_World[index].localPosition += m_Dir * speed;
                }
            }
        }

        UpdateWarm();

        AI_Update();
    }

    private void KeyController()
    {
        if (m_AI)
        {
            return;
        }
        if (maskTime != -1)
        {
            return;
        }

            if (Input.GetKeyDown(KeyCode.Q))
        {
            DataMgr.Instance().SetPlayerControl(true);
        }
        else if (Input.GetKeyDown(KeyCode.E))
        {
            DataMgr.Instance().SetPlayerControl(false);
        }

        if (!m_Control)
        {
            return;
        }

        if (Input.GetKeyDown(KeyCode.A))
        {
            MoveLeft();
        }
        else if (Input.GetKeyDown(KeyCode.D))
        {
            MoveRight();
        }
        else if (Input.GetKeyUp(KeyCode.A) || Input.GetKeyUp(KeyCode.D))
        {
            StopMove();
        }
        else if (Input.GetKeyDown(KeyCode.Space))
        {
            TryCatchWood();
        }
    }

    public void MoveLeft()
    {
        if (!m_Home)
        {
            m_Dir = Vector3.right;
        }
        else
        {
            m_Dir = Vector3.left;
        }
        m_Animation.SetDir(true);
        SetAnimationOpen(true);
    }

    public void MoveRight()
    {
        if (!m_Home)
        {
            m_Dir = Vector3.left;
        }
        else
        {
            m_Dir = Vector3.right;
        }
        m_Animation.SetDir(false);
        SetAnimationOpen(true);
    }

    public void StopMove()
    {
        SetAnimationOpen(false);
    }

    public void TryCatchWood()
    {
        RaycastHit hit;

        if (Physics.Raycast(m_Transform.position, Vector3.down, out hit))
        {
            if (hit.collider.transform.parent.name == "Wood")
            {
                DataMgr.Instance().AddWood();
                hit.collider.gameObject.SetActive(false);
                Talk("捡到木材");
            }
        }
    }

    // -- AI --

    private void AI_Update()
    {
        if (m_AI)
        {
            if (m_AIMove)
            {
                IsAIStop();
            }
        }
    }
    public void MoveToTarget(Vector3 pos)
    {
        if (m_Left)
        {
            m_TargetPos = new Vector3(-500 + pos.x, pos.y);
        }
        else
        {
            m_TargetPos = new Vector3(500 + pos.x, pos.y);
        }

        if (m_TargetPos != m_Transform.localPosition)
        {
            if (m_Transform.localPosition.x < m_TargetPos.x)
            {
                MoveRight();
            }
            else
            {
                MoveLeft();
            }
            SetAnimationOpen(true);

            m_AIMove = true;
        }
        else
        {
            StopMove();
        }
    }

    private void IsAIStop()
    {
        if (m_TargetPos.x - m_Transform.localPosition.x < 2 || m_TargetPos.x - m_Transform.localPosition.x > -2)
        {
            m_AIMove = false;
            StopMove();
        }
    }

    public void MoveStopAI()
    {
        m_AIMove = false;
        StopMove();
    }

    // -- AI --

    public void Talk(string text)
    {
        m_Talk.Talk(text, m_Left);
        if (!m_AI)
        {
            DataMgr.Instance().SetTalkCom(m_Left, text);
        }
    }

    private void SetAnimationOpen(bool open)
    {
        if (open)
        {
            if (!m_AI)
            {
                DataMgr.Instance().UesWarm(m_Left, 2);
            }

            if (!m_PlayAnimation)
            {
                m_PlayAnimation = true;
                m_Animation.SetOpen(true);
            }
        }
        else
        {
            if (m_PlayAnimation)
            {
                m_PlayAnimation = false;
                m_Animation.SetOpen(false);
            }
        }
    }


    private void UpdateWarm()
    {
        updateTime += 1;
        if (updateTime >= warmSpeed)
        {
            DataMgr.Instance().UesWarm(m_Left, 2);
            updateTime = 0;
        }

        Color color = warmImage.color;
        color.a = Random.Range(warmValue - 5, warmValue) / 100f;
        warmImage.color = color;

        if (DataMgr.Instance().GetAllHome())
        {
            if ((m_Fire.position.x - m_Transform.position.x < 200) && (m_Fire.position.x - m_Transform.position.x > -200))
            {
                DataMgr.Instance().AddWarm(m_Left, 3);
                if (DataMgr.Instance().GetWoodValue() > 0)
                {
                    DataMgr.Instance().UseAllWood();
                    Talk("火堆旺");
                }

                fireUpdateTime += 1;
                if (fireUpdateTime >= useFireSpeed)
                {
                    DataMgr.Instance().UesFire(1);
                    fireUpdateTime = 0;
                }
            }
            else
            {
                fireUpdateTime = 0;
            }
        }
    }

    private void warmUpdateEvent()
    {
        warmValue = DataMgr.Instance().GetWarmValue(m_Left);
    }

    private void treeSkyUpdatEvent()
    {
        if (m_AI)
        {
            moveRoundX = DataMgr.Instance().GetAIRound();

            return;
        }
        moveRoundX = DataMgr.Instance().GetTreeSkyRound() - 400;
    }

    private void playerContolUpdateEvent()
    {
        m_Control = DataMgr.Instance().GetPlayerControl() == m_Left;
        if (!m_Control && !m_AI)
        {
            StopMove();
            DataMgr.Instance().SetMoveCom(m_Left, m_Transform.localPosition);
        }
        if (m_Control && !m_AI)
        {
            m_Talk.Talk("操控",m_Left);
        }
    }

    private void GotoHome()
    {
        m_Fire.gameObject.SetActive(true);

        DataMgr.Instance().SetActiveCom(m_Left, true);
        DataMgr.Instance().SetActiveCom(!m_Left, true);

        Vector3 pos = m_Transform.localPosition;
        if (m_Left)
        {
            if (treeSkyLeft)
            {
                pos.x = 60;
            }
            else
            {
                pos.x = 430;
            }
        }
        else
        {
            pos.x = -94;
        }
        m_Transform.localPosition = pos;
        DataMgr.Instance().SetMoveCom(m_Left, pos);

        m_Tree.Hide();
        m_Stone.Hide();

        m_Home = true;
        DataMgr.Instance().SetHome(true);

    }

    private void LeftHome()
    {
        m_Fire.gameObject.SetActive(false);

        DataMgr.Instance().SetStopCom(m_Left);
        DataMgr.Instance().SetActiveCom(m_Left, false);
        DataMgr.Instance().SetActiveCom(!m_Left, false);

        Vector3 pos = m_Transform.localPosition;
        if(m_Left)
        {
            pos.x = 250;
        }else
        {
            pos.x = -250;
        }
        m_Transform.localPosition = pos;

        for(int index = 0; index<m_World.Length;index++)
        {
            m_World[index].localPosition = new Vector3(treeSkyLeft? 550: -550, 0);
        }

        m_Wood.Show(treeSkyLeft);
        m_Tree.Show(treeSkyLeft);
        m_Stone.Show(treeSkyLeft);
         m_Home = false;

        DataMgr.Instance().SetHome(false);
    }

    private void UpdateMask()
    {
        if (maskTime == -1)
        {
            return;
        }

        Color color = maskImage.color;
        maskTime += 1;

        if (maskTime < maskSpeed)
        {
            color.a = maskTime / maskSpeed;
        }
        else if (maskTime == maskSpeed)
        {
            color.a = 1;

            if (m_Home)
            {
                LeftHome();
            }
            else
            {
                GotoHome();
            }
        }
        else if (maskTime < maskSpeed * 1.1f)
        {
            color.a = maskSpeed * 1.1f / maskTime;
        }
        else
        {
            color.a = 0;
            maskTime = -1;
        }
        
        maskImage.color = color;
    }

}
