#ifndef ENGINE_H_
#define ENGINE_H_

class Engine {
public:
	Engine() = default;

	bool StartUp();
	void ShutDown();

	void Run();
};

#endif // !ENGINE_H_
