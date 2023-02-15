#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/NumberRenderObject.h>
class UIManager : public GameEngineActor
{
public:
	UIManager();
	~UIManager();

	void SetLife(int Value);
	void SetTime(int Value);
	void SetCoin(int Value);
	void SetScore(int Value);

	UIManager(const UIManager& _Other) = delete;
	UIManager(UIManager&& _Other) noexcept = delete;
	UIManager& operator=(const UIManager& _Other) = delete;
	UIManager& operator=(UIManager&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:

	GameEngineRender* UIImage = nullptr;
	NumberRenderObject LifeNumber;		// 최대 99
	NumberRenderObject StarNumber;		// 최대 99
	NumberRenderObject TimeNumber;		// 최대 999
	NumberRenderObject CoinNumber;		// 최대 99
	NumberRenderObject ScoreNumber;		// 최대 999만
	const float4 NumberScale = { 32 ,28 };
	const float4 NumberBigScale = { 32 ,56 };
	int MarioLife = 0;
};

