#ifndef __LEVEL3_SCENE_H__
#define __LEVEL3_SCENE_H__

#include "Headers.h"
#include "Config.h"
#include "BasicScene.h"
#include "Joystick.h"
#include "BloodBar.h"
#include "Hero.h"
#include "Tauren.h"
#include "TaurenAI.h"
#include "CollisionDetection.h"
#include "Bullet.h"
#include "EndScene.h"

class BasicScene;

class Level3Scene : public BasicScene {
private:
	Joystick* joystick;

	// Hero
	int heroMaxHP;
	Hero* hero;
	float heroWidth;
	BloodBar* heroBloodBar;
	int barrageTimer;  // ��Ļ��ʱ��
	Sprite* barrageEmitter;  // ��Ļ������
	float struckFlySpeed;  // ���� y �ٶ�
	bool struckFlyDown;  // ���ɽ�������׶�

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
	int knockbackCD;
	int barrageCD;

	// �Ʒְ��ǩ
	Label* heroScoreboard;
	Label* taurenScoreboard;

	std::vector<Bullet*> knockbackBullets;
	std::vector<Bullet*> barrageBullets;

public:
	Level3Scene();

	~Level3Scene();

	static Scene* createScene();

	bool init();

	CREATE_FUNC(Level3Scene);

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

	// ���ػ��˰�ť
	void loadKnockbackButton(Point position, int z, int tag = -1);

	// �������˵Ļص�����
	void knockbackButtonCallback(Ref* pSender);

	// �жϻ��˵��ӵ��Ƿ�ɳ���Ļ
	bool isBulletOutOfScreen(Bullet* bullet);

	// �ж��ӵ��Ƿ���� Tauren
	bool isBulletHitTauren(Bullet* bullet);

	// �����ӵ����� Tauren
	void workBulletHitTauren(Bullet* bullet);

	// �����ӵ�
	void updateBullets();

	// ���ص�Ļ��ť
	void loadBarrageButton(Point position, int z, int tag = -1);

	// ������Ļ�Ļص�����
	void barrageButtonCallback(Ref* pSender);

	// ���ص�Ļ������
	void loadBarrageEmitter();

	// ���µ�Ļ
	void updateBarrage();

	// ���� Hero ������
	void updateHeroBeStruckFly();
};

#endif