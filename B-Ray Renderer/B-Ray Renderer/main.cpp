#include <iostream>
#include "engine.h"

int main(int argc, char* argv[]) {

	Engine BRay;
	if (BRay.StartUp())
	{
		BRay.Run();
	}
	else
	{
		printf("B-ray ��Ⱦ������ʧ��\n");
	}
	printf("B-ray ��Ⱦ�����ڹر�\n");
	BRay.ShutDown();

	return 0;
}