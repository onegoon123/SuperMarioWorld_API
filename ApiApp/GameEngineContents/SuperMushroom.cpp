#include "SuperMushroom.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "Mario.h"
#include "ContentsEnums.h"
#include "Map.h"
#include "Block.h"

SuperMushroom::SuperMushroom() {
	ColMap = GameEngineResources::GetInst().ImageFind(Map::MainMap->GetStageColName());
}

SuperMushroom::~SuperMushroom() {

}

void SuperMushroom::Start()
{
	GameEngineRender* Render = CreateRender(RenderOrder::Item);
	Render->SetImage("SUPERMUSHROOM.BMP");
	Render->SetScaleToImage();
	Render->SetPosition({ 0,-29 });
	Collision = CreateCollision(CollisionOrder::Item);
	Collision->SetScale({ 48, 48 });
	Collision->SetPosition({ 0, -25 });
	Collision->SetDebugRenderType(CT_Rect);

	DirValue = 1;
	MoveDir.x = DirValue * Speed;
}

void SuperMushroom::Update(float _DeltaTime)
{

	// �÷��̾�� �浹�� ��
	CollisionCheckParameter Check = { .TargetGroup = static_cast<int>(CollisionOrder::Player), .TargetColType = CT_Rect, .ThisColType = CT_Rect, };
	if (true == Collision->Collision(Check))
	{
		Mario::MainPlayer->NewItem(ItemType::SuperMushroom);
		Death();
	}

	// ȭ�� ������ �������� üũ
	float4 InCameraPos = GetPos() - GetLevel()->GetCameraPos();
	if (0 > InCameraPos.x + 10)
	{
		// ȭ�� ������ ������ ����
		Death();
	}
	if (GameEngineWindow::GetScreenSize().x < InCameraPos.x - 10)
	{
		// ȭ�� ������ ������ ����
		Death();
	}

	// �̵�
	MoveDir.y += GravityAcceleration * _DeltaTime;
	if (GravityMax < MoveDir.y)
	{
		MoveDir.y = GravityMax;
	}

	if (nullptr == ColMap)
	{
		MsgAssert("�浹�� �� �̹����� �����ϴ�.");
	}

	float4 NextPos = GetPos() + MoveDir * _DeltaTime;
	float4 ForwardPos = NextPos;
	ForwardPos.y = GetPos().y - 4;

	// �� �浹 üũ�� �÷� ����
	DWORD PixelColor = ColMap->GetPixelColor(NextPos, White);
	// �� üũ
	if (Black == ColMap->GetPixelColor(ForwardPos, White))
	{
		DirValue = -DirValue;
		MoveDir.x = Speed * DirValue;
		NextPos = GetPos() + MoveDir * _DeltaTime;
		PixelColor = ColMap->GetPixelColor(NextPos, White);
	}
	// �ٴ� üũ
	if (Black == PixelColor)
	{
		MoveDir.x = Speed * DirValue;
		NextPos.y = std::round(NextPos.y);
		// �ٴڿ��� ���� ���� �ö󰣴�
		while (true)
		{
			NextPos.y -= 1;
			PixelColor = ColMap->GetPixelColor(NextPos, Black);
			if (Black != PixelColor)
			{
				SetPos(NextPos);
				MoveDir.y = 0;
				break;
			}
		}
	}
	// �Ʒ����� ����Ǵ� ��ϵ� üũ ex) ����
	else if (Green == PixelColor)
	{
		MoveDir.x = Speed * DirValue;
		NextPos.y = std::round(NextPos.y);
		// �ٴڿ��� ���� ���� �ö󰣴�
		while (true)
		{
			NextPos.y -= 1;
			PixelColor = ColMap->GetPixelColor(NextPos, Black);
			if (White == PixelColor)
			{
				SetPos(NextPos);
				MoveDir.y = 0;
				break;
			}
		}
	}
	// ��Ż�� üũ
	else if (Red == PixelColor)
	{
		MoveDir.x = Speed * DirValue * 0.6f;
		float4 SlopePos = NextPos;
		SlopePos.x += 5;
		SlopePos.y -= 5;
		PixelColor = ColMap->GetPixelColor(SlopePos, Black);
		NextPos.y = std::round(NextPos.y);
		// �ٴڿ��� ���� ���� �ö󰣴�
		while (true)
		{
			NextPos.y -= 1;
			PixelColor = ColMap->GetPixelColor(NextPos, Black);
			if (White == PixelColor)
			{
				SetPos(NextPos);
				MoveDir.y = 0;
				break;
			}
		}
		NextPos.x += 1;
	}

	// ��� üũ
	std::vector<GameEngineCollision*> Collisions;
	Check = { .TargetGroup = static_cast<int>(CollisionOrder::Block), .TargetColType = CT_Rect, .ThisColType = CT_Rect };
	if (true == Collision->Collision(Check, Collisions))
	{
		std::vector<GameEngineCollision*>::iterator Start = Collisions.begin();
		std::vector<GameEngineCollision*>::iterator End = Collisions.end();
		for (; Start != End; Start++)
		{
			Block* ColActor = (*Start)->GetOwner<Block>();
			if (true == ColActor->GetIsRoll())
			{
				continue;
			}
			// �÷��̾ ��Ϻ��� ���� �ִ� ���
			if (GetPos().y < ColActor->GetPos().y - BlockYSize)
			{
				if (0 > MoveDir.y)
				{
					continue;
				}
				float4 Pos = GetPos();
				Pos.y = ColActor->GetPos().y - BlockOnPos;
				Pos.y = std::round(Pos.y);
				SetPos(Pos);
				MoveDir.y = 0.0f;
				continue;
			}
			else if (GetPos().y > ColActor->GetPos().y + BlockYSize)
			{
				continue;
			}
			// �� �� ���
			else
			{
				DirValue = -DirValue;
				MoveDir.x = Speed * DirValue;
			}
		}
	}
	SetMove(MoveDir * _DeltaTime);

}

void SuperMushroom::Render(float _DeltaTime)
{
	//Collision->DebugRender();
}
