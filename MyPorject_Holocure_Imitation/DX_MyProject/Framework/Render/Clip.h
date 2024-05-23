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
	vector<Frame*> frames; // �� Ŭ������ ����� �����ӵ��� ����� ����
	CLIP_TYPE repeat_type;
	bool is_play;	// �ִϸ��̼��� ���� ��������� �ƴ����� ����صδ� ����

	UINT cur_frame_num;	// ��ü ������ �� ���° �������� ���� ��� ������ �����ϴ� ����
	float time;		// fps�� ����ϱ� ���� �ð������ �����صδ� ����
	float fps;	// �ʴ� �� ���� �������� ����� ������ �����ϴ� ����

	bool is_reverse;	// PINGPONG Ÿ�Կ��� �����ϴ� �������Ȳ ���θ� �����ϴ� �ɹ�

public:
	Clip(vector<Frame*> frames, CLIP_TYPE t = CLIP_TYPE::LOOP, float fps = 1.0f / 8.0f);
	~Clip();

	bool isPlaying() { return is_play; }
	Vector2 GetFrameSize() { return frames[cur_frame_num]->GetFrameSize(); }
	Vector2 GetFrameOriginSize() { return frames[cur_frame_num]->GetFrameOriginSize(); }
	void Update();
	void Render();
	void Play(UINT type = 0);
	void Pause();
	void Stop();
	
	UINT GetFrameNum() { return cur_frame_num; }
	void SetFrameNum(UINT num) { cur_frame_num = num; }
};