#include <iostream>
#include "engine.h"

int main(int argc, char* argv[]) {

	Engine BRay;
	if (BRay.StartUp())
	{
		//内部执行循环渲染
		BRay.Run();
	}
	else
	{
		printf("B-ray 渲染器启动失败\n");
	}
	printf("B-ray 渲染器正在关闭\n");
	BRay.ShutDown();

	return 0;
}