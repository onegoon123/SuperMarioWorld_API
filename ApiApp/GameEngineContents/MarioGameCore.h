#pragma once
#include <GameEngineCore/GameEngineCore.h>

#include "ContentsEnums.h"

// 게임전체를 통괄할 클래스
// 싱글톤으로 구성되어 객체로 하나만 구현된다
// 레벨을 로딩하는 기능과 게임 전반의 데이터를 저장하는 기능이 있다
class MarioGameCore : public GameEngineCore
{
public:
	// delete Function
	MarioGameCore(const MarioGameCore& _Other) = delete;
	MarioGameCore(MarioGameCore&& _Other) noexcept = delete;
	MarioGameCore& operator=(const MarioGameCore& _Other) = delete;
	MarioGameCore& operator=(MarioGameCore&& _Other) noexcept = delete;

	// 싱글톤
	inline static MarioGameCore& GetInst()
	{
		return Core;
	}

#pragma region __________마리오 데이터 Setter Getter__________
	inline PowerState GetMarioStateData() const {
		return MarioStateData;
	}
	inline PowerState GetStockStateData() const {
		return StockStateData;
	}
	inline bool GetRidedYoshiData() const {
		return RidedYoshiData;
	}
	inline void SetMarioStateData(PowerState _StateData) {
		MarioStateData = _StateData;
	}
	inline void SetStockStateData(PowerState _StateData) {
		StockStateData = _StateData;
	}
	inline void SetRidedYoshiData(bool _Data) {
		RidedYoshiData = _Data;
	}
#pragma endregion

protected:
	void Start() override;
	void Update() override;
	void End() override;


private:
	// 생성자가 존재하지 않음
	MarioGameCore();
	~MarioGameCore();

	// 싱글톤 객체
	static MarioGameCore Core;
		
	// 마리오 데이터
	PowerState MarioStateData = PowerState::Normal;
	PowerState StockStateData = PowerState::Normal;
	bool RidedYoshiData = false;
};

