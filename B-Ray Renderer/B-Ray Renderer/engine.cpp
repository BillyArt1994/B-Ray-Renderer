#include "engine.h"

bool Engine::StartUp() {
	bool success = true;
	if (!displayManager_.StartUp())
	{
		success = false;
		printf("显示管理系统启动失败... \n");
	}
	else if (!inputManager_.StartUp())
	{
		success = false;
		printf("输入管理系统启动失败... \n");
	}
	else if(!sceneManager_.StartUp())
	{
		success = false;
		printf("场景管理系统启动失败... \n");
	}
	else if (!renderManager_.StartUp(sceneManager_,displayManager_))
	{
		success = false;
		printf("渲染管理系统启动失败... \n");
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
		//计算渲染总次数
		++render_count;
		//检测输入操作
		inputManager_.ProcessInput(flag);
		//场景更新数据
		sceneManager_.Update(delta_time);
		//执行渲染
		renderManager_.Render();
		//打印帧率
		delta_time = SDL_GetTicks() - start_clock;
		printf("总渲染次数 %2.1d: 帧率 (ms):%d\n", render_count, delta_time);
	}
}