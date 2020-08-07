#include"GameScene.h"


GameScene::~GameScene()
{
}

GameScene::GameScene()
{
	InitPicture();//����ͼƬ
	InitpPicture();//���뾫��

	SetGameP(PGameStart);//������Ϸ����
	POINT point = { 0, 0 };
	MouseSide(point);//������λ��
	MouseCSide(point);//�����λ��
}

void GameScene::InitPicture()
{
	CResourcesPool *pResPool = NULL;
	pResPool = CResourcesPool::GetInstance();
	ID2D1Bitmap *pBitmap = NULL;
	/*����*/
	pResPool->AddTexture(TEXT("people"), TEXT("image/����/people.bmp"), &pBitmap);
	pResPool->AddTexture(TEXT("����"), TEXT("image/����/����.bmp"), &pBitmap);
	pResPool->AddTexture(TEXT("��ȡ����"), TEXT("image/����/��ȡ����.bmp"), &pBitmap);
	pResPool->AddTexture(TEXT("����"), TEXT("image/����/����.bmp"), &pBitmap);
	pResPool->AddTexture(TEXT("ͨ��"), TEXT("image/����/ͨ��.bmp"), &pBitmap);
	pResPool->AddTexture(TEXT("����"), TEXT("image/����/����.bmp"), &pBitmap);

	/*��ͼ*/
	pResPool->AddTexture(TEXT("��ʼ"), TEXT("image/��ͼ/��ʼ.bmp"), &pBitmap);
	pResPool->AddTexture(TEXT("��צ���ϰ�"), TEXT("image/��ͼ/��צ���ϰ�.bmp"), &pBitmap);
	pResPool->AddTexture(TEXT("�ѹ�Ӣ"), TEXT("image/��ͼ/�ѹ�Ӣ.bmp"), &pBitmap);
	pResPool->AddTexture(TEXT("����"), TEXT("image/��ͼ/����.bmp"), &pBitmap);
	pResPool->AddTexture(TEXT("��"), TEXT("image/��ͼ/��.bmp"), &pBitmap);
	pResPool->AddTexture(TEXT("ˮ���ϰ�"), TEXT("image/��ͼ/ˮ���ϰ�.bmp"), &pBitmap);
	pResPool->AddTexture(TEXT("��"), TEXT("image/��ͼ/��.bmp"), &pBitmap);
	pResPool->AddTexture(TEXT("���ϰ�"), TEXT("image/��ͼ/���ϰ�.bmp"), &pBitmap);
	pResPool->AddTexture(TEXT("���ϰ�1"), TEXT("image/��ͼ/���ϰ�1.bmp"), &pBitmap);
	pResPool->AddTexture(TEXT("���ϰ�2"), TEXT("image/��ͼ/���ϰ�2.bmp"), &pBitmap);
	pResPool->AddTexture(TEXT("���ϰ�"), TEXT("image/��ͼ/���ϰ�.bmp"), &pBitmap);

	/*�ؿ�*/
	pResPool->AddTexture(TEXT("��צ��ؿ�"), TEXT("image/�ؿ�/��צ��.bmp"), &pBitmap);
	pResPool->AddTexture(TEXT("���ֹؿ�"), TEXT("image/�ؿ�/����.bmp"), &pBitmap);
	pResPool->AddTexture(TEXT("�ѹ�Ӣ�ؿ�"), TEXT("image/�ؿ�/�ѹ�Ӣ.bmp"), &pBitmap);
	pResPool->AddTexture(TEXT("����ؿ�"), TEXT("image/�ؿ�/����.bmp"), &pBitmap);
	pResPool->AddTexture(TEXT("���ؿ�"), TEXT("image/�ؿ�/��.bmp"), &pBitmap);
	pResPool->AddTexture(TEXT("ˮ�ιؿ�"), TEXT("image/�ؿ�/ˮ��.bmp"), &pBitmap);
	pResPool->AddTexture(TEXT("��ؿ�"), TEXT("image/�ؿ�/��.bmp"), &pBitmap);
	pResPool->AddTexture(TEXT("�ƹؿ�"), TEXT("image/�ؿ�/��.bmp"), &pBitmap);
}

