#pragma once
#include "Framework\Game.h"
#define HinderNumber 20


class Earth :public CGame
{
public:
	Earth(HWND hWnd, int fps = 0);
	~Earth(void);

public:
	void Init();
	void Update(float fDelataTime);
	void Render();

/*׼������*/
private:
	POINT Mpoint;//����ƶ�λ��
	POINT Cpoint;//�����λ��
	int GameP;//��Ϸ����-��ʼ����ѡ�ػ��ǽ�����Ϸ��
	bool IsGamePlay;//������Ϸ
	bool IsGameOver;//��Ϸ�Ƿ�ر�
public:
	void GetPicture();//����ͼƬ
	void Erase();//������
	void MouseSide();//������λ��
	void MouseCSide();//�����λ��
	void MouseMove();//������
	void MouseClick();//�����
	void GamePlaing(bool);//��Ϸ�Ƿ������
	void GameProgress(int);//������Ϸ����
	inline int GetGameP();//�õ���Ϸ����
	void SetGameOver();//���ùر���Ϸ
	void White();//��¼����
	void Read();//��ȡ����
	

/*��ʼ����*/
private:
	CAnimationSprite *GameStart;//��Ϸ��ʼ����
	RECT rGameStart;//��ʼ�Ŀ�
	bool IsSelectGameStart;//�Ƿ�Ӵ���
public:
	void GetGameStart();//�õ�ͼƬ
	void DeleteGameStart();//������
	void SelectGameStrat();//�����ʼ
	void MoveGameStrat();//������ʼ
	void GameStartPlay();//����ͼ��

/*ѡ�ؽ���*/
private:
	CAnimationSprite *GamePass[8];//��Ϸѡ�ؽ���
	bool IsPassSelect[8];//ѡ��״̬
	bool IsGamePass[8];//ͨ��״̬
	bool GP[8];//������
	int Gp;//�����ùؿ�
	float GameTime[8];//�ؿ�ʱ��
	int GameMunber;//��ǰ�ؿ�
public:
	void ChangePass();//ͨ���Ĺؿ��Ĳ�ͬ״̬
	void GetGamePass();//�õ�ͼƬ
	void DeleteGamePass();//������
	void SelectGamePass();//����ؿ�
	void MoveGamePass();//�����ؿ�
	void SetGameTime(int p,int m,int s);//����ͨ��ʱ��
	void SetGamePass(int i);//����ͨ��״̬
	void SetTip();//������ʾ
	inline int GetGameMunber();//�õ���ǰ�ؿ�

/*��Ϸ����*/
private:
	CAnimationSprite *GameScreen;//��Ϸ����
	CSprite *GFood[3];//ʳ��
	CAnimationSprite *Again;//����
	CAnimationSprite *Back;//����
	CSprite *Fail;//ʧ��
	CSprite *Success;//ʤ��
	int  FoodNumber;//���ʳ��
	bool IsGetFood[3];//�Ƿ�õ�ʳ��
	RECT ss;//Բ�Ŀ�
	bool IsMoveRestart;//����Ƿ����������
	bool IsMoveReturn;//����Ƿ���ڷ�����
public:
	void GetPlayScreen();//�õ���Ϸ�����ͼƬ
	void DelectPlayScreen();//����ͼƬ
	void Restart();//����=��ʼ��
	void Return();//����
	void MoveReturn();//��������
	void MoveRestart();//��������
	void SetFood();//���õ���
	void GetFood();//��õ���
	void FoodFirst();//���߳�ʼ��
	void First_in();//��һ�ν�����Ϸ-��ûд
	void GameSuccess();//������Ϸʤ��ͼƬ
	void GameOver();//������Ϸʧ��ͼƬ
	void GameSuccess(int);//��Ϸʤ��
	inline bool IsRestart();//�Ƿ������ݼ�
	inline bool IsGOver();//�Ƿ񰴷��ؿ�ݼ�
	void IsMoveInRestart();//�Ƿ����ŵ�������
	void IsMoveInReturn();//�Ƿ����ŵ�������

/*��������*/
private:
	CAnimationSprite *People;//����������
	float RotationAngle;//��ת�Ƕ�
	POINT oldPos;//����������һ��ʼ��λ��
	float PeoHeight;//�����ͼƬ�߶�
	float PeoWidth;//�����ͼƬ�߶�
	bool bIsFly;  //�Ƿ��
	bool bIsDown; // �Ƿ�����
	float fFlyDistance; // ���и߶�
	POINT PeopleXaY;//�����λ��
public:
	void GetPeople();//�õ�ͼƬ
	void DelectPeople();//����ͼƬ
	void PeoMove(float fDelataTime);//��ɫ���ƶ�
	void PeoFirst();//��ɫ�ĳ�ʼ��
	void GetPeopleXandY();//�õ������λ��

/*��ʱ��*/
private:
	int GameTime_min;//ʱ��ֲ���
	int GameTime_sec;//ʱ���벿��
	int GameTime_msec;//ʱ����벿��
	HFONT hf;//��ʱ���õĻ���
	int fD;//��ʱ�����ۼ�
public:
	void TimerUpdate(float fDeltaTime);//��ʱ���ĸ���
	void TimerShow();//��ʱ������ʾ
	void Selecthf();//ѡ�뻭��
	void Delecthf();//ɾ������
	void TimeFirst();//��ʱ����ʼ��


/*�ϰ�*/
private:
	CAnimationSprite *Hinder[7][HinderNumber];//�ϰ�
	int HinderSpeed[7][HinderNumber];//�ϰ����ٶ�
	int HinderNum[7];//�ϰ�������
	int IsBSee[7];//�ϰ�״̬
	int PlayWay;//�����Ƿ�ߵ�
	bool IsStatic;//�����Ƿ�̶�
	int IsLeft[2][HinderNumber];//�����-�Ƿ����
	int rinSpeed;//��-�ٶȸı�
public:
	void HinderCreate(/*float fDeltaTime*/);//�����ϰ�-��
	void HinderShow_static();//�����ϰ�-�̶�
	void HinderErase();//�ϰ���ʧ
	void GetHinder();//�����ϰ�ָ��
	void DelectHinder();//�ϰ�����
	void HinderMove();//�ϰ��ƶ�
	void HinderTouch(float fDelataTime);//�Ӵ��ϰ�
	void TouchDie(int p);//��Ͱ�צ��-��
	void Reverse(float fDelataTime);//��-�ߵ�����
	void ChangeSide();//�ѹ�Ӣ-λ�øı�
	void rin();//��-�ٶȸı�
	void light(float fDelataTime);//����-�̶�2��
	void TouchNoSee();//��-������ʧ
	
};