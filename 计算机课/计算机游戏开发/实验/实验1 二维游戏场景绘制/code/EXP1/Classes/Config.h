#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <vector>
using namespace std;

static const int PLAYER_TAG = 110;  // player tag
static const int MAP_TAG = 111;     // map tag
static int PLAYER_WIDTH = 100;		// player img width
static int PLAYER_HEIGHT = 100;	    // player img height
static int PLAYER_JUMP_SPEED = 30;  // player jump speed

static string MAP_TMX_FILE_PATH = "Chapter05/MoveAndControl.tmx";
//static string MAP_TMX_FILE_PATH = "Chapter05/beach.tmx";
static string MAP_BG_LAYER_NAME = "back";  // map background layer name

// static int MAP_FLOUR_NUM = 6;
// static int MAP_FLOUR[] = { 7,8,151,170,171,172 };
// static vector<int> MAP_FLOUR = { 7, 8, 151, 170, 171, 172 };  // �Ż�ʵ��
static vector<int> MAP_FLOUR = { 7, 8, 151, 170, 171, 172, 149, 133 };  // �޸���֦��� Bug
static vector<int> MAP_BLOCK = { 40, 151 };  // �޸������ж� Bug
static vector<int> MAP_THORN = { 84, 85 };  // ����ж� Bug

/*// Tield (0-indexed): 0, 1, 18, 19, 20, 24, 25, 26, 30, 31, 32, 21, 22, 23, 27, 28, 29, 33, 34, 35
static vector<int> MAP_FLOUR = { 1, 2, 19, 20, 21, 25, 26, 27, 31, 32, 33, 22, 23, 24, 28, 29, 30, 34, 35, 36 };  // 1-indexed*/

static string GAME_OVER_TIPS = "Game Over!";  // game failed tips words
static string GAME_SUCCESS = "Success!";      // game success tips words

//	fnt file path
static string TIPS_FNT_PATH = "fonts/futura-48.fnt";

// player img path
static string PLAYER_IMG_PATH[4] = {
	"Chapter05/player/player1.png",
	"Chapter05/player/player2.png",
	"Chapter05/player/player3.png",
	"Chapter05/player/player4.png"
} ;

enum Dir
{
	STOP,
	UP,
	DOWN
};

// �ж� tile �Ƿ��ǵ���
static bool isFloor(int gid)
{
	for (auto floorGID : MAP_FLOUR)
	{
		if (gid == floorGID)
		{
			return true;
		}
	}

	return false;
}

// �ж� tile �Ƿ����赲
static bool isBlock(int gid)
{
	for (auto blockGID : MAP_BLOCK)
	{
		if (gid == blockGID)
		{
			return true;
		}
	}
	for (auto floorGID : MAP_FLOUR)
	{
		if (gid == floorGID)
		{
			return true;
		}
	}

	return false;
}

// �ж� tile �Ƿ��Ǽ��
static bool isThorn(int gid)
{
	for (auto thornGID : MAP_THORN)
	{
		if (gid == thornGID)
		{
			return true;
		}
	}

	return false;
}


#endif