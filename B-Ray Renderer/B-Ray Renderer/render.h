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
	//�̺߳���
	static DWORD WINAPI PartialRender(LPVOID lpParameter);
	//·��׷�ٺ���
	Color PathTracing(const Ray& r , const unsigned BOUNCE)const ;
	//buffer����
	unsigned char* buffer_ = nullptr;
};


#endif // !RENDER_H_