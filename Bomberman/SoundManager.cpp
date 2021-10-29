#include "SoundManager.h"

SoundManager* SoundManager::instance;

SoundManager::SoundManager()
{
	instance = this;

	bufferClick.loadFromFile("Sound/BoutonClick.wav");
	bufferPowerUp1.loadFromFile("Sound/PowerUp1.wav");
	bufferPowerUp2.loadFromFile("Sound/PowerUp2.wav");
	bufferPowerUp3.loadFromFile("Sound/PowerUp3.wav");
	bufferPowerUp4.loadFromFile("Sound/PowerUp4.wav");
	bufferExplosion.loadFromFile("Sound/Explosion.wav");
	bufferWin.loadFromFile("Sound/Win.wav");
	bufferLose.loadFromFile("Sound/KillVoice.wav");

	sClick.setBuffer(bufferClick);
	sPowerUp1.setBuffer(bufferPowerUp1);
	sPowerUp2.setBuffer(bufferPowerUp2);
	sPowerUp3.setBuffer(bufferPowerUp3);
	sPowerUp4.setBuffer(bufferPowerUp4);
	sExplosion.setBuffer(bufferExplosion);
	sWin.setBuffer(bufferWin);
	sLose.setBuffer(bufferLose);
}

SoundManager::~SoundManager()
{

}

void SoundManager::Play(SoundType type)
{
	switch (type)
	{
	case SoundType::Click:
			sClick.play();
			break;
		case SoundType::PowerUp1:
			sPowerUp1.play();
			break;
		case SoundType::PowerUp2:
			sPowerUp2.play();
			break;
		case SoundType::PowerUp3:
			sPowerUp3.play();
			break;
		case SoundType::PowerUp4:
			sPowerUp4.play();
			break;
		case SoundType::Explosion:
			sExplosion.play();
			break;
		case SoundType::Win:
			sWin.play();
			break;
		case SoundType::Lose:
			sLose.play();
			break;
	}
}