using UnityEngine;
using System.Collections.Generic;

public class StoneController : MonoBehaviour {

    public GameObject copyGo;
    private List<GameObject> m_Stone;

    public int sceneWidth;
    public int sceneNumber;
    public int[] sceneTreeNumber;

    private Color[] colors = {
        new Color(0.12f,0.13f,0.11f),
        new Color(0.25f,0.26f,0.25f),
        new Color(0.42f,0.42f,0.41f),
        new Color(0.22f,0.23f,0.22f),
    };

    public void Show(bool left)
    {
        this.gameObject.SetActive(true);

        if (m_Stone == null)
        {
            m_Stone = new List<GameObject>();
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
        for (int index = 0; index < sceneNumber; index++)
        {
            offsetWidths[index] = sceneWidth / sceneTreeNumber[index];
            for (int treeIndex = 0; treeIndex < sceneTreeNumber[index]; treeIndex++)
            {
                objectTree = AddStone();
                m_Stone.Add(objectTree);
                UpdateStone(objectTree, index);
                Vector3 pos = objectTree.transform.localPosition;
                pos.x = sceneWidth * (index + 1) + offsetWidths[index] * treeIndex + Random.Range(-20, 20);
                pos.x = left ? -pos.x : pos.x;
                pos.y = Random.Range(-450, -500);
                ((RectTransform)objectTree.transform).localPosition = pos;
            }
        }

    }

    private void Refresh(bool left)
    {
        int[] offsetWidths = new int[sceneNumber];
        GameObject objectTree;
        for (int index = 0,objectIndex = 0; index < sceneNumber; index++)
        {
            offsetWidths[index] = sceneWidth / sceneTreeNumber[index];
            for (int treeIndex = 0; treeIndex < sceneTreeNumber[index]; treeIndex++, objectIndex++)
            {
                objectTree = m_Stone[objectIndex];
                UpdateStone(objectTree, index);
                Vector3 pos = objectTree.transform.localPosition;
                pos.x = sceneWidth * (index + 1) + offsetWidths[index] * treeIndex + Random.Range(-20, 20);
                pos.x = left ? -pos.x : pos.x;
                pos.y = Random.Range(-450, -500);
                ((RectTransform)objectTree.transform).localPosition = pos;
            }
        }

    }

    private GameObject AddStone()
    {
        GameObject objectGo = GameObject.Instantiate(copyGo);
        objectGo.transform.SetParent(this.transform);
        objectGo.transform.localScale = Vector3.one;
        objectGo.SetActive(true);
        return objectGo;
    }

    private void UpdateStone(GameObject target, int sceneIndex)
    {
        float width = Random.Range(40, 160);
        float height = Random.Range(80, 200);

        Transform targetTra = target.transform;
        RectTransform targetRectTra = (RectTransform)targetTra;

        targetRectTra.sizeDelta = new Vector2(width, height);

        UnityEngine.UI.Image image = target.GetComponent<UnityEngine.UI.Image>();
        int colorIndex = Random.Range(0, colors.Length - 1);
        image.color = colors[colorIndex];
    }
}
