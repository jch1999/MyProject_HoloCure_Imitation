#pragma once
class LevelLabel :public UI
{
protected:
	static vector<shared_ptr<const Frame>>& GetLevelLabelFrams();
	static int& GetLevelLabelUseCnt();

protected:
	LevelText* levelText;
public:
	LevelLabel(Vector2 inSize = Vector2(20.0f, 9.0f), Vector2 inScale = Vector2(2.0f, 2.0f), Vector2 inOffset = Vector2(0.0f, 0.0f));
	~LevelLabel();


	// UI을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
	virtual void InitFrame() override;
	virtual void ClearFrame() override;

	virtual void SetID(UI::UI_ID id) override;

	void SetLevel(int level);
	void SetActive(bool active);
};