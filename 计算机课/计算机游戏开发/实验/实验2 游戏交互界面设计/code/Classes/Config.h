#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "cocos2d.h"
USING_NS_CC;
using namespace cocos2d;

#include "AppDelegate.h"
#include <algorithm>
#include <cstring>

static std::mt19937 rnd(time(0));

int generateRandomInteger(int l, int r);

const int BOARD_WIDTH = 624;
const int BOARD_WIDTH_BIAS = 200;
const int BOARD_HEIGHT = 768;

// 3 ����
const std::string BALL1_PATH = "Chapter10/ball1.png";
const std::string BALL2_PATH = "Chapter10/ball2.png";
const std::string BALL3_PATH = "Chapter10/ball3.png";
const int BALL_TAG_BIAS = 10;  // ��� Tag ��÷ֵ�ƫ����
const int BALL1_TAG = 11;
const int BALL2_TAG = 12;
const int BALL3_TAG = 13;

// ��ǩ����
const std::string TIPS_FNT_PATH = "fonts/futura-48.fnt";

// �Ʒְ�
const int SCOREBOARD_TAG = 1;

// ����
static std::string BACKGROUND_PATH = "background.png";
static std::string BOARD1_PATH = "board1.png";
static std::string BOARD2_PATH = "board2.png";
static std::string BOARD3_PATH = "board3.png";

// �ж���
static std::string LINE_PATH = "line.png";
const int LINE_TAG = 100;

// note
static std::string NOTE1_PATH = "note1.png";
const int NOTE1_TAG = 201;
static std::string NOTE2_PATH = "note2.png";
const int NOTE2_TAG = 202;
static std::string NOTE3_PATH = "note3.png";
const int NOTE3_TAG = 203;

// note ����Ч��
static std::string HIT_PATH = "hit.png";
static std::string PERFECT_PATH = "perfect.png";
static std::string GOOD_PATH = "good.png";
static std::string BAD_PATH = "bad.png";
static std::string MISS_PATH = "miss.png";
const float DELTA_SCALE = 0.025;  // ÿ�� scale += 0.025
const float DELTA_ANGLE = 1;  // ÿ��ת 1��
const float DELTA_OPACITY = 2;  // ÿ�� -2% ��͸����
const float DELTA_POSITION_Y = 1;  // ÿ�� y += 1

// ��Ч������
static std::string SHAOGUANWO_SOUND_PATH = "shaoguanwo.mp3";
static std::string HIT_SOUND_PATH = "hit.mp3";
static std::string PEOPLE_IS_PATH = "people is.mp3";
static std::string INTRO_PATH = "intro.mp3";
static std::string MIRAGE_PATH = "mirage.mp3";

// ����
static float VOLUME = 0.9;

// ��¼���
static std::string LOGINBOARD_PATH = "Login_1/Login_1.ExportJson";

// ��ʾ
const int LEVEL1_HINT_TAG = 501;
static std::string LEVEL1_HINT_PATH = "Level1Hint.png";
const int LEVEL2_HINT_TAG = 502;
static std::string LEVEL2_HINT_PATH = "Level2Hint.png";
const int LEVEL3_HINT_TAG = 503;
static std::string LEVEL3_HINT_PATH = "Level3Hint.png";

// ������
const int ACCURACY_TAG = 601;
const int PERFECT_TAG = 601;
const int GOOD_TAG = 602;
const int BAD_TAG = 603;
const int MISS_TAG = 604;
static std::string LEVEL1_RESULT_PATH = "Level1Result_1/Level1Result_1.ExportJson";
static std::string LEVEL2_RESULT_PATH = "Level2Result_1/Level2Result_1.ExportJson";
static std::string LEVEL3_RESULT_PATH = "Level3Result_1/Level3Result_1.ExportJson";

// �ı�
const int WORDS_TAG = 1000;

#endif