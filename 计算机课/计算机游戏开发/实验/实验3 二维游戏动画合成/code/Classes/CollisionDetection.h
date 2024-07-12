#ifndef __COLLISION_DETECTION_H__
#define __COLLISION_DETECTION_H__

#include "Headers.h"
#include "Config.h"
#include "Hero.h"
#include "Tauren.h"
#include "TaurenAI.h"

class CollisionDetection : public Node {
private:
	Hero* hero;
	Tauren* tauren;
	TaurenAI* taurenAI;

public:
	CollisionDetection();

	~CollisionDetection();
	
	static CollisionDetection* create(Node* parent, Hero* _hero, Tauren* _tauren, TaurenAI* _taurenAI);

	bool init(Node* parent, Hero* _hero, Tauren* _tauren, TaurenAI* _taurenAI);

	void update(float dt);

	void setHero(Hero* _hero);

	Hero* getHero();

	void setTauren(Tauren* _tauren);

	Tauren* getTauren();

	// �ж� Hero �ܷ񹥻��� Tauren
	bool canHeroAttackTauren();

	// �ж� Tauren �ܷ񹥻��� Hero
	bool canTaurenAttackHero();
};

#endif