using UnityEngine;
using System.Collections;


public class playController : MonoBehaviour
{
    private playerStateController playerState;
    void Start()
    {
        playerState = playerStateController.GetInstance();
    }

    void Update()
    {

        if (Input.GetKeyUp(KeyCode.LeftArrow))
        {
            playerState.GetKeyControl(PlayerState.Standing, DirectionState.Not, true);
        }
        if (Input.GetKeyUp(KeyCode.RightArrow))
        {
            playerState.GetKeyControl(PlayerState.Standing, DirectionState.Not, true);
        }
        if (Input.anyKey)
        {
            if (Input.GetKeyDown(KeyCode.LeftArrow))
            {
                playerState.GetKeyControl(PlayerState.Moving, DirectionState.Left);
            }

            if (Input.GetKeyDown(KeyCode.RightArrow))
            {
                playerState.GetKeyControl(PlayerState.Moving, DirectionState.Right);
            }
            if (Input.GetKeyDown(KeyCode.DownArrow))
            {
                playerState.GetKeyControl(PlayerState.PrepareDown);
            }

            if (Input.GetKeyDown(KeyCode.Space))
            {
                playerState.GetKeyControl(PlayerState.Jump);
            }

            if (Input.GetKeyDown(KeyCode.A))
            {
                playerState.GetKeyControl(PlayerState.Rotate, DirectionState.Left);
            }

            if (Input.GetKeyDown(KeyCode.D))
            {
                playerState.GetKeyControl(PlayerState.Rotate, DirectionState.Right);
            }

        }
    }
}
