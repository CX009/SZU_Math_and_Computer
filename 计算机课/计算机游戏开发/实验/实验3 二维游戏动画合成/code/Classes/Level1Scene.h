#ifndef __LEVEL1_SCENE_H__
#define __LEVEL1_SCENE_H__

#include "Headers.h"
#include "Config.h"
#include "BasicScene.h"
#include "Joystick.h"
#include "BloodBar.h"
#include "Hero.h"
#include "Tauren.h"
#include "TaurenAI.h"
#include "CollisionDetection.h"

#include "Level2Scene.h"

class BasicScene;

class Level1Scene : public BasicScene {
private:
	Joystick* joystick;

	// Hero
	int heroMaxHP;
	Hero* hero;
	float heroWidth;
	BloodBar* heroBloodBar;

	// Tauren
	int taurenMaxHP;
	Tauren* tauren;
	float taurenWidth;
	BloodBar* taurenBloodBar;
	TaurenAI* taurenAI;
	Sprite* taurenShield;  // Tauren �Ķ���

	// ��ײ���
	CollisionDetection* collisionDetection;

	// ���� CD
	int attackCD;
	int defenseCD;

	// �Ʒְ��ǩ
	Label* heroScoreboard;
	Label* taurenScoreboard;

public:
	Level1Scene();

	~Level1Scene();

	static Scene* createScene();

	bool init();

	CREATE_FUNC(Level1Scene);

	void update(float dt);

	// Ԥ��������
	void preloadSounds();

	// ���̼����Ļص�����
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);

	// ��Ϸʤ��
	void workVictory();

	// ��Ϸʧ��
	void workDefeat();

	// ��Ϸʤ���ж�
	void gameJudgement();

	// ����ҡ��
	void loadJoystick(std::string joystickPath, std::string joystickButtonPath, float joystickRadius, Point position, int z);

	// ���� Hero
	void loadHero(int _maxHP, Point position, int z);

	// ���� Hero Ѫ��
	void loadHeroBloodBar(int _maxHP, int _HP, Point position, int z,
		std::string bloodBarPath, std::string bloodBarBackgroundPath, BloodBarDirection _bloodBarDirection = RIGHT, int tag = -1);

	// ���� Hero �ƶ�
	void workHeroMovement();

	// ���� Tauren
	void loadTauren(int _maxHP, Point position, int z);

	// ���� Tauren Ѫ��
	void loadTaurenBloodBar(int _maxHP, int _HP, Point position, int z,
		std::string bloodBarPath, std::string bloodBarBackgroundPath, BloodBarDirection _bloodBarDirection = RIGHT, int tag = -1);

	// ���� Tauren �ƶ�
	void workTaurenMovement();

	// ����Ѫ��
	void updateBloodBar();

	// ���� Hero �Ʒְ�
	void loadHeroScoreboard(int score, Point position, int z, int tag = -1);

	// ���� Tauren �Ʒְ�
	void loadTaurenScoreboard(int score, Point position, int z, int tag = -1);

	// ���� Hero �Ʒְ�
	void updateHeroScoreboard(int score);

	// ���� Tauren �Ʒְ�
	void updateTaurenScoreboard(int score);

	// �����Ʊ���
	void loadCloudBackground(int z, int tag = -1);

	// �����Ʊ���
	void updateCloudBackground();

	// �������м��ܵİ�ť
	void updateSkillButtons();

	// ���ع�����ť
	void loadAttackButton(Point position, int z, int tag = -1);

	// ������ť�Ļص�����
	void attackButtonCallback(Ref* pSender);

	// ���ط�����ť
	void loadDefenseButton(Point position, int z, int tag = -1);

	// ������ť�Ļص�����
	void defenseButtonCallback(Ref* pSender);

	// ���� Tauren �Ķ���
	void loadTaurenShield();

	// ���� Tauren �Ķ��Ƶ�λ��
	void updateTaurenShieldPosition();
};

#endif