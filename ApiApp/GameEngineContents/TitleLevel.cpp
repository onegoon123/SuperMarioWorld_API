#include "TitleLevel.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineRender.h>
#include "TitleImage.h"

TitleLevel::TitleLevel() {

}

TitleLevel::~TitleLevel() {

}

void TitleLevel::Loading()
{
	// 시작시 타이틀화면에 표시될 이미지를 먼저 로딩한다

	// 이미지 파일 경로검색
	// 1. ContentsResources 폴더가 있는 곳을 찾는다
	// 2. ContentsResources 폴더로 이동
	// 3. Image 폴더로 이동
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");

	// 타이틀 화면에 표시될 이미지들을 로딩한다
	// 추가로 마리오는 미리 Cut 기능을 이용해 자른다 (이미지 분할 데이터 생성)
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("MARIO.BMP"))->Cut(19, 37);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("SKY.BMP"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("STAGE1.BMP"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("BACKGROUND01.BMP"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("TITLE.BMP"));

	// 타이틀 이미지들을 표시할 엑터 생성
	CreateActor<TitleImage>();
}

void TitleLevel::Update()
{
	
}
