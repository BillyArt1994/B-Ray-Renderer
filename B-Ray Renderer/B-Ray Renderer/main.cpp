#include <iostream>
#include "vec3.h"
#include "mesh.h"
#include "ray.h"
#include "camera.h"
#include "svpng.h"

int main(int argc, char* argv[]) {


	/*
	//image
	const int nx = 300;
	const int ny = 300;
	//camera
	Camera maincamera(Vec3(0.0f, 0.0f, -5.0f), 1.0f);
	Mesh box("./scene/scene_01/Box.obj");
	const Vec3 horizontal(2.0f, 0.0f, 0.0f);
	const Vec3 vertical(0.0f, 2.0f, 0.0f);
	const Vec3 left_low_corner(-1.0f, -2.0f, maincamera.transform_.position_.z);
	unsigned char* rgb = new unsigned char[nx * ny * 3]{ '\0' };

	for (size_t i = 0; i < nx; i++)
	{
		for (size_t j = 0; j < ny; j++)
		{
			float u = (float)i / (nx - 1);
			float v = (float)j / (ny - 1);
			Vec3 pixelpos(left_low_corner + u * horizontal + v * vertical);
			Ray r(pixelpos, pixelpos- maincamera.transform_.position_);
			float t;
			for (size_t i = 0; i < box.get_face_count_(); i++)
			{
				if (true)
				{

				}
			}
		}
	}

	FILE* fp = fopen("render.png", "wb");
	svpng(fp, nx, ny, rgb, 0);
	*/
	return 0;
}