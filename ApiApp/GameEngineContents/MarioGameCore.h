#pragma once
#include <GameEngineCore/GameEngineCore.h>

#include "ContentsEnums.h"

// ������ü�� ����� Ŭ����
// �̱������� �����Ǿ� ��ü�� �ϳ��� �����ȴ�
// ������ �ε��ϴ� ��ɰ� ���� ������ �����͸� �����ϴ� ����� �ִ�
class MarioGameCore : public GameEngineCore
{
public:
	// delete Function
	MarioGameCore(const MarioGameCore& _Other) = delete;
	MarioGameCore(MarioGameCore&& _Other) noexcept = delete;
	MarioGameCore& operator=(const MarioGameCore& _Other) = delete;
	MarioGameCore& operator=(MarioGameCore&& _Other) noexcept = delete;

	// �̱���
	inline static MarioGameCore& GetInst()
	{
		return Core;
	}

#pragma region __________������ ������ Setter Getter__________
	inline MarioState GetMarioStateData() const {
		return MarioStateData;
	}
	inline MarioState GetStockStateData() const {
		return StockStateData;
	}
	inline bool GetRidedYoshiData() const {
		return RidedYoshiData;
	}
	inline void SetMarioStateData(MarioState _StateData) {
		MarioStateData = _StateData;
	}
	inline void SetStockStateData(MarioState _StateData) {
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
	// �����ڰ� �������� ����
	MarioGameCore();
	~MarioGameCore();

	// �̱��� ��ü
	static MarioGameCore Core;
		
	// ������ ������
	MarioState MarioStateData = MarioState::Normal;
	MarioState StockStateData = MarioState::Normal;
	bool RidedYoshiData = false;
};

