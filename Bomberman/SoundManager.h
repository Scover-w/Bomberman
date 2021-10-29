#pragma once
#include <SFML/Audio.hpp>
#include "SoundType.h"
using namespace sf;

class SoundManager
{
private:

	SoundBuffer bufferClick;
	Sound sClick;

	SoundBuffer bufferPowerUp1;
	Sound sPowerUp1;

	SoundBuffer bufferPowerUp2;
	Sound sPowerUp2;

	SoundBuffer bufferPowerUp3;
	Sound sPowerUp3;

	SoundBuffer bufferPowerUp4;
	Sound sPowerUp4;

	SoundBuffer bufferExplosion;
	Sound sExplosion;

	SoundBuffer bufferWin;
	Sound sWin;

	SoundBuffer bufferLose;
	Sound sLose;

public:
	static SoundManager* instance;

	SoundManager();
	~SoundManager();

	void Play(SoundType);
};

