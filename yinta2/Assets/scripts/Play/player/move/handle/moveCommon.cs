using UnityEngine;
using System.Collections;

public class moveCommon : MonoBehaviour {

    static moveMessage movemessageinstance;
    static moveMessage Movemessage
    {
        get
        {
            if (movemessageinstance == null)
                movemessageinstance = gameCommon.moveMessageGetInstance;
            return movemessageinstance;
        }
    }
    static Transform playertransform;
    static Transform playerTransfrom
    {
        get
        {
            if (playertransform == null)
                playertransform = gameCommon.playerTransform;
            return playertransform;
        }
    }
    static Transform cameratransform;
    static Transform cameraTransform
    {
        get
        {
            if (cameratransform == null)
                cameratransform = gameCommon.MainCamera;
            return cameratransform;
        }
    }

    public static void Distroy()
    {
        movemessageinstance = null;
        playertransform = null;
        cameratransform = null;
    }


    #region 射线

    public static bool DoubleRaycast(bool IsFromPlayer,bool IsAll, RaycastLay raycastLay, 
        Vector3 excursion, DirectionState state, float Dircoe,out RaycastHit hit, float maxdistance, 
        RaycastLay checkinlay = RaycastLay.allLay,bool IsCheck = false)
    {
        bool b = false;
        hit = new RaycastHit();
        Vector3[] checkPos = new Vector3[2];
        Vector3 side = state == DirectionState.right ? gameCommon.checkExcursionPosition_forward : gameCommon.checkExcursionPosition_right;
        if(Abs(excursion.y) <0.1f)
        {
            side = new Vector3(Abs(side.x)+ Abs(excursion.x), Abs(side.y)+ Abs(excursion.y), Abs(side.z) + Abs(excursion.z));
            checkPos[0] = side;
            checkPos[1] = -side;
        }
        else
        {
            checkPos[0] = side +excursion;
            checkPos[1] = -side + excursion;
        }


        int all = 0;
        
        for (int i =0;i<2;i++)
        {
            bool Check = false;
            if(IsFromPlayer)
            {
                if(PlayerRaycast(checkPos[i], state,Dircoe,out hit,maxdistance, checkinlay, IsCheck) == raycastLay)
                {
                    Check = true;
                }
            }
            else
            {
                if(CameraRaycast(checkPos[i], out hit,maxdistance, checkinlay, IsCheck) == raycastLay)
                {
                    Check = true;
                }
            }

            if (Check)
            {
                if (IsAll)
                {
                    all += 1;
                }
                else
                {
                    b = true;
                    break;
                }
            }
            
        }

        if(IsAll)
        {
            b = all == 2 ? true : false;
        }

        return b;
    }

    public static RaycastLay PlayerRaycast(Vector3 Excursion, DirectionState state, float coe ,out RaycastHit hit, float maxdistance, RaycastLay checkinlay = RaycastLay.allLay, bool IsCheck= false)
    {
        bool b = false;
        RaycastLay lay = RaycastLay.Notthing;

        Vector3 checkPos = playerTransfrom.position + Excursion;

        if (Raycast(checkPos, state, coe, out hit, maxdistance,checkinlay,IsCheck))
            b = true;

        lay = GetRaycastLay(b, hit);

        return lay;
    }

    public static RaycastLay PlayerRaycast(Vector3 Excursion, Vector3 dir,out RaycastHit hit,float maxdistance, RaycastLay checkinlay = RaycastLay.allLay, bool IsCheck = false)
    {
        bool b = false;
        RaycastLay lay = RaycastLay.Notthing;

        if (Raycast(playerTransfrom.position+Excursion, dir, out hit, maxdistance, checkinlay, IsCheck))
            b = true;
        
        lay = GetRaycastLay(b, hit);

        return lay;
    }

    public static RaycastLay CameraRaycast(Vector3 Excursion, out RaycastHit hit, float maxdistance, RaycastLay checkinlay = RaycastLay.allLay, bool IsCheck = false)
    {
        bool b = false;
        RaycastLay lay = RaycastLay.Notthing;

        Vector3 checkPos = playerTransfrom.position;

        checkPos += Excursion;

        if (IsPlayerFaceX(DirectionState.forward))
            checkPos.x = cameraTransform.position.x;
        else
            checkPos.z = cameraTransform.position.z;
        

        Vector3 forward = playerTransfrom.forward;
        forward.y = 0;

        if (Raycast(checkPos, forward, out hit, maxdistance,checkinlay,IsCheck))
            b = true;

        lay = GetRaycastLay(b, hit);

        return lay;
    }

