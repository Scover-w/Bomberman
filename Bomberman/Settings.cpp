#include "Settings.h"

const Vector2i Settings::SIZE_SCREEN = Vector2i(1920, 1080);

const float Settings::ZOOM = 1.1f;

const Vector2f Settings::MULTIPLIED_SIZE_SCREEN = Vector2f(SIZE_SCREEN.x * ZOOM, SIZE_SCREEN.y * ZOOM);


const int Settings::SIZE_GAME_MAP = 13;
const int Settings::SIZE_UI_MAP = 28;

const float Settings::ISOMETRIC_SIZE_TILE = 79.9031f;

const float Settings::CARTESIAN_ATOMIC_HEIGHT = 113.0f;
const float Settings::HALF_CARTESIAN_ATOMIC_HEIGHT = CARTESIAN_ATOMIC_HEIGHT / 2.0f;

const Vector2f Settings::GAME_TRANSLATION_MAP = Vector2f(79.0f, 57.0f);
const Vector2f Settings::UI_TRANSLATION_MAP = Vector2f(79.0f, 57.0f - (8 * ISOMETRIC_SIZE_TILE)  - 37.0f);