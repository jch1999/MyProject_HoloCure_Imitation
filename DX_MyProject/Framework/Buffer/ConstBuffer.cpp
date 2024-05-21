#include "framework.h"

ConstBuffer::ConstBuffer(void* data, UINT data_size)
	:data(data),data_size(data_size)
{
	// 정점 버퍼와 똑같이 같은 코드를 가져와 일부를 수정
	// 이번엔 총 4부분을 본 클래스에 맞게 교체함
	D3D11_BUFFER_DESC bd = {};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = data_size;
	// (1)ByteWidth
	// 이번엔 총 용량 그 자체를 입력받았으니 그대로 사용

	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	// (2) 이 버퍼가 어떤 것을 저장해두는 버퍼인지를 알리느 맴버
	// 이 버퍼가 어떤 것을 저장해두는 버퍼인지를 알리는 맴버
	// 이 버퍼는 상수를 다루는 버퍼이므로 "상수를 다루는 버퍼다"라고 셰이더에 알리기 위해 위와 같이 수정

	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem = data;
	// (3)pSysMem
	// 정점 버퍼와 마찬가지로 입력받은 void*를 그대로 이용
	DEVICE->CreateBuffer(&bd, &initData, &buffer);
	// (4) 함수 전반적으로
	// 기존에 사용했던 위치에서의 변수명 대신 이 클래스에서 사용하는 맴버의 이름으로 바꿔주기
	// 그리고 기존에 사용되었던 코드들 중에서도 매크로 등으로 줄일 수 있는 부분은 줄여두기
	// 이런 정점 버퍼 쪽에서 고쳤던 것과 똑같으므로 그 쪽에서 가져왔다면 수정 안 해도 무방
}

ConstBuffer::~ConstBuffer()
{
	buffer->Release();
}

void ConstBuffer::SetVS(UINT slot)
{
	DVC->UpdateSubresource(buffer, 0, NULL, data, 0, 0);
	//버퍼에 데이터를 저장하는 함수
	DVC->VSSetConstantBuffers(slot, 1, &buffer);
	// 저장된 버퍼를 VS(=정점 셰이더)로 넘기는데,
	// 정확히는 셰이더의 slot번 슬롯에 해당 데이터를 넘김
}

void ConstBuffer::SetPS(UINT slot)
{
	DVC->UpdateSubresource(buffer, 0, NULL, data, 0, 0);
	//버퍼에 데이터를 저장하는 함수
	DVC->PSSetConstantBuffers(slot, 1, &buffer);
	// 저장된 버퍼를 PS(=정점 셰이더)로 넘기는데,
	// 정확히는 셰이더의 slot번 슬롯에 해당 데이터를 넘김
}
// 이 slot이라는 개념은 저번에 사용했던 것과는 전혀 다른 새로운 셰이더를 만들면서 설명