    public static bool Raycast(Vector3 pos, Vector3 dir, out RaycastHit hit, float maxdistance, RaycastLay checkinlay = RaycastLay.allLay, bool IsCheck = false)
    {
        bool b = false;
        
        if (IsCheck)
        {
            Debug.DrawRay(pos, dir * maxdistance);
            Debug.Break();
        }

        string name = GetLayerName(checkinlay);

        if (checkinlay == RaycastLay.allLay)
        {
            if (Physics.Raycast(pos, dir, out hit, maxdistance))
                b = true;
        }
        else
        {
            if (Physics.Raycast(pos, dir, out hit, maxdistance, 1 << LayerMask.NameToLayer(name)))
                b = true;
        }

        return b;
    }
    public static bool Raycast(Vector3 pos, DirectionState state, float coe, out RaycastHit hit, float maxdistance, RaycastLay checkinlay = RaycastLay.allLay, bool IsCheck = false)
    {
        bool b = false;
        
        Vector3 dir = GetDirection(state, coe);

        if (IsCheck)
        {
            Debug.DrawRay(pos, dir * maxdistance);
            Debug.Break();
        }

        string name = GetLayerName(checkinlay);

        if (checkinlay == RaycastLay.allLay)
        {
            if (Physics.Raycast(pos, dir, out hit, maxdistance))
                b = true;
        }
        else
        {
            if (Physics.Raycast(pos, dir, out hit, maxdistance,1<<LayerMask.NameToLayer(name)))
                b = true;
        }
        return b;
    }
    #endregion

    #region rance
    public static float GetRance(Transform tra, DirectionState state, bool IsCanMoveOut,bool IsCheck =false)
    {
        float rance = 0;
        float side = 0;

        GetDirectionLength(tra, state, out rance, out side);
        
        if (IsCanMoveOut)
            rance += side;
        else
            rance -= side;

        rance = rance / 2f;

        if (IsCheck)
        {
            if (state == DirectionState.up)
            {
                Debug.DrawRay(tra.position + playerTransfrom.up * rance, playerTransfrom.forward * 100);
                Debug.DrawRay(tra.position - playerTransfrom.up * rance, playerTransfrom.forward * 100);
            }
            else
            {
                Debug.DrawRay(tra.position + playerTransfrom.right * rance, Vector3.up * 100);
                Debug.DrawRay(tra.position - playerTransfrom.right * rance, Vector3.up * 100);
            }
            Debug.Break();
        }
        return rance;
    }

    public static bool IsMoveOutRance(Transform target, float rance, bool IsVertical)
    {
        bool b = false;

        DirectionState dirState = IsVertical ? DirectionState.up: DirectionState.right;

        float distance = GetPlayerAndTargetDistance(target, dirState);

        distance=Abs(distance);

      //  Debug.Log("距离："+distance+"范围："+rance);

        if (distance > rance)
            b = true;

        return b;
    }

    public static bool IsCanMoveinRance(Transform target, DirectionState state, Vector3 dir)
    {
        bool b = false;

        float distance = GetPlayerAndTargetDistance(target, state);
        Vector3 check = distance * dir;

        if(state == DirectionState.up)
        {
            if (check.y > 0 )
                b = true;
        }
        else
        {
            if (IsPlayerFaceX(state))
            {
                if (check.x > 0)
                    b = true;
            }
            else
            {
                if (check.z > 0)
                    b = true;
            }
        }

        return b;
    }
    #endregion

    #region y轴移动中的x轴相关计算
    public static Vector3 MoveJumpX()
    {
        Vector3 Speed = Vector3.zero;

        Vector3 dir = Movemessage.JumpDir;
        float speed = gameCommon.jumpXspeed;
        float coe = dir == gameCommon.Right ? 1 : -1;

        Speed += speed  * Movemessage.JumpxPower * dir;

        Speed += CheckIsNeeddodge(Movemessage.Standobject, DirectionState.right,coe, speed, true,false);

        return Speed;
    }

    public static Vector3 MoveDownX(float speed)
    {
        Vector3 Speed = Vector3.zero;
        Vector3 dir = Movemessage.DownDir;
        float coe = dir == gameCommon.Right ? 1 : -1;

        Speed += dir * speed * Movemessage.DownxPower;
        Speed += CheckIsNeeddodge(Movemessage.Standobject, DirectionState.right,coe, speed,true,false);
        return Speed;
    }

