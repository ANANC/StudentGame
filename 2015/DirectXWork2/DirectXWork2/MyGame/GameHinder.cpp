#include"GameHinder.h"
#include"GamePlay.h"
#include"People.h"
#include"GameSelect.h"

CGameHinder::~CGameHinder()
{
}

CGameHinder::CGameHinder()
{
	pCGameScene = GameScene::GetInstance();

	
	pCGameScene->GetGFood(GFood);
	pCGameScene->GetHinder(Hinder);
	pCGameScene->GetPeople(&People);

	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < HinderNumber; j++)
		{
			Hinder[i][j]->SetVisible(false);
			HinderSpeed[i][j] = 0;//速度
		}
		HinderNum[i] = 0;//数量
		IsBSee[i] = 0;//状态
	}

	PlayWay = 1;//操作是否颠倒
	IsStatic = false;//人物是否固定
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < HinderNumber; j++)
			IsLeft[i][j] = 0;//是否左边
	}
	rinSpeed = 1;//雨，速度改变

	rectClient = { 0,0,866,606 };
	//GameNumber = pCGameSelect->GetGameMunber();

	oldPos_2 = { 866 / 2 - Hinder[2][0]->GetWidth() / 2 - 10, 8 };
	oldPos_3 = { 866 / 2 - Hinder[3][0]->GetWidth() / 2-2 , 65 };
}

void CGameHinder::HinderErase()
{
	GameNumber = pCGameSelect->GetGameMunber();
	for (int i = 0; i < GameNumber; i++)
	{
		for (int j = 0; j < HinderNum[i]; j++)
		{
			Hinder[i][j]->SetVisible(false);
		}
		HinderNum[i] = 0;//数量
	}
	PlayWay = 1;
	rinSpeed = 1;
}

void CGameHinder::HinderCreate()
{
	pCGamePeople = CGamePeople::GetInstance();
	pCGamePlay = CGamePlay::GetInstance();
	pCGameSelect = CGameSelect::GetInstance();

	GameNumber = pCGameSelect->GetGameMunber();
	srand((unsigned)time(NULL));
	/*鱼*/
	if (GameNumber == 1 || GameNumber > 1)
	{
		int Num;
		if (GameNumber<5)
			Num = 10;
		else
			Num = 2 + GameNumber;
		for (int i = 0; i <= Num; i++)
		{
			int y = int(rand() % rectClient.bottom) + 1;
			if (i % 2 != 0)
				Hinder[0][HinderNum[0]++]->SetPos(D2D1::Point2F(rectClient.right, y));

			else
			{
				Hinder[0][HinderNum[0] - 1]->SetPos(D2D1::Point2F(rectClient.left, y));
				Hinder[0][HinderNum[0] - 1]->SetTexPos(0, Hinder[0][HinderNum[0] - 1]->GetHeight());
				IsLeft[0][HinderNum[0] - 1] = 1;
			}
			HinderSpeed[0][HinderNum[0] - 1] = rand() % 13 + 1;
			Hinder[0][HinderNum[0] - 1]->SetVisible(true);
		}

	}

	/*八爪鱼*/
	if (GameNumber == 2 || GameNumber > 2)
	{
		int Num = GameNumber;
		if (GameNumber < 4)
			Num = GameNumber;
		else
			Num = 3;
		int k = rand() % 2 + 1;
		for (int i = 0; i <= Num; i++)
		{
			int x = int(rand() % rectClient.right) + 1;
			Hinder[1][HinderNum[1]++]->SetPos(D2D1::Point2F(x, rectClient.bottom));
			Hinder[1][HinderNum[1] - 1]->Play();
			//Hinder[1][HinderNum[1] - 1]->SetTransparent(true);
			HinderSpeed[1][HinderNum[1] - 1] = k++;
			Hinder[1][HinderNum[1] - 1]->SetVisible(true);
		}
	}

	/*水滴*/
	if (GameNumber == 5 || GameNumber > 5)
	{
		int Num = GameNumber + 4;
		for (int i = 0; i <= Num; i++)
		{
			int x = int(rand() % rectClient.right) + 1;
			Hinder[4][HinderNum[4]++]->SetPos(D2D1::Point2F(x, rectClient.top));
			//Hinder[4][HinderNum[4] - 1]->SetTransparent(true);
			HinderSpeed[4][HinderNum[4] - 1] = rand() % 24 + 1;
			Hinder[4][HinderNum[4] - 1]->SetVisible(true);
		}
	}

	/*闪电*/
	if (GameNumber == 6 || GameNumber > 6)
	{
		int Num = GameNumber;
		for (int i = 0; i <= Num; i++)
		{
			int x = int(rand() % rectClient.right) + 1;
			Hinder[5][HinderNum[5]++]->SetPos(D2D1::Point2F(x, rectClient.top));
			//Hinder[5][HinderNum[5] - 1]->SetTransparent(true);
			HinderSpeed[5][HinderNum[5] - 1] = rand() % 8 + 1;
			Hinder[5][HinderNum[5] - 1]->SetVisible(true);
		}
	}

	/*云*/
	if (GameNumber == 7 || GameNumber > 7)
	{
		int Num = GameNumber;
		for (int i = 0; i <= Num; i++)
		{
			int y = int(rand() % rectClient.bottom) + 1;
			if (i % 2 == 0)
				Hinder[6][HinderNum[6]++]->SetPos(D2D1::Point2F(rectClient.right, y));
			else
			{
				Hinder[6][HinderNum[6]++]->SetPos(D2D1::Point2F(rectClient.left, y));
				IsLeft[1][HinderNum[6] - 1] = 1;
			}
			//Hinder[6][HinderNum[6] - 1]->SetTransparent(true);
			HinderSpeed[6][HinderNum[6] - 1] = rand() % 9 + 1;
			Hinder[6][HinderNum[6] - 1]->SetVisible(true);
		}
	}

}


