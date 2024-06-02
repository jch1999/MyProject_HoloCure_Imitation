#pragma once
class SuperChattoTime :public Buff
{
protected:

public:
	SuperChattoTime();
	~SuperChattoTime();


	// Buff을(를) 통해 상속됨
	virtual bool LevelDown() override;

	virtual void Update() override;

	virtual void Render() override;

	virtual void PostRender() override;

	virtual bool LevelUp() override;

};