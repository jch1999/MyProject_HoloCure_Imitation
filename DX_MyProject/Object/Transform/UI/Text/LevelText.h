#pragma once
class LevelText :public SpecialText
{
public:
	LevelText();
	~LevelText();


	// UI��(��) ���� ��ӵ�
	virtual void Update() override;

	virtual void Render() override;

	virtual void PostRender() override;
	virtual void SetID(UI::UI_ID id) override;
	virtual void SetClipIdx(int idx) override;
};