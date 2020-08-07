#include"GameSelect.h"

CGameSelect::~CGameSelect()
{
}

CGameSelect::CGameSelect()
{
	pCGameScene = GameScene::GetInstance();

	pCGameScene->GetGamePass(GamePass);
	pCGameScene->GetGameScreen(&GameScreen);
	pCGameScene->GetGFood(GFood);
	pCGameScene->GetAgain(&Again);
	pCGameScene->GetBack(&Back);
	pCGameScene->GetPeople(&People);

	D2D1_POINT_2F point = { 40, 80 };
	int w = GamePass[0]->GetWidth();
	int h = GamePass[0]->GetHeight();
	for (int i = 0; i < 8; i++)
	{
		if (i==0)
			point.x = 40;
		else if (i == 4)
		{
			point.x = 40;
			point.y += 30 + h;
		}
		else
			point.x += w + 40;
		GamePass[i]->SetPos(point);
		GamePass[i]->SetVisible(false);
	}

	for (int i = 1; i < 8; i++)
	{
		IsPassSelect[i] = true;//ѡ��״̬
		IsGamePass[i] = false;//ͨ��״̬
		GP[i] = false;//������
	}
	GP[0] = false;//������
	IsPassSelect[0] = true;//��һ�ؿ�ѡ	
	IsGamePass[0] = false;//ͨ��״̬-��һ��
	for (int i = 0; i < 8; i++)
		GameTime[i] = 0;//ͨ��ʱ��
	GameMunber = 0;//��ǰ�ؿ�
	Gp = -1;//�����ùؿ�
}

void CGameSelect::ChangePass()
{
	if (GameTime[0])
	{
		if (GameTime[0] < 0.1 && GameTime[0] != 0)
			GamePass[0]->SetTexturePos(0, 183 * 3);

		if (GameTime[0]<0.6 && GameTime[0] >= 0.1)
			GamePass[0]->SetTexturePos(0, 182.222 * 2);

		if (GameTime[0]>0.6)
			GamePass[0]->SetTexturePos(0, 182.222);
	}
	for (int i = 1; i < 8; i++)
	{
		if (!IsGamePass[i] && IsGamePass[i - 1])
		{
			GamePass[i]->SetTexturePos(0, 182.5);
			IsPassSelect[i] = true;
		}

		if (GameTime[i]<0.2 && GameTime[i] != 0 && IsGamePass[i])
			GamePass[i]->SetTexturePos(0, 182.5 * 4);

		if (GameTime[i]<0.5 && GameTime[i] >= 0.2 && IsGamePass[i])
			GamePass[i]->SetTexturePos(0, 182.5 * 3);

		if (GameTime[i]>0.5 && IsGamePass[i])
			GamePass[i]->SetTexturePos(0, 182.5 * 2);
	}
}

void CGameSelect::SelectGamePass()
{
	pCGamePlay = CGamePlay::GetInstance();
	pCGamePeople = CGamePeople::GetInstance();
	pCGameHinder = CGameHinder::GetInstance();
	pCGameTime = CGameTime::GetInstance();
	for (int i = 0; i < 8; i++)
	{
		if (!IsPassSelect[i])
			continue;

		if (GamePass[i]->IsSelected(pCGameScene->GetCpoint().x, pCGameScene->GetCpoint().y))
		{
			/*ѡ�ز��ɼ�*/
			for (int j = 0; j < 8; j++)
				GamePass[j]->SetVisible(false);

			/*������ߣ��ϰ��ɼ�*/
			GameScreen->SetVisible(true);//��ͼ
			GameScreen->Play();
			Again->SetVisible(true);//����
			Back->SetVisible(true);//����
			for (int j = 0; j < 3; j++)
				GFood[j]->SetVisible(true);//ʳ��
			People->SetVisible(true);//����
			People->Play();

			/*�޸���Ϸ״̬*/
			GameMunber = i;//���õ�ǰ�ؿ�
			pCGameScene->SetGameP(PGamePlaying);//������Ϸ״̬

			/*������ߣ��ϰ�,��ʱ����ʼ��*/
			pCGamePlay->FoodFirst();//����
			pCGamePeople->PeoFirst();//����
			pCGameTime->TimeFirst();//��ʱ��
			pCGameHinder->HinderCreate();//��̬�ϰ�
			pCGameHinder->HinderShow_static();//��̬�ϰ�

			/*���Ե��±���*/
			/*Two_F->SetVisible(true);
			Two_FF[0]->SetVisible(true);
			Two_FF[1]->SetVisible(true);*/

			return;
		}
	}
}