    public static Vector3 StandtoForward(Vector3 dir)
    {//修改方法：根据旋转次数，当为倍数时，且不为之前要做的倍数，检测是否做了，没有，检测是否可以做，如果可以，就做。当不为倍数时初始化，不做。
        Vector3 speed = Vector3.zero;
        RaycastHit hit;
        #region 之前的一些方法
        //bool IsNeedToMove = false;
        //bool IsCanToMove = false;

        //RaycastHit hit;
        //Vector3 excursion;

        //if (IsStandinBack())
        //    IsNeedToMove = true;

        //if(IsNeedToMove)
        //    IsCanToMove = !IshasobstructInforward();

        //if (IsCanToMove)
        //{
        //    excursion = -gameCommon.checkExcursionPosition_up * 3;
        //    if (CameraRaycast(excursion,out hit,1000))
        //    {
        //        Transform tra = hit.collider.transform;
        //        if(tra != Movemessage.Standobject)
        //        {
        //            Movemessage.UpdateStandobject(tra);
        //        }
        //    }

        //    speed += MoveToReallyPos(Movemessage.Standobject, 0.5f, -1, -0.5f);

        //}

        //RaycastHit hit;
        //Vector3 excursion = -gameCommon.checkExcursionPosition_up * 3;
        //if (CameraRaycast(excursion, out hit, 1000) == RaycastLay.standTag)
        //{
        //    Transform tra = hit.collider.transform;
        //    if(tra == Movemessage.Standobject)
        //    {
        //        if (IsStandinBack())
        //        {
        //            if (!IshasobstructInforward())
        //            {
        //                float high;
        //                float width;//判断版的面向
        //                if(IsPlayerFaceX(DirectionState.forward))
        //                {
        //                    high = GetSize(tra, "x");
        //                    width = GetSize(tra, "z");
        //                }
        //                else
        //                {
        //                    high = GetSize(tra, "z");
        //                    width = GetSize(tra, "x");
        //                }

        //                if (high > width)
        //                {
        //                    Vector3 distance = GetPlayerAndTargetDistance(tra, DirectionState.forward) * playerTransfrom.forward;
        //                    bool IsNeedDo = false;
        //                    if(IsPlayerFaceX(DirectionState.forward))
        //                    {
        //                        if (distance.x < 0)
        //                            IsNeedDo = true;
        //                    }
        //                    else
        //                    {
        //                        if (distance.z < 0)
        //                            IsNeedDo = true;
        //                    }

        //                    if(IsNeedDo)
        //                        speed += MoveToReallyPos(Movemessage.Standobject, 0.5f, -1, -0.3f);
        //                }
        //            }

        //        }
        //    }else
        //    {
        //        if(IsStandinBack())
        //        {
        //            if (!IshasobstructInforward())
        //            {
        //                Movemessage.UpdateStandobject(tra);
        //                speed += MoveToReallyPos(Movemessage.Standobject, 0.5f, -1, -0.3f);
        //            }
        //        }else
        //        {
        //            excursion = gameCommon.checkExcursionPosition_forward;
        //            float coe = 1;
        //            bool IsInback = true;
        //            for(int i =0;i<2;i++)
        //            {
        //                if (PlayerRaycast(excursion * coe, dir, out hit, 5) == RaycastLay.dailyTag)
        //                {
        //                    IsInback = false;
        //                    break;
        //                }
        //            }

        //            if(IsInback)
        //            {
        //                Movemessage.UpdateStandobject(tra);
        //                speed += MoveToReallyPos(Movemessage.Standobject, 0.5f, -1, -0.3f);
        //            }
        //        }
        //    }
        //}
        #endregion

        if (Movemessage.IsStandInbace)
        {
            if (!IshasobstructInforward(out hit))
            {
                Vector3 excursion = -gameCommon.checkExcursionPosition_up;
                
                if(CameraRaycast(excursion,out hit,1000) == RaycastLay.standTag)
                {
                    Transform tra = hit.collider.transform;
                    if (tra != Movemessage.Standobject)
                    {
                        Movemessage.UpdateStandobject(tra);
                    }
                    speed = MoveToReallyPos(DirectionState.forward, -1, tra, 0.5f, -0.5f, -0.8f);
                    Movemessage.IsStandInbace = false;
                }
            }
        }

        return speed;
    }

    
    public static void IsStandinBack()
    {
        //bool b = gameCommon.playerStateControllorGetInstance.IsinBack();

        RaycastHit hit;
        if(PlayerRaycast(Vector3.zero,DirectionState.forward,-1,out hit,25,RaycastLay.wallTag) == RaycastLay.wallTag)
        {
            Movemessage.IsStandInbace = true;
        }
        
    }

