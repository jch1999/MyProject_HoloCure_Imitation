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
// cbuffer( = Construct Buffer = 상수 버퍼) 3개를 선언하고, 이 버퍼들을 각각에 슬롯에 등록한다는 뜻
// 각가의 버퍼에는 각각 4X4 크기의 행렬이 들어가있음
// 이것들은 각각 W, V, P 변환을 위해 C++ 쪽에서 받아와야 하는 공간/시점/변환이 기록되어있는 데이터

// world라고 하는, world 행렬을 저장하는 상수 버퍼는 b0라는 "슬롯"에 등록해 그 슬롯을 통해 데이터를 입력받겠다
// view라고 하는, view 행렬을 저장하는 상수 버퍼는 b1아는 "슬롯"에 등록해 그 슬롯을 통해 데이터를 입력받겠다
// projection라고 하는, projection 행렬을 저장하는 상수 버퍼는 b2라는 "슬롯"에 등록해 그 슬롯을 통해 데이터를 입력받겠다

// 라는 식으로, 셰이더가 데이터를 입력받는 슬롯 각각이 어떤 데이터를 받아오는지에 대해 그 매칭을 정의하는 구문

// 이렇게 셰이터 측에서 어느 슬롯을 통해 데이터를 받을 것이지 설정해두면
// 이후 메인 프로젝트( = C++ 쪽 코드) 쪽에서 어느 슬롯에 데이터를 보내겠다고 명시하고 보내기만 하면
// 셰이더에서 해당 슬롯을 통해 알아서 데이터를 받아 이후의 처리를 진행

struct VertexInput
{
	float4 pos : POSITION;
	// float4 : HLSL에서 지원하는 자료형으로, 실수 4개를 저장함
	float4 color : COLOR;
};

struct PixelInput
{
	float4 position : SV_Position;
	float4 color : COLOR;
};

PixelInput VS(VertexInput input)
{
	PixelInput output;
	output.position = mul(input.pos, world);
	// mul : HLSL에서 지원하는 행렬과 행렬 간 곱셈을 지원해주는 예약어
	// 정확히는 백터 X 행렬도 지원해주고, 실제로 지금 여기서는 백터 X 행렬로서 기능하는 중
    output.position = mul(output.position, view);
    output.position = mul(output.position, projection);
	
	// 위 3개는 각각 World 변환, View 변환, Projection 변환을 담당하는 코드
	// -> WVP변환은 오브젝트가 가지고 있는 자료를 월드/뷰/프로젝션 순으로 곱하는 단계
	
	output.color = input.color; // 색상은 WVP 변환과 관련없으므로 기존 데이터를 그대로 시멘틱를 그대로 시멘틱만 변경하는 느낌으로 옮기기
	
	return output;
}
