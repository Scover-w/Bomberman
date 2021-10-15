#include "Settings.h"

const int Settings::HEIGHT_SCREEN = 1080;//650;
const int Settings::WIDTH_SCREEN = 1920;//850;

const int Settings::MULTIPLIED_HEIGHT_SCREEN = HEIGHT_SCREEN * 1.1f;
const int Settings::MULTIPLIED_WIDTH_SCREEN = WIDTH_SCREEN * 1.1f;

const int Settings::NB_HEIGHT_MAP = 13;
const int Settings::NB_WIDTH_MAP = 13;

const int Settings::ATOMIC_HEIGHT_MAP = 81;
const int Settings::ATOMIC_WIDTH_MAP = 41;

const int Settings::HEIGHT_MAP = ATOMIC_HEIGHT_MAP * NB_HEIGHT_MAP;
const int Settings::WIDTH_MAP = ATOMIC_WIDTH_MAP * NB_WIDTH_MAP;

const float Settings::CARTESIAN_ATOMIC_HEIGHT = 113.0f;

const float Settings::X_TRANSLATION_MAP = 79.0f;
const float Settings::Y_TRANSLATION_MAP = 57.0f;