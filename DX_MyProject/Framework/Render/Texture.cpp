#include "framework.h"

unordered_map<wstring, Texture*> Texture::texture_data;
// 클래스에서 static으로 선언한 맴버 변수는 반드시 .cpp 어딘가에서 이렇게 따로 선언을 해줘야만
// 정상적으로 사용이 가능함

Texture::Texture(ID3D11ShaderResourceView* srv, ScratchImage& image)
	: srv(srv),image(move(image))
	// move() : DirectX에서 지원하고 있는 ScrachImage의 함수,
	//			ScrachImage의 객체 하나에 있는 데이터를 다른 객체에 옮기는 데 사용하는 함수
{
}

Texture::~Texture()
{
	srv->Release();
}

Texture* Texture::Add(wstring file)
// static 함수이므로 Texture 인스턴스에 접근하지 않아도 사용 가능
{
	if (texture_data.count(file)>0) // 입력받은 파일이 이미 맵에 저장되어 있는 파일이라면
	{
		return texture_data[file];	// 그 파일을 통해 생성된 texture  인스턴스의 주소를 맵에서 찾아 반환
	}

	// 만약 없다면(=위의 if문을 통과했다면)
	// 여기서부터 본격적으로 인스턴스 생성 과정을 거침

	ScratchImage image;
	ID3D11ShaderResourceView* srv;
	// 위에서도 이야기했지만 이 함수는 static 함수
	// 따라서, 이 클래스의 인스턴스가 존재하지 않는 상황에서도 실행할 수 있어야 한다는 의미
	// 그렇기 때문에 이 함수 안에서는 이 클래스가 가지고 있는 static이 아닌 맴버는 사용할 수 없어서
	// 사용하려면 여기에 따로 선언을 해서 지역 변수로 이용해야 함

	LoadFromWICFile(file.c_str(), WIC_FLAGS_NONE, nullptr, image);
	// 이 함수는 wstring을 인식하지 못하므로 LPCWSTR로 바꿔줘야 함
	CreateShaderResourceView(DEVICE, image.GetImages(), image.GetImageCount(), image.GetMetadata(), &srv);

	// 위 과정을 이용해 만들어진 image와 srv를 이용해 새 Texture 인스턴스를 생성
	Texture* t = new Texture(srv, image);

	// 인스턴스가 완성됐으면 이를 맵에 저장
	texture_data[file] = t;
	// 이러면 앞으로 같은 파일주소로 Add를 호출했을 경우 여기에 저장되어 있는 인스턴스가 대신 호출될 것

	return t;
}

void Texture::Delete()
{
	for (auto t : texture_data)
	{
		delete t.second;
	}
}

Vector2 Texture::GetSize()
// 이 텍스쳐(=이미지 파일)이 가지고 있는 데이터의 크기(=사진 크기)를 반환하는 함수
{
	return Vector2(image.GetMetadata().width, image.GetMetadata().height);
	// 텍스쳐의 메타데이터(파일의 내용물이 아닌 파일 자체에 대한 설명을 담당하는 데이터)룰 받아와서
	// 그 중 텍스쳐의 가로 전체 크기/세로 전체 크기를 이요해 이 텍스쳐의 크기를 확인하여 반환

	// 이미지 파일 자체의 크기를 이용해야 할 때 사용하게 되고,
	// 앞으로 우리는 이걸 우리가 사용하는 전체 이미지 중 
	// 우리가 이번에 사용하고자 하는 스프라이트가 전체 이미지에서 어느 정도의 비중을 가지고 있는지
	// 계산할 때 주로 불러와 사용하게 됨
}

void Texture::Set(UINT slot)
{
	DVC->PSSetShaderResources(slot, 1, &srv);
}
