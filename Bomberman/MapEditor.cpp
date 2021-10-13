#include "MapEditor.h"



bool MapEditor::LoadMap(int mapId, MapEntity(&map2)[169])
{
	fstream file("Maps/Map" + to_string(mapId) + ".bin", ios::binary | ios::in | ios::out);

	cout << "Want to load Map" << to_string(mapId) << ".bin" << endl;

	if (!file.read(reinterpret_cast<char*>(&map2), sizeof(map2)))
	{
		cout << "Map " << to_string(mapId) << "failed to load." << std::endl;
		return false;
	}

	file.close();

	return true;
}

void MapEditor::WriteMap(int mapId, MapEntity(&map2)[169])
{
	fstream file("Maps/Map" + to_string(mapId) + ".bin", ios::trunc | ios::binary | ios::in | ios::out);

	cout << "Map " << to_string(mapId) << " saved." << endl;

	file.write(reinterpret_cast<char*>(&map2), sizeof(map2));

	file.close();
}

bool MapEditor::DoesMapExist(int mapId)
{
	FILE* file;
	errno_t err;

	string name = "Maps/Map" + to_string(mapId) + ".bin";

	err = fopen_s(&file, name.c_str(), "r");
	if (err == 0)
	{
		cout << "Map " << mapId << " does exist." << endl;
		fclose(file);
		return true;
	}

	cout << "Map " << mapId << " doesn't exist." << endl;
	return false;
}

int MapEditor::GetMaxId()
{
	int i = 2;

	while (DoesMapExist(i))
	{
		i++;
	}
	return i - 1;
}