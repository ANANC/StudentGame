#include"WaterManager.h"

GWaterManager::GWaterManager()
{	
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			pGameWater[j + row*i] = new GameWater();
			D2D1_POINT_2F p = { i*91 + 12, j*90 + 10 };
			pGameWater[j + row*i]->SetWaterPos(p);
			pGameWater[j + row*i]->SetCol(j);
			pGameWater[j + row*i]->SetRow(i);
			pGameWater[j + row*i]->SetGWProgress(Nothing);
			pGameWater[j + row*i]->ChangeWaterProgress();
		}
	}
	rClient = {13,10,478,470};

	/*点击音效*/
	pClickMusic = new XAudio2SoundPlayer();
	pClickMusic->LoadSound(TEXT("resource\\点点.wav"));
	/*爆炸音效*/
	pBoomMusic = new XAudio2SoundPlayer();
	pBoomMusic->LoadSound(TEXT("resource\\爆.wav"));
}

GWaterManager::~GWaterManager()
{
}

void GWaterManager::Init()
{
	for (int i = 0; i < col*row; i++)
	{
		pGameWater[i]->SetGWProgress(Nothing);
		pGameWater[i]->ChangeWaterProgress();
	}
}

BOOL GWaterManager::MClick(POINT p)
{
	for (int i = 0; i < row*col; i++)
	{
		if (pGameWater[i]->IsClick(p))
		{
			//如果出于爆炸状态，不能通过点击改变状态
			if (pGameWater[i]->GetGWProgress() == NothingWithSmall)
				continue;

			//改变大水滴状态
			pGameWater[i]->SetClick();
			pGameWater[i]->ChangeWaterProgress();

			//如果是爆炸，向小水滴链表添加对象
			if (pGameWater[i]->GetGWProgress() == NothingWithSmall)
			{
				GameWaterSmall *k = new GameWaterSmall;
				for (int j = 0; j < 4; j++)
				{
					D2D1_POINT_2F p = pGameWater[i]->GetWaterPos();
					p.x += k->GetWatersHotPos(j).x;
					p.y += k->GetWatersHotPos(j).y;
					k->SetWaterSPos(j, p);
				}
				k->SetCol(pGameWater[i]->GetCol());
				k->SetRow(pGameWater[i]->GetRow());
				pGameWaterSmall.push_back(k);
			}

			//水滴容量减少
			SetAddWNumber(-1);
			//点击音效
			pClickMusic->PlaySound(pClickMusic->GetSoundCount());
			return true;
		}
	}
	return false;
}


void GWaterManager::WaterTouch()
{
	if (pGameWaterSmall.empty())
		return;

	Iterator = pGameWaterSmall.begin();
	while (Iterator != pGameWaterSmall.end())
	{
		for (int j = 0; j < 4; j++)
		{
			//如果可见性为假，跳过这次循环
			if (!(*Iterator)->GetWaterSamllVisible(j))
				continue;

			//首先一直改变位移
			//是否跳出屏幕外
			D2D1_POINT_2F point = (*Iterator)->GetWaterSPos(j);
			//POINT p = { (*Iterator)->GetWaterSPos(j).x, (*Iterator)->GetWaterSPos(j).y };
			if (point.x > rClient.right || point.x<rClient.left || point.y>rClient.bottom || point.y < rClient.top)
			{
				//如果跳出屏幕外，不再改变，设置小水滴脱离状态
				(*Iterator)->SetSmallOverNumber();
				(*Iterator)->SetWaterSamllVisible(j, false);
				continue;
			}

			//没有跳出，位置继续改变
			//D2D1_POINT_2F point = (*Iterator)->GetWaterSPos(j);
			if (j == 2)//上
				(*Iterator)->SetWaterSPos(j, D2D1::Point2F(point.x, point.y - 3));
			if (j == 0)//右
				(*Iterator)->SetWaterSPos(j, D2D1::Point2F(point.x + 3, point.y));
			if (j == 3)//下
				(*Iterator)->SetWaterSPos(j, D2D1::Point2F(point.x, point.y + 3));
			if (j == 1)//左
				(*Iterator)->SetWaterSPos(j, D2D1::Point2F(point.x - 3, point.y));

			////获取要检测碰撞的下标
			//GetTouchNumber(*Iterator, j);
			//for (int k = 0; k < TNumber.size(); k++)
			for (int k = 0; k < col*row;k++)
			{
				/*if (pGameWater[TNumber[k]]->GetGWProgress() == Nothing || pGameWater[TNumber[k]]->GetGWProgress() == NothingWithSmall)
					continue;*/

				if (pGameWater[k]->GetGWProgress() == Nothing || pGameWater[k]->GetGWProgress() == NothingWithSmall)
					continue;

				//如果接触了
				/*if (IsTouch(&pGameWater[TNumber[k]], *Iterator, j))*/
				if (IsTouch(&pGameWater[k], *Iterator, j))
				{
					//设置小水滴脱离状态
					(*Iterator)->SetSmallOverNumber();

					//接触的小水滴可见性为假
					(*Iterator)->SetWaterSamllVisible(j, false);

					//改变被接触的大水滴的状态
					/*pGameWater[TNumber[k]]->SetClick();
					pGameWater[TNumber[k]]->ChangeWaterProgress();*/
					pGameWater[k]->SetClick();
					pGameWater[k]->ChangeWaterProgress();

					//被接触的大水滴是否爆左
					/*if (pGameWater[TNumber[k]]->GetGWProgress() == NothingWithSmall)*/
					if (pGameWater[k]->GetGWProgress() == NothingWithSmall)
					{
						int i = (*Iterator)->GetCol() + (*Iterator)->GetRow() * 5;

						//如果是，检测接触值是否为真
						/*if (pGameWater[TNumber[k]]->GetTouch())*/
						if (pGameWater[k]->GetTouch() || pGameWater[i]->GetTouch())
						{
							//如果是水滴总量加一
							SetAddWNumber(1);
						}
						else
						{
							//不是就设置为真
							/*pGameWater[TNumber[k]]->SetTouch(true);*/
							pGameWater[k]->SetTouch(true);
							pGameWater[i]->SetTouch(true);
						}

						//添加小水滴到链表
						GameWaterSmall *pGWaterSmall = new GameWaterSmall;
						for (int j = 0; j < 4; j++)
						{
							/*D2D1_POINT_2F p = pGameWater[TNumber[k]]->GetWaterPos();*/
							D2D1_POINT_2F p = pGameWater[k]->GetWaterPos();
							p.x += pGWaterSmall->GetWatersHotPos(j).x;
							p.y += pGWaterSmall->GetWatersHotPos(j).y;
							pGWaterSmall->SetWaterSPos(j, p);
						}
						/*pGWaterSmall->SetCol(pGameWater[TNumber[k]]->GetCol());
						pGWaterSmall->SetRow(pGameWater[TNumber[k]]->GetRow());*/
						pGWaterSmall->SetCol(pGameWater[k]->GetCol());
						pGWaterSmall->SetRow(pGameWater[k]->GetRow());
						pGameWaterSmall.push_back(pGWaterSmall);
					}

					//爆炸音效
					pBoomMusic->PlaySound(pBoomMusic->GetSoundCount());
				}
			}
		}
		//如果4个小水滴都脱离就改变被接触的水滴的状态
		if ((*Iterator)->GetSmallOverNumber() == 4)
		{
			//改变大水滴的状态
			int i = (*Iterator)->GetCol() + (*Iterator)->GetRow() * 5;
			pGameWater[i]->SetClick();
			pGameWater[i]->ChangeWaterProgress();
			pGameWater[i]->SetTouch(false);

			//记录该删除的对象
			Iterator = pGameWaterSmall.erase(Iterator);
		}
		else
		{
			++(Iterator);
		}
	}
}

