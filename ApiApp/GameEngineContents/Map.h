#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineCore/GameEngineActor.h>
#include <string.h>
#include <vector>

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

	void SetImage(const std::string_view& _SkyName, const std::string_view& _BackGroundName, const std::string_view& _StageName);
	void SetStartPos(const std::vector <float4>& _StartPos);
	void NewActor(const GameEngineActor* _Actor);
	void NewActor(const std::vector<GameEngineActor*> _Actors);
	void MoveMap(int _StartPosIndex);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
private:
	GameEngineRender* SkyRender = nullptr;
	GameEngineRender* BackGroundRender = nullptr;
	GameEngineRender* StageRender = nullptr;

	std::string_view SkyName = "";
	std::string_view BackGroundName = "";
	std::string_view StageName = "";

	std::vector <float4> StartPos = std::vector <float4>();
	std::vector<GameEngineActor*> Actors = std::vector<GameEngineActor*>();

	void ObjectOn();
	void ObjectOff();
};

