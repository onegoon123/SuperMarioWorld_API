#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineCore/GameEngineActor.h>
#include <string.h>
#include <vector>

const int Black = RGB(0, 0, 0);			// �ٴ�, �� ǥ�� ����
const int White = RGB(255, 255, 255);	// �� ���� ǥ�� ����
const int Green = RGB(0, 255, 0);		// �Ʒ����� ����Ǵ� �ٴ� ǥ�� ����
const int Red = RGB(255, 0, 0);			// ��Ż�� ǥ�� ����

class Map : public GameEngineActor
{
public:


	Map();
	~Map();

	static Map* MainMap;

	Map(const Map& _Other) = delete;
	Map(Map&& _Other) noexcept = delete;
	Map& operator=(const Map& _Other) = delete;
	Map& operator=(Map&& _Other) noexcept = delete;

	void SetImage(const std::string_view& _BackGroundName, const std::string_view& _StageName, const std::string_view& _StageColName);
	void SetStartPos(const std::vector <float4>& _StartPos);
	void NewActor(const GameEngineActor* _Actor);
	void NewActor(const std::vector<GameEngineActor*> _Actors);
	void MoveMap(int _StartPosIndex);

	inline GameEngineRender* GetBackGroundRender()
	{
		return BackGroundRender;
	}

	inline GameEngineRender* GetStageRender()
	{
		return StageRender;
	}

	inline std::string_view GetStageColName()
	{
		return StageColName;
	}
	inline float4 GetBackGroundSize()
	{
		return BackGroundSize;
	}
	inline float4 GetStageSize()
	{
		return StageSize;
	}
	inline void BackGroundAnimOn()
	{
		IsBackAnim = true;
	}
	inline void AddStartPos(const float4& _Pos)
	{
		StartPos.push_back(_Pos);
	}

protected:
	void Update(float _DeltaTime);
private:
	GameEngineRender* BackGroundRender = nullptr;
	GameEngineRender* StageRender = nullptr;
	float4 BackGroundSize = float4::Zero;
	float4 StageSize = float4::Zero;
	std::string_view BackGroundName = "";
	std::string_view StageName = "";
	std::string_view StageColName = "";

	bool IsBackAnim = false;

	std::vector <float4> StartPos = std::vector <float4>();
	std::vector<GameEngineActor*> Actors = std::vector<GameEngineActor*>();

	void ObjectOn();
	void ObjectOff();
};

