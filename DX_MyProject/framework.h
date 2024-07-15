// framework.h: �̸� �����ϵ� ��� �����Դϴ�.
// �Ʒ� ������ ������ �� ���� �����ϵǾ�����, ���� ���忡 ���� ���� ������ ����մϴ�.
// �ڵ� ������ �� ���� �ڵ� �˻� ����� �����Ͽ� IntelliSense ���ɿ��� ������ ��Ĩ�ϴ�.
// �׷��� ���⿡ ������ ������ ���� �� ������Ʈ�Ǵ� ��� ��� �ٽ� �����ϵ˴ϴ�.
// ���⿡ ���� ������Ʈ�� ������ �߰����� ������. �׷��� ������ ���ϵ˴ϴ�.

// �̸� �����ϵ� ��� : ���α׷��� �����ϱ� ���� ��� ���ϵ鸸�� �̸� �������Ͽ�
// �������μ� �����ε��� �����ص� ��
// �̸� �����ϵ� ����� ����� ��� �� ��� �ȿ� �ִ� ������� ������Ʈ�� ����Ǳ� ���� �̸� �������μ� �����ϵǾ�
// .pch �������� ��������� �ǰ�,
// �� ������ �����ϵ� ��� ��ü�� ���������� ������ �ʴ� �̻� ���� �����ϵ� �� ������� �������� �����ϰ�
// �� ���Ͽ��� �� ����� ������� ������ ����� �� �ֵ��� �ϴ� ������ ��

// ����ϴ� ������ ũ�� 2����
// 1) �̸� �����ϵ� ����� ������Ʈ ��ü���� ����ϴ� ���̱� ������,
// �� ���Ͽ��� �� �̸� �����ϵ� ����� ����ϰڴٰ� ����صα⸸ �ϸ�
// ������� Ư�� ����� ���Խ�Ű���� ���� �ʰ� �̸� �����ϵ� ��� ���ο� �ִ� ������ ���� ������ �� �� ����

// 2) �⺻������ �ϳ��� ������Ʈ���� ���Խ�Ű�� ����� ���� �ƹ��� ���� ��Ƶ� ���ʰ� ������ �Ǹ�,
// �� Ŀ�ٶ� ������Ʈ�� ��쿣 100�� ������ ������ �Ѿ�� ��찡 ���η���
// �̷� �͵��� �Ź� �������� ��� �ð��� �ɷ��� ���� ���� �ɸ��� ��
// �׷��� ���� �������ϰ� �� ������� ���� ������ �������μ� �̸� �����ΰ� �̸� �ΰ�ΰ� ���ٸ�
// �����Ͽ� �ɸ��� �ð��� �ſ� ũ�� ����ǹǷ� �̿��Ѵ� ��

#ifndef PCH_H
#define PCH_H

// ���⿡ �̸� �������Ϸ��� ��� �߰�
#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����
#include <windows.h>
#include <windowsx.h>

// ���� ��ũ�� ����� �����ϴ� ����

#define WIN_START_X 100
#define WIN_START_Y 100
// ������ â�� ó���� ���� �� ��� ��ġ���� �������� ������ ��ũ��

#define WIN_WIDTH 1280
#define WIN_HEIGHT 720

#define WIN_CENTER_X (WIN_WIDTH * 0.5f)
#define WIN_CENTER_Y (WIN_HEIGHT * 0.5f)
#define WIN_CENTER (Vector2(WIN_CENTER_X,WIN_CENTER_Y))
// ȭ�� �߾��� ��ǥ�� ��ũ�ημ� �ս��� �̿��� �� �ֵ��� ����

#define GRAVITY 98.0f // �߷��� ���⿡ �����صּ�
// �ٸ� ���� ������Ʈ���� �� ���� �̿��� �� �ֵ��� ������

// �⺻ �̵� �ӵ��� ��ũ�η� ����� ����
#define defaultSPD 100.0f

// ��ü ȭ���� Ư���� ĭ���� ������ ���� ĭ�� ũ�� ��
#define CELL_X 100
#define CELL_Y 100

// FixedUpdate ����
#define FIXED_INTERVAL 0.02f

// ���� ��ũ�� ���๮�� �����ϴ� ����
#define DEVICE (Device::Get()->GetDevice())
#define DVC (Device::Get()->GetDeviceContext())

#define DELTA (Timer::Get()->GetDeltaTime())
#define FPS (Timer::Get()->GetFPS())

#define KEY_CON (Control::Get())

#define CAM Environment::Get()->GetMainCamera()
#define LERP(s,e,t) (s+(e-s)*t)

// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <vector>
#include <unordered_map>
#include <string>
#define _USE_MATH_DEFINES // �ﰢ�� �ٷ�� ����, �ű⿡ ���� pi�� ����ϰڴ� ����
#include <math.h>
#include <random>
#include <map>
#include <set>

// DirectX11 ���� ���̺귯��
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dcompiler.lib")
// ���� ������� ���� DirectX���� ����ϴ� ��ɵ��� ������

