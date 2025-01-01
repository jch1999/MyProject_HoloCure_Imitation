#pragma once
class PlayerIcon :public UI
{
protected:
	static vector<shared_ptr<const Frame>>& GetPlayerIconFrames();
	static int& GetPlayerIconUseCnt();

public:
	PlayerIcon(Vector2 inSize = Vector2(43.0f, 38.0f), Vector2 inScale = Vector2(1.0f, 1.0f), Vector2 inOffset = Vector2(0.0f, 0.0f));
	~PlayerIcon();

	// UI을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
	
	virtual void SetID(UI::UI_ID id) override;

	virtual void InitFrame() override;
	virtual void ClearFrame() override;
};