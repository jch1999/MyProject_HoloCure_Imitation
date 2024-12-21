#pragma once
// Clip : ������ ���� ������ ��ü���� �ִϸ��̼��� ����ϴ� Ŭ����
// ���� �ǹ�(ª�� �߶� ����)ó��, 
//�ִϸ��̼� �ϳ��ϳ��� ª���� �� ª�� �ִϸ��̼��� ���� �����ϴ� �뵵
class Clip
{
public:
	enum class CLIP_TYPE
	{
		END, LOOP, PINGPONG
	};
	// �� Ŭ���� �����ϰ� �ִ� �̹������� � ������� ����� �������� ��Ÿ���� ������
	// END : �� �� ����� ������ �״�� ��(������ �������� ���� ����Ʈ ���� ��ǥ��)
	// LOOP : �� �� ����� ������ ó�� ���������� ���ƿͼ� ����� �ݺ�
	// PINGPONG : �� �� ����� ������ ������ �����Ӻ��� �������� ����ϰ�, 
	//				ó�� �����ӱ��� ����� ������ �ٽ� ó������ ������ϴ� ���� �ݺ�

private:
	vector<shared_ptr<const Frame>>& frames; // �� Ŭ������ ����� �����ӵ��� ����� ����
	CLIP_TYPE repeat_type;
	mutable bool is_play;	// �ִϸ��̼��� ���� ��������� �ƴ����� ����صδ� ����

	mutable UINT cur_frame_num;	// ��ü ������ �� ���° �������� ���� ��� ������ �����ϴ� ����
	mutable float time;		// fps�� ����ϱ� ���� �ð������ �����صδ� ����
	float fps;	// �ʴ� �� ���� �������� ����� ������ �����ϴ� ����

	mutable bool is_reverse;	// PINGPONG Ÿ�Կ��� �����ϴ� �������Ȳ ���θ� �����ϴ� �ɹ�

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