void CGameHinder::HinderShow_static()
{

	GameNumber = pCGameSelect->GetGameMunber();
	srand((unsigned)time(NULL));

	/*树*/
	if (GameNumber == 3 || GameNumber > 3)
	{
		int Num = GameNumber - 1;
		if (Num > 5)
			Num = 3;
		
		float Ro = rand() % 30 + 50;
		for (int i = 0; i < Num; i++)
		{
			/*位置*/
			

			World = D2D1::Matrix3x2F::Identity();
			World = World * D2D1::Matrix3x2F::Translation(oldPos_2.x, oldPos_2.y);
			World = World * D2D1::Matrix3x2F::Rotation(Ro, D2D1::Point2F(425.5f, 284));
			D2D1_POINT_2F wp = { 0, 0 };
			wp = World.TransformPoint(wp);
			Hinder[2][i]->SetPos(wp);
			Hinder[2][i]->SetRotationAngle(Ro);

			Ro += rand() % 100 + 40;
			///*背景*/
			//Hinder[2][i]->SetTransparent(true);

			/*可见*/
			Hinder[2][i]->SetVisible(true);

			HinderNum[2]++;//障碍的数量
		}
	}

	/*蒲公英*/
	if (GameNumber == 4 || GameNumber > 4)
	{
		int Num = GameNumber - 2;
		if (Num > 5)
			Num = 4;
		
		float Ro = rand() % 50 + 70;

		for (int i = 0; i < Num; i++)
		{
			/*位置*/
			World = D2D1::Matrix3x2F::Identity();
			World = World * D2D1::Matrix3x2F::Translation(oldPos_3.x, oldPos_3.y);
			World = World * D2D1::Matrix3x2F::Rotation(Ro, D2D1::Point2F(425.5f, 284));
			D2D1_POINT_2F wp = { 0, 0 };
			wp = World.TransformPoint(wp);
			Hinder[3][i]->SetPos(wp);
			Hinder[3][i]->SetRotationAngle(Ro);
			
			Ro += rand() % 80 + 60;

			/*背景*/
			//Hinder[3][i]->SetTransparent(true);

			/*可见*/
			Hinder[3][i]->SetVisible(true);

			HinderNum[3]++;//障碍的数量
		}
	}
}

void CGameHinder::HinderMove()
{
	if (pCGameScene->GetGameP() != PGamePlaying)
		return;

	GameNumber = pCGameSelect->GetGameMunber();

	for (int i = 0; i <= GameNumber; i++)
	{
		if (i == 2 || i == 3)//固定位置
			continue;

		if (i == 0 || i == 6)//横向移动
		{
			for (int j = 0; j < HinderNum[i]; j++)
			{
				/*移动*/
				int k = 0;
				if (i == 6)
					k = 1;
				if (IsLeft[k][j])
					Hinder[i][j]->SetPos(D2D1::Point2F(Hinder[i][j]->GetPos().x + HinderSpeed[i][j], Hinder[i][j]->GetPos().y));
				else
					Hinder[i][j]->SetPos(D2D1::Point2F(Hinder[i][j]->GetPos().x - HinderSpeed[i][j], Hinder[i][j]->GetPos().y));

				/*超出屏幕*/
				if (Hinder[i][j]->GetPos().x>rectClient.right)//超过右边
					Hinder[i][j]->SetPos(D2D1::Point2F(0, Hinder[i][j]->GetPos().y));
				if (Hinder[i][j]->GetPos().x<rectClient.left)//超过左边
					Hinder[i][j]->SetPos(D2D1::Point2F(rectClient.right, Hinder[i][j]->GetPos().y));
			}
		}

		if (i == 4 || i == 5)// 竖向向下移动
		{
			for (int j = 0; j < HinderNum[i]; j++)
			{
				/*移动*/
				Hinder[i][j]->SetPos(D2D1::Point2F(Hinder[i][j]->GetPos().x, Hinder[i][j]->GetPos().y + HinderSpeed[i][j]));

				/*超出屏幕*/
				if (Hinder[i][j]->GetPos().y>rectClient.bottom)
					Hinder[i][j]->SetPos(D2D1::Point2F(Hinder[i][j]->GetPos().x, 0));
			}
		}

		if (i == 1)//八爪鱼
		{
			static int height = Hinder[1][0]->GetHeight();
			static float RO = 0.0;
			for (int j = 0; j < HinderNum[i]; j++)
			{
				RO += 0.01;
				int h;
				if (j % 2 == 0)
					h = (rand() %4+8) * sin(RO);
				else
					h = (rand() % 10 + 10) * cos(RO);
				Hinder[1][j]->SetPos(D2D1::Point2F(Hinder[i][j]->GetPos().x + h, Hinder[i][j]->GetPos().y - HinderSpeed[i][j]));

				/*超出屏幕*/
				if (Hinder[1][j]->GetPos().y + height<rectClient.top)
					Hinder[1][j]->SetPos(D2D1::Point2F(Hinder[i][j]->GetPos().x, rectClient.bottom));
			}
		}

	}
}

