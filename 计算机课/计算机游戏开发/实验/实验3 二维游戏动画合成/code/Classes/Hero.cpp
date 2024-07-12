#include "Hero.h"

Hero::Hero() {
}

Hero::~Hero() {
}

void Hero::setArmature(Armature* _armature) {
	armature = _armature;
}

Armature* Hero::getArmature() {
	return armature;
}

int Hero::getMaxHP() {
	return maxHP;
}

void Hero::setHP(int _HP) {
	HP = _HP;
}

int Hero::getHP() {
	return HP;
}

void Hero::setState(State _state) {
	state = _state;
}

State Hero::getState() {
	return state;
}

void Hero::setIsRunning(bool _isRunning) {
	isRunning = _isRunning;
}

bool Hero::getIsRunning() {
	return isRunning;
}

void Hero::setIsAttacking(bool _isAttacking) {
	isAttacking = _isAttacking;
}

bool Hero::getIsAttacking() {
	return isAttacking;
}

void Hero::setIsHurt(bool _isHurt) {
	isHurt = _isHurt;
}

bool Hero::getIsHurt() {
	return isHurt;
}

void Hero::setIsDead(bool _isDead) {
	isDead = _isDead;
}

bool Hero::getIsDead() {
	return isDead;
}

Hero* Hero::create(int _maxHP, Point position) {
	Hero* pRet = new(std::nothrow) Hero();
	if (pRet && pRet->init(_maxHP, position)) {
		pRet->autorelease();
		return pRet;
	}
	else {
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}
}

bool Hero::init(int _maxHP, Point position) {
	if (!Sprite::init()) {
		return false;
	}

	maxHP = _maxHP;
	HP = maxHP;
	isRunning = false;
	isAttacking = false;
	isHurt = false;
	isDead = false;
	isDefensing = false;
	smittenLock = 0;
	struckFlySpeed = 0;

	ArmatureDataManager::getInstance()->addArmatureFileInfo(ANIMATION_HERO_PATH.c_str());
	armature = Armature::create("Hero");
	if (!armature) {
		CCLOG("Hero loaded failed.");
		return false;
	}

	armature->setPosition(Point::ZERO);
	armature->getAnimation()->play("loading");
	armature->getAnimation()->setFrameEventCallFunc(
		CC_CALLBACK_0(Hero::onFrameEvent, this,
			std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4)
	);

	this->addChild(armature);
	this->setPosition(position);
	this->scheduleUpdate();

	return true;
}

void Hero::update(float dt) {
	if (HP <= 0) {
		switchState(DEAD);
	}

	switch (state) {
		case STAND: {
			// �ܶ�����ִֻ��һ�� loading , ������ attack �����޷�����
			// if (!isDead && isRunning && !isHurt) {
			if (!isDead && isRunning) {
				armature->getAnimation()->play("loading");
				isRunning = false;
			}

			break;
		}
		case MOVELEFT: {
			// if (!isDead && this->getPositionX() > 0 && !isHurt && !isAttacking) {
			if (!isDead && this->getPositionX() > 0 && !isAttacking) {
				if (!isRunning) {
					armature->getAnimation()->play("run");
					isRunning = true;
				}

				// if (armature->getScaleX() != 1) {
				if (doubleCompare(armature->getScaleX(), -1)) {
					armature->setScaleX(-1);
				}

				// this->setPositionX(this->getPositionX() - SPEED_X);
			}

			break;
		}
		case MOVERIGHT: {
			// if (!isDead && this->getPositionX() < Director::getInstance()->getVisibleSize().width && !isHurt && !isAttacking) {
			if (!isDead && this->getPositionX() < Director::getInstance()->getVisibleSize().width && !isAttacking) {
				if (!isRunning) {
					armature->getAnimation()->play("run");
					isRunning = true;
				}

				// if (armature->getScaleX() != -1) {
				if (doubleCompare(armature->getScaleX(), 1)) {
					armature->setScaleX(1);
				}

				// this->setPositionX(this->getPositionX() + SPEED_X);
			}

			break;
		}
		case ATTACK: {
			// if (!isDead && !isHurt) {
			if (!isDead) {
				armature->getAnimation()->play("attack");
				isAttacking = true;

				// ���Ź�����Ч
				SimpleAudioEngine::getInstance()->playEffect(HIT_METAL_PATH.c_str());
			}

			break;
		}
		case DEAD: {
			if (!isDead) {
				armature->getAnimation()->play("death");
				isDead = true;
			}
			
			break;
		}
		case SMITTEN: {
			if (!isDead && isHurt) {
				armature->getAnimation()->play("smitten");
				// isHurt = false;
			}

			break;
		}
		case DEFENSE: {
			if (!isDead) {
				armature->getAnimation()->play("defend");
				isDefensing = true;
			}

			break;
		}
	}

	// ���˵���
	if (smittenLock) {
		smittenLock++;
		if (smittenLock >= HERO_SMITTEN_LOCK) {
			smittenLock = 0;
		}
	}
}

