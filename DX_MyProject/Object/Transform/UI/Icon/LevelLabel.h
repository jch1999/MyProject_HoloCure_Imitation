#pragma once
class LevelLabel :public UI
{
protected:
	LevelText* levelText;
public:
	LevelLabel();
	~LevelLabel();


	// UI��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void SetState(UI::UI_STATE state);
	virtual void SetID(UI::UI_ID id) override;

	void SetLevel(int level);
	void SetActive(bool active);
};