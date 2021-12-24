#ifndef RENDER_H_
#define RENDER_H_
#define THREAD_NUM 6u
#include <Windows.h>
#include "vec3.h"
#include "ray.h"
#include "renderParams.h"
#include "sceneManager.h"

struct ThreadParams {
	ThreadParams() = default;
	unsigned height = 0u;
	unsigned width = 0u;
	unsigned char* buffer_ptr = nullptr;
};

class Render
{
public:

	void RenderBuffer();

private:
	//funaction
	static DWORD WINAPI PartialRender(LPVOID lpParameter);//线程函数
	static Color PathTracing(const Ray& r, const unsigned BOUNCE);//路径追踪函数
	//data
	unsigned char* buffer_ = nullptr;
	static Camera* maincamera_;
	ThreadParams* threadParams_ = nullptr;
};

Camera* Render::maincamera_ = nullptr;

#endif // !RENDER_H_