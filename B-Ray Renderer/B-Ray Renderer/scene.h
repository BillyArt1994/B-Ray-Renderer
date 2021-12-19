#ifndef SCENE_H_
#define SCENE_H_

class Scene {
public:
	//constructor
	Scene() = default;
	//funaction
	bool StartUp(unsigned _id);
	void Update(unsigned int _deltaT);
	//data

};

#endif // !SCENE_H_
