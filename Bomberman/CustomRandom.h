#pragma once
#include <stdlib.h> 
#include <time.h>   
#include <math.h>

class CustomRandom
{
public:
	CustomRandom();
	~CustomRandom();

	static int GetRandom(int, int);
	static float GetPseudoRandom(int i);
};

