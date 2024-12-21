#pragma once
// Clip : 프레임 등을 관리해 전체적인 애니메이션을 출력하는 클래스
// 원래 의미(짧게 잘라낸 영상)처럼, 
//애니메이션 하나하나는 짧으니 그 짧은 애니메이션을 각각 관리하는 용도
class Clip
{
public:
	enum class CLIP_TYPE
	{
		END, LOOP, PINGPONG
	};
	// 이 클립이 저장하고 있는 이미지들을 어떤 순서대로 출력할 것인지를 나타내는 열거형
	// END : 한 번 재생이 끝나면 그대로 끝(공격이 명중했을 때의 이펙트 등이 대표적)
	// LOOP : 한 번 재생이 끝나면 처음 프레임으로 돌아와서 재생을 반복
	// PINGPONG : 한 번 재생이 끝나면 마지막 프레임부터 역순으로 재생하고, 
	//				처음 프레임까지 재생이 끝나면 다시 처음부터 재재생하는 것을 반복

private:
	vector<shared_ptr<const Frame>>& frames; // 이 클릭에서 재생할 프레임들이 저장된 백터
	CLIP_TYPE repeat_type;
	mutable bool is_play;	// 애니메이션이 현재 재생중인지 아닌지를 기록해두는 변수

	mutable UINT cur_frame_num;	// 전체 프레임 중 몇번째 프레임을 현재 재생 중인지 저장하는 변수
	mutable float time;		// fps를 계산하기 위해 시간경과를 저장해두는 변수
	float fps;	// 초당 몇 장의 프레임을 재생할 것이지 결정하는 변수

	mutable bool is_reverse;	// PINGPONG 타입에만 존재하는 역재생상황 여부를 저장하는 맴버

public:
	Clip(vector<shared_ptr<const Frame>>& frames, CLIP_TYPE t = CLIP_TYPE::LOOP, float fps = 1.0f / 8.0f);
	~Clip();

	const bool isPlaying() const { return is_play; }
	const Vector2 GetFrameSize() const { return frames[cur_frame_num]->GetFrameSize(); }
	const Vector2 GetFrameOriginSize() const { return frames[cur_frame_num]->GetFrameOriginSize(); }
	void Update() const;
	void Render() const;
	void Play(UINT type = 0) const;
	void Pause() const;
	void Stop()const;
	
	const UINT GetFrameNum() const { return cur_frame_num; }
	const size_t GetFrameCnt() const { return frames.size(); }
	void SetFrameNum(UINT num) const { cur_frame_num = num; }
};