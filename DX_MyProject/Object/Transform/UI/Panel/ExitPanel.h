#pragma once
class ExitPanel :public Panel
{
protected:
	ImageArea* popUp;
	Button* resumBtn, exitBtn;
	int selectIdx;
public:
	ExitPanel();
	~ExitPanel();

	// UI��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
};