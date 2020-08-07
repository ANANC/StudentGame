#pragma once

//#include<Windows.h>
//#include<dwrite.h>
#include"..\���-3CGame\SpritesManager.h"
#include"..\���-3CGame\ResourcesPool.h"

#define HinderNumber 20

using namespace std;

enum GameProgress /*��Ϸ״̬*/
{
	PGameStart,
	PGameSelect,
	PGamePlaying,
	PGamePlayWin,
	PGamePlayFail
};

class GameScene
{
public:
	static GameScene *GetInstance()
	{
		if (!instance)
		{
			instance = new GameScene();
		}
		return instance;
	}

	virtual ~GameScene(void);

private:
	GameScene();
	static GameScene *instance;

	static POINT Mpoint;//����ƶ�λ��
	static POINT Cpoint;//�����λ��
	GameProgress GameP;//��Ϸ����-��ʼ����ѡ�ػ��ǽ�����Ϸ��

	CAnimationSprite *GameStart;//��Ϸ��ʼ����
	CAnimationSprite *GamePass[8];//��Ϸѡ�ؽ���
	CAnimationSprite *GameScreen;//��Ϸ����
	//static CSprite *Two_F;//�㱳��
	//static CAnimationSprite *Two_FF[2];//�����
	CSprite *GFood[3];//ʳ��
	CAnimationSprite *Again;//����
	CAnimationSprite *Back;//����
	CSprite *Fail;//ʧ��
	CSprite *Success;//ʤ��
	CAnimationSprite *People;//����������
	CAnimationSprite *Hinder[7][HinderNumber];//�ϰ�

/*ͼƬ��غ���*/
	void InitPicture();//����ͼƬ
	void InitpPicture();//���뾫��

public:
	static void MouseSide(POINT MS);//������λ��
	static void MouseCSide(POINT MC);//�����λ��

	inline void SetGameP(GameProgress);//������Ϸ����
	GameProgress GetGameP(){return GameP;}//�õ���Ϸ����
	inline POINT GetMpoint(){ return Mpoint; }//�õ�����ƶ�λ��
	inline POINT GetCpoint(){ return Cpoint; }//�õ�����ƶ�λ��

public:
	void GetGameStart(CAnimationSprite **p){
		*p = GameStart;}

	void GetGamePass(CAnimationSprite *p[]){
		for (int i = 0; i < 8; i++)
		{
			p[i] = GamePass[i];
		}
	}

	void GetGameScreen(CAnimationSprite **p){
	*p = GameScreen;}

	void GetAgain(CAnimationSprite **p){
		*p = Again; }

	void GetBack(CAnimationSprite **p){
		*p = Back; }

	void GetPeople(CAnimationSprite **p){
		*p = People; }

	void GetHinder(CAnimationSprite *p[][HinderNumber]){
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < HinderNumber;j++)
				p[i][j] = Hinder[i][j];
		}
	}

	void GetGFood(CSprite *p[]){ 
		for (int i = 0; i < 3; i++)
		{
			p[i] = GFood[i];
		}
	}

	void GetFail(CSprite **p){ 
		*p = Fail; }

	void GetSuccess(CSprite **p){ 
		*p = Success; }
};