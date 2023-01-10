#pragma once
#include <GameEngineCore/GameEngineCore.h>

// �̷��� Ŭ������ ����� ��� ����ü�� �̱����̶�� �մϴ�.

// ���� :
class MarioGameCore : public GameEngineCore
{
public:
	// delete Function
	MarioGameCore(const MarioGameCore& _Other) = delete;
	MarioGameCore(MarioGameCore&& _Other) noexcept = delete;
	MarioGameCore& operator=(const MarioGameCore& _Other) = delete;
	MarioGameCore& operator=(MarioGameCore&& _Other) noexcept = delete;

	// �̱���
	static MarioGameCore& GetInst()
	{
		return Core;
	}
	
	// �ǰݽ� ����Ǹ� ���忡 �ִ� �������� ������ �Լ�
	void TakeOutStock() {
		// ���忡 �ִ� ���� ���� ������ ����

		// ������ ����
		//StockItem = 0;
	}

protected:
	void Start() override;
	void Update() override;
	void End() override;


private:
	// �����ڸ� ����.
	// constrcuter destructer
	MarioGameCore();
	~MarioGameCore();

	// �ڱ⸦ �ڽ��� ������
	// ���α׷��� ��Ʋ� ���� 1���� ��ü�� ���������
	// static StudyGameCore* Core;
	static MarioGameCore Core;
	//int StockItem;
};

