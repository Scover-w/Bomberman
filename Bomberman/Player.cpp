#include "Player.h"
#include "CustomMath.h"


Player::Player()
{
    if (texture.loadFromFile("Images/Player/SpriteSheetPlayer.png"))
    {
        sprite.setTexture(texture);
        texture.setSmooth(true);
    }

    maskSprite.height = 171;
    maskSprite.width = 156;
}

Player::~Player()
{

}

void Player::KeyManager(Event& e)
{
    if (e.type == e.KeyPressed)
    {
        switch (e.key.code)
        {
            case Keyboard::Left:
                keys[0] = true;
                break;

            case Keyboard::Right:
                keys[1] = true;
                break;

            case Keyboard::Up:
                keys[2] = true;
                break;

            case Keyboard::Down:
                keys[3] = true;
                break;

            case Keyboard::D:
                KillPlayer();
                break;
        }
    }
    else if (e.type == e.KeyReleased)
    {
        switch (e.key.code)
        {
            case Keyboard::Left:
                keys[0] = false;
                break;

            case Keyboard::Right:
                keys[1] = false;
                break;

            case Keyboard::Up:
                keys[2] = false;
                break;

            case Keyboard::Down:
                keys[3] = false;
                break;
        }
    }
}

void Player::SetDirectionAnimationVector2i()
{
    if (direction.x < -0.0001f) // Right
    {
        directionAnimationV2i.x = 0;
        directionAnimationV2i.y = 1;
    }
    else if (direction.x > 0.0001f) // Left
    {
        directionAnimationV2i.x = 1;
        directionAnimationV2i.y = 0;
    }
    else if (direction.y > 0.0001f) // Up
    {
        directionAnimationV2i.x = 0;
        directionAnimationV2i.y = 0;
    }
    else if (direction.y < -0.0001f) // Down
    {
        directionAnimationV2i.x = 1;
        directionAnimationV2i.y = 1;
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
    
    if (!keys[0] && !keys[1] && !keys[2] && !keys[3])
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

    if (keys[0] ^ keys[1])
        direction.x = keys[0] ? 1.0f : -1.0f;
    else
    {
        if (keys[2] ^ keys[3])
            direction.y = keys[2] ? 1.0f : -1.0f;
    }
    

    direction *= speed * Timer::instance->GetDeltaTime();}

void Player::KillPlayer()
{
    animation = 0.0f;
    isAlive = false;
}

bool Player ::isDead()
{
    return (!isAlive && animation > 2.0f);
}

void Player::Move()
{
    if (!isAlive)
        return;

    position += direction;
    sprite.setPosition(CustomMath::CartesianToIsometric(position));
}

void Player::Draw()
{
    if (isAlive)
    {
        int stateAnim = GetStateAnimation();
        SetDirectionAnimationVector2i();
        maskSprite.top = 324 * directionAnimationV2i.y + directionAnimationV2i.x * 171; // (171 * 2 = 324)

        maskSprite.left = 156 * stateAnim;
        sprite.setTextureRect(maskSprite);
    }
    else
    {
        int stateAnim = GetStateAnimationDeath();
        maskSprite.top = 684 + directionAnimationV2i.y * directionAnimationV2i.x * 171; // (171 * 4 = 684)
        maskSprite.left = 156 * stateAnim;
        sprite.setTextureRect(maskSprite);
    }

    sprite.setOrigin(73,108);
    
    StaticWindow::window->draw(sprite);
}