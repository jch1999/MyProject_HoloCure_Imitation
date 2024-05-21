cbuffer world : register(b0)
{
	matrix world;
}
cbuffer view : register(b1)
{
	matrix view;
}
cbuffer projection : register(b2)
{
	matrix projection;
}

struct VertexInput
{
	float4 pos : POSITION;
	float4 uv : UV;
	// uv : 텍스쳐를 이용하기 위해서 사용하는 2번째 좌표인 uvw
	// 위쪽의 pos이 정점의 위치를 나타내기 위해 사용하는 좌표였다면,
	// uvw는 이 오브젝트 전체를 표시할 때 이 정점이 전체 그림 중
	// 어느 부분의 출력을 담당하고 있는 것인지를 기록하는 또다른 좌표
	
	// 텍스쳐 파일에서의 x, y, z 좌표를 이 u, v, w에 저장하는 것
};

struct PixelInput
{
	float4 position : SV_Position;
	float4 uv : UV;
};

PixelInput VS(VertexInput input)
{
	PixelInput output;
	output.position = mul(input.pos, world);
	output.position = mul(output.position, view);
	output.position = mul(output.position, projection);
	
	output.uv = input.uv;
	
	return output;
}