    public static bool IshasobstructInforward(out RaycastHit hit)
    {
        bool b = false;
        
        if (DoubleRaycast(true, false, RaycastLay.wallTag, Vector3.zero, DirectionState.forward, -1, out hit, 1000, RaycastLay.wallTag))
        {
            b = true;
        }

        return b;
    }

    public static bool IshasobstructofStand()
    {
        bool b = false;
        RaycastHit hit;
        Vector3 excursion = -gameCommon.checkExcursionPosition_up;
        Vector3 side = gameCommon.checkExcursionPosition_right;
        float coe = 1;
        int all = 0;
        for (int i = 0; i < 2; i++)
        {
            if (moveCommon.CameraRaycast(excursion + side * coe, out hit, 1000) != RaycastLay.standTag)
            {
                all += 1;
            }
        }

        if (all == 2)
            b = true;

        return b;
    }


    public static Vector3 StandOn()
    {
        Vector3 pos = Vector3.zero;
        RaycastHit hit;
        // if (moveCommon.PlayerRaycast(Vector3.zero, DirectionState.up, -1, out hit, 5)  == RaycastLay.Notthing )
        if(!IsTouchRoad(out hit))
        {
            Vector3 excursion = -gameCommon.checkExcursionPosition_up;
            if (moveCommon.PlayerRaycast(excursion, gameCommon.Right, out hit,1000,RaycastLay.standTag) == RaycastLay.standTag)
            {
                pos = MoveToReallyPos(DirectionState.right, 1, hit.collider.transform, 0.5f, 0.5f, 0.3f);
            }
            else if (moveCommon.PlayerRaycast(excursion, -gameCommon.Right, out hit, 1000, RaycastLay.standTag) == RaycastLay.standTag)
            {
                pos = MoveToReallyPos(DirectionState.right, -1, hit.collider.transform, 0.5f, 0.5f, 0.3f);
            }
            else if (moveCommon.PlayerRaycast(excursion, -gameCommon.Forward, out hit,1000, RaycastLay.standTag) == RaycastLay.standTag)
            {
                pos = MoveToReallyPos(DirectionState.forward, -1, hit.collider.transform, 0.5f, 0.5f, 0.3f);
            }
            else if (moveCommon.PlayerRaycast(excursion, gameCommon.Forward, out hit, 1000, RaycastLay.standTag) == RaycastLay.standTag)
            {
                pos = MoveToReallyPos(DirectionState.forward, 1, hit.collider.transform, 0.5f, 0.5f, 0.3f);
            }

            // pos += dir *0.8f;
        }
        return pos;
    }

    public static bool IsTouchStandofside(out RaycastHit hit)
    {
        bool b = false;
        hit = new RaycastHit();
        float coe = 1;
        for (int i = 0; i < 2; i++)
        {
            if (moveCommon.DoubleRaycast(true, false, RaycastLay.standTag, Vector3.zero, DirectionState.right, coe, out hit, 1))
            {
                b = true;
                break;
            }
            coe *= -1;
        }

        return b;
    }

    #endregion

    #region z轴的相关计算
    //public static Vector3 MoveToReallyPos(Transform tra,
    //    float lengthCoe,float playerLengthCoe,float LengthdailyCoe,
    //    bool IswithY = false,float highCoe = 0, float playerHighCoe =0,float HighdailyCoe =0)
    //{
    //    Vector3 Speed = Vector3.zero;

    //    Vector3 forward = playerTransfrom.forward;
    //    forward.y = 0;

    //    float length;
    //    float playerLength;

    //    GetDirectionLength(tra, DirectionState.forward,out length,out playerLength);

    //    if (IsPlayerFaceX(DirectionState.forward))
    //        Speed.x = tra.position.x;
    //    else
    //        Speed.z = tra.position.z;
    //    Speed += -forward * (length* lengthCoe + playerLength* playerLengthCoe + LengthdailyCoe);
    //    if (IsPlayerFaceX(DirectionState.forward))
    //        Speed.x -= playerTransfrom.position.x;
    //    else
    //        Speed.z -= playerTransfrom.position.z;

