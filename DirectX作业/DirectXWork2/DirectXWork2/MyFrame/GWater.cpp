#include"GWater.h"


GameWater::GameWater()
{
	CResourcesPool *pResPool = NULL;
	pResPool = CResourcesPool::GetInstance();
	CNSpritesManager *pSpritesManager = NULL;
	pSpritesManager = CNSpritesManager::GetInstance();

	D2D1_SIZE_F Size = pResPool->GetResource(TEXT("Water"))->pTexture->GetSize();
	int w = Size.width / 4, h = Size.height / 2;
	pWater = pSpritesManager->CreateAnimationSprite(TEXT("Water"), 4, 5, D2D1::Point2F(0, 0), w, h);
	/*pWater->SetHotSpot(D2D1::Point2F(w/2,h/2));*/

	GWProgress = Nothing;
	Touch = false;
	
	/*水滴*/
	WaterRect[0] = { 36, 36, 63, 66 };//小
	WaterRect[1] = { 27, 28, 74, 73 };//中
	WaterRect[2] = { 9, 17, 92, 84 };//大
	
}

GameWater::~GameWater()
{
}

void GameWater::SetWaterPos(D2D1_POINT_2F p)
{
	Wpos = p;
	Wpos.x += pWater->GetHotSpot().x;
	Wpos.y += pWater->GetHotSpot().y;
	pWater->SetPos(Wpos);
}

D2D1_POINT_2F GameWater::GetWaterPos()
{
	return Wpos;
}


void GameWater::SetClick()
{
	switch (GWProgress)
	{
	case little:
		GWProgress = middle;
		break;

	case middle:
		GWProgress = big;
		break;

	case big:
		GWProgress = NothingWithSmall;
		break;

	case NothingWithSmall:
		GWProgress = Nothing;
		break;

	case Nothing:
		GWProgress = little;
		break;

	}
}

void GameWater::ChangeWaterProgress()
{
	int w = pWater->GetWidth();
	switch (GWProgress)
	{
	case little:
		pWater->SetVisible(true);
		pWater->SetTexPos(0,0);
		pWater->SetBoxDeviant(WaterRect[0]);
		break;

	case middle:
		pWater->SetVisible(true);
		pWater->SetTexPos(w*1, 0);
		pWater->SetBoxDeviant(WaterRect[1]);
		break;

	case big:
		pWater->SetVisible(true);
		pWater->SetTexPos(w*2, 0);
		pWater->SetBoxDeviant(WaterRect[2]);
		break;

	case NothingWithSmall:
		pWater->SetVisible(false);
		pWater->SetTexturePos(w * 3, 0);
		break;

	case Nothing:
		pWater->SetVisible(false);
		pWater->SetTexturePos(w*3, 0);
		break;
	}
}

void GameWater::SetTouch(bool p)
{
	Touch = p;
}

BOOL GameWater::GetTouch()
{
	return Touch;
}

BOOL GameWater::IsClick(POINT p)
{
	return pWater->IsSelected(p.x, p.y);
}



WaterProgress GameWater::GetGWProgress()
{
	return GWProgress;
}

void GameWater::SetGWProgress(WaterProgress p)
{
	GWProgress = p;
}

RECT GameWater::GetWaterRect(WaterProgress p)
{
	switch (p)
	{
	case little:
		return WaterRect[0];
	case middle:
		return WaterRect[1];
	case big:
		return WaterRect[2];
	default:
		RECT R = {0};
		return R;
	}
}

void GameWater::SetCol(int p)
{
	Col = p;
}

void GameWater::SetRow(int p)
{
	Row = p;
}

int GameWater::GetCol()
{
	return Col;
}

int GameWater::GetRow()
{
	return Row;
}

BOOL GameWater::IsTouch(RECT &rect)
{

	return pWater->CollideWith(rect);
}

BOOL GameWater::IsTouch(CNSprite nsprite)
{
	return pWater->CollideWith(nsprite);
}