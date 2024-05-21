#include "framework.h"


Program::Program()
{
	Create();	// �ϼ�
	scenes.push_back(new TestScene());
	scenes.push_back(new AnimateScene());
	scene_idx = 0;
	// �� ���α׷��� ����� Scene�� �����ϴ� �κ�
	// scene ��ü�� �Ŀ� ����
}

Program::~Program()
{
	for (auto s : scenes)
		delete s;
}

void Program::Update()
{
	if (KEY_CON->Down(VK_DELETE))
	{
		++scene_idx %= 2;
	}
	Control::Get()->Update();
	Timer::Get()->Update();
	// ��ƿ��Ƽ�� �ٷ�� �̱��� ��ü���� ������Ʈ�� ������ ���� ������Ʈ
	
	if (KEY_CON->Down(VK_F9))
		Collider::SetDebugMode();

	scenes[scene_idx]->Update();
	CAM->Update();
}

void Program::Render()
{
	Device::Get()->Clear();
	// Scene�� ����ϱ� ���� ȭ���� �ʱ�ȭ��Ű�� �۾�

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	// ���� 2���� DX11 / WIN �ü������ �� ������(=â)�� ����ڴٰ� �˸��� �Լ�
	// �׷��� ������ ���� ���� ������ ����°� ���� NewFrame �Լ�

	string fps = "FPS : " + to_string(Timer::Get()->GetFPS());
	ImGui::Text(fps.c_str());
	ImGui::Text("Total Run Time : %f", Timer::Get()->GetRunTime());
	// Text : ImGui �� printf
	// �̸� �̿��� ����׿� â�� ����� ������ ����

	scenes[scene_idx]->Render();
	// Scene�� ������
	// ������(Rendering) : �׷��� ���α׷��ֿ��� ������Ʈ�� ȭ�鿡 ����� �� �ֵ��� �����δ� ���� ����

	scenes[scene_idx]->PostRender();

	ImGui::Render();	// ImGui ��ü�� �������ϴ� �Լ�
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	// ImGui ������ ���޵� �����͵���, �������� ��ü(-â)���� ǥ���� �� �ֵ��� ������ִ� �Լ�

	Device::Get()->Present();
	// ����ۿ� �������� ���� �������� �̸� ������� ȭ��� �����Ͽ� ������۸� ó���� ����
	// ���������� ���⼭ ȭ�� ����� ���� �� �Ϸᰡ ��

}

void Program::Create()
// ���α׷��� ó�� ��������� �� ���� �����Ű�� �ʱ�ȭ���Ѿ� �� ������� ��Ƶ� �Լ�
// ���������δ� �����ڳ� ������������, ���߿� �����ڿ��� �� �κ� �ܿ��� �߰������� ���� ������ ���Ƽ�
// �̸��� �и����ѵдٴ� �������� ������ ��
{
	Device::Get();
	// �̱��� ��ü�� Device�� ���� �ʱ�ȭ�� ���ÿ� ����

	Control::Get();
	Timer::Get();
	// ���������� �̱������� �����Ǿ�� �� �ν��Ͻ����� ���⼭ �ʱ�ȭ�� ���ÿ� ����

	Environment::Get();

	ImGui::CreateContext(); // ImGui ��ü�� ������ �Լ�
	ImGui::StyleColorsClassic(); // StyleColorsDark() - ��������� ImGui â�� ������ ������ ������� �����ϴ� �Լ�
	// Light, Classic�� �����Ƿ� ���ϴ� �׸��� �̿����ָ� ��

	ImGui_ImplDX11_Init(DEVICE, DVC);
	// DX11 ȯ�濡�� ����ϴ� ImGui��� ����
	ImGui_ImplWin32_Init(hWnd);
	// ������ �ü������ ����ϴ� ImGui��� ����
	// �̷��� �� 4���� �̿��� �� ���α׷����� ImGui�� ����ϰڴ� ���� �� �ʱ�ȭ
}

void Program::Delete()
{
	Device::Delete();
	Control::Delete();
	Timer::Delete();
}


