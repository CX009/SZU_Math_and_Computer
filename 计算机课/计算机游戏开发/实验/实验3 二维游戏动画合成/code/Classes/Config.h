#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "Headers.h"

static const float epsilon = 1e-6;
static const float pi = acos(-1.0f);

// ��ɫ״̬
enum State {
	STAND, 
	MOVELEFT, 
	MOVERIGHT,
	ATTACK,
	DEAD, 
	SMITTEN, 
	DEFENSE
};

// �����������
static std::mt19937 rnd(time(0));

// ����
static const std::string TIPS_FNT_PATH = "fonts/futura-48.fnt";

// ����ͼ
static const std::string START_BACKGROUND_PATH = "backgrounds/StartBackground.png";
static const std::string LEVEL1_BACKGROUND_PATH = "backgrounds/Level1Background.png";
static const std::string LEVEL2_BACKGROUND_PATH = "backgrounds/Level2Background.png";
static const std::string LEVEL3_BACKGROUND_PATH = "backgrounds/Level3Background.png";
static const std::string END_BACKGROUND_PATH = "backgrounds/EndBackground.png";

// ����/��ʾ
static const float HINT_DELTA_PERCENT = 0.01;  // ����/��ʾ�����ٶ�
static const std::string HINT_BACKGROUND_PATH = "hints/HintBackground.png";
static const int START_AND_PAUSE_HINT_TAG = 301;
static const std::string START_AND_PAUSE_HINT = "Press SPACE to start or P to pause/resume.";
static const std::string REPLAY_AND_NEXT_HINT = "Press R to replay or N to the next level.";
static const std::string START_STORY_PATH = "hints/StartStory.png";
static const std::string END_STORY_PATH = "hints/EndStory.png";

// �Ʊ���
static const int CLOUD_BACKGROUND_TAG = 100;
static const std::string CLOUD_BACKGROUND_PATH = "cloud.png";

// ���½ǹرհ�ť
static const std::string CLOSE_BUTTON_PATH = "CloseButton/CloseNormal.png";
static const std::string CLOSE_BUTTON_SELECTED_PATH = "CloseButton/Selected.png";

// ҡ��
static const float JOYSTICK_RADIUS = 63.0;
static const std::string JOYSTICK_PATH = "JoyStick/joystick.png";
static const std::string JOYSTICK_BUTTON_PATH = "JoyStick/joystick_button.png";

// Ѫ��
static const std::string HERO_BLOOD_BAR_PATH = "BloodBar/HeroBloodBar.png";
static const std::string HERO_BLOOD_BAR_BACKGROUND_PATH = "BloodBar/HeroBloodBarBackground.png";
static const std::string TAUREN_BLOOD_BAR_PATH = "BloodBar/TaurenBloodBar.png";
static const std::string TAUREN_BLOOD_BAR_BACKGROUND_PATH = "BloodBar/TaurenBloodBarBackground.png";

// ��������
static const std::string ANIMATION_HERO_PATH = "Hero/Hero.ExportJson";
static const std::string ANIMATION_TAUREN_PATH = "tauren/tauren.ExportJson";

// ���ܰ�ť
static const int ATTACK_BUTTON_TAG = 201;
static const std::string ATTACK_BUTTON = "SkillButtons/AttackButton.png";
static const std::string ATTACK_BUTTON_PRESSED = "SkillButtons/AttackButtonPressed.png";
static const int DEFENSE_BUTTON_TAG = 202;
static const std::string DEFENSE_BUTTON = "SkillButtons/DefenseButton.png";
static const std::string DEFENSE_BUTTON_PRESSED = "SkillButtons/DefenseButtonPressed.png";
static const int KNOCKBACK_BUTTON_TAG = 203;
static const std::string KNOCKBACK_BUTTON = "SkillButtons/KnockbackButton.png";
static const std::string KNOCKBACK_BUTTON_PRESSED = "SkillButtons/KnockbackButtonPressed.png";
static const int BARRAGE_BUTTON_TAG = 204;
static const std::string BARRAGE_BUTTON = "SkillButtons/BarrageButton.png";
static const std::string BARRAGE_BUTTON_PRESSED = "SkillButtons/BarrageButtonPressed.png";

// HERO ���� CD
static const int ATTACK_CD = 60;
static const int DEFENSE_CD = 50;
static const int KNOCKBACK_CD = 200;
static const int BARRAGE_CD = 500;

// ������ͼ
static const std::string TAUREN_SHIELD_PATH = "SkillItems/TaurenShield.png";
static const std::vector<std::string> BULLET_PATHS = {
	"SkillItems/bullet1.png",
	"SkillItems/bullet2.png",
	"SkillItems/bullet3.png",
	"SkillItems/bullet4.png"
};
static const std::string BARRAGE_EMITTER_PATH = "SkillItems/emitter.png";

// Tauren ���� CD
static const int TAUREN_DEFENSE_CD = 400;
static const int TAUREN_STEALTH_CD = 500;
static const int TAUREN_STRIKE_FLY_CD = 600;

// ����
static const int BASIC_DAMAGE = 10;  // ƽ A ����������
static const int DEFENSE_DAMAGE = 5;  // Hero ���������Ĺ�����
static const int SPEED_X = 4;  // ��ɫ�ƶ��ٶ�
static const int HERO_SMITTEN_LOCK = 50;  // Hero �����������˵���Сʱ����
static int TAUREN_SWITCH_ACTION = 300;  // Tauren �л��������е�ʱ����
static const int BULLET_BASIC_DAMAGE = 10;  // �ӵ��Ļ����˺�
static const int BULLET_SPEED = 10;  // �ӵ��ٶȵ�ģ
static const float BULLET_FORCE = 5;  // �ӵ����˾��������ٶȵ� x �����ı���
static const int TAUREN_STEALTH_TIME = 5;  // Tauren ����ʱ�� (��λ: s)
static const int BARRAGE_EMITTER_ROTATE_SPEED = 60;  // ��Ļ��������ת�ٶ� (0.1 s ���ĽǶ�)
static const int HERO_BARRAGE_TIME = 300;  // ��Ļ����ʱ��
static const int BARRAGE_DELTA_TIME = 50;  // ��Ļ�ķ���ʱ����
static const int BARRAGE_DELTA_ANGLE = 30;  // ���ڵ�Ļ�ķ���ǶȲ�
static const int BARRAGE_BASIC_DAMAGE = 1;  // ��Ļ�Ļ����˺�
static const float STRUCK_FLY_BASIC_SPEED = 50;  // ���ɵĳ��ٶ� (���)
static const float g = 0.98;  // �������ٶ�
static const int STRUCK_FLY_BASIC_DAMAGE = 30;  // ���ɵĻ����˺�

// bgm
static const std::string MOFA_PATH = "sounds/mofa.mp3";
static const std::string DOKU_PATH = "sounds/doku.mp3";
static const std::string FAIRY_PATH = "sounds/fairy.mp3";

// ��Ч
static const std::string HIT_METAL_PATH = "sounds/hitMetal.mp3";
static const std::string GLASS_BREAK_PATH = "sounds/glassBreak.mp3";

// �Ʒְ�
static int heroScore = 0;
static int taurenScore = 0;

// �Ƚϸ�������С
int doubleCompare(double a, double b);

// ����������� [l, r] �ڵ�����
int generateRandomInteger(int l, int r);

#endif