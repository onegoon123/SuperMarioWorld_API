#include "Map.h"
#include <GameEngineBase/GameEngineMath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRender.h>
#include "ContentsEnums.h"
#include "Mario.h"
Map* Map::MainMap = nullptr;

Map::Map() {

}

Map::~Map() {

}

void Map::SetImage(const std::string_view& _BackGroundName, const std::string_view& _StageName, const std::string_view& _StageColName)
{
	BackGroundName = _BackGroundName;
	StageName = _StageName;
	StageColName = _StageColName;

	if ("" != StageName)
	{
		StageRender = CreateRender(StageName, RenderOrder::Map);
		StageSize = StageRender->GetImage()->GetImageScale();
		StageRender->SetScale(StageSize);
		StageRender->SetPosition(StageSize.half());
		StageRender->Off();
	}

	if ("" != BackGroundName)
	{
		BackGroundRender = CreateRender(BackGroundName, RenderOrder::BackGround);
		if (true == IsBackAnim)
		{
			BackGroundSize = BackGroundRender->GetImage()->GetImageScale();
			BackGroundSize.x /= 4;
		}
		else
		{
			BackGroundSize = BackGroundRender->GetImage()->GetImageScale();
		}
		BackGroundRender->SetScale(BackGroundSize);
		BackGroundRender->SetPosition(BackGroundSize.half());
		BackGroundRender->Off();

		int BackGroundNum = StageSize.ix() / BackGroundSize.ix();
		for (int i = 1; i <= BackGroundNum; i++)
		{
			GameEngineRender* Render = CreateRender(BackGroundName, RenderOrder::BackGround);
			if (true == IsBackAnim)
			{
				Render->CreateAnimation({ .AnimationName = "BackGroundAnim", .ImageName = BackGroundName, .Start = 0, .End = 3 });
				Render->ChangeAnimation("BackGroundAnim");
			}
			Render->SetScale(BackGroundSize);
			Render->SetPosition(BackGroundSize.half());
			Render->SetMove({ BackGroundSize.x * i, 0 });
		}
	}


}

void Map::SetStartPos(const std::vector<float4>& _StartPos)
{
}

void Map::MoveMap(int _StartPosIndex)
{
	if (StartPos.size() < _StartPosIndex)
	{
		MsgAssert("���� ��ġ Vector�� ������ ������ϴ�")
	}
	Mario::MainPlayer->SetPos(StartPos[_StartPosIndex]);

	if (nullptr != MainMap)
	{
		if (this == MainMap)
		{
			MsgAssert("���� ������� ���� �ٽ� ����Ϸ� �߽��ϴ�");
		}
		//MainMap->ObjectOff();
	}
	MainMap = this;
	if (nullptr != BackGroundRender)
	{
		BackGroundRender->On();
	}
	if (nullptr != StageRender)
	{
		StageRender->On();
	}
	//ObjectOn();
}

void Map::Update(float _DeltaTime)
{
}