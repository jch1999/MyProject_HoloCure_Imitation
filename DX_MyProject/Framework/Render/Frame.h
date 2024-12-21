#pragma once
class Frame
{
private:
	vector<VertexUV> vertices;	// ������ �����ϴ� ����
	vector<UINT> indices;	// ����� ������ �ε����� ������ ����

	VertexBuffer* VB;
	IndexBuffer *IB;
	// �� 2���� ���͵��� ����ϴ� ���۵�

	Texture* texture;
	// ��� �������� ���� �� �������� ����ϴ� �̹����� ����ؾ� ��
	// �� �̹����� �� ������ ���� ����
	
	Vector2 frame_size;
	// �������� ������ ����� ������

public:
	Frame(wstring file, Vector2 startUV=Vector2(0,0),Vector2 endUV=Vector2(1,1));
	Frame(wstring file, float x, float y, float w, float h);
	~Frame();

public:
	void Render() const;

	// �� �������� ����ϴ� ��������Ʈ�� ���� ������ ����ϴ� ũ��
	const Vector2 Size() const { return texture->GetSize(); }
	// �� �������� ������ ����� ����� ����ϴ� �Լ�
	const Vector2 GetFrameSize() const  { return frame_size; }
	// �� �������� ����ϴ� ��������Ʈ�� ���� ���ϰ� ������ ����� ����� Ȯ������ ���� ����� �̿�,
	// �� �������� ����ϴ� ��������Ʈ ��ü�� ���� ũ�⸦ ����� ��ȯ�ϴ� �Լ�
	const Vector2 GetFrameOriginSize() const { return frame_size * texture->GetSize(); }
};