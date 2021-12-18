#ifndef ENGINE_H_
#define ENGINE_H_
#include "displayManager.h"

class Engine {
public:
	//constructor
	Engine() = default;

	//funaction
	bool StartUp();
	void ShutDown();
	void Run();
private:
	//data
	DisplayManager displayManager_;
};

#endif // !ENGINE_H_