    //    if (IswithY)
    //    {
    //        GetDirectionLength(tra, DirectionState.up, out length, out playerLength);
    //        Speed.y = tra.position.y;
    //        Speed += Vector3.up * (length * highCoe + playerLength * playerHighCoe + HighdailyCoe);
    //        Speed.y -= playerTransfrom.position.y;
    //    }
    //    return Speed;
    //}

    public static Vector3 MoveToReallyPos(DirectionState state,float coe,Transform tra,float lengthCoe, float playerLengthCoe, float LengthdailyCoe)
    {
        Vector3 pos = Vector3.zero;

        float length;
        float playerLength;
        Vector3 direction = GetDirection(state, coe);
        Vector3 playerDirPos = Vector3.zero;

        GetDirectionLength(tra, state, out length, out playerLength);

        if(state == DirectionState.up)
        {
            pos.y = tra.position.y;
            playerDirPos.y = playerTransfrom.position.y;
        }
        else
        {
            if(IsPlayerFaceX(state))
            {
                pos.x = tra.position.x;
                playerDirPos.x = playerTransfrom.position.x;
            }
            else
            {
                pos.z = tra.position.z;
                playerDirPos.z = playerTransfrom.position.z;
            }
        }

        pos += direction * (length * lengthCoe + playerLength * playerLengthCoe + LengthdailyCoe);
        pos -= playerDirPos;
        
        return pos;
    }



    public static Vector3 CheckIsNeeddodge(Transform Standobject,DirectionState state,float coe, float speed,bool LaynameIswall, bool LaynameIsStand,bool IsMove = false,bool IsCheck = false)
    {
        Vector3 Speed = Vector3.zero;
        RaycastHit hit;
        float Maxdistance = speed *7;
        Transform checkTra = null;
        bool IsNeedDo = false;
        Vector3 right = gameCommon.Playersize_right * gameCommon.Right * 0.5f;
        if (LaynameIswall)
        {
           // if (IsMove && !IshasobstructofStand())
           if(IsMove)
            {
                if (DoubleRaycast(true, false, RaycastLay.wallTag, Vector3.zero, state, coe, out hit, Maxdistance, RaycastLay.wallTag,IsCheck))
                {
                    //if (DoubleRaycast(false, false, RaycastLay.wallTag, right, DirectionState.forward, 1, out hit, gameCommon.cameraDistance, RaycastLay.wallTag, IsCheck))
                    {
                        IsNeedDo = true;
                        checkTra = hit.collider.transform;
                    }
                }
            }
            if (!IsMove)
            {
                if (DoubleRaycast(false, false, RaycastLay.wallTag, right, DirectionState.forward, 1, out hit, gameCommon.cameraDistance, RaycastLay.wallTag, IsCheck))
                {
                    IsNeedDo = true;
                    checkTra = hit.collider.transform;
                    if(Movemessage.IsCanmoveinforward == false)
                    {
                        if (checkTra == Movemessage.FaceWall)
                            IsNeedDo = false;
                    }
                }
            }

        }

        if(LaynameIsStand)
        {
            if(DoubleRaycast(true,false,RaycastLay.standTag,Vector3.zero,state,coe,out hit,Maxdistance,RaycastLay.allLay,IsCheck))
            //if(DoubleRaycast(false,false,RaycastLay.standTag,Vector3.zero,DirectionState.forward,1,out hit,gameCommon.cameraDistance,RaycastLay.allLay,IsCheck))
            {
                IsNeedDo = true;
                checkTra = hit.collider.transform;
                if (Movemessage.IsCanmoveinforward == false)
                {
                    if (checkTra == Movemessage.FaceWall)
                        IsNeedDo = false;
                }
            }
        }
        
        if(IsNeedDo)
        {
            Speed = MoveToReallyPos(DirectionState.forward, -1, checkTra, 0.5f, 1f, 1f);
        }

        return Speed;
    }
    #endregion
    
