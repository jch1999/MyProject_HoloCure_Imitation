#pragma once

class VertexShader
{
private:
	ID3D11VertexShader* VS;
	// 정점 셰이더를 담당할 클래스 객체
	ID3D11InputLayout* input_layout;
	// DirectX 장치에 어떤 정점 데이터를 전달할 것인지
	// 그 레이아웃(=구조)의 명세서를 저장해두는 객체
	// 여기에 저장된 데이터를 토대로 정점이 입력되었을 때 셰이더 측에서 이를 해석하여 이용
	 
	ID3DBlob* vertex_blob; // 생성자에서 사요했던, 셰이더 생성에 필요한 임시 객체를 맴버로 빼낸 것
	ID3D11ShaderReflection* reflection;	// 빛의 반사 같은, 물리적 의미의 반사를 구현하는 데 필요한 맴버
	// 단, 우리가 직접 쓸 일은 ㅇ벗음, 오로지 코드의 호환성 때문에 작성한 것에 불과

	static unordered_map<wstring, VertexShader*> shader_data;
	// 같은 파일을 이용해 만든 셰이더를,
	// 파일의 이름을 키로 삼아서 순서가 필요하지 않은 map에 저장함
	// 그 후, 같은 파일의 이름을 통해 VertexShader의 객체가 호출된다면
	// 여기에 있나 체크하여 없으면 그 자리에서 생성, 있으면 해당 객체를 반환

	void CreateInputLayout();
	void CreateInputLayoutByPos();
	UINT type;

public:
	VertexShader(wstring file_loc, UINT type = 0,
		DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG);
	~VertexShader();

	static VertexShader* GetInstance(wstring file_loc, UINT type = 0);
	static void Delete();
	// Singleton을 만들 때, 외부에서 생성자를 곧바로 호출할 수 없으니
	// 생성자 역할을 겸하는 인스턴스 접근자를 만들었던 것이 기억날 것
	// 지금 이 변경된 클래스도 Singleton은 아님.
	// 하지만, 객체를 불러올 때 new를 그냥 쓴느 게 아니라 위 함수를 이용하는 것으로
	// 이미 만들어진 객체가 있을 경우 추가로 만들지 않고 가져오는 것이 가능
	// 이를 위해 static으로 자료구조를 만들어뒀으니,
	// 마찬가지로 static으로 해당 자료구조를 할당 해제하기 위한 delete 함수를 만들어둔 것

	void Release();
	ID3D11InputLayout* GetInputLayout() { return input_layout; }
	ID3D11VertexShader* GetVertexShader() { return VS; }

	void Set();
};