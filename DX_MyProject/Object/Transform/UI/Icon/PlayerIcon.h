#pragma once
class PlayerIcon :public UI
{
protected:
	static vector<shared_ptr<const Frame>>& GetPlayerIconFrames();
	static int& GetPlayerIconUseCnt();

public:
	PlayerIcon();
	~PlayerIcon();

	// UI을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
	
	virtual void SetID(UI::UI_ID id);

	virtual void InitFrame() override;
	virtual void ClearFrame() override;
};