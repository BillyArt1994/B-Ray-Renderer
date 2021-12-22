#ifndef RENDER_H_
#define RENDER_H_
#define THREAD_NUM 6u
#include <Windows.h>
#include "vec3.h"
#include "ray.h"
struct ThreadParams {
	ThreadParams() = default;
	unsigned height = 0u;
	unsigned width = 0u;
};

class Render
{
public:

	void RenderBuffer();

private:
	//线程函数
	static DWORD WINAPI PartialRender(LPVOID lpParameter);
	//路径追踪函数
	Color PathTracing(const Ray& r , const unsigned BOUNCE)const ;
	//buffer数据
	unsigned char* buffer_ = nullptr;
};


#endif // !RENDER_H_