#include"People.h"

#define KEY_LEFT (GetKeyState(VK_LEFT) & 0x80)>0 ? true : false
#define KEY_RIGHT  (GetKeyState(VK_RIGHT) & 0x80)>0 ? true : false
#define KEY_SPACE  (GetKeyState(VK_SPACE) & 0x80)>0 ? true : false
//#define KEY_SHIFT  (GetKeyState(VK_SHIFT) & 0x80)>0 ? true : false
//#define KEY_CTRL  (GetKeyState(VK_ESCAPE) & 0x80)>0 ? true : false

//CGameHinder *CGameHinder::instance = NULL;

CGamePeople::~CGamePeople()
{
}

CGamePeople::CGamePeople()
{
	pCGameScene = GameScene::GetInstance();
	pCGameScene->GetPeople(&People);

	People->SetVisible(false);
	CAnimationSprite *GameScreen;
	pCGameScene->GetGameScreen(&GameScreen);
	int x = GameScreen->GetWidth() / 2 - People->GetWidth() / 2;
	People->SetPos(D2D1::Point2F(x, 70));
	PeopleXaY = { 0, 0 };

	RotationAngle = 0;//旋转角度
	//操作人物一开始的位置
	
	PeoHeight = People->GetHeight();//人物图片的高度
	PeoWidth = People->GetWidth();//人物图片的宽度
	oldPos = { People->GetPos().x + PeoWidth / 2, People->GetPos().y };
	bIsFly = false;//是非飞
	bIsDown = false;//是否下落
	fFlyDistance = 0;//飞行高度

	CGameHinder *pCGameHinder = CGameHinder::GetInstance();
	pCGameHinder->GetPlayWay(PlayWay);
	pCGameHinder->GetIsStatic(IsStatic);
	pCGameHinder->GetrinSpeed(rinSpeed);

	Rotation = D2D1::Matrix3x2F::Identity();
	Translation = D2D1::Matrix3x2F::Identity();
	World = D2D1::Matrix3x2F::Identity();

}

void CGamePeople::PeoMove(float fDelataTime)
{

	static float fTime;
	float Rota = 0.7;

	if (pCGameScene->GetGameP() != PGamePlaying || IsStatic)
		return;

	bool IsMove;
	if (KEY_LEFT)
	{
		RotationAngle -= Rota * PlayWay * rinSpeed;
		People->SetTexturePos(0, 0);
		IsMove = true;
	}
	else if (KEY_RIGHT)
	{
		RotationAngle += Rota * PlayWay *rinSpeed;
		People->SetTexturePos(0, PeoHeight);
		IsMove = true;
	}
	else
		IsMove = false;

	if (KEY_SPACE)
		bIsFly = true;


	fTime += fDelataTime;
	if (fTime >= 0.06 && bIsFly && !bIsDown)//飞
	{
		fTime = 0;
		fFlyDistance += 5;
		if (fFlyDistance >= 45)
			bIsDown = true;
		People->SetTexturePos(0, PeoHeight * 2);
	}
	if (fTime >= 0.06 && bIsFly && bIsDown)//下落
	{
		fTime = 0;
		fFlyDistance -= 7;
		if (fFlyDistance <= 0)
		{
			bIsDown = false;
			bIsFly = false;
		}
		People->SetTexturePos(0, PeoHeight * 4);
	}

	if (IsMove || bIsFly)
		People->Resume();
	else
		People->Stop();

	Translation = D2D1::Matrix3x2F::Identity();
	Rotation = D2D1::Matrix3x2F::Identity();
	if (!bIsFly)
		Translation = D2D1::Matrix3x2F::Translation(oldPos.x, oldPos.y);
	else
		Translation = D2D1::Matrix3x2F::Translation(oldPos.x, oldPos.y - fFlyDistance);
	
	Rotation =  D2D1::Matrix3x2F::Rotation(RotationAngle, D2D1::Point2F(425.5f, 284));
	World = Translation* Rotation;
}

void CGamePeople::ShowPeoMove(ID2D1HwndRenderTarget *pRenderTarget)
{
	D2D1_POINT_2F wp = { 0, 0 };
	wp = World.TransformPoint(wp);
	People->SetPos(wp);
	People->SetRotationAngle(RotationAngle);
}

void CGamePeople::PeoFirst()
{
	RotationAngle = 0;
	People->Play();
	People->SetTexturePos(0, 0);
	People->SetRotationAngle(RotationAngle);
	People->SetPos(D2D1::Point2F(oldPos.x, oldPos.y));
}

void CGamePeople::GetPeopleXandY()
{
	PeopleXaY.x = People->GetPos().x;
	PeopleXaY.y = People->GetPos().y;
}