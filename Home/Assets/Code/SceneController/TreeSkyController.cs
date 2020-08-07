using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class TreeSkyController : MonoBehaviour {

    public GameObject copyGo;
    private List<GameObject> m_Trees;

    public int sceneWidth;
    public int sceneNumber;
    public int[] sceneTreeNumber;

    private Color[] colors = {
        new Color(0.00f,0.13f,0.15f),
        new Color(0.15f,0.40f,0.24f),
        new Color(0.03f,0.23f,0.24f),
        new Color(0.18f,0.33f,0.19f),
        new Color(0.00f,0.06f,0.09f),
        new Color(0.11f,0.27f,0.11f),
        new Color(0.22f,0.38f,0.25f),
        new Color(0.03f,0.25f,0.15f),
    };

	// Use this for initialization
	void Start () {
        DataMgr.Instance().SetTreeSkyRound(sceneWidth * sceneNumber);
        
    }
	
	public void Show(bool left)
    {
        this.gameObject.SetActive(true);

        if (m_Trees == null)
        {
            m_Trees = new List<GameObject>();
            Create(left);
        }
        else
        {
            Refresh(left);
        }
    }

    public void Hide()
    {
        this.gameObject.SetActive(false);
    }

    private void Create(bool left)
    {
        int[] offsetWidths = new int[sceneNumber];
        GameObject objectTree;
        for (int index = 0; index < sceneNumber;index++)
        {
            offsetWidths[index] = sceneWidth / sceneTreeNumber[index];
            for (int treeIndex = 0; treeIndex < sceneTreeNumber[index]; treeIndex++)
            {
                objectTree = AddTree();
                m_Trees.Add(objectTree);
                UpdateTree(objectTree, index);
                Vector3 pos = objectTree.transform.localPosition;
                pos.x = sceneWidth * (index) + offsetWidths[index] * treeIndex + Random.Range(-20, 20);
                pos.x = left ? -pos.x : pos.x;
                pos.y = Random.Range(0, 40);
                pos.y += Random.Range(0, 40);
                ((RectTransform)objectTree.transform).localPosition = pos;
            }
        }
        
    }


    private void Refresh(bool left)
    {
        int[] offsetWidths = new int[sceneNumber];
        GameObject objectTree;
        for (int index = 0,objectIndex=0; index < sceneNumber; index++)
        {
            offsetWidths[index] = sceneWidth / sceneTreeNumber[index];
            for (int treeIndex = 0; treeIndex < sceneTreeNumber[index]; treeIndex++, objectIndex++)
            {
                objectTree = m_Trees[objectIndex];
                UpdateTree(objectTree, index);
                Vector3 pos = objectTree.transform.localPosition;
                pos.x = sceneWidth * (index + 1) + offsetWidths[index] * treeIndex + Random.Range(-20, 20);
                pos.x = left ? -pos.x : pos.x;
                pos.y = Random.Range(0, 40);
                pos.y += Random.Range(0, 40);
                ((RectTransform)objectTree.transform).localPosition = pos;
            }
        }

    }

    private GameObject AddTree()
    {
        GameObject objectGo = GameObject.Instantiate(copyGo);
        objectGo.transform.SetParent(this.transform);
        objectGo.transform.localScale = Vector3.one;
        objectGo.SetActive(true);
        return objectGo;
    }

    private void UpdateTree(GameObject target,int sceneIndex)
    {
        float width = Random.Range(120, 260);
        float height = Random.Range(500, 1200);

        Transform targetTra = target.transform;
        RectTransform targetRectTra = (RectTransform)targetTra;

        targetRectTra.sizeDelta = new Vector2(width, height);

        UnityEngine.UI.Image image = target.GetComponent<UnityEngine.UI.Image>();
        int colorIndex = Random.Range(0, colors.Length - 1);
        image.color = colors[colorIndex];

    }
}
