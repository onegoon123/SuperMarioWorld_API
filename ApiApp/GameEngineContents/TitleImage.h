#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "MarioGameCore.h"
class TitleImage : public GameEngineActor
{
public:
	TitleImage();
	~TitleImage();

	TitleImage(const TitleImage& _Other) = delete;
	TitleImage(TitleImage&& _Other) noexcept = delete;
	TitleImage& operator=(const TitleImage& _Other) = delete;
	TitleImage& operator=(TitleImage&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
private:
	// (임시) 타이틀 화면에서의 시간을 저장
	float AccTime = 0;
};

