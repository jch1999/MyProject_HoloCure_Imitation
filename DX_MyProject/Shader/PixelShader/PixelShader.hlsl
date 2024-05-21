cbuffer Color : register(b0)
{
	float4 color;
}
// VS측과 마찬가지로 색상버퍼를 0번 슬롯으로 받아들이도록 설정

struct PixelInput
{
	float4 position : SV_Position;
	float4 color : COLOR;
};

float4 PS(PixelInput input) : SV_TARGET
{
	return input.color * color;
	// 위에서 슬롯을 받아온 색상 버퍼를 그래도 곱해줌
	// 이를 통해 정점이 가지고 있는 색에 추가로 버퍼가 가지고 있는 색을 보정하여 화면에 출력하도록 함
	
}