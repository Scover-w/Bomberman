#include "Player.h"
#include "CustomMath.h"


Player::Player()
{
    image.SetTexture("Images/Player/SpriteSheetPlayer.png");

    maskSprite.height = 171;
    maskSprite.width = 156;

    position.x = 0.0f;
    position.y = 0.0f;
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

    if (animation > 1.0f)
        animation -= 1.0f;
}

int Player::GetStateAnimation()
{
    DeltaAnimation();
    
    if (!Keyboard::isKeyPressed(Keyboard::Left) && !Keyboard::isKeyPressed(Keyboard::Right) 
        && !Keyboard::isKeyPressed(Keyboard::Up) && !Keyboard::isKeyPressed(Keyboard::Down))
    {
        return 0;
    }

    if (animation < 0.125f)
        return 0;
    else if (animation < 0.25f)
        return 1;
    else if (animation < 0.375f)
        return 2;
    else if (animation < 0.5f)
        return 3;
    else if (animation < 0.625f)
        return 4;
    else if (animation < 0.750f)
        return 5;
    else if (animation < 0.875f)
        return 6;
    else if (animation < 1.0f)
        return 7;
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
    

    direction *= speed * Timer::instance->GetDeltaTime();}

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

    position += direction;
    image.SetPosition(CustomMath::CartesianToIsometric(position));
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

    image.SetOrigin(73,108);
    
    image.Draw();
}