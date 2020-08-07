using UnityEngine;
using System.Collections.Generic;

public class WoodController : MonoBehaviour {

    public GameObject copyGo;
    private List<GameObject> m_Woods;

    public int sceneWidth;
    public int sceneNumber;
    public int[] sceneTreeNumber;
    public int[] refreshTime;

    public Sprite[] sprites;
    
    private int[] waitTime;
    // Use this for initialization
    void Start()
    {
        waitTime = new int[sceneNumber];
    }

    public void Show(bool left)
    {
        if(m_Woods == null)
        {
            m_Woods = new List<GameObject>();
            Create(left);
        }else
        {
            Refresh(left);
        }
    }

    void Update()
    {
        if (m_Woods == null)
        {
            return;
        }
            for (int index = 0, cellIndex = 0; index < sceneNumber; index++)
        {
            cellIndex = index * sceneTreeNumber[index];

            if (waitTime[index] == -1)
            {
                continue;
            }

            waitTime[index] += 1;
            if(waitTime[index]<refreshTime[index])
            {
                continue;
            }

            GameObject objectTree;

            for (int treeIndex = 0; treeIndex < sceneTreeNumber[index]; treeIndex++, cellIndex++)
            {
                objectTree = m_Woods[cellIndex];
                objectTree.SetActive(true);
            }

            waitTime[index] = -1;
        }
    }


    private void Create(bool left)
    {
        int[] offsetWidths = new int[sceneNumber];
        GameObject objectTree;
        for (int index = 0; index < sceneNumber; index++)
        {
            waitTime[index] = 0;
            offsetWidths[index] = sceneWidth / sceneTreeNumber[index];
            for (int treeIndex = 0; treeIndex < sceneTreeNumber[index]; treeIndex++)
            {
                objectTree = AddWood();
                m_Woods.Add(objectTree);
                UpdateWood(objectTree, index);
                Vector3 pos = objectTree.transform.localPosition;
                pos.x = sceneWidth * (index + 1) + offsetWidths[index] * treeIndex + Random.Range(-40, 40) + Random.Range(-60, 60);
                pos.x = left ? -pos.x : pos.x;
                pos.y = Random.Range(-230, -280);
                ((RectTransform)objectTree.transform).localPosition = pos;
            }
        }

    }

    private void Refresh(bool left)
    {
        int[] offsetWidths = new int[sceneNumber];
        GameObject objectTree;
        for (int index = 0,cellIndex = 0; index < sceneNumber; index++)
        {
            waitTime[index] = 0;

            offsetWidths[index] = sceneWidth / sceneTreeNumber[index];
            for (int treeIndex = 0; treeIndex < sceneTreeNumber[index]; treeIndex++, cellIndex++)
            {
                objectTree = m_Woods[cellIndex];
                objectTree.SetActive(false);
                UpdateWood(objectTree, index);
                Vector3 pos = objectTree.transform.localPosition;
                pos.x = sceneWidth * (index + 1) + offsetWidths[index] * treeIndex + Random.Range(-60, 60);
                pos.x = left ? -pos.x : pos.x;
                pos.y = Random.Range(-230, -280);
                ((RectTransform)objectTree.transform).localPosition = pos;
            }
        }
    }

    private GameObject AddWood()
    {
        GameObject objectGo = GameObject.Instantiate(copyGo);
        objectGo.transform.SetParent(this.transform);
        objectGo.transform.localScale = Vector3.one;
        return objectGo;
    }

    private void UpdateWood(GameObject target, int sceneIndex)
    {
        Transform targetTra = target.transform;
        
        UnityEngine.UI.Image image = target.GetComponent<UnityEngine.UI.Image>();
        image.sprite = sprites[Random.Range(0, 1)];
    }
    
}
