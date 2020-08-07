#include"GameScene.h"


GameScene::~GameScene()
{
}

GameScene::GameScene()
{
	InitPicture();//载入图片
	InitpPicture();//载入精灵

	SetGameP(PGameStart);//设置游戏进程
	POINT point = { 0, 0 };
	MouseSide(point);//鼠标放置位置
	MouseCSide(point);//鼠标点击位置
}

void GameScene::InitPicture()
{
	CResourcesPool *pResPool = NULL;
	pResPool = CResourcesPool::GetInstance();
	ID2D1Bitmap *pBitmap = NULL;
	/*道具*/
	pResPool->AddTexture(TEXT("people"), TEXT("image/道具/people.bmp"), &pBitmap);
	pResPool->AddTexture(TEXT("返回"), TEXT("image/道具/返回.bmp"), &pBitmap);
	pResPool->AddTexture(TEXT("获取道具"), TEXT("image/道具/获取道具.bmp"), &pBitmap);
	pResPool->AddTexture(TEXT("死亡"), TEXT("image/道具/死亡.bmp"), &pBitmap);
	pResPool->AddTexture(TEXT("通关"), TEXT("image/道具/通关.bmp"), &pBitmap);
	pResPool->AddTexture(TEXT("重来"), TEXT("image/道具/重来.bmp"), &pBitmap);

	/*地图*/
	pResPool->AddTexture(TEXT("开始"), TEXT("image/地图/开始.bmp"), &pBitmap);
	pResPool->AddTexture(TEXT("八爪鱼障碍"), TEXT("image/地图/八爪鱼障碍.bmp"), &pBitmap);
	pResPool->AddTexture(TEXT("蒲公英"), TEXT("image/地图/蒲公英.bmp"), &pBitmap);
	pResPool->AddTexture(TEXT("闪电"), TEXT("image/地图/闪电.bmp"), &pBitmap);
	pResPool->AddTexture(TEXT("树"), TEXT("image/地图/树.bmp"), &pBitmap);
	pResPool->AddTexture(TEXT("水滴障碍"), TEXT("image/地图/水滴障碍.bmp"), &pBitmap);
	pResPool->AddTexture(TEXT("鱼"), TEXT("image/地图/鱼.bmp"), &pBitmap);
	pResPool->AddTexture(TEXT("鱼障碍"), TEXT("image/地图/鱼障碍.bmp"), &pBitmap);
	pResPool->AddTexture(TEXT("鱼障碍1"), TEXT("image/地图/鱼障碍1.bmp"), &pBitmap);
	pResPool->AddTexture(TEXT("鱼障碍2"), TEXT("image/地图/鱼障碍2.bmp"), &pBitmap);
	pResPool->AddTexture(TEXT("云障碍"), TEXT("image/地图/云障碍.bmp"), &pBitmap);

	/*关卡*/
	pResPool->AddTexture(TEXT("八爪鱼关卡"), TEXT("image/关卡/八爪鱼.bmp"), &pBitmap);
	pResPool->AddTexture(TEXT("练手关卡"), TEXT("image/关卡/练手.bmp"), &pBitmap);
	pResPool->AddTexture(TEXT("蒲公英关卡"), TEXT("image/关卡/蒲公英.bmp"), &pBitmap);
	pResPool->AddTexture(TEXT("闪电关卡"), TEXT("image/关卡/闪电.bmp"), &pBitmap);
	pResPool->AddTexture(TEXT("树关卡"), TEXT("image/关卡/树.bmp"), &pBitmap);
	pResPool->AddTexture(TEXT("水滴关卡"), TEXT("image/关卡/水滴.bmp"), &pBitmap);
	pResPool->AddTexture(TEXT("鱼关卡"), TEXT("image/关卡/鱼.bmp"), &pBitmap);
	pResPool->AddTexture(TEXT("云关卡"), TEXT("image/关卡/云.bmp"), &pBitmap);
}

