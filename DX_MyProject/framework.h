// framework.h: 미리 컴파일된 헤더 파일입니다.
// 아래 나열된 파일은 한 번만 컴파일되었으며, 향후 빌드에 대한 빌드 성능을 향상합니다.
// 코드 컴파일 및 여러 코드 검색 기능을 포함하여 IntelliSense 성능에도 영향을 미칩니다.
// 그러나 여기에 나열된 파일은 빌드 간 업데이트되는 경우 모두 다시 컴파일됩니다.
// 여기에 자주 업데이트할 파일을 추가하지 마세요. 그러면 성능이 저하됩니다.

// 미리 컴파일된 헤더 : 프로그램이 시작하기 전에 헤더 파일들만을 미리 컴파일하여
// 파일으로서 만들어두도록 지정해둔 것
// 미리 컴파일된 헤더를 사용할 경우 이 헤더 안에 있는 내용들은 프로젝트가 빌드되기 전에 미리 파일으로서 컴파일되어
// .pch 파일으로 만들어지게 되고,
// 이 파일은 컴파일된 헤더 자체에 변동사항이 생기지 않는 이상 추후 컴파일될 때 헤더들의 컴파일을 생략하고
// 이 파일에서 각 헤더의 내용들을 가져와 사용할 수 있도록 하는 역할을 함

// 사용하는 이유는 크게 2가지
// 1) 미리 컴파일된 헤더는 프로젝트 자체에서 사용하는 것이기 때문에,
// 각 파일에서 이 미리 컴파일된 헤더를 사용하겠다고 명시해두기만 하면
// 헤더에서 특정 헤더를 포함시키던가 하지 않고도 미리 컴파일된 헤더 내부에 있는 내용을 전부 가져다 쓸 수 있음

// 2) 기본적으로 하나의 프로젝트에서 포함시키는 헤더의 수는 아무리 적게 잡아도 수십게 단위가 되며,
// 좀 커다란 프로젝트인 경우엔 100개 단위는 가볍게 넘어가는 경우가 수두룩함
// 이런 것들을 매번 컴파일할 경우 시간이 걸려도 한참 오래 걸리게 됨
// 그래서 자주 컴파일하게 될 내용들을 따로 빼내어 파일으로서 미리 만들어두고 이를 두고두고 쓴다면
// 컴파일에 걸리는 시간이 매우 크게 단축되므로 이용한는 것

#ifndef PCH_H
#define PCH_H

// 여기에 미리 컴파일하려는 헤더 추가
#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
#include <windowsx.h>

// 각종 메크로 상수를 선언하는 구간

#define WIN_START_X 100
#define WIN_START_Y 100
// 윈도우 창이 처음에 열릴 때 어느 위치에서 열릴지를 결정할 매크로

#define WIN_WIDTH 1280
#define WIN_HEIGHT 720

#define WIN_CENTER_X (WIN_WIDTH * 0.5f)
#define WIN_CENTER_Y (WIN_HEIGHT * 0.5f)
#define WIN_CENTER (Vector2(WIN_CENTER_X,WIN_CENTER_Y))
// 화면 중앙의 좌표를 매크로로서 손쉽게 이용할 수 있도록 선언

#define GRAVITY 98.0f // 중력을 여기에 정의해둬서
// 다른 여러 오브젝트에서 이 값을 이용할 수 있도록 만들어둠

// 기본 이동 속도를 매크로로 만들어 관리
#define defaultSPD 100.0f

// 전체 화면을 특정한 칸으로 나누기 위한 칸의 크기 값
#define CELL_X 100
#define CELL_Y 100

// FixedUpdate 간격
#define FIXED_INTERVAL 0.02f

// 각종 매크로 단축문을 선언하는 구간
#define DEVICE (Device::Get()->GetDevice())
#define DVC (Device::Get()->GetDeviceContext())

#define DELTA (Timer::Get()->GetDeltaTime())
#define FPS (Timer::Get()->GetFPS())

#define KEY_CON (Control::Get())

#define CAM Environment::Get()->GetMainCamera()
#define LERP(s,e,t) (s+(e-s)*t)

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <vector>
#include <unordered_map>
#include <string>
#define _USE_MATH_DEFINES // 삼각비를 다루기 위해, 거기에 사용될 pi를 사용하겠다 선언
#include <math.h>
#include <random>
#include <map>
#include <set>

// DirectX11 관련 라이브러리
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dcompiler.lib")
// 위의 내용들을 통해 DirectX에서 사용하는 기능들을 가져옴

