#include "Player.h"
#include "CustomMath.h"


sf::Vector2i Player::upRightCorner(10, -10);
sf::Vector2i Player::downLeftCorner(-10, 10);

Player::Player()
{
    image.SetTexture("Images/Player/SpriteSheetPlayer.png");
    image.SetOrigin(77, 128);
    maskSprite.height = 171;
    maskSprite.width = 156;
}

Player::~Player()
{

}

void Player::SetDirectionAnimationVector2i()
{
    if (direction.x < -0.0001f) // Right
    {
        directionAnimationV2i.x = 1;
        directionAnimationV2i.y = 0;
    }
    else if (direction.x > 0.0001f) // Left
    {
        directionAnimationV2i.x = 0;
        directionAnimationV2i.y = 1;
    }
    else if (direction.y > 0.0001f) // Up
    {
        directionAnimationV2i.x = 1;
        directionAnimationV2i.y = 1;
    }
    else if (direction.y < -0.0001f) // Down
    {
        directionAnimationV2i.x = 0;
        directionAnimationV2i.y = 0;
    }
    else
    {
        directionAnimationV2i.x = 0;
        directionAnimationV2i.y = 1;
    }
}

void Player::DeltaAnimation()
{
    animation += Timer::instance->GetDeltaTime();

    if (!isAlive)
        return;

    if (animation > 0.8f)
        animation -= .8f;
}

int Player::GetStateAnimation()
{
    DeltaAnimation();
    
    if (!Keyboard::isKeyPressed(Keyboard::Left) && !Keyboard::isKeyPressed(Keyboard::Right) 
        && !Keyboard::isKeyPressed(Keyboard::Up) && !Keyboard::isKeyPressed(Keyboard::Down))
    {
        return 0;
    }

    if (animation < 0.1f)
        return 0;
    else if (animation < 0.2f)
        return 1;
    else if (animation < 0.3f)
        return 2;
    else if (animation < 0.4f)
        return 3;
    else if (animation < 0.5f)
        return 4;
    else if (animation < 0.6f)
        return 5;
    else if (animation < 0.7f)
        return 6;
    else if (animation < 0.8f)
        return 7;
}

int Player::GetDeltaXPlayer(int i)
{
    if (i % 2)
        return upRightCorner.x;
    else
        return downLeftCorner.x;
}

int Player::GetDeltaYPlayer(int i)
{
    if (i % 2)
        return upRightCorner.y;
    else
        return downLeftCorner.y;
}

void Player::GetFuturPosPlayer(Vector2f pos)
{
    int k = 0;
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            sf::Vector2i posInt;
            posInt.x = (pos.x + GetDeltaXPlayer(i)) / Settings::CARTESIAN_ATOMIC_HEIGHT;
            posInt.y = (pos.y + GetDeltaYPlayer(j)) / Settings::CARTESIAN_ATOMIC_HEIGHT;

            futurPosPlayerId[k] = posInt.y * 13 + posInt.x;
            k++;
        }
    }
}

int Player::GetStateAnimationDeath()
{
    DeltaAnimation();

    if (animation < 0.125f)
        return 0;
    else if (animation < 0.25f)
        return 1;
    else if (animation < 0.375f)
        return 2;
    else
        return 3;
}


void Player::SetMap(MapEntity* mp)
{
    map = mp;
}

int Player::GetPositionIndex()
{
    return positionIndex;
}

void Player::ResetPosition()
{
    Vector2f temp(Settings::CARTESIAN_ATOMIC_HEIGHT / 2, Settings::CARTESIAN_ATOMIC_HEIGHT / 2);
    cartPosition = temp;
}

void Player::GetDirection()
{
    direction.x = 0.0f;
    direction.y = 0.0f;

    if (Keyboard::isKeyPressed(Keyboard::Left) ^ Keyboard::isKeyPressed(Keyboard::Right))
        direction.x = Keyboard::isKeyPressed(Keyboard::Right) ? 1.0f : -1.0f;
    else
    {
        if (Keyboard::isKeyPressed(Keyboard::Up) ^ Keyboard::isKeyPressed(Keyboard::Down))
            direction.y = Keyboard::isKeyPressed(Keyboard::Down) ? 1.0f : -1.0f;
    }
    


    direction.x = direction.x * (speed * Timer::instance->GetDeltaTime());
    direction.y = direction.y * (speed * Timer::instance->GetDeltaTime());
}

void Player::KillPlayer()
{
    animation = 0.0f;
    isAlive = false;
}

bool Player::isDead()
{
    return (!isAlive && animation > 2.0f);
}

void Player::Move()
{
    if (!isAlive)
        return;


    Vector2f futurePosition(cartPosition.x + direction.x, cartPosition.y + direction.y);

    GetFuturPosPlayer(futurePosition);

    cout << "PositionIndex : " << positionIndex << endl;

    bool isWall = false;

    if (futurePosition.x > 1469 || futurePosition.x < 0 || futurePosition.y > 1469 || futurePosition.y < 0)
        isWall = true;

   
    for (int j = 0; j < 4; j++)
    {
        cout << futurPosPlayerId[j] << endl;
        if (map[futurPosPlayerId[j]] == MapEntity::Wall)
            isWall = true;
    }
    cout << "---------------------" << endl;

    if (!isWall)
    {
        cartPosition.x += direction.x;
        cartPosition.y += direction.y;
    }



    positionIndex = CustomMath::CartCoordFToPosition(cartPosition);

    image.SetPosition(CustomMath::CartesianToIsometric(cartPosition));
}

void Player::Draw()
{
    if (isAlive)
    {
        int stateAnim = GetStateAnimation();
        SetDirectionAnimationVector2i();
        maskSprite.top = 324 * directionAnimationV2i.y + directionAnimationV2i.x * 171; // (171 * 2 = 324)

        maskSprite.left = 156 * stateAnim;
        image.SetTextureRect(maskSprite);
    }
    else
    {
        int stateAnim = GetStateAnimationDeath();
        maskSprite.top = 684 + directionAnimationV2i.y * directionAnimationV2i.x * 171; // (171 * 4 = 684)
        maskSprite.left = 156 * stateAnim;
        image.SetTextureRect(maskSprite);
    }

    //image.SetOrigin(77,128);
    
    image.Draw();
}