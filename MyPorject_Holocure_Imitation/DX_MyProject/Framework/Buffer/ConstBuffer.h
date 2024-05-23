#pragma once
// Const(상수) Buffer - 정점용으로 사용하는 버퍼, 혹은 정점의 순서를 기록하기 위해 사용하는 버퍼(IndexBuffer) 외에
// 다른 용도로 사용하는 버퍼는 기본적으로 상수 버퍼를 이용함
// 정점 버퍼, 인덱스 버퍼 둘은 DX에서 직접적으로 개별적으로 다루는 버퍼이지만
// 나머지 버퍼들은 딱히 전용 버퍼를 만들어두지 않으므로,
// 그것들을 통틀어서 구성하는 버퍼

// 이 클래스는 그 자체를 곧바로 이용하지 않고,
// 각 용도에 맞는 상수 버퍼를 만들 때 이 클래스를 상속해 이용할 예정
// 각각의 자식 클래스는 GlobalBuffer.h에 전부 만들어둠
class ConstBuffer
{
private:
	ID3D11Buffer* buffer;
	// DX11에서 사용하는 규격의 버퍼

	void* data;
	// 이 버퍼 객체에 저장될 데이터를 맴버 변수로 미리 선언해둔 것
	// 어떤 데이터가 들어올지는 어떤 상수 버퍼냐에 따라 달라지므로 지금은 확인 불가

	UINT data_size;
	// 이 상수 버퍼에 들어온 데이터의 용량을 기록하는 버퍼
	// VertexBuffer의 stride와 비슷하긴 하나, 이 쪽은 말 그대로 어떤 데이터가 들어올 지 모르니 범용성있게 명명

public:
	ConstBuffer(void* data, UINT data_size);
	~ConstBuffer();

	void SetVS(UINT slot);
	void SetPS(UINT slot);
};