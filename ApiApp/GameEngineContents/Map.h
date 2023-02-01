#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <string.h>

class Map : public GameEngineActor
{
public:
	Map();
	~Map();

	Map(const Map& _Other) = delete;
	Map(Map&& _Other) noexcept = delete;
	Map& operator=(const Map& _Other) = delete;
	Map& operator=(Map&& _Other) noexcept = delete;

	void NewMap(std::string_view _SkyName, std::string_view _BackGroundName, std::string_view _StageName);

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
};

