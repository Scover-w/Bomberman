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

float CustomRandom::GetPseudoRandom(int i)
{
    float x = sinf(i / 169.0f) * 10000.0f;
    x = (x - floorf(x)) * 4.0f;

    return x;
}