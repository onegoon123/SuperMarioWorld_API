#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineActor.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>

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

	class TitleImage : public GameEngineActor
	{
		void Render() override {
			GameEngineImage* Image = GameEngineResources::GetInst().ImageFind("TITLE.BMP");
			GameEngineWindow::GetDoubleBufferImage()->TransCopy(Image, GameEngineWindow::GetScreenSize().half(), { 1024, 896 }, float4::Zero, Image->GetImageScale());
		}
	};
};

