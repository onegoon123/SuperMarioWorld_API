#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineRender.h>


enum class FadeState {
	FadeIn,
	FadeOut,
	STOP
};

class LevelLoader : public GameEngineActor
{
public:
	LevelLoader();
	~LevelLoader();

	

	static void ChangeLevel(const std::string_view& _Name);

	LevelLoader(const LevelLoader& _Other) = delete;
	LevelLoader(LevelLoader&& _Other) noexcept = delete;
	LevelLoader& operator=(const LevelLoader& _Other) = delete;
	LevelLoader& operator=(LevelLoader&& _Other) noexcept = delete;

protected:
	void Start() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void Update(float _DeltaTime);
private:

	static LevelLoader* MainLoader;
	std::string_view LevelName = "";
	GameEngineRender* FadeRender = nullptr;
	FadeState State = FadeState::STOP;
	bool IsFadeIn;
	bool IsFadeOut;
	float Speed = 255.0f * 1.5f;
	float Timer = 0;

	void FadeInUpdate(float _DeltaTime);
	void FadeOutUpdate(float _DeltaTime);
};