#pragma comment(lib, "dxguid.lib")
#include "../DirectXTex/DirectXTex.h"
// DirectTex�� ����ϱ� ���� �߰��ϴ� ���̺귯��
// ���⼭�� ..�� "���� ����(=�⺻ ����)���� �� �ܰ� ���� ������ �ö󰡶�� �ǹ�

// ������Ʈ ������ �������� �ش� ������Ʈ�� üũ�Ͽ� �����ص� �ȴٰ� �㰡�� �ؾ߸�
// �̷��� �ٸ� ������Ʈ�� �ִ� ������ �ҷ��� �� ����
// �׷��� ������ ������ �� �ִ� ���ϴ� �ο����� �ʾ� ������ ������ �߻�

#include "../ImGui/imgui.h"
#include "../ImGui/imgui_impl_win32.h"
#include "../ImGui/imgui_impl_dx11.h"
/*
* ImGui ������Ʈ�� github���� �ٿ� �޾� ������ ���� Ǭ��
* ImGui-master��� ������ ������ ��
* ImGui ������Ʈ ���� �ȿ� �����ϴ� Backend���� ���� ����ϴ� OS�� �ش�(���� win32)�ϴ� .cpp, .h ������� ���ϰ�
* ���� ����ϴ� DX ������ �ش��ϴ� ���ϸ��� .cpp�� .h ������ �����ؼ�
* ImGui-master �ȿ� �ٿ��ִ´�.
* ImGui-master�� �����ϴ� ��� .cpp�� .h ������ �����Ѵ�
* ���� ������Ʈ�� ���Ե� �ַ�ǿ� �� ������Ʈ�� �����Ѵ�
* �� ������Ʈ�� ������ ������ �ٿ��ְ� ������Ʈ�� ���Խ�Ų��.
* 
* �ش� ������Ʈ�� �Ӽ� - �����Ӽ� - �Ϲ� - �������Ŀ��� ���� ���̺귯���� �����ϰ� �����Ų��
* ���� ������Ʈ�� �߰� - ���� �� �� ������Ʈ(������ �ٿ����� ������Ʈ)�� �����ϵ����Ѵ�.
*/
/*
* ���� 3���� Imgui��� �ܺ� ���̺귯���� �̿��ϱ� ���� �ʿ��� ����
* ImGui : ���α׷��� ���� �з����� ���� �ս��� ����� �� �ְ� ������ִ� Graphic User Interface
* �����δ� ������� �� �� ���� �з����͸� ���� Ȯ���Ϸ��� �뵵�� ����� ����
* 
* ����ϱ� ���� �ʿ��� ���� - ���� ����
1. ImGui�� ���� �˻��ؼ� ������ GitHub���� ��ü ������ �ٿ�ް� �ƹ��͵� ���� �ƹ� ������ Ǯ��
(Code -> Download ZIP)
2. ������ Ǭ �������� ImGui_master/backend/ ��������
imgui_impl_dx11.h & cpp
imgui_impl_win32.h & cpp
�� 4�� ������ ImGui_master ������ ����
3. ImGui_master ������ �ִ� ��� cpp, h ������ �����Ͽ�
�ٸ� ������ ������ �غ� ��ġ��
4. ���� �� ������Ʈ ��ü�� �⺻ ������ �� ���� Library�� ����,
3���� ������ ������ �ش� ������ ������ ImGui ������ ����� �ٿ��ֱ�
5. �̷��� �߰��� ���ϵ��� ������Ʈ�� ����
6. ���� �ۼ��� Include ��ó������ 3�� �ۼ�
7. Ȥ�ó� �߰��� cpp ���ϵ��� �̸� �����ϵ� ����� ����ϵ��� �����Ǿ� ������ ��� �������� ����
*/
using namespace std;
using namespace DirectX;

// �������� �� (�̸� �����ϵ�) ����� ���� ���̺귯������ ����ؼ� �߰��� ���ε�
// �߰��ϴ� ������ ���� ������ �߻��ϴ� ��찡 �����
// ���� �� ����� ��� �߰��Ǵ����� ��Ȯ�� �ľ��ϰ� �־���� ��

// �̸� �����ϵ� ����� ���� ��쿣 �� ����� �ִ� ������� ������Ʈ���� ���� ���Ե� ��ó�� �ν��ϰ� ��
// �׷��� ������ Ŀ���ϵ� ���� ��Ÿ ����� ���������� �� ����� �� ���������� �����ϱ� ������,
// ���� �������� ���� ���� ����� ������ ����ϴ� ����� �� ���ʿ� ���ԵǾ��� ��� ������ �߻�
// ���� ����� ������ �ִ��� ������� ���������� ���α׷��� ����Ǳ� ������,
// ���⿡ ����� �߰��� ���� ������ �ִ��� �����ؼ� �־�� ��

typedef XMFLOAT4 Float4;
typedef XMFLOAT3 Float3;
typedef XMFLOAT2 Float2;
// XMFLOAT : DX���� ���Ǵ�, �Ǽ��� N����ŭ ������� ����ü