// �л�״̬
void Hero::switchState(State _state) {
	if (_state == SMITTEN) {
		armature->getAnimation()->play("smitten");
		isHurt = true;
		isDefensing = false;
	}
	
	state = _state;
}

// ֡����
void Hero::onFrameEvent(cocostudio::Bone* bone, const std::string& evt, int originFrameIndex, int currentFrameIndex) {
	if (evt == "attack_end") {
		armature->getAnimation()->play("loading");
		isAttacking = false;
	}
	else if (evt == "smitten_end") {
		armature->getAnimation()->play("loading");
		isHurt = false;
	}
	else if (evt == "defense_end") {
		armature->getAnimation()->play("loading");
		isDefensing = false;
	}
}

// ����
void Hero::playHurt() {
	// ���������ڼ䲻����
	if (smittenLock) {
		return;
	}

	smittenLock = 1;
	if (isDefensing) {
		displayBloodTips(std::max(BASIC_DAMAGE - DEFENSE_DAMAGE, 0));
	}
	else {
		displayBloodTips(BASIC_DAMAGE);
	}
	this->switchState(SMITTEN);
}

// ��ʾ��Ѫ (ƽ A)
void Hero::displayBloodTips(int basicDamage) {
	// 20% Miss
	int missRand = generateRandomInteger(1, 10);
	if (missRand <= 2) {
		auto label = Label::createWithBMFont(TIPS_FNT_PATH, "Miss");
		label->setColor(Color3B::GREEN);
		label->setPosition(Point(20 + generateRandomInteger(0, 80), 10 + generateRandomInteger(0, 80)));
		label->runAction(
			Sequence::create(
				MoveBy::create(0.7f, Point(0, 30)),
				CallFunc::create(CC_CALLBACK_0(Hero::bloodTipFlyEnd, this, label)),
				nullptr
			)
		);

		this->addChild(label, 15);

		return;
	}

	// 20% ������, 5% ������
	int hitCount = 1;  // ��������
	int hitRand = generateRandomInteger(1, 100);
	if (hitRand <= 5) {
		hitCount = 3;
	}
	else if (hitRand <= 20) {
		hitCount = 2;
	}
	// hitCount = 1;  // ȡ������

	for (int i = 0; i < hitCount; i++) {
		int damage;

		// 20% ����
		int criticalRand = generateRandomInteger(1, 10);
		if (criticalRand <= 2) {
			damage = basicDamage + generateRandomInteger(10, 20);
		}
		else {
			damage = basicDamage + generateRandomInteger(0, 10);
		}
		// damage = basicDamage;  // ȡ�����������
		setHP(HP - damage);

		auto label = Label::createWithBMFont(TIPS_FNT_PATH, StringUtils::format("-%d", damage));
		if (criticalRand <= 2) {
			label->setColor(Color3B::RED);  // ����Ϊ��ɫ
		}
		else {
			label->setColor(Color3B::ORANGE);  // �Ǳ���Ϊ��ɫ
		}
		label->setPosition(Point(20 + generateRandomInteger(0, 80), 10 + generateRandomInteger(0, 80)));
		label->runAction(
			Sequence::create(
				MoveBy::create(0.7f, Point(0, 30)), 
				CallFunc::create(CC_CALLBACK_0(Hero::bloodTipFlyEnd, this, label)),
				nullptr
			)
		);

		this->addChild(label, 15);
	}
}

// ��Ѫ�������Ʋ���ʧ
void Hero::bloodTipFlyEnd(Label* label) {
	label->setVisible(false);
	label->removeFromParent();
}

void Hero::setIsDefensing(bool _isDefensing) {
	isDefensing = _isDefensing;
}

bool Hero::getIsDefensing() {
	return isDefensing;
}

void Hero::setStruckFlySpeed(float _struckFlySpeed) {
	struckFlySpeed = _struckFlySpeed;
}

float Hero::getStruckFlySpeed() {
	return struckFlySpeed;
}

// ��ʾ��Ѫ (����)
void Hero::displayBloodTip(int basicDamage) {
	int damage = basicDamage + generateRandomInteger(0, 10);
	setHP(HP - damage);

	auto label = Label::createWithBMFont(TIPS_FNT_PATH, StringUtils::format("-%d", damage));
	label->setColor(Color3B::RED);
	label->setPosition(Point(20 + generateRandomInteger(0, 80), 10 + generateRandomInteger(0, 80)));
	label->runAction(
		Sequence::create(
			MoveBy::create(0.7f, Point(0, 30)),
			CallFunc::create(CC_CALLBACK_0(Hero::bloodTipFlyEnd, this, label)),
			nullptr
		)
	);

	this->addChild(label, 15);
}