#pragma comment(lib, "dxguid.lib")
#include "../DirectXTex/DirectXTex.h"
// DirectTex를 사용하기 위해 추가하는 라이브러리
// 여기서의 ..은 "현재 폴더(=기본 폴더)에서 한 단계 상위 폴더로 올라가라는 의미

// 프로젝트 설정의 참조에서 해당 프로젝트를 체크하여 참조해도 된다고 허가를 해야만
// 이렇게 다른 프로젝트에 있는 파일을 불러올 수 있음
// 그러지 않으면 접근할 수 있는 권하니 부여되지 않아 컴파일 에러가 발생

#include "../ImGui/imgui.h"
#include "../ImGui/imgui_impl_win32.h"
#include "../ImGui/imgui_impl_dx11.h"
/*
* ImGui 프로젝트를 github에서 다운 받아 적당한 곳에 푼다
* ImGui-master라는 폴더가 생겼을 것
* ImGui 프로젝트 폴더 안에 존재하는 Backend에서 현재 사용하는 OS에 해당(현재 win32)하는 .cpp, .h 헤더명의 파일과
* 현재 사용하는 DX 버전에 해당하는 파일명의 .cpp와 .h 파일을 복사해서
* ImGui-master 안에 붙여넣는다.
* ImGui-master에 존재하는 모든 .cpp와 .h 파일을 복사한다
* 현재 프로젝트가 포함된 솔루션에 빈 프로젝트를 생성한다
* 빈 프로젝트에 복사한 파일을 붙여넣고 프로젝트에 포함시킨다.
* 
* 해당 프로젝트를 속성 - 구성속성 - 일반 - 구성형식에서 정적 라이브러리로 설정하고 적용시킨다
* 현재 프로젝트에 추가 - 참조 로 빈 프로젝트(파일을 붙여넣은 프로젝트)를 참조하도록한다.
*/
/*
* 위의 3줄은 Imgui라는 외부 라이브러리를 이용하기 위해 필요한 구문
* ImGui : 프로그램의 각종 패러미터 등을 손쉽게 출력할 수 있게 만들어주는 Graphic User Interface
* 앞으로는 디버깅을 할 때 각종 패러미터를 쉽게 확인하려는 용도로 사용할 예정
* 
* 사용하기 위해 필요한 과정 - 옛날 버전
1. ImGui를 구글 검색해서 나오는 GitHub에서 전체 파일을 다운받고 아무것도 없는 아무 폴더에 풀기
(Code -> Download ZIP)
2. 압축을 푼 폴더에서 ImGui_master/backend/ 폴더에서
imgui_impl_dx11.h & cpp
imgui_impl_win32.h & cpp
위 4개 파일을 ImGui_master 폴더에 복사
3. ImGui_master 폴더에 있는 모든 cpp, h 파일을 복사하여
다른 폴더에 복사할 준비를 마치기
4. 지금 이 프로젝트 자체의 기본 폴더에 새 폴더 Library를 생성,
3에서 복사한 파일을 해당 폴더에 새로이 ImGui 폴더를 만들어 붙여넣기
5. 이렇게 추가한 파일들을 프로젝트에 포함
6. 위에 작성한 Include 전처리문을 3줄 작성
7. 혹시나 추가한 cpp 파일들이 미리 컴파일된 헤더를 사용하도록 설정되어 있으면 사용 안함으로 변경
*/
using namespace std;
using namespace DirectX;

// 이제부터 이 (미리 컴파일된) 헤더에 여러 라이브러리들을 계속해서 추가할 것인데
// 추가하는 순서에 따라서 에러가 발생하는 경우가 빈발함
// 따라서 각 헤더가 어디에 추가되는지를 정확히 파악하고 넣어줘야 함

// 미리 컴파일된 헤더가 사용될 경우엔 그 헤더가 있는 내용들을 프로젝트에서 전부 포함된 것처럼 인식하게 됨
// 그러나 실제로 커파일될 때는 여타 헤더와 마찬가지로 이 헤더의 맨 위에서부터 실행하기 때문에,
// 아직 컴파일이 되지 않은 헤더의 내용을 사용하는 헤더가 더 위쪽에 포함되었을 경우 에러가 발생
// 따라서 헤더의 순서를 최대한 지켜줘야 정상적으로 프로그램이 실행되기 때문에,
// 여기에 헤더를 추가할 때는 순서를 최대한 주의해서 넣어둘 것

typedef XMFLOAT4 Float4;
typedef XMFLOAT3 Float3;
typedef XMFLOAT2 Float2;
// XMFLOAT : DX에서 사용되는, 실수를 N개만큼 묶어놓는 구조체

