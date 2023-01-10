#pragma once
#include <GameEngineCore/GameEngineCore.h>

// 이렇게 클래스를 만드는 방식 그자체를 싱글톤이라고 합니다.

// 설명 :
class MarioGameCore : public GameEngineCore
{
public:
	// delete Function
	MarioGameCore(const MarioGameCore& _Other) = delete;
	MarioGameCore(MarioGameCore&& _Other) noexcept = delete;
	MarioGameCore& operator=(const MarioGameCore& _Other) = delete;
	MarioGameCore& operator=(MarioGameCore&& _Other) noexcept = delete;

	// 싱글톤
	static MarioGameCore& GetInst()
	{
		return Core;
	}
	
	// 피격시 실행되며 스톡에 있는 아이템을 꺼내는 함수
	void TakeOutStock() {
		// 스톡에 있는 값에 따라 아이템 생성

		// 스톡을 비운다
		//StockItem = 0;
	}

protected:
	void Start() override;
	void Update() override;
	void End() override;


private:
	// 생성자를 막아.
	// constrcuter destructer
	MarioGameCore();
	~MarioGameCore();

	// 자기를 자신이 가지면
	// 프로그램을 통틀어서 오직 1개의 객체만 만들어진다
	// static StudyGameCore* Core;
	static MarioGameCore Core;
	//int StockItem;
};

