#ifndef RENDER_H_
#define RENDER_H_
#define THREAD_NUM 6u
#include <Windows.h>
#include "vec3.h"
#include "ray.h"
#include "renderParams.h"
#include "sceneManager.h"
#include "displayManager.h"

struct ThreadParams {
	ThreadParams() = default;
	ThreadParams(unsigned _height, unsigned _width, unsigned char* _buffer_ptr, Vec3 _horizontal, Vec3 _vertical, Vec3 _startpos):height(_height), width(_width), horizontal(_horizontal), vertical(_vertical), startpos(_startpos), buffer_ptr(_buffer_ptr) {}
	unsigned height = 0u;
	unsigned width = 0u;
	unsigned char* buffer_ptr = nullptr;
	Vec3 horizontal;
	Vec3 vertical;
	Vec3 startpos;
};

class Render
{
public:

	void RenderBuffer();
	~Render();
private:
	//funaction
	static DWORD WINAPI PartialRender(LPVOID lpParameter);//线程函数
	static Color PathTracing(const Ray& r, const unsigned BOUNCE);//路径追踪函数
	//data
	unsigned char* buffer_ = nullptr;
	static Camera* maincamera_;
	ThreadParams* threadParams_ = nullptr;
	DisplayManager* displayManager_ptr_ = nullptr;
};

Camera* Render::maincamera_ = nullptr;

#endif // !RENDER_H_