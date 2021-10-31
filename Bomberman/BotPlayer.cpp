#include "BotPlayer.h"

//MapEntity* BotPlayer::map = nullptr;

BotPlayer::BotPlayer() : Player()
{

}

BotPlayer::~BotPlayer()
{

}


void BotPlayer::Reset()
{
    Player::Reset();
    Vector2f startPos;

    switch (id)
    {
        case 1:
            startPos = Vector2f(Settings::CARTESIAN_ATOMIC_HEIGHT * 12 + Settings::HALF_CARTESIAN_ATOMIC_HEIGHT, Settings::CARTESIAN_ATOMIC_HEIGHT - Settings::HALF_CARTESIAN_ATOMIC_HEIGHT);
            break;
        case 2:
            startPos = Vector2f(Settings::CARTESIAN_ATOMIC_HEIGHT * 12 + Settings::HALF_CARTESIAN_ATOMIC_HEIGHT, Settings::CARTESIAN_ATOMIC_HEIGHT * 12 + Settings::HALF_CARTESIAN_ATOMIC_HEIGHT);
            break;
        case 3:
            startPos = Vector2f(Settings::CARTESIAN_ATOMIC_HEIGHT - Settings::HALF_CARTESIAN_ATOMIC_HEIGHT, Settings::CARTESIAN_ATOMIC_HEIGHT * 12 + Settings::HALF_CARTESIAN_ATOMIC_HEIGHT);
            break;
    }

    cartPosition = startPos;
    positionIndex = CustomMath::GM_CartCoordFToPosition(cartPosition);

    Vector2f p = CustomMath::GM_CartesianToIsometric(cartPosition);
    image.SetPosition(p);
    shadow.SetPosition(p);
}

void BotPlayer::SetRandomDirection()
{
    int rd = CustomRandom::GetRandom(0, 4);

    switch (rd)
    {
    case 0:
        modelDirection.x = 1;
        modelDirection.y = 0;
        break;
    case 1:
        modelDirection.x = 0;
        modelDirection.y = 1;
        break;
    case 2:
        modelDirection.x = -1;
        modelDirection.y = 0;
        break;
    case 3:
        modelDirection.x = 0;
        modelDirection.y = -1;
        break;
    }
}

void BotPlayer::RemoveBomb()
{
    bombs--;
}

int BotPlayer::Update()
{
    if (isDead)
        return -1;
    int posId = -1;

    if (!hasMoved)
    {
        SetRandomDirection();
    }

    direction.x = modelDirection.x * (speed * Timer::instance->GetDeltaTime());
    direction.y = modelDirection.y * (speed * Timer::instance->GetDeltaTime());

    ManageInvicibility();
    Move();

    if (bombs > 0 && *(map + positionIndex) != MapEntity::Bomb)
    {
        posId = positionIndex;
        RemoveBomb();
    }

    return posId;
}