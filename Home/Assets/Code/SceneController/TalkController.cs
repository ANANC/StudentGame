using UnityEngine;
using System.Collections.Generic;
using UnityEngine.UI;

public class TalkController : MonoBehaviour {

    public float speed;
    public float scaleTime;
    public float activeTime;
    public float moveTime;
    public Transform CopyTarget;
    private List<info> m_Talks;

	// Use this for initialization
	void Start () {
        m_Talks = new List<info>();
        info curInfo = new info(CopyTarget);
        curInfo.avtiveTime = -1;
        m_Talks.Add(curInfo);

    }

    // Update is called once per frame
    void Update()
    {
        Transform curTra;
        for (int index = 0; index < m_Talks.Count; index++)
        {
            if (m_Talks[index].avtiveTime == -1)
            {
                continue;
            }

            curTra = m_Talks[index].target;
            m_Talks[index].avtiveTime += 1;

            if (m_Talks[index].avtiveTime< scaleTime)
            {
                float value = m_Talks[index].avtiveTime / scaleTime;
                curTra.localScale = Vector3.one * value;
                Color color = m_Talks[index].image.color;
                color.a = value;
                m_Talks[index].image.color = color;
            }else if (m_Talks[index].avtiveTime == scaleTime || m_Talks[index].avtiveTime < activeTime)
            {
                curTra.localScale = Vector3.one;
                Color color = m_Talks[index].image.color;
                color.a = 1;
                m_Talks[index].image.color = color;
            }else if(m_Talks[index].avtiveTime > activeTime && m_Talks[index].avtiveTime< moveTime)
            {
                curTra.localPosition += Vector3.up * speed;
                float value = moveTime/ m_Talks[index].avtiveTime ;
                curTra.localScale = Vector3.one * value;
                Color color = m_Talks[index].image.color;
                color.a = value;
                m_Talks[index].image.color = color;
            }else if(m_Talks[index].avtiveTime >= moveTime)
            {
                m_Talks[index].target.gameObject.SetActive(false);

                m_Talks[index].avtiveTime = -1;
            }
           


        }
    }

    public void Talk(string text, bool left)
    {
        Color color = left ? new Color(0.89f, 0.69f, 0.08f, 0) : new Color(0.82f, 0.20f, 0.21f, 0);
        for (int index = 0; index < m_Talks.Count; index++)
        {
            m_Talks[index].image.color = color;
        }
        SetInfo(text);
    }


    private void SetInfo(string text)
    {
        info curInfo = null;
        for (int index =0;index< m_Talks.Count;index++)
        {
            if(m_Talks[index].avtiveTime == -1)
            {
                curInfo = m_Talks[index];
            }
            else
            {
                m_Talks[index].target.localPosition += Vector3.up * 90;
            }
        }

        if(curInfo == null)
        {
            GameObject go = GameObject.Instantiate(CopyTarget.gameObject);
            go.transform.SetParent(this.transform);
            go.transform.localScale = Vector3.one;
            curInfo = new info(go.transform);
            m_Talks.Add(curInfo);
        }

        curInfo.target.gameObject.SetActive(true);
        curInfo.target.localPosition = Vector3.zero;
        Color color = curInfo.image.color;
        color.a = 1;
        curInfo.image.color = color;
        curInfo.text.text = text;
        curInfo.avtiveTime = 0;
    }

    private class info
    {
        public Transform target;
        public Image image;
        public Text text;
        public int avtiveTime;

        public info(Transform root)
        {
            target = root;
            image = target.Find("Image").GetComponent<Image>();
            text = target.Find("Text").GetComponent<Text>();
            avtiveTime = 0;
        }
    }
}
