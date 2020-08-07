using UnityEngine;
using System.Collections;

public class playerAnimator {

    static playerAnimator _instance;
    public static playerAnimator GetInstance
    {
        get
        {
            if (_instance == null)
                _instance = new playerAnimator();
            return _instance;
        }
    }

    playerStateControllor stateControllor;
    private Animator animator;
    Stack stateStack;
    bool IsStopDazeIEnumerator;


     playerAnimator() {
        animator = gameCommon.playerTransform.GetChild(0).GetComponent<Animator>();
        stateStack = new Stack();
        IsStopDazeIEnumerator = false;
    }

    public static void Distroy()
    {
        _instance = null;
    }

	
    public void SetState(PlayerState state)
    {
        if (stateStack.Count != 0)
        {
            PlayerState oldState;
            oldState = (PlayerState)stateStack.Pop();
            SetState(oldState, false);
            if (oldState == PlayerState.Standing)
                IsStopDazeIEnumerator = true;
        }
        stateStack.Push(state);
        SetState(state, true);
        if (state != PlayerState.shinning)
        {
            if (animator.GetInteger("Direction") == -1)
            { animator.SetInteger("Direction", 0); }
        }
    }

    IEnumerator StartStand()
    {
        float time = 0;
        while (true)
        {

            time += Time.deltaTime;
            if (time > 3)
            {
                SetDaze(true);
            }
            if (time > 3.5f)
            {
                SetDaze(false);
                time = 0;
            }

            if (IsStopDazeIEnumerator)
            {
                SetDaze(false);
                break;
            }

            yield return 0;
        }
    }

    void SetState(PlayerState state,bool b)
    {
        if(state == PlayerState.Standing || state == PlayerState.StandMoveStand)
        {
            animator.SetBool("IsStand", b); 
            if (stateControllor == null)
            {
                stateControllor = gameCommon.playerStateControllorGetInstance;
            }
            IsStopDazeIEnumerator = false;
            stateControllor.ToStartCoroutine(StartStand());
        }
        if(state == PlayerState.Moving)
        {
            animator.SetBool("IsRun", b);
        }
        if (state == PlayerState.Jump)
        {
            animator.SetBool("IsJump", b);
        }
        if (state == PlayerState.Dowing)
        {
            animator.SetBool("IsDown", b);
        }
        if(state == PlayerState.shinning)
        {
            animator.SetBool("IsShin",b);
        }
        if(state == PlayerState.hanging)
        {
            animator.SetBool("IsHang", b);
        }
    }

    void SetDaze(bool b)
    {
        animator.SetBool("IsDaze", b);
    }

    public void SetDirection(DirectionState state,float coe)
    {
        if(state == DirectionState.right)
        {
            if(coe == 1)
            {
                animator.SetInteger("Direction", 1);
            }
            if(coe == -1)
            {
                animator.SetInteger("Direction", 0);
            }
        }
        if(state == DirectionState.up)
        {
            PlayerState nowPlayerstate = (PlayerState)stateStack.Pop();
            if (nowPlayerstate == PlayerState.shinning)
            { animator.SetInteger("Direction", -1); }
            stateStack.Push(nowPlayerstate);
        }
    }
}
