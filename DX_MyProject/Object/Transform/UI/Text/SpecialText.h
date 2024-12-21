#pragma once
class SpecialText :public UI
{
protected:
	static shared_ptr<Frame> LevelUpFrame;
	static vector<shared_ptr<const Frame>> WhiteNumberFrames;
	static vector<shared_ptr<const Frame>> YellowNumberFrames;
	static vector<shared_ptr<const Frame>> RedNumberFrames;
	static bool bInited;
	static int TextUseCnt;

public:
	SpecialText();
	~SpecialText();


	// UI을(를) 통해 상속됨
	virtual void Init() override;

	virtual void SetState(UI::UI_STATE inState) override;
};