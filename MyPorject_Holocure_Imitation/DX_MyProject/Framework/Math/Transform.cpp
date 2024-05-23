#include "framework.h"

Transform::Transform(Vector2 p, Vector2 s, float a, Matrix* parent)
	:pos(p),scale(s),rot(Float3(0.0f,0.0f,a)),parent(parent)
{
	world = XMMatrixIdentity();	// 일단 월드 행렬은 단위행렬로 초기화\

	right = Vector2(1, 0);
	up = Vector2(0, -1);
	// 오르쪽 위를 DX의 좌표계에 맞춰서 단위백터로서 정의

	WB = new MatrixBuffer();
	// 오브젝트 각각이 출력에 사용될 월드 행렬을 셰이더에 직접 넘길 수 있도록
	// 월드 변환에 사용될 버퍼를 각자가 알아서 생성
}

Transform::~Transform()
{
	delete WB;
}

void Transform::WorldUpdate()
// 이 함수를 통해 이 트랜스폼의 실제 위치를 계산해서 월드 행렬
{
	S = XMMatrixScaling(scale.x, scale.y, 1.0f);
	/* Matrix S : Scale 변환 행렬 - 오브젝트의 스케일(=크기)을 행렬에 저장
	* 위의 함수는 DX에서 제공하는, scale의 값을 입력해주면 그에 맞는 Scale 변환 행렬을 만들어
	* 4X4 크기의 행렬으로서 반환해주는 함수
	* 
	* scale.x = a, scale.y = b, scale.z = c
	* ( a 0 0 0 )
	* ( 0 b 0 0 )
	* ( 0 0 c 0 )
	* ( 0 0 0 1 )
	* 
	*/
	R = XMMatrixRotationZ(rot.z);
	/* Matrix R  : 오브젝트의 회전도를 담당하는 Rotation 변환 행렬
	* S와 마찬가지로 알아서 행렬을 만들어주는 DX 함수를 이용해 만듦
	* 
	* 원래대로라면 x, y, z 각각의 회전가을 받아서 이를 동시에 이용해 행렬을 만드는
	* XMMatrixRotationRollPitchYaw(x,y,z)를 통해서 만들지만
	* 현재 이 프로젝트는 2D를 만들고 있기 때문에 z축의 회전각만 이용
	* 그리고 저 XMMatrixRotationRollPitchYaw 함수는 사실상 X축 하나만으로 만든 행렬과 Y축 하나만으로 만든 행렬,
	* Z축 하나만으로 만든 행렬을 순차적으로 곱하여 만드는 행렬
	* -> 그 앞의 X축과 Y축을 이용해 만드는 행렬을 만드는 과정을 생략하고 Z축으로만 만든 것
	* 
	* 그렇게 Z축만 이용해 만들어지는 행렬은 다음과 같음 : 
	* angle = a라 했을 때
	* ( cos(a) -sin(a) 0 0 )
	* ( sin(a)  cos(a) 0 0 )
	* (  0       0     1 0 )
	* (  0       0     0 1 )
	*/
	T = XMMatrixTranslation(pos.x, pos.y, 0.0f);
	/* Matrix T : 오브젝트의 "투명", 즉 "이동"을 관리하는 Trnaslation 변환 행렬
	* 그냥 좌표에 따른 이동을 이 행렬을 통해 저장한다고 보면 OK
	* 
	* pos.x = a, pos.y = b, pos.z = c
	* ( 1 0 0 0 )
	* ( 0 1 0 0 )
	* ( 0 0 1 0 )
	* ( a b c 1 )
	*/

	P = XMMatrixTranslation(pivot.x, pivot.y, 0.0f);
	IP = XMMatrixInverse(NULL, P);
	// 위 둘은 각각 pivot을 이용해서 pivot있을 때를 전제로 하여
	// 추가적으로 변환 행렬을 만든 것
	// 기본적인 SRT 행렬과는 달리, 피벗을 이용한 연산을 하게 될 경우
	// 피벗 행렬의 역행렬까지 구해서 SRT 변환 행렬을 구한 것에 곱해야 할 필요성이 있음
	// 그 역행렬을 구하는 함수가 위의 XMMatrixInverse()

	world = IP * S * R * T * P;
	// 그렇게 구한 변환 행렬들을 순서에 맞게 곱해주면
	// 이 오브젝트가 위치한 월드 행렬이 완성됨

	if (this->parent != NULL)
		world *= *this->parent;
	// 완성된 월드 행렬에, 만약 이 오브젝트가 다른 오브젝트의 위치에 의존하는 오브젝트라면
	// 그 의존하는 오브젝트의 월드를 가져와서 위에서 구한 월드에 곱하여 최종적인 좌표를 연산

	// 여기까지가 SRT 변환

	// 이 아래부터는 그렇게 만들어진 월드 행렬을 이용해
	// 우리가 Transform을 다룰 때 추가로 사용하게 될 데이터들을 맴버들에다가 추출해 저장하는 과정

	XMStoreFloat4x4(&mat_world, world);
	// 우리가 구했던 XMMATRIX를 Float4X4 데이터에 복사하는 함수를 이용해 복사

	right = Vector2(mat_world._11, mat_world._12);
	up = Vector2(mat_world._21, mat_world._22);
	// 그렇게 구한 오브젝트의 현재 행렬에서 데이터를 직접 꺼내어
	// 현재 이 트랜스폼이 보고 있는 오른쪽 방향과 위쪽 방향을 저장

	XMVECTOR outS, outR, outT;
	// 이것들은 각각 변환 완료된 월드 행렬에서 추출한 Scale, Rotation, Translation 데이터를
	// 각각 임시로 저장해둘 변수
	// 지금 우리가 필요한 건 어디까지나 global_scale에 저장할 outS 하나뿐이지만
	// 아래에서 사용할 추출 함수가 이 3개를 전부 요구하기 때문에 어쩔 수 없이 선언한 것

	XMMatrixDecompose(&outS, &outR, &outT, world);
	// 하나의 완성된 world 행렬에서 위의 3가지 데이터를 추출하는 함수를 통해
	// 각각의 데이터를 방금 선언한 변수에 저장
	XMStoreFloat2(&global_scale, outS);
	// 그 중 월드가 가지고 있걷 scale = 전체 좌표계 상에서의 scale을 global_scale에 저장

	WB->Set(world);
	// 모든 작업이 끝났으면 이 오브젝트의 world 행렬을 
	// 이 오브젝트가 셰이더에 넘길 때 쓸 월드 버퍼에 저장
}
