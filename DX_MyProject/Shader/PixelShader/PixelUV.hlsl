cbuffer Color : register(b0)
{
	float4 color;
}

struct PixelInput
{
	float4 position : SV_Position;
	float4 uv : UV;
};

SamplerState samp : register(s0);
Texture2D map : register(t0);
// samp : 텍스쳐 데이터에서 특정한 한 점을 뽑아와 그 점의 정보를 임시로 저장하는 버퍼
// map : samp에 저장된 각 픽셀의 값들을 프로그램(그래픽)에서 출력할 위치에 맞게 저장하는 버퍼
// 이 둘을 합쳐서 최종적으로 그려낼 그래픽 데이터를 결정하는 버퍼로 이용하며,
// 이미지 등의 텍스쳐 파일에서 정보를 추출해 모니터에 출력할 그래픽으로 바꾸는 용도

float4 PS(PixelInput input) : SV_TARGET
{
	return map.Sample(samp, input.uv) * color;
	// 텍스쳐 파일에서 samp를 통해 뽑아온 데이터를 uv값에 해당하는 map의 좌표에 저장
	// 만약 색상버퍼에 값이 들어와있다면 그렇게 가져온 이미지 데이터에다가 추가적으로 색보정을 가함
	
}

/*

과제라기보단 준비물 :

어느 방향을 바라보고 있는지 한 눈에 알 수 있는 이미지를 하나 준비해올 것

*/