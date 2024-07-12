#ifndef __TAUREN_AI_H__
#define __TAUREN_AI_H__

#include "Headers.h"
#include "Config.h"
#include "Hero.h"
#include "Tauren.h"

enum TaurenDirection {
	FACELEFT, 
	FACERIGHT
};

class TaurenAI : public Node {
private:
	Hero* hero;
	Tauren* tauren;
	
	State taurenState;

	TaurenDirection taurenDirection;  // Tauren ����ķ���
	int taurenSwitchAction;  // Tauren �ı������ʱ��

	int defenseCD;
	int stealthCD;
	int strikeFlyCD;

public:
	TaurenAI();

	~TaurenAI();

	static TaurenAI* create(Node* parent);

	bool init(Node* parent);

	void update(float dt);

	void setAI(Hero* _hero, Tauren* _tauren);

	void stand();

	void moveLeft();

	void moveRight();

	void attack();

	void setTaurenState(State _taurenState);

	State getTaurenState();

	// ���� TaurenAI
	void startAction(TaurenDirection _taurenDirection = TaurenDirection::FACELEFT);
	
	// ֹͣ TaurenAI
	void stopAction();

	void setTaurenDirection(TaurenDirection _taurenDirection);

	TaurenDirection getTaurenDirection();

	void setTaurenSwitchAction(int _taurenSwitchAction);

	int getTaurenSwitchAction();

	// ���¶�������
	void updateTaurenAction();

	// �������м���
	void updateSkills();

	void setDefenseCD(int _defenseCD);
	
	int getDefenseCD();

	void setStealthCD(int _stealthCD);

	int getStealthCD();

	void setStrikeFlyCD(int _strikeFlyCD);

	int getStrikeFlyCD();
};

#endif