void GameScene::InitpPicture()
{
	CSpritesManager *pSpritesManager = NULL;
	pSpritesManager = CSpritesManager::GetInstance();

	CResourcesPool *pResPool = NULL;
	pResPool = CResourcesPool::GetInstance();

	D2D1_SIZE_F Size;
	int w, h;

	/*��ʼ����*/
	Size = pResPool->GetResource(TEXT("��ʼ"))->pTexture->GetSize();
	w = Size.width / 3; h = Size.height / 2;
	GameStart = pSpritesManager->CreateAnimationSprite(TEXT("��ʼ"), 3, 30, D2D1::Point2F(0, 0), w, h);


	/*ѡ�ؽ���*/
	Size = pResPool->GetResource(TEXT("���ֹؿ�"))->pTexture->GetSize();
	w = Size.width / 2; h = Size.height / 4;
	GamePass[0] = pSpritesManager->CreateAnimationSprite(TEXT("���ֹؿ�"), 2, 1, D2D1::Point2F(0, 0), w, h);
	
	Size = pResPool->GetResource(TEXT("��ؿ�"))->pTexture->GetSize();
	w = Size.width / 2; h = Size.height / 5;
	GamePass[1] = pSpritesManager->CreateAnimationSprite(TEXT("��ؿ�"), 2, 1, D2D1::Point2F(0, 0), w, h);

	Size = pResPool->GetResource(TEXT("��צ��ؿ�"))->pTexture->GetSize();
	w = Size.width / 2; h = Size.height / 5;
	GamePass[2] = pSpritesManager->CreateAnimationSprite(TEXT("��צ��ؿ�"), 2, 1, D2D1::Point2F(0, 0), w, h);

	Size = pResPool->GetResource(TEXT("���ؿ�"))->pTexture->GetSize();
	w = Size.width / 2; h = Size.height / 5;
	GamePass[3] = pSpritesManager->CreateAnimationSprite(TEXT("���ؿ�"), 2, 1, D2D1::Point2F(0, 0), w, h);

	Size = pResPool->GetResource(TEXT("�ѹ�Ӣ�ؿ�"))->pTexture->GetSize();
	w = Size.width / 2; h = Size.height / 5;
	GamePass[4] = pSpritesManager->CreateAnimationSprite(TEXT("�ѹ�Ӣ�ؿ�"), 2, 1, D2D1::Point2F(0, 0), w, h);

	Size = pResPool->GetResource(TEXT("ˮ�ιؿ�"))->pTexture->GetSize();
	w = Size.width / 2; h = Size.height / 5;
	GamePass[5] = pSpritesManager->CreateAnimationSprite(TEXT("ˮ�ιؿ�"), 2, 1, D2D1::Point2F(0, 0), w, h);

	Size = pResPool->GetResource(TEXT("����ؿ�"))->pTexture->GetSize();
	w = Size.width / 2; h = Size.height / 5;
	GamePass[6] = pSpritesManager->CreateAnimationSprite(TEXT("����ؿ�"), 2, 1, D2D1::Point2F(0, 0), w, h);

	Size = pResPool->GetResource(TEXT("�ƹؿ�"))->pTexture->GetSize();
	w = Size.width / 2; h = Size.height / 5;
	GamePass[7] = pSpritesManager->CreateAnimationSprite(TEXT("�ƹؿ�"), 2, 1, D2D1::Point2F(0, 0), w, h);


	/*��Ϸ����*/
	Size = pResPool->GetResource(TEXT("��"))->pTexture->GetSize();
	w = Size.width / 3; h = Size.height/5;
	GameScreen = pSpritesManager->CreateAnimationSprite(TEXT("��"), 3, 20, D2D1::Point2F(0, 0), w, h);//��ͼ


	Size = pResPool->GetResource(TEXT("����"))->pTexture->GetSize();
	w = Size.width / 2; h = Size.height;
	Again = pSpritesManager->CreateAnimationSprite(TEXT("����"), 2, 1, D2D1::Point2F(0, 0), w, h);

	Size = pResPool->GetResource(TEXT("����"))->pTexture->GetSize();
	w = Size.width / 2; h = Size.height;
	Back = pSpritesManager->CreateAnimationSprite(TEXT("����"), 2, 1, D2D1::Point2F(0, 0), w, h);

	Fail = pSpritesManager->CreateSprite(TEXT("����"), D2D1::Point2F(0, 0));
	Success = pSpritesManager->CreateSprite(TEXT("ͨ��"), D2D1::Point2F(0, 0));
	for (int i = 0; i < 3; i++)
		GFood[i] = pSpritesManager->CreateSprite(TEXT("��ȡ����"), D2D1::Point2F(0, 0));

	/*��������*/
	Size = pResPool->GetResource(TEXT("people"))->pTexture->GetSize();
	w = Size.width / 4, h = Size.height / 6;
	People = pSpritesManager->CreateAnimationSprite(TEXT("people"), 4, 10, D2D1::Point2F(0, 0), w, h);

	for (int i = 0; i < HinderNumber; i++)
	{
		Size = pResPool->GetResource(TEXT("���ϰ�"))->pTexture->GetSize();
		w = Size.width; h = Size.height/2;
		Hinder[0][i] = pSpritesManager->CreateAnimationSprite(TEXT("���ϰ�"), 1, 1, D2D1::Point2F(0, 0), w, h);

		Size = pResPool->GetResource(TEXT("��צ���ϰ�"))->pTexture->GetSize();
		w = Size.width / 4, h = Size.height;
		Hinder[1][i] = pSpritesManager->CreateAnimationSprite(TEXT("��צ���ϰ�"), 4, 20, D2D1::Point2F(0, 0), w, h);

		Hinder[2][i] = pSpritesManager->CreateAnimationSprite(TEXT("��"), 1, 1, D2D1::Point2F(0, 0), 0, 0);

		Hinder[3][i] = pSpritesManager->CreateAnimationSprite(TEXT("�ѹ�Ӣ"), 1, 1, D2D1::Point2F(0, 0), 0, 0);

		Hinder[4][i] = pSpritesManager->CreateAnimationSprite(TEXT("ˮ���ϰ�"), 1, 1, D2D1::Point2F(0, 0), 0, 0);

		Hinder[5][i] = pSpritesManager->CreateAnimationSprite(TEXT("����"), 1, 1, D2D1::Point2F(0, 0), 0, 0);

		Hinder[6][i] = pSpritesManager->CreateAnimationSprite(TEXT("���ϰ�"), 1, 1, D2D1::Point2F(0, 0), 0,0);

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

