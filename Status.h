#include <chrono>
#include <iostream>
#include "Obstacles.h"
#include "Player.h"
using namespace std;
class Status		
{
public:
	float window_width = 1024, window_height = 768;
	bool gameOver = false;
};