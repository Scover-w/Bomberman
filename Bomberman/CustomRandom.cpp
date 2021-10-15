#include "CustomRandom.h"

CustomRandom::CustomRandom()
{
	srand(time(NULL));
}

CustomRandom::~CustomRandom()
{

}

int CustomRandom::GetRandom(int a, int b)
{
	return rand() % b + a;
}