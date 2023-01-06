#include "GameEngineDirectory.h"
#include <GameEngineBase/GameEngineDebug.h>

GameEngineDirectory::GameEngineDirectory()
{
}

GameEngineDirectory::~GameEngineDirectory()
{
}
void GameEngineDirectory::MoveParentToDirectory(const std::string_view& _String)
{
	std::string MovePath = "\\";
	MovePath += _String;

	Path.MoveParentToChildPath(MovePath.c_str());
}

bool GameEngineDirectory::Move(const std::string_view& _String)
{
	std::string MovePath = "\\";
	MovePath += _String;
	return Path.Move(MovePath.c_str());
}

GameEnginePath GameEngineDirectory::GetPlusFileName(const std::string_view& _String)
{

	std::string PathString = Path.GetPathToString();
	PathString += "\\";
	PathString += _String;
	GameEnginePath NewPath = PathString;

	return NewPath;
}

bool GameEngineDirectory::MoveParent()
{

	/*
	* String���� �θ� �̵��ϴ� ���
	std::string PathStr = Path.GetPathToString();
	size_t FindIndex = PathStr.find("\\");
	size_t Index = 0;
	while (FindIndex != std::string::npos) {
		Index = FindIndex;
		FindIndex = PathStr.find("\\", FindIndex + 1);
	}
	// PathStr = "D:\\AR45\\SuperMarioWorld_API\\ApiApp\\ApiApp"

	PathStr.erase(Index, PathStr.size());
	*/
	if (true == Path.IsRoot())
	{
		MsgAssert("��Ʈ ���丮�� �θ���丮�� �̵��Ҽ� �����ϴ�.");
		return false;
	}

	Path.MoveParent();

	return true;
}