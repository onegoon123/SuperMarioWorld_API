#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineRender.h>
class WorldLevel;

class WorldMap
{
	
public:
	class Point
	{
	public:
		Point(const float4& _Pos) {
			Pos = _Pos;
		}
		Point(const float4& _Pos, const std::string_view& _StageName, bool IsLock = false) {
			Pos = _Pos;
			StageName = _StageName;
			Lock = IsLock;
		}
		~Point() {
			if (Up != nullptr)
			{
				Point* DeletePoint = Up;
				DeletePoint->ErasePoint(this);
				this->ErasePoint(DeletePoint);
				delete DeletePoint;
			}
			if (Left != nullptr)
			{
				Point* DeletePoint = Left;
				DeletePoint->ErasePoint(this);
				this->ErasePoint(DeletePoint);
				delete DeletePoint;
			}
			if (Down != nullptr)
			{
				Point* DeletePoint = Down;
				DeletePoint->ErasePoint(this);
				this->ErasePoint(DeletePoint);
				delete DeletePoint;
			}
			if (Right != nullptr)
			{
				Point* DeletePoint = Right;
				DeletePoint->ErasePoint(this);
				this->ErasePoint(DeletePoint);
				delete DeletePoint;
			}
		}
		float4 Pos = float4::Zero;
		std::string_view StageName = "";
		Point* Up = nullptr;
		Point* Down = nullptr;
		Point* Left = nullptr;
		Point* Right = nullptr;
		bool Lock = false;

		void ErasePoint(const Point* _Point)
		{
			if (Up == _Point)
			{
				Up = nullptr;
			}
			if (Down == _Point)
			{
				Down = nullptr;
			}
			if (Left == _Point)
			{
				Left = nullptr;
			}
			if (Right == _Point)
			{
				Right = nullptr;
			}
		}
		bool IsStage()
		{
			return StageName != "";
		}

		void Unlock()
		{
			Lock = false;
		}
		void SetUp(Point* _Up)
		{
			Up = _Up;
			_Up->Down = this;
		}
		void SetDown(Point* _Down)
		{
			Down = _Down;
			_Down->Up = this;
		}
		void SetLeft(Point* _Left)
		{
			Left = _Left;
			_Left->Right = this;
		}
		void SetRight(Point* _Right)
		{
			Right = _Right;
			_Right->Left = this;
		}
	};

	WorldMap(Point* StartPoint)
	{
		StagePointer = StartPoint;
	}
	~WorldMap()
	{
		if (nullptr != StagePointer)
		{
			delete StagePointer;
			StagePointer = nullptr;
		}
	}

	bool MoveUp()
	{
		if (nullptr != StagePointer->Up)
		{
			if (true == StagePointer->Up->Lock)
			{
				return false;
			}
			StagePointer = StagePointer->Up;
			return true;
		}
		return false;
	}
	bool MoveDown()
	{
		if (nullptr != StagePointer->Down)
		{
			if (true == StagePointer->Down->Lock)
			{
				return false;
			}
			StagePointer = StagePointer->Down;
			return true;
		}
		return false;
	}
	bool MoveLeft()
	{
		if (nullptr != StagePointer->Left)
		{
			if (true == StagePointer->Left->Lock)
			{
				return false;
			}
			StagePointer = StagePointer->Left;
			return true;
		}
		return false;
	}
	bool MoveRight()
	{
		if (nullptr != StagePointer->Right)
		{
			if (true == StagePointer->Right->Lock)
			{
				return false;
			}
			StagePointer = StagePointer->Right;
			return true;
		}
		return false;
	}
	bool IsStage()
	{
		return StagePointer->IsStage();
	}
	const std::string_view& GetStage()
	{
		return StagePointer->StageName;
	}
	const float4& GetPos()
	{
		return StagePointer->Pos;
	}
private:
	Point* StagePointer = nullptr;
};

class WorldMario : public GameEngineActor
{
	friend WorldLevel;
public:
	WorldMario();
	~WorldMario();

	//static WorldMario* WorldData;
	//static void Reset();

	WorldMario(const WorldMario& _Other) = delete;
	WorldMario(WorldMario&& _Other) noexcept = delete;
	WorldMario& operator=(const WorldMario& _Other) = delete;
	WorldMario& operator=(WorldMario&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void LevelChangeStart(GameEngineLevel* _Prev) override;
private:
	const float speed = 100;
	bool IsStart = false;
	bool IsMove = false;
	float4 StartPos = float4::Zero;
	float4 EndPos = float4::Zero;
	float Timer = 0;
	GameEngineRender* AnimationRender = nullptr;
	WorldMap* Map = nullptr;

	WorldMap::Point* Stage1 = nullptr;
	WorldMap::Point* Stage2 = nullptr;
	WorldMap::Point* Stage3 = nullptr;
	WorldMap::Point* Stage4 = nullptr;
	WorldMap::Point* Stage5 = nullptr;
};

