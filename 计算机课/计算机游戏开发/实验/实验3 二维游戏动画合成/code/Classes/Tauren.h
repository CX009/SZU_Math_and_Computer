#ifndef __TAUREN_SCENE_H__
#define __TAUREN_SCENE_H__

#include "Headers.h"
#include "Config.h"

class Tauren : public cocos2d::Sprite {
private:
	int maxHP;
	int HP;

	Armature* armature;
	State state;
	bool isRunning;
	bool isAttacking;
	bool isHurt;
	bool isDead;

	bool isDefensing;

public:
	Tauren();
	
	~Tauren();

	void setArmature(Armature* _armature);

	Armature* getArmature();

	int getMaxHP();

	void setHP(int _HP);

	int getHP();

	void setState(State _state);

	State getState();

	void setIsRunning(bool _isRunning);

	bool getIsRunning();

	void setIsAttacking(bool _isAttacking);

	bool getIsAttacking();

	void setIsHurt(bool _isHurt);

	bool getIsHurt();

	void setIsDead(bool _isDead);

	bool getIsDead();

	void setIsDefensing(bool _isDefensing);

	bool getIsDefensing();

	static Tauren* create(int _maxHP, Point position);

	bool init(int _maxHP, Point position);

	void update(float dt);

	// �л�״̬
	void switchState(State _state);

	// ֡����
	void onFrameEvent(cocostudio::Bone* bone, const std::string& evt, int originFrameIndex, int currentFrameIndex);

	// ����
	void playHurt(int bulletDamage = 0);

	// ��ʾ������Ѫ (�ӵ�)
	void displayBloodTip(int basicDamage);

	// ��ʾ�����Ѫ (ƽ A)
	void displayBloodTips(int basicDamage);

	// ��Ѫ�������Ʋ���ʧ
	void bloodTipFlyEnd(Label* label);

	// 
};

#endif