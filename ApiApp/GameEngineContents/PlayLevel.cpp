#include "PlayLevel.h"
#include "Mario.h"
#include <GameEngineBase/GameEngineDirectory.h>

PlayLevel::PlayLevel()
{
}

PlayLevel::~PlayLevel()
{
}

void PlayLevel::Loading()
{
	// 이런 경로를 절대 경로.
	// "D:\Project\AR45\WINAPI\APIApp\ContentsResources\Iamge\Heros.bmp";

	// std::string Text = "D:\Project\AR45\WINAPI\APIApp\ContentsResources\Iamge\Heros.bmp";

	GameEngineDirectory Dir;
	//Dir.MoveParent();
	//Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");

	Dir.GetPlusFileName("Mario.bmp");



	//if (true == Path.IsExistsToPlusString("\\Heros.bmp"))
	//{
	//	int a = 0;
	//}

	//bool Result = false;
	//Result = Path.IsExistsToPlusString("\\ContentsResources");
	//Path.MoveParent();
	//Result = Path.IsExistsToPlusString("\\ContentsResources");
	//Path.MoveParent();
	//Result = Path.IsExistsToPlusString("\\ContentsResources");
	//Path.MoveParent();
	//Result = Path.IsExistsToPlusString("\\ContentsResources");
	//Path.MoveParent();


	// 만들어야할 것들을 만드는 시점이 Loading시점입니다.
	CreateActor<Mario>();
}

void PlayLevel::Update()
{

}