void GameScene::InitpPicture()
{
	CSpritesManager *pSpritesManager = NULL;
	pSpritesManager = CSpritesManager::GetInstance();

	CResourcesPool *pResPool = NULL;
	pResPool = CResourcesPool::GetInstance();

	D2D1_SIZE_F Size;
	int w, h;

	/*开始界面*/
	Size = pResPool->GetResource(TEXT("开始"))->pTexture->GetSize();
	w = Size.width / 3; h = Size.height / 2;
	GameStart = pSpritesManager->CreateAnimationSprite(TEXT("开始"), 3, 30, D2D1::Point2F(0, 0), w, h);


	/*选关界面*/
	Size = pResPool->GetResource(TEXT("练手关卡"))->pTexture->GetSize();
	w = Size.width / 2; h = Size.height / 4;
	GamePass[0] = pSpritesManager->CreateAnimationSprite(TEXT("练手关卡"), 2, 1, D2D1::Point2F(0, 0), w, h);
	
	Size = pResPool->GetResource(TEXT("鱼关卡"))->pTexture->GetSize();
	w = Size.width / 2; h = Size.height / 5;
	GamePass[1] = pSpritesManager->CreateAnimationSprite(TEXT("鱼关卡"), 2, 1, D2D1::Point2F(0, 0), w, h);

	Size = pResPool->GetResource(TEXT("八爪鱼关卡"))->pTexture->GetSize();
	w = Size.width / 2; h = Size.height / 5;
	GamePass[2] = pSpritesManager->CreateAnimationSprite(TEXT("八爪鱼关卡"), 2, 1, D2D1::Point2F(0, 0), w, h);

	Size = pResPool->GetResource(TEXT("树关卡"))->pTexture->GetSize();
	w = Size.width / 2; h = Size.height / 5;
	GamePass[3] = pSpritesManager->CreateAnimationSprite(TEXT("树关卡"), 2, 1, D2D1::Point2F(0, 0), w, h);

	Size = pResPool->GetResource(TEXT("蒲公英关卡"))->pTexture->GetSize();
	w = Size.width / 2; h = Size.height / 5;
	GamePass[4] = pSpritesManager->CreateAnimationSprite(TEXT("蒲公英关卡"), 2, 1, D2D1::Point2F(0, 0), w, h);

	Size = pResPool->GetResource(TEXT("水滴关卡"))->pTexture->GetSize();
	w = Size.width / 2; h = Size.height / 5;
	GamePass[5] = pSpritesManager->CreateAnimationSprite(TEXT("水滴关卡"), 2, 1, D2D1::Point2F(0, 0), w, h);

	Size = pResPool->GetResource(TEXT("闪电关卡"))->pTexture->GetSize();
	w = Size.width / 2; h = Size.height / 5;
	GamePass[6] = pSpritesManager->CreateAnimationSprite(TEXT("闪电关卡"), 2, 1, D2D1::Point2F(0, 0), w, h);

	Size = pResPool->GetResource(TEXT("云关卡"))->pTexture->GetSize();
	w = Size.width / 2; h = Size.height / 5;
	GamePass[7] = pSpritesManager->CreateAnimationSprite(TEXT("云关卡"), 2, 1, D2D1::Point2F(0, 0), w, h);


	/*游戏界面*/
	Size = pResPool->GetResource(TEXT("鱼"))->pTexture->GetSize();
	w = Size.width / 3; h = Size.height/5;
	GameScreen = pSpritesManager->CreateAnimationSprite(TEXT("鱼"), 3, 20, D2D1::Point2F(0, 0), w, h);//地图


	Size = pResPool->GetResource(TEXT("重来"))->pTexture->GetSize();
	w = Size.width / 2; h = Size.height;
	Again = pSpritesManager->CreateAnimationSprite(TEXT("重来"), 2, 1, D2D1::Point2F(0, 0), w, h);

	Size = pResPool->GetResource(TEXT("返回"))->pTexture->GetSize();
	w = Size.width / 2; h = Size.height;
	Back = pSpritesManager->CreateAnimationSprite(TEXT("返回"), 2, 1, D2D1::Point2F(0, 0), w, h);

	Fail = pSpritesManager->CreateSprite(TEXT("死亡"), D2D1::Point2F(0, 0));
	Success = pSpritesManager->CreateSprite(TEXT("通关"), D2D1::Point2F(0, 0));
	for (int i = 0; i < 3; i++)
		GFood[i] = pSpritesManager->CreateSprite(TEXT("获取道具"), D2D1::Point2F(0, 0));

	/*操作人物*/
	Size = pResPool->GetResource(TEXT("people"))->pTexture->GetSize();
	w = Size.width / 4, h = Size.height / 6;
	People = pSpritesManager->CreateAnimationSprite(TEXT("people"), 4, 10, D2D1::Point2F(0, 0), w, h);

	for (int i = 0; i < HinderNumber; i++)
	{
		Size = pResPool->GetResource(TEXT("鱼障碍"))->pTexture->GetSize();
		w = Size.width; h = Size.height/2;
		Hinder[0][i] = pSpritesManager->CreateAnimationSprite(TEXT("鱼障碍"), 1, 1, D2D1::Point2F(0, 0), w, h);

		Size = pResPool->GetResource(TEXT("八爪鱼障碍"))->pTexture->GetSize();
		w = Size.width / 4, h = Size.height;
		Hinder[1][i] = pSpritesManager->CreateAnimationSprite(TEXT("八爪鱼障碍"), 4, 20, D2D1::Point2F(0, 0), w, h);

		Hinder[2][i] = pSpritesManager->CreateAnimationSprite(TEXT("树"), 1, 1, D2D1::Point2F(0, 0), 0, 0);

		Hinder[3][i] = pSpritesManager->CreateAnimationSprite(TEXT("蒲公英"), 1, 1, D2D1::Point2F(0, 0), 0, 0);

		Hinder[4][i] = pSpritesManager->CreateAnimationSprite(TEXT("水滴障碍"), 1, 1, D2D1::Point2F(0, 0), 0, 0);

		Hinder[5][i] = pSpritesManager->CreateAnimationSprite(TEXT("闪电"), 1, 1, D2D1::Point2F(0, 0), 0, 0);

		Hinder[6][i] = pSpritesManager->CreateAnimationSprite(TEXT("云障碍"), 1, 1, D2D1::Point2F(0, 0), 0,0);

	}
}

void GameScene::MouseSide(POINT MS)
{
	Mpoint = MS;
}

void GameScene::MouseCSide(POINT MC)
{
	Cpoint = MC;
}

void GameScene::SetGameP(GameProgress p)
{
	GameP = p;
}

