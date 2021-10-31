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

DirectionBot BotPlayer::CanMoveToCell(int i)
{
    MapEntity tempME = MapEntity::None;
    switch (i)
    {
        case DirectionBot::Up:

            if (positionIndex % Settings::SIZE_GAME_MAP == 0)
                return DirectionBot::No;

            tempME = *(map + (positionIndex - 1));
            return (tempME == MapEntity::None || tempME > MapEntity::Bomb) ? DirectionBot::Up : DirectionBot::No;

        case DirectionBot::Down:

            if (positionIndex % Settings::SIZE_GAME_MAP == Settings::SIZE_GAME_MAP - 1)
                return DirectionBot::No;

            tempME = *(map + (positionIndex + 1));
            return (tempME == MapEntity::None || tempME > MapEntity::Bomb) ? DirectionBot::Down : DirectionBot::No;
        
        case DirectionBot::Left:

            if (positionIndex > 155)
                return DirectionBot::No;

            tempME = *(map + (positionIndex + Settings::SIZE_GAME_MAP));
            return (tempME == MapEntity::None || tempME > MapEntity::Bomb) ? DirectionBot::Left : DirectionBot::No;

        default: //DirectionBot::Right

            if (positionIndex < 13)
                return DirectionBot::No;

            tempME = *(map + (positionIndex - Settings::SIZE_GAME_MAP));
            return (tempME == MapEntity::None || tempME > MapEntity::Bomb) ? DirectionBot::Right : DirectionBot::No;
    }
}

DirectionBot BotPlayer::GetInverseDirection(DirectionBot dBot)
{
    switch (dBot)
    {
        case Up:
            return DirectionBot::Down;
        case Down:
            return DirectionBot::Up;
        case Left:
            return DirectionBot::Right;
        case Right:
            return DirectionBot::Left;
    }
}

void BotPlayer::SetRandomDirection()
{
    DirectionBot tempDir;
    int j = 0;
    for (int i = 0; i < 4; i++)
    {
        tempDir = CanMoveToCell(i);
        if (tempDir != DirectionBot::No)
        {
            potentialDirections[j] = tempDir;
            j++;
        }
    }

    DirectionBot selectedDirection;

    if (j == 0)
    {
        selectedDirection = static_cast<DirectionBot>(CustomRandom::GetRandom(0, 4));
    }
    else if(j == 1)
    {
        selectedDirection = potentialDirections[0];
    }
    else
    {
        do
        {
            int rd = CustomRandom::GetRandom(0, j);
            selectedDirection = potentialDirections[rd];
        } while (selectedDirection == GetInverseDirection(modelDirection));
    }

    modelDirection = selectedDirection;

    switch (modelDirection)
    {
        case DirectionBot::Up:
            modelDirectionV.x = -1;
            modelDirectionV.y = 0;
            break;
        case DirectionBot::Down:
            modelDirectionV.x = 1;
            modelDirectionV.y = 0;
            break;
        case DirectionBot::Left:
            modelDirectionV.x = 0;
            modelDirectionV.y = 1;
            break;
        case DirectionBot::Right:
            modelDirectionV.x = 0;
            modelDirectionV.y = -1;
            break;
    }
}

void BotPlayer::RemoveBomb()
{
    bombs--;
}

bool BotPlayer::IsInMiddleCell()
{
    int xNb = positionIndex % Settings::SIZE_GAME_MAP;
    int yNb = positionIndex / Settings::SIZE_GAME_MAP;
    Vector2f middlePosition = Vector2f(cartPosition.x - xNb * Settings::CARTESIAN_ATOMIC_HEIGHT, cartPosition.y - yNb * Settings::CARTESIAN_ATOMIC_HEIGHT);

    middlePosition.x = abs(middlePosition.x - Settings::HALF_CARTESIAN_ATOMIC_HEIGHT);
    middlePosition.y = abs(middlePosition.y - Settings::HALF_CARTESIAN_ATOMIC_HEIGHT);

    if (middlePosition.x < 20.0f && middlePosition.y < 20.0f)
        return true;

    return false;
}

void BotPlayer::SetInverseDirection()
{
    modelDirectionV *= -1;
}

int BotPlayer::Update()
{
    if (isDead)
        return -1;
    int posId = -1;

    if (!hasMoved)
    {
        SetInverseDirection();
    }

    bool middleCell = IsInMiddleCell();
    if (middleCell && !risingMiddleCell)
    {
        risingMiddleCell = true;
        SetRandomDirection();
        if (bombs > 0 && *(map + positionIndex) != MapEntity::Bomb)
        {
            posId = positionIndex;
            RemoveBomb();
        }
    }
    else if (!middleCell)
        risingMiddleCell = false;

    direction.x = modelDirectionV.x * (speed * Timer::instance->GetDeltaTime());
    direction.y = modelDirectionV.y * (speed * Timer::instance->GetDeltaTime());

    ManageInvicibility();
    Move();

    

    return posId;
}