#include"GWaterSmall.h"

GameWaterSmall::GameWaterSmall()
{
	CResourcesPool *pResPool = NULL;
	pResPool = CResourcesPool::GetInstance();
	CNSpritesManager *pSpritesManager = NULL;
	pSpritesManager = CNSpritesManager::GetInstance();

	D2D1_SIZE_F Size = pResPool->GetResource(TEXT("Water"))->pTexture->GetSize();
	int w = Size.width / 4, h = Size.height / 2;
	for (int i = 0; i < 4; i++)
	{
		pWaterSmall[i] = pSpritesManager->CreateAnimationSprite(TEXT("Water"), 4, 5, D2D1::Point2F(0,0), w, h);
		pWaterSmall[i]->SetTexPos(w*i, h);
		//pWaterSmall[i]->SetVisible(false);
	}

	/*小水滴*/
	WaterSamllRect[0] = { 33, 38, 70, 61 };//右
	pWaterSmall[0]->SetBoxDeviant(WaterSamllRect[0]);
	pWaterSmall[0]->SetHotSpot(D2D1::Point2F(w, h/2));

	WaterSamllRect[1] = { 31, 39, 63, 66 };//左
	pWaterSmall[1]->SetBoxDeviant(WaterSamllRect[1]);
	pWaterSmall[1]->SetHotSpot(D2D1::Point2F(0,h/2));

	WaterSamllRect[2] = { 38, 31, 61, 67 };//上
	pWaterSmall[2]->SetBoxDeviant(WaterSamllRect[2]);
	pWaterSmall[2]->SetHotSpot(D2D1::Point2F(w/2,0));

	WaterSamllRect[3] = { 37, 30, 64, 66 };//下
	pWaterSmall[3]->SetBoxDeviant(WaterSamllRect[3]);
	pWaterSmall[3]->SetHotSpot(D2D1::Point2F(w/2,h));


	SmallOverNumber = 0;
}

GameWaterSmall::~GameWaterSmall()
{
}

void GameWaterSmall::SetWaterSPos(int i, D2D1_POINT_2F p)
{
	WSpos[i] = p;
	/*WSpos[i].x += pWaterSmall[i]->GetHotSpot().x;
	WSpos[i].y += pWaterSmall[i]->GetHotSpot().y;*/
	pWaterSmall[i]->SetPos(WSpos[i]);
}

D2D1_POINT_2F GameWaterSmall::GetWatersHotPos(int i)
{
	D2D1_POINT_2F p;
	CResourcesPool *pResPool = NULL;
	pResPool = CResourcesPool::GetInstance();
	D2D1_SIZE_F Size = pResPool->GetResource(TEXT("Water"))->pTexture->GetSize();
	int w = Size.width / 4, h = Size.height / 2;
	if (i == 0)//右
	{
		p = { w, h / 2 };
	}
	if (i == 1)//左
	{
		p = { 0, h / 2 };
	}
	if (i == 2)//上
	{
		p = { w / 2, 0 };
	}
	if (i == 3)//下
	{
		p = { w / 2, h };
	}
	return p;
}

const D2D1_RECT_F *GameWaterSmall::GetWatersBoundingBox(int i)
{
	return pWaterSmall[i]->GetBoundingBox();
}

D2D1_POINT_2F GameWaterSmall::GetWaterSPos(int i)
{
	return WSpos[i];
}


void GameWaterSmall::SetSmallOverNumber(int i)
{
	if (i == -1)
		SmallOverNumber++;
	else
		SmallOverNumber = i;
}

int GameWaterSmall::GetSmallOverNumber()
{
	return SmallOverNumber;
}

void GameWaterSmall::SetWaterSamllVisible(int i, BOOL p)
{
	pWaterSmall[i]->SetVisible(p);
}

void GameWaterSmall::SetCol(int p)
{
	Col = p;
}

void GameWaterSmall::SetRow(int p)
{
	Row = p;
}

int GameWaterSmall::GetCol()
{
	return Col;
}

int GameWaterSmall::GetRow()
{
	return Row;
}

const CAnimationSprite GameWaterSmall::GetWatersAnimationSprite(int i)
{
	return *pWaterSmall[i];
}

BOOL GameWaterSmall::GetWaterSamllVisible(int i)
{
	return pWaterSmall[i]->IsVisible();
}