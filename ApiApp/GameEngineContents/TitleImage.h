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
	// (�ӽ�) Ÿ��Ʋ ȭ�鿡���� �ð��� ����
	float AccTime = 0;
};

