#include "render.h"

void Render::RenderBuffer() {
	HANDLE hThread[THREAD_NUM];
	threadParams_ptr_ = new ThreadParams[THREAD_NUM];
	unsigned height(0), width(0);

	for (size_t i = 0; i < THREAD_NUM; i++)
	{
		height = displayManager_ptr_->SCREEN_HEIGHT;
		width = displayManager_ptr_->SCREEN_WIDTH;
		Vec3 vertical(maincamera_ptr_->vertical_ / THREAD_NUM);
		threadParams_ptr_[i] = ThreadParams(
			height,
			width,
			buffer_ + i * height * width * 3u,
			maincamera_ptr_->horizontal_,
			vertical,
			maincamera_ptr_->low_left_corner_ + i * vertical
		);
		hThread[i] = CreateThread(NULL, 0, PartialRender, (LPDWORD) & (threadParams_ptr_[i]), 0, NULL);
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
			Vec3 pixelpos(params.startpos+ params.horizontal * u + params.vertical * v);
			Ray r(pixelpos, pixelpos- maincamera_ptr_->transform_.position_);
			Color pixel_color = PathTracing(r,RenderParams::BOUNCE);
			*(p++) = pixel_color.x;
			*(p++) = pixel_color.y;
			*(p++) = pixel_color.z;
		}
	}
	return 0;
}

Color Render::PathTracing(const Ray& r, const unsigned BOUNCE)  {
	
		if (globaloctree_ptr_->Intersect(r))
		{
			return Color(255.0f, 0.0f, 0.0f);
		}
	return Color(255.0f, 255.0f, 255.0f);
}

Render::~Render() {
	//删除线程参数对象
	delete[] threadParams_ptr_;
	threadParams_ptr_ = nullptr;
}