#pragma once
class Frame
{
private:
	vector<VertexUV> vertices;	// 정점을 저장하는 백터
	vector<UINT> indices;	// 사용할 정점의 인덱스를 저장할 백터

	VertexBuffer* VB;
	IndexBuffer *IB;
	// 위 2개의 백터들을 담당하는 버퍼들

	Texture* texture;
	// 모든 프레임은 각각 그 프레임이 담당하는 이미지를 출력해야 함
	// 그 이미지를 이 변수를 통해 관리
	
	Vector2 frame_size;
	// 프레임이 실제로 출력할 사이즈

public:
	Frame(wstring file, Vector2 startUV=Vector2(0,0),Vector2 endUV=Vector2(1,1));
	Frame(wstring file, float x, float y, float w, float h);
	~Frame();

public:
	void Render() const;

	// 이 프레임이 사용하는 스프라이트의 원본 파일이 담당하는 크기
	const Vector2 Size() const { return texture->GetSize(); }
	// 이 프레임이 실제로 출력할 사이즈를 담당하는 함수
	const Vector2 GetFrameSize() const  { return frame_size; }
	// 이 프레임이 사용하는 스프라이트의 원본 파일과 실제로 출력할 사이즈를 확정짓기 위한 비용을 이용,
	// 이 프레임이 담당하는 스프라이트 자체의 본래 크기를 계산해 반환하는 함수
	const Vector2 GetFrameOriginSize() const { return frame_size * texture->GetSize(); }
};