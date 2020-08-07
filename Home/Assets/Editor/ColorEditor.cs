using UnityEditor;
using System.Collections;

public class ColorEditor : EditorWindow {

    private string inputStr;
    private string colorStr;
    private string changeStr;

    [MenuItem("Tool/Color")]
    private static void Open()
    {
        EditorWindow.GetWindow<ColorEditor>();
    }


    private void OnGUI()
    {
        inputStr = EditorGUILayout.TextField("颜色：", colorStr);
        if(inputStr!=colorStr)
        {
            colorStr = inputStr;
            string[] colors = colorStr.Split(',');
            float r = float.Parse(colors[0]) / 255f;
            float g = float.Parse(colors[1]) / 255f;
            float b = float.Parse(colors[2]) / 255f;
            changeStr = string.Format("{0:N2},{1:N2},{2:N2}", r, g, b);
        }
         EditorGUILayout.TextField("转换：", changeStr);
    }
}
