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
		printf("B-ray äÖÈ¾Æ÷Æô¶¯Ê§°Ü\n");
	}
	printf("B-ray äÖÈ¾Æ÷ÕıÔÚ¹Ø±Õ\n");
	BRay.ShutDown();

	return 0;
}