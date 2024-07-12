#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <vector>
using namespace std;
USING_NS_CC;

static const int PLAYER_TAG = 110;  // player tag
static const int MAP_TAG = 111;     // map tag

static int PLAYER_WIDTH = 80;		// player img width
static int PLAYER_HEIGHT = 100;	    // player img height
static int PLAYER_JUMP_INITIAL_SPEED = 2;  // ��ҵĳ�ʼ��ֱ�ٶ�
static int PLAYER_JUMP_MAX_SPEED = 30;  // ��ҵ������ֱ�ٶ�
// static int PLAYER_MAP_MOVE_SPEED = 3;  // ��Һ͵�ͼ���ƶ��ٶ�
static int ITEM_WIDTH = 32;  // ���߿��
static int ITEM_HEIGHT = 32;  // ���߸߶�
static float EPS = 1;  // ��ײ
static int EFFECT_TIME = 75;  // ��������ʱ��

static string BACKGROUND_FILE_PATH = "whale.png";  // ����;
static string MAP_TMX_FILE_PATH = "Chapter05/beach (empty).tmx";  // ��ͼ (��������)
static string MAP_BG_LAYER_NAME = "Layer 1";  // map background layer name
static string EGG_FILE_PATH = "egg.png";  // Ƥ��
static string GRAIN_FILE_PATH = "grain.png";  // ����
static string MICROPHONE_FILE_PATH = "microphone.png";  // ��

// static int MAP_FLOUR_NUM = 6;
// static int MAP_FLOUR[] = { 7,8,151,170,171,172 };
// static vector<int> MAP_FLOUR = { 7, 8, 151, 170, 171, 172 };  // �Ż�ʵ��
// static vector<int> MAP_FLOUR = { 7, 8, 151, 170, 171, 172, 149, 133 };  // �޸���֦��� Bug
// Tield (0-indexed): 0, 1, 18, 19, 20, 24, 25, 26, 30, 31, 32, 21, 22, 23, 27, 28, 29, 33, 34, 35
static vector<int> MAP_FLOUR = { 1, 2, 19, 20, 21, 25, 26, 27, 31, 32, 33, 22, 23, 24, 28, 29, 30, 34, 35, 36, 8, 14 };  // ���� tile
static vector<int> MAP_BLOCK;  // �赲 tile
static vector<int> MAP_THORN;  // ��� tile
static vector<int> MAP_ENDPOINT = { 11, 17 };  // �յ�

static string GAME_OVER_TIPS = "Game Over!";  // game failed tips words
static string GAME_SUCCESS = "Success!";      // game success tips words

static string PICKUP_SOUND_EFFECT = "pick up.mp3";  // ���������Ч
static string SUCCESS_SOUND_EFFECT = "success.mp3";  // ʤ����Ч
static string GAMEOVER_SOUND_EFFECT = "game over.mp3";  // ʧ����Ч

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

// Ƥ��
static vector<int> EGG_TAGS = {
	200,  // Ƥ�� 0
	201,  // Ƥ�� 1
	202,  // Ƥ�� 2

};
static vector<Vec2> EGG_POSITIONS = {
	{ 19, 23 },  // Ƥ�� 0
	{ 39, 23 },  // Ƥ�� 1
	{ 61, 19 },  // Ƥ�� 2
};

// ����
static vector<int> GRAIN_TAGS = {
	300,  // ���� 0
	301,  // ���� 1
	302,  // ���� 2
};
static vector<Vec2> GRAIN_POSITIONS = {
	{ 8, 23 }, // ���� 0
	{ 53, 18 },  // ���� 1
	{ 69, 19 },  // ���� 2
};

// ��˷�
static vector<int> MICROPHONE_TAGS = {
	400,  // ��˷� 0
	401,  // ��˷� 1
};
static vector<Vec2> MICROPHONE_POSITIONS = {
	{ 23, 22 }, // ��˷� 0
	{ 46, 21 },  // ��˷� 1
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
	return false;

	for (auto thornGID : MAP_THORN)
	{
		if (gid == thornGID)
		{
			return true;
		}
	}

	return false;
}

// �ж� tile �Ƿ����յ�
static bool isEndpoint(int gid)
{
	for (auto endpointGID : MAP_ENDPOINT)
	{
		if (gid == endpointGID)
		{
			return true;
		}
	}

	return false;
}

#endif