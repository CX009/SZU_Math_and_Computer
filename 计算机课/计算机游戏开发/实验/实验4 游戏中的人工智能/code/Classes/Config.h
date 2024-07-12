#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "Headers.h"

static const int INF = 0x3f3f3f3f;
static const float epsilon = 1e-6;
static const float pi = acos(-1.0f);

// �����������
static std::mt19937 rnd(time(0));

// ����
static const std::string TIPS_FNT_PATH = "fonts/futura-48.fnt";

// ���½ǹرհ�ť
static const std::string CLOSE_BUTTON_PATH = "CloseButton/CloseNormal.png";
static const std::string CLOSE_BUTTON_SELECTED_PATH = "CloseButton/Selected.png";

// �Թ�
static const int MAP_UNIT = 32;
static const int MAP_WIDTH = 32;
static const int MAP_HEIGHT = 20;
static const std::string TILED_MAZE_1_PATH = "mazes/tiledMaze1.tmx";
static const std::string TILED_MAZE_2_PATH = "mazes/tiledMaze2.tmx";
static const std::string WALL_LAYER_NAME = "Wall";
static const std::vector<int> ACCESSIBLE_TILES = { 1 };
static const std::vector<int> INACCESSIBLE_TILES = { 3, 4 };

// ��ɫ
static const std::string CATTAIL_TILE_PATH = "characters/cattail.png";
static const std::string WALNUT_TILE_PATH = "characters/walnut.png";

// ���ߺ�����ͼ��
static const std::string FORBIDDEN_TILE_PATH = "items/forbidden.png";
static const std::string PORTAL_TILE_PATH = "items/portal.png";
static const std::string SKULL_TILE_PATH = "items/skull.png";
static const std::string SPEED_DOWN_TILE_PATH = "items/speedDown.png";
static const std::string SPEED_UP_TILE_PATH = "items/speedUp.png";

// ��ʾ��Ϣ
static const std::string PLACE_TIP = "Click to place the walnut!";
static const std::string FIND_TIP = "Found the walnut!";
static const std::string NO_WAY_TIP = "No way!";
static const std::string DANGEROUS_TIP = "Dangerous! Press R to restart!";

// ����
static const std::string START_BACKGROUND_PATH = "backgrounds/startBackground.png";
static const std::string PLAY_BUTTON_PATH = "backgrounds/startButton.png";

// ����Ч��
static const std::string PARTICLE_PATH = "particles/BurstPipe.plist";

// ·������ɫ
static const std::vector<Color4F> COLORS = {
	Color4F::BLACK,
	Color4F::GREEN,
	Color4F::MAGENTA,
	Color4F::ORANGE,
	Color4F::RED,
	Color4F::WHITE,
	Color4F::YELLOW
};

// ��������Ч
static const std::string BGM_PATH = "music/chun xue.mp3";
static const std::string FIND_SOUND_PATH = "music/laugh.mp3";
static const std::string DANGEROUS_SOUND_PATH = "music/die.mp3";
static const std::string SPEED_UP_SOUND_PATH = "music/speedUp.mp3";
static const std::string SPEED_DOWN_SOUND_PATH = "music/speedDown.mp3";
static const std::string VICTORY_SOUND_PATH = "music/victory.mp3";

static const float PLAY_BUTTON_FLY_SPEED = 10;

// �Ƚϸ�������С
int doubleCompare(double a, double b);

// ����������� [l, r] �ڵ�����
int generateRandomInteger(int l, int r);

#endif