#pragma once
class CounterIcon :public UI
{
protected:
	static vector<shared_ptr<Frame>> counterIconFrmaes;
	static bool bInited;
	static int CounterIconCnt;

public:
	CounterIcon();
	~CounterIcon();

	// UI��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void SetState(UI::UI_STATE state);
	virtual void SetID(UI::UI_ID id);
};