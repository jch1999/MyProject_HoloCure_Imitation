#pragma once
class SuperChattoTime :public Buff
{
protected:

public:
	SuperChattoTime();
	~SuperChattoTime();


	// Buff��(��) ���� ��ӵ�
	virtual bool LevelDown() override;

	virtual void Update() override;

	virtual void Render() override;

	virtual void PostRender() override;

	virtual bool LevelUp() override;

};