#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineRender.h>

class WorldMap
{
public:
	class Point
	{
	public:
		Point(const float4& _Pos) {
			Pos = _Pos;
		}
		Point(const float4& _Pos, const std::string_view& _StageName) {
			Pos = _Pos;
			StageName = _StageName;
		}
		~Point() {
			if (Up != nullptr)
			{
				Up->Down = nullptr;
				delete Up;
				Up = nullptr;
			}
			if (Left != nullptr)
			{
				Left->Right = nullptr;
				delete Left;
				Left = nullptr;
			}
			if (Down != nullptr)
			{
				Down->Up = nullptr;
				delete Down;
				Down = nullptr;
			}
			if (Right != nullptr)
			{
				Right->Left = nullptr;
				delete Right;
				Right = nullptr;
			}
		}
		float4 Pos = float4::Zero;
		std::string_view StageName = "";
		Point* Up = nullptr;
		Point* Down = nullptr;
		Point* Left = nullptr;
		Point* Right = nullptr;

		bool IsStage()
		{
			return StageName != "";
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

	void MoveUp()
	{
		if (nullptr != StagePointer->Up)
		{
			StagePointer = StagePointer->Up;
		}
	}
	void MoveDown()
	{
		if (nullptr != StagePointer->Down)
		{
			StagePointer = StagePointer->Down;
		}
	}
	void MoveLeft()
	{
		if (nullptr != StagePointer->Left)
		{
			StagePointer = StagePointer->Left;
		}
	}
	void MoveRight()
	{
		if (nullptr != StagePointer->Right)
		{
			StagePointer = StagePointer->Right;
		}
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
public:
	WorldMario();
	~WorldMario();

	WorldMario(const WorldMario& _Other) = delete;
	WorldMario(WorldMario&& _Other) noexcept = delete;
	WorldMario& operator=(const WorldMario& _Other) = delete;
	WorldMario& operator=(WorldMario&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
private:
	GameEngineRender* AnimationRender = nullptr;
	WorldMap* Map = nullptr;
};

