#include "Player.h"
#include "CustomMath.h"


Vector2i Player::upRightCorner(10, -10);
Vector2i Player::downLeftCorner(-10, 10);

Color Player::invicible(255, 255, 255, 150);
Color Player::normal(255, 255, 255, 255);

int Player::nbPlayer = 0;

Player::Player()
{
    image.SetTexture("Images/Player/SpriteSheetPlayer.png");
    image.SetOrigin(77, 128);
    maskSprite.height = 171;
    maskSprite.width = 156;

    id = nbPlayer;
    nbPlayer++;
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

    if (isDead())
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

void Player::SetOnBombId(int bombPos)
{
    onBombId = bombPos;
}

int Player::GetPositionIndex()
{
    return positionIndex;
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


bool Player::isDead()
{
    return lives <= 0;
}

void Player::TakeDamage()
{
    if (isInvicible)
        return;

    lives--;

    if (!isDead())
    {
        isInvicible = true;
        invincibilityTime = 0.0f;
        image.SetColor(invicible);
    }
}

void Player::CheckDamageBomb(const ExplosionData& eData)
{
    Vector2f positionf = image.GetPosition();
    positionf = CustomMath::IsometricToCartesian(positionf);
    Vector2i position(positionf.x / Settings::CARTESIAN_ATOMIC_HEIGHT, positionf.y / Settings::CARTESIAN_ATOMIC_HEIGHT);

    if (position.y == eData.centerId.y)
    {
        if (position.x >= eData.centerId.x && position.x <= eData.centerId.x + eData.xRight)
        {
            TakeDamage();
            return;
        }
        if (position.x <= eData.centerId.x && position.x >= eData.centerId.x - eData.xLeft)
        {
            TakeDamage();
            return;
        }
    }

    if (position.x == eData.centerId.x)
    {
        if (position.y >= eData.centerId.y && position.y <= eData.centerId.y + eData.yDown)
        {
            TakeDamage();
            return;
        }
        if (position.y <= eData.centerId.y && position.y >= eData.centerId.y - eData.yUp)
        {
            TakeDamage();
            return;
        }
    }
}

void Player::Move()
{
    if (isDead())
        return;


    Vector2f futurePosition(cartPosition.x + direction.x, cartPosition.y + direction.y);

    GetFuturPosPlayer(futurePosition);


    bool isWall = false;
    bool isBomb = false;

    if (futurePosition.x > 1469 || futurePosition.x < 0 || futurePosition.y > 1469 || futurePosition.y < 0)
        isWall = true;

   
    for (int j = 0; j < 4; j++)
    {
        if (map[futurPosPlayerId[j]] == MapEntity::Wall || map[futurPosPlayerId[j]] == MapEntity::DBlock)
            isWall = true;

        if (map[futurPosPlayerId[j]] == MapEntity::Bomb && futurPosPlayerId[j] != onBombId)
            isBomb = true;
    }

    if (!isBomb)
        onBombId = -1;

    if (!isWall && !isBomb)
    {
        cartPosition.x += direction.x;
        cartPosition.y += direction.y;
    }

    positionIndex = CustomMath::CartCoordFToPosition(cartPosition);
    CheckCollectable();

    image.SetPosition(CustomMath::CartesianToIsometric(cartPosition));
}

void Player::ManageInvicibility()
{
    if (isInvicible)
    {
        invincibilityTime += Timer::instance->GetDeltaTime();

        if (invincibilityTime >= 3.0f)
        {
            isInvicible = false;
            image.SetColor(normal);
        }
    }
}

void Player::CheckCollectable()
{
    MapEntity mE = *(map + positionIndex);
    bool isIn = false;
    switch (mE)
    {
        case LifeIt:
            AddLife();
            isIn = true;
            break;
        case BombIt:
            AddBomb();
            isIn = true;
            break;
        case SpeedIt:
            AddSpeed();
            isIn = true;
            break;
        case PowerIt:
            AddRange();
            isIn = true;
            break;
    }

    if (isIn)
    {
        *(map + positionIndex) = MapEntity::None;
    }
}

int Player::GetId()
{
    return id;
}

void Player::AddSpeed()
{
    speed += 20.0f;
}

void Player::AddBomb()
{
    bombs++;
}

void Player::AddRange()
{
    range++;
}

void Player::AddLife()
{
    lives++;
}

bool Player::AskRemoveBomb()
{
    if (bombs == 0)
        return false;
    
    bombs--;
    return true;
}

void Player::Reset()
{
    lives = 10;
    range = 1;
    bombs = 1;
    speed = 120.0f;
    animation = 0.0f;
    isInvicible = false;

    Vector2f temp(Settings::CARTESIAN_ATOMIC_HEIGHT / 2, Settings::CARTESIAN_ATOMIC_HEIGHT / 2);
    cartPosition = temp;
}

int Player::GetRange()
{
    return range;
}

void Player::Update()
{
    ManageInvicibility();
    GetDirection();
    Move();
}

void Player::Draw()
{
    if (!isDead())
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

    image.Draw();
}