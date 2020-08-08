using UnityEngine;
using System.Collections;

public class DialogBox : MonoBehaviour {

    public GameObject Dialog;
    public GameObject DialogTextBoxLabelGameObject;
    public GameObject DialogSelectTextButtonLabel;
    public GameObject DialogSelectLeftButtonLabel;
    public GameObject DialogSelectTextButton;
    public GameObject DialogSelectShopButton;
    public GameObject DialogSelectLeftButton;

    npc Selectnpc;

    protected Vector3 LeftButtonPos;

    public static DialogBox insatance;

    public static DialogBox GetInstance()
    {
        return insatance;
    }

    void Start()
    {
        Dialog.SetActive(false);
        DialogTextBoxLabelGameObject.GetComponent<UIWidget>().pivot = UIWidget.Pivot.Center;
        LeftButtonPos = DialogSelectLeftButton.transform.position;

        insatance = this;

        UIEventListener.Get(DialogSelectTextButton).onClick = TextClick;
        UIEventListener.Get(DialogSelectLeftButton).onClick = LeftClick;
        UIEventListener.Get(DialogSelectShopButton).onClick = ShopClick;
    }

    public void SelectNpc(npc g)
    {
        Selectnpc = g;
    }

    void TextClick(GameObject g)
    {
        Selectnpc.TextButtonClick();
    }

    void LeftClick(GameObject g)
    {
        Selectnpc.LeftButtonClick();
    }

    void ShopClick(GameObject g)
    {
        Selectnpc.ShopButtonClick();
    }

    public void TextOpen(string SelectText, string sleepTell,bool IsNeedShop = false)
    {
        Dialog.SetActive(true);
        DialogSelectTextButtonLabel.GetComponent<UILabel>().text =SelectText;
        DialogTextBoxLabelGameObject.GetComponent<UILabel>().text = sleepTell;

        if (IsNeedShop)
            DialogSelectShopButton.SetActive(true);
        else
        {
            DialogSelectShopButton.SetActive(false);
            DialogSelectLeftButton.transform.position = DialogSelectShopButton.transform.position;
        }
    }

    public void LeftButtonClick(bool IsClickDialogSelectTextButton)
    {
        Dialog.SetActive(false);
        DialogSelectTextButton.SetActive(true);
        DialogSelectShopButton.SetActive(true);
        if (IsClickDialogSelectTextButton)
        {
            DialogSelectLeftButton.transform.position = LeftButtonPos;
        }
        DialogSelectLeftButtonLabel.GetComponent<UILabel>().text = "没什么事了。";
    }

    public void TextButtonClick(string s)
    {
        DialogTextBoxLabelGameObject.GetComponent<UILabel>().text = s;

        DialogSelectTextButton.SetActive(false);
        DialogSelectShopButton.SetActive(false);
        DialogSelectLeftButton.transform.position = DialogSelectTextButton.transform.position;
        DialogSelectLeftButtonLabel.GetComponent<UILabel>().text = "好的。";
    }
}
