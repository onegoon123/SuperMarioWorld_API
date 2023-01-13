#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// 게임 시작시 나오는 화면
// LEVEL1 맵과 마리오가 화면에 렌더링
// 버튼을 입력하면 월드맵 레벨로 이동
class TitleLevel : public GameEngineLevel
{
public:
	TitleLevel();
	~TitleLevel();

	TitleLevel(const TitleLevel& _Other) = delete;
	TitleLevel(TitleLevel&& _Other) noexcept = delete;
	TitleLevel& operator=(const TitleLevel& _Other) = delete;
	TitleLevel& operator=(TitleLevel&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update() override;

private:

};

