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

	/*�����Ч*/
	pClickMusic = new XAudio2SoundPlayer();
	pClickMusic->LoadSound(TEXT("resource\\���.wav"));
	/*��ը��Ч*/
	pBoomMusic = new XAudio2SoundPlayer();
	pBoomMusic->LoadSound(TEXT("resource\\��.wav"));
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
			//������ڱ�ը״̬������ͨ������ı�״̬
			if (pGameWater[i]->GetGWProgress() == NothingWithSmall)
				continue;

			//�ı��ˮ��״̬
			pGameWater[i]->SetClick();
			pGameWater[i]->ChangeWaterProgress();

			//����Ǳ�ը����Сˮ��������Ӷ���
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

			//ˮ����������
			SetAddWNumber(-1);
			//�����Ч
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
			//����ɼ���Ϊ�٣��������ѭ��
			if (!(*Iterator)->GetWaterSamllVisible(j))
				continue;

			//����һֱ�ı�λ��
			//�Ƿ�������Ļ��
			D2D1_POINT_2F point = (*Iterator)->GetWaterSPos(j);
			//POINT p = { (*Iterator)->GetWaterSPos(j).x, (*Iterator)->GetWaterSPos(j).y };
			if (point.x > rClient.right || point.x<rClient.left || point.y>rClient.bottom || point.y < rClient.top)
			{
				//���������Ļ�⣬���ٸı䣬����Сˮ������״̬
				(*Iterator)->SetSmallOverNumber();
				(*Iterator)->SetWaterSamllVisible(j, false);
				continue;
			}

			//û��������λ�ü����ı�
			//D2D1_POINT_2F point = (*Iterator)->GetWaterSPos(j);
			if (j == 2)//��
				(*Iterator)->SetWaterSPos(j, D2D1::Point2F(point.x, point.y - 3));
			if (j == 0)//��
				(*Iterator)->SetWaterSPos(j, D2D1::Point2F(point.x + 3, point.y));
			if (j == 3)//��
				(*Iterator)->SetWaterSPos(j, D2D1::Point2F(point.x, point.y + 3));
			if (j == 1)//��
				(*Iterator)->SetWaterSPos(j, D2D1::Point2F(point.x - 3, point.y));

			////��ȡҪ�����ײ���±�
			//GetTouchNumber(*Iterator, j);
			//for (int k = 0; k < TNumber.size(); k++)
			for (int k = 0; k < col*row;k++)
			{
				/*if (pGameWater[TNumber[k]]->GetGWProgress() == Nothing || pGameWater[TNumber[k]]->GetGWProgress() == NothingWithSmall)
					continue;*/

				if (pGameWater[k]->GetGWProgress() == Nothing || pGameWater[k]->GetGWProgress() == NothingWithSmall)
					continue;

				//����Ӵ���
				/*if (IsTouch(&pGameWater[TNumber[k]], *Iterator, j))*/
				if (IsTouch(&pGameWater[k], *Iterator, j))
				{
					//����Сˮ������״̬
					(*Iterator)->SetSmallOverNumber();

					//�Ӵ���Сˮ�οɼ���Ϊ��
					(*Iterator)->SetWaterSamllVisible(j, false);

					//�ı䱻�Ӵ��Ĵ�ˮ�ε�״̬
					/*pGameWater[TNumber[k]]->SetClick();
					pGameWater[TNumber[k]]->ChangeWaterProgress();*/
					pGameWater[k]->SetClick();
					pGameWater[k]->ChangeWaterProgress();

					//���Ӵ��Ĵ�ˮ���Ƿ���
					/*if (pGameWater[TNumber[k]]->GetGWProgress() == NothingWithSmall)*/
					if (pGameWater[k]->GetGWProgress() == NothingWithSmall)
					{
						int i = (*Iterator)->GetCol() + (*Iterator)->GetRow() * 5;

						//����ǣ����Ӵ�ֵ�Ƿ�Ϊ��
						/*if (pGameWater[TNumber[k]]->GetTouch())*/
						if (pGameWater[k]->GetTouch() || pGameWater[i]->GetTouch())
						{
							//�����ˮ��������һ
							SetAddWNumber(1);
						}
						else
						{
							//���Ǿ�����Ϊ��
							/*pGameWater[TNumber[k]]->SetTouch(true);*/
							pGameWater[k]->SetTouch(true);
							pGameWater[i]->SetTouch(true);
						}

						//���Сˮ�ε�����
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

					//��ը��Ч
					pBoomMusic->PlaySound(pBoomMusic->GetSoundCount());
				}
			}
		}
		//���4��Сˮ�ζ�����͸ı䱻�Ӵ���ˮ�ε�״̬
		if ((*Iterator)->GetSmallOverNumber() == 4)
		{
			//�ı��ˮ�ε�״̬
			int i = (*Iterator)->GetCol() + (*Iterator)->GetRow() * 5;
			pGameWater[i]->SetClick();
			pGameWater[i]->ChangeWaterProgress();
			pGameWater[i]->SetTouch(false);

			//��¼��ɾ���Ķ���
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

	TNumber.clear();//���

	switch (i)
	{
	case 2://��
		for (; Row != 0;Row-=1)
			TNumber.push_back(Col + Row * 5);
		break;
	case 0://��
		for (; Col != col;Col+=1)
			TNumber.push_back(Col + Row * 5);
		break;
	case 3://��
		for (; Row != row;Row+=1)
			TNumber.push_back(Col + Row * 5);
		break;
	case 1://��
		for (; Col != 0;Col-=1)
			TNumber.push_back(Col + Row * 5);
		break;
	default:
		break;
	}
}


BOOL GWaterManager::IsTouch(GameWater **pW, GameWaterSmall *pWS, int i)
{
	//����
	//const D2D1_RECT_F *r = pWS->GetWatersBoundingBox(i);
	//RECT rect = {r->left,r->top,r->right,r->bottom};
	//return (*pW)->IsTouch(rect);

	//����
	return (*pW)->IsTouch(pWS->GetWatersAnimationSprite(i));
}

int GWaterManager::GetAddWNumber()
{
	return AddWNumber;
}

void GWaterManager::SetAddWNumber(int p)
{
	if (p == 0)//�Ѿ�����ˣ���ʼ��
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