using UnityEngine;
using UnityEngine.UI;


public class AnimationController : MonoBehaviour
{
    public Sprite[] LeftSprites;
    public Sprite[] RightSprites;

    private Sprite[] MainSprites;

    public float speed;
    private SpriteRenderer spriterenderer;
    private Image image;
    private bool play = true;

    void Start()
    {
        spriterenderer = GetComponent<SpriteRenderer>();
        image = GetComponent<Image>();
    }

    void Update()
    {
        if(!play)
        {
            return;
        }
        int index = (int)(Time.time * speed) % MainSprites.Length;
        spriterenderer.sprite = MainSprites[index];
        image.sprite = MainSprites[index];
    }

    public void SetOpen(bool open)
    {
        if (spriterenderer != null)
        {
            spriterenderer.sprite = MainSprites[0];
        }
        if (image != null)
        {
            image.sprite = MainSprites[0];
        }
        play = open;
       
    }

    public void SetDir(bool left)
    {
        MainSprites = left ? LeftSprites: RightSprites;
    }

}
