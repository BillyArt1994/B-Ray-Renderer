#include "render.h"

void Render::RenderBuffer() {
	HANDLE hThread[THREAD_NUM];
	ThreadParams* threadParams = new ThreadParams[THREAD_NUM];
	for (size_t i = 0; i < THREAD_NUM; i++)
	{
		threadParams[i] = ThreadParams();
		hThread[i] = CreateThread(NULL, 0, PartialRender, (LPDWORD) & (threadParams[i]), 0, NULL);
	}
	WaitForMultipleObjects(THREAD_NUM, hThread, TRUE, INFINITE);
}


DWORD WINAPI Render::PartialRender(LPVOID lpParameter) {
	const struct ThreadParams params = *(struct ThreadParams*)lpParameter;
	const unsigned width = params.width, heigth = params.height;
	float u, v;

	for (size_t i = 0; i < heigth; i++)
	{
		for (size_t j = 0; j < width; j++)
		{
			u = float(j)/(params.width - 1);
			v = float(i)/(params.height - 1);
			Color pixel_color = PathTracing();
		}

	}
	return 0;
}

Color Render::PathTracing(const Ray& r, const unsigned BOUNCE) const  {

}