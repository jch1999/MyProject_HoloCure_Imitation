#pragma once
// Vertex(정점) Buffer - 셰이더에 정점의 데이터를 넘길 때 사용하려는 용도로 만들어진 클래스
class VertexBuffer
{
private:
	ID3D11Buffer* buffer;
	// DX11에서 사용하는 규격의 버퍼

	UINT stride;
	// 이 인스턴스에서 저장하고 있는 버퍼가 한 칸마다 사용하는 용량을
	// 이 UINT(unsigned int)에 저장해두는 역할

	UINT offset;
	// 사용할 오프셋을 기록하는 맴버

public:
	VertexBuffer(void* data, UINT s, UINT count);
	~VertexBuffer();

	void Set(D3D11_PRIMITIVE_TOPOLOGY type=D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	// 도형을 출력하는 방식을 이제 버퍼에서 관리하도록 해주는 함수

};