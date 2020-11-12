#pragma once

#include <thread>
#include <mutex>

class GameObjectData {

public:
	GameObjectData();
	~GameObjectData();

	int postX;
	std::mutex lock;
};
