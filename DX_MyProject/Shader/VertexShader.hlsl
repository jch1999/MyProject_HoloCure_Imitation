// HLSL : High-Level Shader Language, 고레벨 셰이더 언어
// 인간이 이해하기 쉽게 고도화 시킨 셰이더 언어
// 셰이더를 다루기 위해 만들어진 언어로, 이 언어를 통해 그래픽 파이프라인에서 다루는 셰이더들을 관리함

// 이 셰이더라고 하는 것은 DirectX에서 다루는 내용이기는 하나, HLSL이라는 다른 언어를 쓰고 있기 때문에
// C++ 언어와 완전히 호환되지 않음
// 따라서 셰이더(HLSL) 고유의 용에 맞게 구성해줘야 하고,
// 특히 프로젝트의 메인 코드 쪽(C++)에서 어느 데이터가 들어오는 것이지 이 파일에서 알 방도가 없기 때문에
// 보내주는 C++ 쪽에서 Input-Assembler 단계를 통해 어떤 데이터를 보내주는 것인지 명시해줘야 하는 것

// 그 과정에서 사용하는 것이 바로 아래에 있는 구조체들(포멧)

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

	
// 변수 뒤에 다른 이름이 적혀있는 것을 확인 가능
// 이는 시멘틱(Symentic)이라 부름
	
// C++에서 데이터를 HLSL 파일에 보낸 때, 보낸 데이터가 정확히 어디에 사용되는 데이터인지를 명시해야 하는데
// 그 때 그 도착지를 표기하기 위해 사용하는 개념
// C++에서 POSITION이라고 태그를 붙여서 보낸 데이터는 이 파일의  VertexInput안에 있는 POSITION 시멘틱을 가진
// 이 pos라는 변수에 저장되는 것
// 자세한 건 VertexShader.cpp에서 설명


PixelInput VS(VertexInput input)
// VS : VertexShader의 줄임으로, 이 함수에서 정점 셰이더의 처리가 이뤄진다는 의미
// 이 셰이더의 main()에 해당하는 함수로, 디폴트로는 main으로 설정되어있는 것을 임의로 이름을 바꾼 것

// 입력받는 매개변수로는 C++에서 시멘틱을 통해 값이 전달된 VertexInput을 받으며,
// 그 결과물로 PS에 사용할 데이터인 PixelInput을 반환
{
	PixelInput output;
	output.position = input.pos;
	output.color = input.color;
	// 현재는 이 셰이더에서 특별한 작업은 하지 않을 것이므로,
	// 입력받은 데이터를 그대로 PixelInput으로 변환하여 PS에 옮겨주는 것
	
	// VertexInput과 PixelInput은 맴버의 자료형 자체는 똑같은데
	// 그 맴버 각각이 가지고 있는 시멘틱이 성로 다름
	// PS에서는 PI가 가지고 있는 시멘틱을 이용해 처리해야 하기 때문에,
	// 그 시멘틱을 변경해주는 작업이라고 봐도 무방
	// 나중엔 실제로 VS에서 다른 작업을 할 것이기 때문에 분리하는 것이 맞긴 함
	
	return output;
}

float4 PS(PixelInput input) : SV_TARGET
// PS : PixelShader의 줄임으로, 이 함수에서 픽셀 셰이더의 처리가 이뤄진다는 의미
// 마찬가지로 디폴트 네임은 main
{
	// 입력받은 데이터를 딱히 가공하진 않으므로 이를 그대로 모니터에 출력할 색으로 출력
	return input.color;
	
	// PI의 맴버에는 현재 이 픽셀의 위치가 같이 기록되어 있음
	// 이는 PS에선 사용하지 않지만 실제로 이 데이터가 모니터의 어느 픽셀을 담당할 것인지를 명시하는 역할을 가지고 있어서
	// 여기서는 사요하지 않더라도 구축해둘 필요가 잇음
	// 나중에는 이 좌표를 가지고 특정한 처리를 하게 되는 일도 있을 수 있기 때문에
	// 이를 대비하는 역할도 겸함
}
