#include "Framework.h"
#include "IndexBuffer.h"
/*
* 인덱스 버퍼 : 정점의 순서를 기록하는 버퍼
* 지금까지 우리는 도형을 그릴 때 정점의 순선느 그냥 깊게 고민할 것 없이 입력된 순서대로 0번부터 이용해왔음
* 이 방식을 쓸 경우 정점 하나의 데이터 자체가 굉장히 커졌을 때 정점의 개수를 줄이는 난이도가 상당히 높다 -> 최적하 시 문제가 있을 수 있다?
* 
* 이를 해결하기 위해, 정점 자체는 사용할 정점 하나마다 한 번씩만 입력하고
* 실제로 출력할 때 이 정점 중 몇 번을 부를 것이지 그 순서를 기록한 다른 버퍼를 이용해서
* 하나의 정점을 여러번 이용할 수도 있고, 우리가 정점을 입력하는 순서를
* 반드시 처음부터 시계방향을 지켜서 넣을 필요가 없도록 하여 정점을 다루는 난이도를 낮추는 데 이용하는 버퍼
*/
IndexBuffer::IndexBuffer(void* data, UINT count)
{
	D3D11_BUFFER_DESC bd = {};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(UINT) * count;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	// VertexBuffer와 크게 다를 점은 없으나,
	// 어떤 버퍼에 대한 내용인지는 당연히 다르게 표기되어 있어야 함

	// 추가로, 셰이더에서 다루는 정점의 인덱스는 UINT일 수 밖에 없으므로(-1번째 정점 같은 건 없음)
	// 이 버퍼의 크기는 입력받은 데이터에 들어있는 자료의 수 * sizeof(UINT)일 수 밖에 없음

	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem = data;

	DEVICE->CreateBuffer(&bd, &initData, &buffer);

}

IndexBuffer::~IndexBuffer()
{
	buffer->Release();
}

void IndexBuffer::Set()
{
	DVC->IASetIndexBuffer(buffer, DXGI_FORMAT_R32_UINT, 0);
}