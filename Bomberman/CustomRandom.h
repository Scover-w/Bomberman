#pragma once
#include <stdlib.h> 
#include <time.h>   

class CustomRandom
{
public:
	CustomRandom();
	~CustomRandom();

	static int GetRandom(int, int);
};

