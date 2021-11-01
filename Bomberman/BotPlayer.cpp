#include "BotPlayer.h"


BotPlayer::BotPlayer() : Player()
{

}
BotPlayer::~BotPlayer()
{

}

#pragma region Private
bool BotPlayer::IsInMiddleCell()
{
    int xNb = positionIndex % Settings::SIZE_GAME_MAP;
    int yNb = positionIndex / Settings::SIZE_GAME_MAP;
    Vector2f middlePosition = Vector2f(cartPositionV2f.x - xNb * Settings::CARTESIAN_ATOMIC_HEIGHT, cartPositionV2f.y - yNb * Settings::CARTESIAN_ATOMIC_HEIGHT);

    middlePosition.x = abs(middlePosition.x - Settings::HALF_CARTESIAN_ATOMIC_HEIGHT);
    middlePosition.y = abs(middlePosition.y - Settings::HALF_CARTESIAN_ATOMIC_HEIGHT);

    if (middlePosition.x < 20.0f && middlePosition.y < 20.0f)
        return true;

    return false;
}
void BotPlayer::SetInverseDirection()
{
    modelDirectionV2i *= -1;
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
    else if (j == 1)
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
            modelDirectionV2i.x = -1;
            modelDirectionV2i.y = 0;
            break;
        case DirectionBot::Down:
            modelDirectionV2i.x = 1;
            modelDirectionV2i.y = 0;
            break;
        case DirectionBot::Left:
            modelDirectionV2i.x = 0;
            modelDirectionV2i.y = 1;
            break;
        case DirectionBot::Right:
            modelDirectionV2i.x = 0;
            modelDirectionV2i.y = -1;
            break;
    }
}

bool BotPlayer::AskPutBomb()
{
    if (bombs <= 0)
        return false;

    int j = 0;
    for (int i = 0; i < 4; i++)
    {
        if (IsDestroyableOrPlayerAround(i))
            return true;
    }
    return false;
}
void BotPlayer::RemoveBomb()
{
    bombs--;
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

bool BotPlayer::IsDestroyableOrPlayerAround(int i)
{
    int tempPosIndex;
    switch (i)
    {
    case DirectionBot::Up:

        if (positionIndex % Settings::SIZE_GAME_MAP == 0)
            return false;

        tempPosIndex = positionIndex - 1;
        break;

    case DirectionBot::Down:

        if (positionIndex % Settings::SIZE_GAME_MAP == Settings::SIZE_GAME_MAP - 1)
            return false;

        tempPosIndex = positionIndex + 1;
        break;

    case DirectionBot::Left:

        if (positionIndex > 155)
            return false;

        tempPosIndex = positionIndex + Settings::SIZE_GAME_MAP;
        break;

    default: //DirectionBot::Right

        if (positionIndex < 13)
            return false;

        tempPosIndex = positionIndex - Settings::SIZE_GAME_MAP;
        break;
    }

    if (*(map + (tempPosIndex)) == MapEntity::DBlock)
        return true;

    if (player->GetPositionIndex() == tempPosIndex)
        return true;

    return false;
}
#pragma endregion


#pragma region Public
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

    cartPositionV2f = startPos;
    positionIndex = CustomMath::GM_CartCoordFToPosition(cartPositionV2f);

    Vector2f p = CustomMath::GM_CartesianToIsometric(cartPositionV2f);
    image.SetPosition(p);
    shadowImg.SetPosition(p);
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
        if (AskPutBomb())
        {
            RemoveBomb();
            posId = positionIndex;
        }
    }
    else if (!middleCell)
        risingMiddleCell = false;

    directionV2f.x = modelDirectionV2i.x * (speed * Timer::instance->GetDeltaTime());
    directionV2f.y = modelDirectionV2i.y * (speed * Timer::instance->GetDeltaTime());

    ManageInvicibility();
    Move();



    return posId;
}
#pragma endregion





