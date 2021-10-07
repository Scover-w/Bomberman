#include "MapDrawer.h"

MapDrawer* MapDrawer::instance;

MapDrawer::MapDrawer()
{
	instance = this;

	if (mapEntitiesT[0].loadFromFile("Images/Walls/BrickAlt1.png"))
	{
		mapEntitiesS[0].setTexture(mapEntitiesT[0]);
		mapEntitiesT[0].setSmooth(true);
		mapEntitiesS[0].setOrigin(80, 37);
	}
	if (mapEntitiesT[1].loadFromFile("Images/Destructible/RedRuby.png"))
	{
		mapEntitiesS[1].setTexture(mapEntitiesT[1]);
		mapEntitiesT[1].setSmooth(true);
		mapEntitiesS[1].setOrigin(80, 37);
	}
}

MapDrawer::~MapDrawer()
{

}

void MapDrawer::SetMap(MapEntity(&map2)[169])
{
	map = map2;
}

void MapDrawer::Draw()
{
	Vector2f positionSelection;
	for (int i = 0; i < 169; i++)
	{
		switch (*(map + i))
		{
			case MapEntity::None:

				break;

			case MapEntity::Wall:
				positionSelection = CustomMath::PositionToIsoCoordF(i);
				mapEntitiesS[0].setPosition(positionSelection);
				StaticWindow::window->draw(mapEntitiesS[0]);
				break;

			case MapEntity::DBlock:
				positionSelection = CustomMath::PositionToIsoCoordF(i);
				mapEntitiesS[1].setPosition(positionSelection);
				StaticWindow::window->draw(mapEntitiesS[1]);
				break;

			case MapEntity::Bomb:

				break;

			case MapEntity::Item:

				break;
		}

		if (i % 13 == 0 && i != 0)
		{
			// CHeck if need to draw player
		}
	}
}