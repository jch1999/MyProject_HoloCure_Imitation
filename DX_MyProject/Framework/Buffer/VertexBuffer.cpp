#include "framework.h"

VertexBuffer::VertexBuffer(void* data, UINT s, UINT count)
	:stride(s),offset(0)
{
	// 기존의 각 도형의 생성자에서 버퍼를 만들어서 저장했던 부분을 가져오되,
	// 총 3부분을 본 클래스에 맞게 교체함

	D3D11_BUFFER_DESC bd = {};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = stride * count;
	// (1) ByteWidth
	// 이 버퍼가 가지고 있는 데이터의 총 크기를 기록하는 변수
	// 도형에서 사용할 때는 그 도형의 정점을 몇 개 이용했는지 확인해서 정점의 크기 * 정점의 개수를 곱하면 됐으나
	// 여기서는 어떤 정점이 사용될지 이 클래스 내에선 알지 못하도 stride로서 입력 받아야 함
	// 따라서  정점 하나의 용량 * 여기에 입력될 정점 데이터의 총 데이터의 개수를 입력받아서 총 용량을 계산하는 것
	
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	// 이 버퍼가 어떤 것을 기록해두는 버퍼인지를 알리는 맴버
	// 지금은 정점을 기록하는 버퍼이므로 고칠 필요 없음

	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem = data;
	// (2) pSysMem
	// 기존 도형에서  다룰 때는 정점에 기록된 행렬을 생성자 내부에서 만들었기 때문에 이를 이용하면 됐음
	// 하지만 여기선 정점의 데이터를 매개변수인 void*로 받기 때문에, 이용할 필요조차 없이 그대로 그 주소를 입력

	DEVICE->CreateBuffer(&bd, &initData, &buffer);
	// (3) 함수 전반적으로
	// 기존에 사용됐던 위치에서의 변수명 대신 이 클래스에서 사용하는 맴버의 이름으로 바꿔주기
	// 그리고 기존에 사용되었던 코드들 중에서도 매크로 등으로 줄일 수 있는 부분은 줄여두기
}

VertexBuffer::~VertexBuffer()
{
	buffer->Release();
}

void VertexBuffer::Set(D3D11_PRIMITIVE_TOPOLOGY type)
{
	// Device::Get()->GetDeviceContext();
	DVC->IASetVertexBuffers(0, 1, &buffer, &stride, &offset);
	DVC->IASetPrimitiveTopology(type);
}