typedef XMMATRIX Matrix;
// XMMATRIX : DX���� ���Ǵ�, ���� ������ ������ ������ �� �ִ� ���Ͽ� ����ü
// ���Ͽ�(Union) : 2���� �̻��� �ڷ����� ���ο� ������ �־,
// ������ �� �Էµ� �����Ϳ� ���� ���������� �ڷ����� �����Ǵ� ����ü
// �� Matrix�� �⺻������ 4x4 ũ���� ����� �ٷ��, DirectX���� ����� �̿��� �� �� �ڷ����� �䱸�ϱ� ������
// �̸� ��������

// Framework Header - ���α׷��� �����ϴ� �� �־� ���밡 �Ǹ� �츮�� ������ ���̺귯��

//		Utility Header - ���α׷� �������⼭ ����� �������� ���(=��ƿ��Ƽ)���� �����ϴ� �����
#include "Framework/Utility/Singleton.h"
#include "Framework/Utility/Timer.h"
#include "Framework/Utility/Control.h"
#include "Framework/Utility/Random.h"

//		Buffer Header - DirectX �������� ���̴��� ������ �ѱ� �� ����ϰ� �� ���۸� ������ �����
#include "Framework/Buffer/IndexBuffer.h"
#include "Framework/Buffer/VertexBuffer.h"
#include "Framework/Buffer/ConstBuffer.h"
#include "Framework/Buffer/GlobalBuffer.h"

//		Math Header - DirectX�� �Ѿ� 3D ������ ���õ� ������ ������ ����ϴ� ��Ʈ
#include "Framework/Math/Vector2.h"
#include "Framework/Math/Transform.h"

//		�̺з� - �� ���������� ���� �����ص��� �ʴ� �����
#include "Framework/System/Device.h"
#include "Framework/Shader/VertexShader.h"
#include "Framework/Shader/PixelShader.h"



// Object Header - ���α׷����� �̿�� ������Ʈ��� ���õ� �����
#include "Object/Shape/Vertex.h" // ������ ���⿡ ���ǵǾ������Ƿ�, ������ ������ ���õ� ����� ������� ���
// �� ������ٴ� �ݵ�� �ڿ� �;� ��
#include "Object/Shape/Shape.h" // ���� Ŭ������ ���⼭ �����ϹǷ�,
// �̸� ��ӹ޴� �ٸ� Ŭ�������� �� ����� include������ �ݵ�� �Ʒ��� ��ġ�ؾ� ��
//#include "Object/Shape/Triangle.h"
//#include "Object/Shape/Hexagon.h" // �� ���� ���� ���õǾ����� ������ ��� ������ �ص� �������
//#include "Object/Shape/Star.h"
// �� ���� ������ ����ϴ� Ŭ�������̸� ����� ������Ʈ���� ���������� ���⼭�� ����

// Envrinomnet Header - ���α׷��� ���ư��� ȯ���� �����ϴ� �����ӿ�ũ
#include "Framework/Environment/Camera.h"
#include "Framework/Environment/Environment.h"

// FrameWork Header - Collision Header - �浹ó���� �ٷ�� ���
#include "Framework/Collision/Collider.h"
#include "Framework/Collision/RectCollider.h"
#include "Framework/Collision/CircleCollider.h"

// FrameWork Header - Render Shader -  �������� �����͸� ����(ȭ�鿡 ����ϴµ� ����� �̹��� ������ ���� ����)�ϴ� Ŭ����
// �߰��� ������ ����ϴ� �κ��� �־ �ݵ�� ������ ���ǵ� �ڿ� ����Ǿ�� ��
#include "Framework/Render/Texture.h"
#include "Framework/Render/Frame.h"
#include "Framework/Render/Clip.h"

//	Shape Header - ������ ����� ����ϴ� Ŭ������
#include "Object/Shape/ShapeList.h"
//#include "Object/Shape/SRTTriangle.h"
//#include "Object/Shape/Circle.h"

//	Transform Header - ������Ʈ���� ���� ������ ����ϴ� Ŭ������
#include "Object/Transform/TransformList.h" // ������ Transform���μ� ������ ���ϵ���
// ������� ���� �����ϱ� ����,
// �̸� �����ϵ� ��������� �׳� ���ΰ�
// �ش� �������� ���� ���� ������� �ٷ�� ����� ���� ����� �ű⼭ ����

//	Skill Header - Transform Ŭ������ �ν��Ͻ����� Ȱ���� ����� ����ϴ� Ŭ������
#include "Object/Skill/SkillList.h"

// Spawner Header - Enemy�� Item ���� ������ ����ϴ� Ŭ������
#include "Object/Spwaner/SpawnerList.h"

// Programe Header - ���α׷����� ������ �����ϴ� �κ��� ����ϴ� �����
#include "Scenes/Scene.h"
#include "Scenes/SceneList.h"

#include "Program/Program.h"

// ���� ���� �����
extern HWND hWnd;
extern Vector2 mouse_pos;
extern bool isPause;
#endif //PCH_H
