#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Map : public GameEngineActor
{
public:
	Map();
	~Map();

	Map(const Map& _Other) = delete;
	Map(Map&& _Other) noexcept = delete;
	Map& operator=(const Map& _Other) = delete;
	Map& operator=(Map&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
private:
	GameEngineRender* SkyRender = nullptr;
	GameEngineRender* BackGroundRender = nullptr;
	GameEngineRender* StageRender = nullptr;
};