void CGameSelect::SetGamePass(int i)
{
	IsGamePass[i] = true;
}

int CGameSelect::GetGameMunber()
{
	return GameMunber;
}

void CGameSelect::MoveGamePass()
{
	for (int i = 0; i < 8; i++)
	{
		if (GamePass[i]->IsSelected(pCGameScene->GetMpoint().x, pCGameScene->GetMpoint().y))
		{
			/*int x = GamePass[i]->GetWidth();
			int y = GamePass[i]->GetTexturePos().y;
			GamePass[i]->SetTexturePos(x, y);*/
			GP[i] = true;
			Gp = i;
			break;
		}
		else
		{
			if (GP[i] == false)
				continue;

			/*int y = GamePass[i]->GetTexturePos().y;
			GamePass[i]->SetTexturePos(0, y);*/
			GP[i] = false;
			/*Gp = -1;*/
			break;
		}
	}
}

void CGameSelect::MoveChangeGamePass()
{
	if (GP[Gp])
	{
		int x = GamePass[Gp]->GetWidth();
		int y = GamePass[Gp]->GetTexturePos().y;
		GamePass[Gp]->SetTexPos(x, y);
	}
	else
	{
		if (Gp == -1)
			return;
		int y = GamePass[Gp]->GetTexturePos().y;
		GamePass[Gp]->SetTexPos(0, y);
		Gp = -1;
	}
}

void CGameSelect::SetTip(ID2D1HwndRenderTarget *pRenderTarget, IDWriteTextFormat *pTextFormat, ID2D1SolidColorBrush *pTextBrush)//w160 h182
{
	TCHAR szBuffer[15];
	int iLength;
	D2D1_RECT_F textRect;
	switch (Gp)
	{
	case 0:
		if (GP[0])
		{
			iLength = wsprintf(szBuffer, TEXT("��Ծ���߹������ľ���"));
			textRect = { 20, 10 + 80 + 182, 20 + 200, 10 + 80 + 182 +15};
		}
		break;
	case 1:
		if (GP[1])
		{
			iLength = wsprintf(szBuffer, TEXT("��Ⱥ��ӵ����ں��������ζ�"));
			textRect = { 40 + 160 + 20, 10 + 80 + 182, 40 + 160 + 20 + 200, 10 + 80 + 182 + 15 };
		}
		break;
	case 2:
		if (GP[2])
		{
			iLength = wsprintf(szBuffer, TEXT("�����İ�צ�����ǲ����������"));
			textRect = { 40 + 160 * 2 + 60, 10 + 80 + 182, 40 + 160 * 2 + 60 + 200, 10 + 80 + 182 + 15 };
		}
		break;
	case 3:
		if (GP[3])
		{
			iLength = wsprintf(szBuffer, TEXT("������յ�����;����ʧ����"));
			textRect = { 40 + 160 * 3 + 100, 10 + 80 + 182, 40 + 160 * 3 + 100+200, 10 + 80 + 182+15 };
		}
		break;
	case 4:
		if (GP[4])
		{
			iLength = wsprintf(szBuffer, TEXT("ɢ����ص��ѹ�ӢƮ�����"));
			textRect = { 40 - 20, 40 + 80 + 182, 40 - 20+200, 40 + 80 + 182+15 };
		}
			break;
	case 5:
		if (GP[5])
		{
			iLength = wsprintf(szBuffer, TEXT("·�˻�æ�����������"));
			textRect = { 20 + 160 + 45-5, 40 + 80 + 182, 20 + 160 + 45+200-5, 40 + 80 + 182+15 };
		}
			break;
	case 6:
		if (GP[6])
		{
			iLength = wsprintf(szBuffer, TEXT("����ʹ��ͣס�˽Ų�"));
			textRect = { 10 + 160 * 2 + 90, 40 + 80 + 182, 10 + 160 * 2 + 90+200, 40 + 80 + 182+15 };
		}
		break;
	case 7:
		if (GP[7])
		{
			iLength = wsprintf(szBuffer, TEXT("�ƶ���ס���䱦"));
			textRect = { 40 + 160 * 3 + 100, 40 + 80 + 182, 40 + 160 * 3 + 100+200, 40 + 80 + 182+15 };
		}
		break;
	default:
		iLength = wsprintf(szBuffer, TEXT(""));
		break;
	}
	//pTextBrush->SetColor(D2D1::ColorF(0xdadada));
	pRenderTarget->DrawText(szBuffer, iLength, pTextFormat, textRect, pTextBrush);

}