    #region 基础计算
    static Vector3 GetDirection(DirectionState state,float coe)
    {
        Vector3 dir = Vector3.zero;
        if (state == DirectionState.forward)
        {
            if (IsPlayerFaceX(state))
            { dir.x = playerTransfrom.forward.x * coe; }
            else
            { dir.z = playerTransfrom.forward.z * coe; }
        }
        if (state == DirectionState.right)
        {
            if (IsPlayerFaceX(state))
            { dir.x = playerTransfrom.right.x * coe; }
            else
            { dir.z = playerTransfrom.right.z * coe; }
        }
        if (state == DirectionState.up)
        {
            dir.y = playerTransfrom.up.y * coe;
        }
        return dir;
    }
    public static bool IsPlayerFaceX(DirectionState state)
    {
        bool b = false;
        if (state == DirectionState.forward)
        {
            if (Abs(playerTransfrom.forward.x) >0.5f)
                b = true;
        }
        if (state == DirectionState.right)
        {
            if (Abs(playerTransfrom.right.x) > 0.5f)
                b = true;
        }
        return b;
    }

    static float GetSize(Transform tra, string s)
    {
        float length = 0;
        if (s == "x")
            length = tra.GetComponent<Renderer>().bounds.size.x;
        if (s == "y")
            length = tra.GetComponent<Renderer>().bounds.size.y;
        if (s == "z")
            length = tra.GetComponent<Renderer>().bounds.size.z;
        return length;
    }

    public static float GetPlayerAndTargetDistance(Transform target,DirectionState state)
    {
        float distance = 0;

        if (state == DirectionState.up)
            distance = target.position.y - playerTransfrom.position.y;
        else
        {
            if(IsPlayerFaceX(state))
                distance = target.position.x - playerTransfrom.position.x;
            else
                distance = target.position.z - playerTransfrom.position.z;
        }
        
        return distance;
    }
    
    static void GetDirectionLength(Transform target,DirectionState state,out float targetLength,out float playerLength)
    {
        if (state == DirectionState.up)
        {
            targetLength = GetSize(target, "y");
            playerLength = gameCommon.Playersize_Up;
        }
        else
        {
            if (IsPlayerFaceX(state))
                targetLength = GetSize(target, "x");
            else
                targetLength = GetSize(target, "z");

            if (state == DirectionState.forward)
                playerLength = gameCommon.Playersize_forward;
            else
                playerLength = gameCommon.Playersize_right;
        }
    }

    public static bool IsTouchRoad(out RaycastHit hit)
    {
        bool b = false;
        hit = new RaycastHit();
        float length = gameCommon.Playersize_Up*0.5f+0.5f;
        Vector3 excursion = gameCommon.Playersize_right*0.4f * gameCommon.Right;
        float coe = 1;

        for (int i = 0; i < 2; i++)
        {
            if (PlayerRaycast(excursion * coe, DirectionState.up, -1, out hit, length) == RaycastLay.standTag)
            {
                b = true;
                break;
            }
        }

        //if (DoubleRaycast(true, false, RaycastLay.standTag, Vector3.zero, DirectionState.up, -1, out hit, length))
        //    b = true;

        return b;
    }

    public static Vector3 GetPlayerAndTargetDistance(Vector3 pos)
    {
        return pos - playerTransfrom.position;
    }

    public static float Abs(float infloat)
    {
        float outfloat;
        outfloat = infloat < 0 ? -infloat : infloat;
        return outfloat;
    }

    static RaycastLay GetRaycastLay(bool IsCanCheck,RaycastHit hit)
    {
        RaycastLay lay = RaycastLay.Notthing;
        if (IsCanCheck)
        {
            if (hit.collider.gameObject.layer == LayerMask.NameToLayer(gameCommon.dailyTag))
                lay = RaycastLay.dailyTag;
            if (hit.collider.gameObject.layer == LayerMask.NameToLayer(gameCommon.wallTag))
                lay = RaycastLay.wallTag;
            if (hit.collider.gameObject.layer == LayerMask.NameToLayer(gameCommon.shinTag))
                lay = RaycastLay.shinTag;
            if (hit.collider.gameObject.layer == LayerMask.NameToLayer(gameCommon.standTag))
                lay = RaycastLay.standTag;
        }
        return lay;
    }

    static string GetLayerName(RaycastLay lay)
    {
        string name = "";

        if (lay == RaycastLay.standTag)
            name = gameCommon.standTag;
        if (lay == RaycastLay.dailyTag)
            name = gameCommon.dailyTag;
        if (lay == RaycastLay.shinTag)
            name = gameCommon.shinTag;
        if (lay == RaycastLay.wallTag)
            name = gameCommon.wallTag;

        return name;
    }
    #endregion
    
}
