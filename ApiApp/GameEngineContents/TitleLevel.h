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
			{
				GameEngineImage* Image = GameEngineResources::GetInst().ImageFind("SKY.BMP");
				GameEngineWindow::GetDoubleBufferImage()->TransCopy(Image, GameEngineWindow::GetScreenSize().half(), { 1024, 896}, float4::Zero, Image->GetImageScale());
			}
			{
				GameEngineImage* Image = GameEngineResources::GetInst().ImageFind("BACKGROUND01.BMP");
				GameEngineWindow::GetDoubleBufferImage()->TransCopy(Image, { 0,-100 }, { 2048, 1728 }, float4::Zero, Image->GetImageScale());
			}
			{
				GameEngineImage* Image = GameEngineResources::GetInst().ImageFind("STAGE1.BMP");
				GameEngineWindow::GetDoubleBufferImage()->TransCopy(Image, {10500,40}, {21868, 1728}, float4::Zero, Image->GetImageScale());
			}
			{
				GameEngineImage* Image = GameEngineResources::GetInst().ImageFind("MARIO.BMP");
				GameEngineWindow::GetDoubleBufferImage()->TransCopy(Image, 0, {200, 654}, {192, 192});
			}
			{
				GameEngineImage* Image = GameEngineResources::GetInst().ImageFind("TITLE.BMP");
				GameEngineWindow::GetDoubleBufferImage()->TransCopy(Image, GameEngineWindow::GetScreenSize().half(), { 1024, 896 }, float4::Zero, Image->GetImageScale());
			}
		}
	};
};