void CGameHinder::HinderTouch(float fDelataTime)
{
	GameNumber = pCGameSelect->GetGameMunber();
	switch (GameNumber)
	{
	case 1:
		TouchDie(0);
		break;

	case 2:
		TouchDie(0);
		TouchDie(1);
		break;

	case 3:
		TouchDie(0);
		TouchDie(1);
		Reverse(fDelataTime);
		break;

	case 4:
		TouchDie(0);
		TouchDie(1);
		Reverse(fDelataTime);
		ChangeSide();
		break;

	case 5:
		TouchDie(0);
		TouchDie(1);
		Reverse(fDelataTime);
		ChangeSide();
		rin();
		break;

	case 6:
		TouchDie(0);
		TouchDie(1);
		Reverse(fDelataTime);
		ChangeSide();
		rin();
		light(fDelataTime);
		break;

	case 7:
		TouchDie(0);
		TouchDie(1);
		Reverse(fDelataTime);
		ChangeSide();
		rin();
		light(fDelataTime);
		TouchNoSee();
		break;

	default:
		break;
	}

}

void CGameHinder::TouchDie(int p)
{
	for (int i = 0; i < HinderNum[p]; i++)
	{
		if (Hinder[p][i]->CollideWith(*People))
			pCGamePlay->GameOver();
	}
}

void CGameHinder::Reverse(float fDelataTime)
{
	static int k = 0, n = 0;
	static bool IsTouch = 0;
	static float ft = 0;

	for (int i = 0; i < HinderNum[2]; i++)
	{
		if (Hinder[2][i]->CollideWith(*People))
		{
			if (++k % 2 == 0)
			{
				PlayWay = 1;
				pCGamePeople->SetRotationAngle(0.5);
			}

			else
			{
				PlayWay = -1;
				pCGamePeople->SetRotationAngle(-0.5);
			}
			IsTouch = 1;
			n = i;
		}
	}

}

void CGameHinder::ChangeSide()
{
	for (int i = 0; i < HinderNum[3]; i++)
	{
		if (Hinder[3][i]->CollideWith(*People))
		{
			srand(time(NULL));
			float R = rand() % 20 + 1;
			pCGamePeople->SetRotationAngle(R);
		}
	}
}

void CGameHinder::rin()
{
	srand((unsigned)time(NULL));
	rinSpeed = int(rand() % 5) + 1;
}

void CGameHinder::light(float fDelataTime)
{
	static float fT = 0;
	if (IsStatic)
	{
		fT += fDelataTime;
		if (fT > 1)
		{
			fT = 0;
			IsStatic = false;
		}
		return;
	}

	for (int i = 0; i < HinderNum[5]; i++)
	{
		if (Hinder[5][i]->CollideWith(*People))
		{
			IsStatic = true;
			break;
		}
	}
}

void CGameHinder::TouchNoSee()
{
	bool IsGetFood[3];//是否得到食物
	pCGamePlay->GetIsGetFood(IsGetFood);

	static int f[3] = { 0 };
	for (int i = 0; i < HinderNum[6]; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (IsGetFood[j])
				continue;
			if (Hinder[6][i]->CSprite::CollideWith(*GFood[j]))
			{
				GFood[j]->SetVisible(false);
				f[j] = i;
			}
		}
	}

	for (int i = 0; i < 3; i++)
	{
		if (f[i])
		{
			if (Hinder[6][f[i]]->CSprite::CollideWith(*GFood[i]) != true)
			{
				GFood[i]->SetVisible(true);
				f[i] = 0;
			}
		}
	}
}