typedef XMMATRIX Matrix;
// XMMATRIX : DX에서 사용되는, 여러 종류의 변수를 저장할 수 있는 유니온 구조체
// 유니온(Union) : 2종류 이상의 자료형을 내부에 가지고 있어서,
// 선언할 때 입력된 데이터에 따라 유동적으로 자료형이 결정되는 구조체
// 이 Matrix는 기본적으로 4x4 크기의 행렬을 다루며, DirectX에서 행렬을 이용할 때 이 자료형을 요구하기 때문에
// 이를 선언해줌

// Framework Header - 프로그램을 구성하는 데 있어 뼈대가 되르 우리가 제작한 라이브러리

//		Utility Header - 프로그램 여기저기서 사용할 기초적인 기능(=유틸리티)들을 관리하는 헤더들
#include "Framework/Utility/Singleton.h"
#include "Framework/Utility/Timer.h"
#include "Framework/Utility/Control.h"
#include "Framework/Utility/Random.h"

//		Buffer Header - DirectX 곳곳에서 셰이더에 정보를 넘길 때 사용하게 될 버퍼를 정의한 헤더들
#include "Framework/Buffer/IndexBuffer.h"
#include "Framework/Buffer/VertexBuffer.h"
#include "Framework/Buffer/ConstBuffer.h"
#include "Framework/Buffer/GlobalBuffer.h"

//		Math Header - DirectX를 넘어 3D 공간과 관련된 수학적 연산을 담당하는 파트
#include "Framework/Math/Vector2.h"
#include "Framework/Math/Transform.h"

//		미분류 - 현 시점에서는 따로 정리해두지 않는 헤더들
#include "Framework/System/Device.h"
#include "Framework/Shader/VertexShader.h"
#include "Framework/Shader/PixelShader.h"



// Object Header - 프로그램에서 이용될 오브젝트들과 관련된 헤더들
#include "Object/Shape/Vertex.h" // 정점이 여기에 정의되어있으므로, 앞으로 정점과 관련된 헤더가 만들어질 경우
// 이 헤더보다는 반드시 뒤에 와야 함
#include "Object/Shape/Shape.h" // 도형 클래스를 여기서 정의하므로,
// 이를 상속받는 다른 클래스들은 이 헤더의 include문보다 반드시 아래에 위치해야 함
//#include "Object/Shape/Triangle.h"
//#include "Object/Shape/Hexagon.h" // 이 둘은 서로 관련되어있지 않으니 어느 순서로 해도 상관없음
//#include "Object/Shape/Star.h"
// 위 셋은 기존에 사용하던 클래스들이며 현재는 프로젝트에서 제외했으니 여기서도 제외

// Envrinomnet Header - 프로그램이 돌아가는 환경을 제어하는 프레임워크
#include "Framework/Environment/Camera.h"
#include "Framework/Environment/Environment.h"

// FrameWork Header - Collision Header - 충돌처리를 다루는 헤더
#include "Framework/Collision/Collider.h"
#include "Framework/Collision/RectCollider.h"
#include "Framework/Collision/CircleCollider.h"

// FrameWork Header - Render Shader -  랜더링할 데이터를 관리(화면에 출력하는데 사용할 이미지 데이터 등을 관리)하는 클래스
// 중간에 정점을 사용하는 부분이 있어서 반드시 정점이 정의된 뒤에 선언되어야 함
#include "Framework/Render/Texture.h"
#include "Framework/Render/Frame.h"
#include "Framework/Render/Clip.h"

//	Shape Header - 도형의 출력을 담당하는 클래스들
#include "Object/Shape/ShapeList.h"
//#include "Object/Shape/SRTTriangle.h"
//#include "Object/Shape/Circle.h"

//	Transform Header - 오브젝트들의 실제 관리를 담당하는 클래스들
#include "Object/Transform/TransformList.h" // 앞으로 Transform으로서 관리할 파일들을
// 헤더에서 쉽게 관리하기 위해,
// 미리 컴파일된 헤더에서는 그냥 놔두고
// 해당 폴더에서 직접 관련 헤더들을 다루는 헤더를 새로 만들어 거기서 관리

//	Skill Header - Transform 클래스의 인스턴스들을 활용한 기능을 담당하는 클래스들
#include "Object/Skill/SkillList.h"

// Spawner Header - Enemy나 Item 등의 생성을 담당하는 클래스들
#include "Object/Spwaner/SpawnerList.h"

// Programe Header - 프로그램에서 실제로 가동하는 부분을 담당하는 헤더들
#include "Scenes/Scene.h"
#include "Scenes/SceneList.h"

#include "Program/Program.h"

// 전역 변수 선언부
extern HWND hWnd;
extern Vector2 mouse_pos;
extern bool isPause;
#endif //PCH_H
