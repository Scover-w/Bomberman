#include "BotPlayer.h"

//MapEntity* BotPlayer::map = nullptr;
int BotPlayer::twodMap[13][13];

BotPlayer::BotPlayer() : Player()
{

}

BotPlayer::~BotPlayer()
{

}

void BotPlayer::ResetPath()
{
    while (!path.empty())
    {
        Vector2i p = path.top();
        path.pop();
    }
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
            startPos = Vector2f(Settings::CARTESIAN_ATOMIC_HEIGHT - Settings::HALF_CARTESIAN_ATOMIC_HEIGHT, Settings::CARTESIAN_ATOMIC_HEIGHT * 12 + Settings::HALF_CARTESIAN_ATOMIC_HEIGHT);
            break;
        case 3:
            startPos = Vector2f(Settings::CARTESIAN_ATOMIC_HEIGHT * 12 + Settings::HALF_CARTESIAN_ATOMIC_HEIGHT, Settings::CARTESIAN_ATOMIC_HEIGHT * 12  + Settings::HALF_CARTESIAN_ATOMIC_HEIGHT);
            break;
    }

    cartPosition = startPos;
    positionIndex = CustomMath::GM_CartCoordFToPosition(cartPosition);

    Vector2f p = CustomMath::GM_CartesianToIsometric(cartPosition);
    image.SetPosition(p);
    shadow.SetPosition(p);

    ResetPath();
}

void BotPlayer::UpdateTwodMap()
{
    for (int x = 0; x < 13; x++)
    {
        for (int y = 0; y < 13; y++)
        {
            twodMap[x][y] = *(map + x + y * 13);
        }
    }
}

int BotPlayer::GetDistance(const Vector2i& pos1, const Vector2i& pos2)
{
	return (abs(pos1.x - pos2.x) + abs(pos1.y - pos2.y));
}

bool BotPlayer::IsValid(const Vector2i& point)
{
	return (point.x > -1 && point.y > -1 && point.x < 13 && point.y < 13);
}

bool BotPlayer::IsUnblocked(const Vector2i& point)
{
	int temp = twodMap[point.x][point.y];
	return IsValid(point) && !(temp >= MapEntity::Wall && temp <= MapEntity::Bomb);
}

bool BotPlayer::IsDestination(const Vector2i& position, const Vector2i& dest)
{
    return IsEqual(position, dest);
}

bool BotPlayer::IsEqual(const Vector2i& v1, const Vector2i& v2)
{
    return (v1.x == v2.x && v1.y == v2.y);
}

void BotPlayer::SetDirection()
{
    Vector2i targetP = path.top();
    Vector2i currentP = Vector2i(positionIndex % 13, positionIndex / 13);
    
    int deltaX = (targetP.x - currentP.x);
    int deltaY = (targetP.y - currentP.y);

    direction.x = deltaX * (speed * Timer::instance->GetDeltaTime());
    direction.y = deltaY * (speed * Timer::instance->GetDeltaTime());
}

void BotPlayer::SetPath(const Vector2i& dest)
{
    ResetPath();

    int x = dest.x;
    int y = dest.y;
    Vector2i next_node = cellDetails[x][y].parent;

    do 
    {
        path.push(next_node);
        next_node = cellDetails[x][y].parent;
        x = next_node.x;
        y = next_node.y;
    } while (!IsEqual(cellDetails[x][y].parent,next_node));

    //path.emplace(x, y);

    SetDirection();
}


bool BotPlayer::IsInTargetCell()
{
    if (path.size() == 0)
        return false;

    int targetPos = path.top().x + path.top().y * 13;
    if(positionIndex != targetPos)
        return false;

    Vector2f middlePosition = Vector2f(cartPosition.x - path.top().x * Settings::CARTESIAN_ATOMIC_HEIGHT, cartPosition.y - path.top().y * Settings::CARTESIAN_ATOMIC_HEIGHT);

    middlePosition.x = abs(middlePosition.x - Settings::HALF_CARTESIAN_ATOMIC_HEIGHT);
    middlePosition.y = abs(middlePosition.y - Settings::HALF_CARTESIAN_ATOMIC_HEIGHT);

    if (middlePosition.x > 20.0f && middlePosition.y > 20.0f)
        return true;

    return false;
}

void BotPlayer::Update()
{
    if (IsInTargetCell())
    {
        // In target
    }


    if (path.size() == 0)
    {
        UpdateTwodMap();
        SearchPath(Vector2i(positionIndex % 13, positionIndex / 13), Vector2i(0,1));
    }

    Vector2i temp = path.top();


    ManageInvicibility();
    Move();
}

void BotPlayer::SearchPath(const Vector2i& src, const Vector2i& dest)
{
    if (!IsValid(src)) {
        return;
    }

    if (!IsValid(dest)) {
        return;
    }

    if (!IsUnblocked(src) || !IsUnblocked(dest))
    {
        return;
    }

    if (IsDestination(src, dest)) 
    {
        return;
    }

    
    memset(closedList, false, sizeof(closedList));

    for (int i = 0; i < 13; i++)
    {
        for (int j = 0; j < 13; j++)
        {
            cellDetails[i][j] = {};
        }
    }
    

    int i, j;

    i = src.x, j = src.y;
    cellDetails[i][j].f = 0.0;
    cellDetails[i][j].g = 0.0;
    cellDetails[i][j].h = 0.0;
    cellDetails[i][j].parent = { i, j };

    std::priority_queue<Tuple, std::vector<Tuple>,
        std::greater<Tuple> >
        openList;

    openList.emplace(0.0, i, j);

    while (!openList.empty()) 
    {
        const Tuple& p = openList.top();

        i = get<1>(p); 
        j = get<2>(p); 

        openList.pop();
        closedList[i][j] = true;
        
        for (int add_x = -1; add_x <= 1; add_x++) 
        {
            for (int add_y = -1; add_y <= 1; add_y++) 
            {
                if (!(add_y == 0 ^ add_x == 0))
                    continue;

                Vector2i neighbour(i + add_x, j + add_y);

                if (IsValid(neighbour)) 
                {
                    if (IsDestination(neighbour,dest)) 
                    { 
                        cellDetails[neighbour.x][neighbour.y].parent = { i, j };
                        SetPath(dest);
                        return;
                    }

                    else if (!closedList[neighbour.x][neighbour.y] && IsUnblocked(neighbour)) 
                    {
                        int gNew, hNew, fNew;
                        gNew = cellDetails[i][j].g + 1;
                        hNew = GetDistance(neighbour, dest);
                        fNew = gNew + hNew;


                        if (cellDetails[neighbour.x][neighbour.y].f == -1 
                            || cellDetails[neighbour.x][neighbour.y].f > fNew) 
                        {
                            openList.emplace(fNew, neighbour.x, neighbour.y);

                            cellDetails[neighbour.x][neighbour.y].g = gNew;
                            cellDetails[neighbour.x][neighbour.y].h = hNew;
                            cellDetails[neighbour.x][neighbour.y].f = fNew;
                            cellDetails[neighbour.x][neighbour.y].parent = { i, j };
                        }
                    }
                }
            }
        }
    }
}