#pragma once
#include <GameEngineCore/GameEngineActor.h>

class UIManager : public GameEngineActor
{
public:
	UIManager();
	~UIManager();

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

};

