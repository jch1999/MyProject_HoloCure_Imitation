#pragma once
class ExitPanel :public Panel
{
protected:
	ImageArea* popUp;
	vector<Button*> btns;
	TextPrinter* pauseText;
	int selectIdx;

public:
	ExitPanel();
	~ExitPanel();

	// UI��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void SetActive(bool active)override;
};