void GWaterManager::GetTouchNumber(GameWaterSmall *p, int i)
{
	GameWaterSmall *pGameWater = p;
	int Col = pGameWater->GetCol();
	int Row = pGameWater->GetRow();

	TNumber.clear();//清空

	switch (i)
	{
	case 2://上
		for (; Row != 0;Row-=1)
			TNumber.push_back(Col + Row * 5);
		break;
	case 0://右
		for (; Col != col;Col+=1)
			TNumber.push_back(Col + Row * 5);
		break;
	case 3://下
		for (; Row != row;Row+=1)
			TNumber.push_back(Col + Row * 5);
		break;
	case 1://左
		for (; Col != 0;Col-=1)
			TNumber.push_back(Col + Row * 5);
		break;
	default:
		break;
	}
}


BOOL GWaterManager::IsTouch(GameWater **pW, GameWaterSmall *pWS, int i)
{
	//矩形
	//const D2D1_RECT_F *r = pWS->GetWatersBoundingBox(i);
	//RECT rect = {r->left,r->top,r->right,r->bottom};
	//return (*pW)->IsTouch(rect);

	//精灵
	return (*pW)->IsTouch(pWS->GetWatersAnimationSprite(i));
}

int GWaterManager::GetAddWNumber()
{
	return AddWNumber;
}

void GWaterManager::SetAddWNumber(int p)
{
	if (p == 0)//已经添加了，初始化
		AddWNumber = 0;
	else
		AddWNumber += p; 
}

void GWaterManager::InitWprocession(int L,int M1,int M2,int B)
{
	srand(time(NULL));
	for (int i = 0; i < L; i++)
	{
		int k = rand() % (col*row);
		pGameWater[k]->SetGWProgress(little);
		pGameWater[k]->ChangeWaterProgress();
	}
	for (int i = 0; i < M1; i++)
	{
		int k = rand() % (col*row);
		pGameWater[k]->SetGWProgress(middle1);
		pGameWater[k]->ChangeWaterProgress();
	}
	for (int i = 0; i < M2; i++)
	{
		int k = rand() % (col*row);
		pGameWater[k]->SetGWProgress(middle2);
		pGameWater[k]->ChangeWaterProgress();
	}
	for (int i = 0; i < B; i++)
	{
		int k = rand() % (col*row);
		pGameWater[k]->SetGWProgress(big);
		pGameWater[k]->ChangeWaterProgress();
	}
}

BOOL GWaterManager::IsAllNothing()
{
	for (int i = 0; i < row*col; i++)
	{
		if (pGameWater[i]->GetGWProgress() != Nothing)
			return false;
	}
	return true;
}

BOOL GWaterManager::IsHaveSmallWaters()
{
	if (pGameWaterSmall.empty())
		return false;
	else
		return true;
}

void GWaterManager::SetWatersVisible(bool b)
{
	for (int i = 0; i < col*row; i++)
		pGameWater[i]->SetVisible(b);
}