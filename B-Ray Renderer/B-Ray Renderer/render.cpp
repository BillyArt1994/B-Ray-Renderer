#include "render.h"

void Render::RenderBuffer() {
	HANDLE hThread[THREAD_NUM];
	threadParams_ = new ThreadParams[THREAD_NUM];
	for (size_t i = 0; i < THREAD_NUM; i++)
	{
		threadParams_[i] = ThreadParams();
		hThread[i] = CreateThread(NULL, 0, PartialRender, (LPDWORD) & (threadParams_[i]), 0, NULL);
	}
	WaitForMultipleObjects(THREAD_NUM, hThread, TRUE, INFINITE);
}

DWORD WINAPI Render::PartialRender(LPVOID lpParameter) {
	const struct ThreadParams params = *(ThreadParams*)lpParameter;
	const unsigned width = params.width, heigth = params.height;
	float u, v;
	unsigned char* p = params.buffer_ptr;
	for (size_t i = 0; i < heigth; i++)
	{
		for (size_t j = 0; j < width; j++)
		{
			u = float(j)/(params.width - 1);
			v = float(i)/(params.height - 1);
			Vec3 pixelpos();
			Ray r( , pixelpos- maincamera_->transform_.position_);
			Color pixel_color = PathTracing(r,RenderParams::BOUNCE);
			*(p++) = pixel_color.x;
			*(p++) = pixel_color.y;
			*(p++) = pixel_color.z;
		}
	}
	return 0;
}

Color Render::PathTracing(const Ray& r, const unsigned BOUNCE)  {
	return Color(255.0f, 0.0f, 0.0f);
}

Render::~Render() {
	//删除线程参数对象
	delete[] threadParams_;
	threadParams_ = nullptr;
}