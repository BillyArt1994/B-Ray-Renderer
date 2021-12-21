#include "engine.h"

bool Engine::StartUp() {
	bool success = true;
	if (!displayManager_.StartUp())
	{
		success = false;
		printf("��ʾ����ϵͳ����ʧ��... \n");
	}
	else if (!inputManager_.StartUp())
	{
		success = false;
		printf("�������ϵͳ����ʧ��... \n");
	}
	else if(!sceneManager_.StartUp())
	{
		success = false;
		printf("��������ϵͳ����ʧ��... \n");
	}
	else if (!renderManager_.StartUp(sceneManager_,displayManager_))
	{
		success = false;
		printf("��Ⱦ����ϵͳ����ʧ��... \n");
	}
	return true;
}

void Engine::ShutDown() {

}

void Engine::Run() {
	bool flag = false;

	unsigned render_count = 0u;
	unsigned start_clock = 0u;
	unsigned delta_time = 0u;

	while (!flag)
	{
		//������Ⱦ�ܴ���
		++render_count;
		//����������
		inputManager_.ProcessInput(flag);
		//������������
		sceneManager_.Update(delta_time);
		//ִ����Ⱦ
		renderManager_.Render();
		//��ӡ֡��
		delta_time = SDL_GetTicks() - start_clock;
		printf("����Ⱦ���� %2.1d: ֡�� (ms):%d\n", render_count, delta_time);
	}
}