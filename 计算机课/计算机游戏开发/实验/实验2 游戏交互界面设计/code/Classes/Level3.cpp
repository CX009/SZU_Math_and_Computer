#include "Level3.h"
#include "Login.h"

USING_NS_CC;

Level3::Level3() : currentTime(0, 0, 0), DELTA_TIMER(100), END_TIME(Time(0, 15, 0)), TARGET_SCORE(10),
	MIN_LINE_Y(100), MAX_LINE_Y(400), MOVE_TIMER(200) {
}

Level3::~Level3() {
}

Scene* Level3::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = Level3::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

void Level3::loadHitLine(std::string linePath, int y, int z) {
	auto line = Sprite::create(linePath);
	hitLine.setLine(line);
	line->setPosition(Point(visibleSize.width / 2, y));
	this->addChild(line, z);
}

// ���� note : ���ࡢʱ�䡢��ʼ x ����
// type = -1 ʱΪ�������, time = (0, 0, 0) ʱΪ���ʱ��, x = -1 ʱΪ�����ʼ x ����
void Level3::loadNote(int type, Time time, float x) {
	if (type == -1) {
		type = generateRandomInteger(1, 3);
	}

	// ���� note ������õ�·���� tag
	std::string notePath;
	int tag;
	if (type == 1) {
		notePath = NOTE1_PATH;
		tag = NOTE1_TAG;
	}
	else if (type == 2) {
		notePath = NOTE2_PATH;
		tag = NOTE2_TAG;
	}
	else {
		notePath = NOTE3_PATH;
		tag = NOTE3_TAG;
	}

	// �½� note
	Note newNote;
	auto note = Sprite::create(notePath);
	newNote.setNote(note);

	if (time == Time(0, 0, 0)) {
		time.setTime(0, generateRandomInteger(1, 5), 0);
	}

	newNote.setTime(time);
	newNote.setLine(&hitLine);
	newNote.setWidth(note->getContentSize().width);
	newNote.setHeight(note->getContentSize().height);
	newNote.setLastSpeed(generateRandomInteger(3, 5));
	newNote.setArrived(false);
	newNote.setLocked(false);
	newNote.setTimer(0);

	if (!cmp(x, -1)) {
		x = generateRandomInteger(
			std::floor(BOARD_WIDTH_BIAS + newNote.getWidth() / 2),
			std::ceil(BOARD_WIDTH_BIAS + BOARD_WIDTH - newNote.getWidth() / 2)
		);
	}

	// ���� note ���볡��
	note->setPosition(Point(x, visibleSize.height));
	this->addChild(note, 5);

	// ���� note ���볡�� notes ��
	notes.push_back(newNote);
}

void Level3::createNote(float dt) {
	total_notes++;
	loadNote(-1, Time(0, 0, 0), -1);
}

void Level3::preloadSounds() {
	// Ԥ������Ч
	SimpleAudioEngine::getInstance()->preloadEffect(HIT_SOUND_PATH.c_str());
	
	// Ԥ��������
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic(MIRAGE_PATH.c_str());
}

bool Level3::init() {
	if (!Layer::init()) {
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// ���ر���
	loadBackground(BACKGROUND_PATH, 0);
	// �������
	loadBoard(BOARD3_PATH, 1);
	// �����ж���
	loadHitLine(LINE_PATH, 200, 2);

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	// �ƶ�����
	bean = Sprite::create("Chapter10/bean.png");
	bean->setPosition(Point(visibleSize.width / 2, 100));
	this->addChild(bean, 6);

	// ҡ��
	m_joystick = Joystick::create(Vec2(100, 100), 63.0f, "Chapter10/j-btn.png", "Chapter10/j-bg.png");
	this->addChild(m_joystick, 4);

	this->scheduleUpdate();

	// loadNote(-1, Time(0, 1, 0), -1);
	// loadNote(-1, Time(0, 2, 0), -1);
	// loadNote(-1, Time(0, 3, 0), -1);

	// �Ʒְ�
	modifyScore(0);

	// ��������
	SimpleAudioEngine::getInstance()->playBackgroundMusic(MIRAGE_PATH.c_str());
	
	// ��ͣ��Ϸ
	pause = true;
	SimpleAudioEngine::getInstance()->pauseBackgroundMusic();

	// ��Ӽ��̼���
	addKeyboardListener();

	// ������ʾ��Ϣ
	loadHint(LEVEL3_HINT_PATH, LEVEL3_HINT_TAG, 10);

	// note ������
	total_notes = 0;
	perfect_notes = 0;
	good_notes = 0;
	miss_notes = 0;
	bad_notes = 0;

	return true;
}

// 0 Ϊ Miss, 1 Ϊ Perfect, 2 Ϊ Good, 3 Ϊ Bad
void Level3::workHit(Note& note, int state) {
	Point position = note.getPosition();
	note.setLocked(true);
	
	switch (state) {
		case 0: {  // Miss
			// ����
			auto miss = Sprite::create(MISS_PATH);
			miss->setPosition(position);
			this->addChild(miss, 8);
			hitTips.push_back(miss);

			// ����
			miss_notes++;

			trash.push_back(note);
			break;
		}

		case 1: {  // Perfect
			// ����
			auto perfect = Sprite::create(PERFECT_PATH);
			perfect->setPosition(position);
			this->addChild(perfect, 8);
			hitTips.push_back(perfect);

			// Ч��
			auto hit = Sprite::create(HIT_PATH);
			hit->setPosition(position);
			this->addChild(hit, 7);
			hitEffects.push_back(hit);

			// ��Ч
			SimpleAudioEngine::getInstance()->playEffect(HIT_SOUND_PATH.c_str());

			// �÷�
			modifyScore(score + 2);

			// ����
			perfect_notes++;

			trash.push_back(note);

			break;
		}

		case 2: {  // Good
			// ����
			auto good = Sprite::create(GOOD_PATH);
			good->setPosition(position);
			this->addChild(good, 8);
			hitTips.push_back(good);

			// Ч��
			auto hit = Sprite::create(HIT_PATH);
			hit->setPosition(position);
			this->addChild(hit, 7);
			hitEffects.push_back(hit);

			// ��Ч
			SimpleAudioEngine::getInstance()->playEffect(HIT_SOUND_PATH.c_str());

			// �÷�
			modifyScore(score + 1);

			// ����
			good_notes++;

			trash.push_back(note);
			break;
		}

		case 3: {  // Bad
			// ����
			auto bad = Sprite::create(BAD_PATH);
			bad->setPosition(position);
			this->addChild(bad, 8);
			hitTips.push_back(bad);

			// �÷�
			modifyScore(score - 1);

			// ����
			bad_notes++;

			break;
		}

		default:
			assert(false);
	}
}

void Level3::updateWords() {
	std::vector<Label*> trash;
	for (auto& wordTip : wordsTips) {
		auto opacity = wordTip->getOpacity();
		wordTip->setOpacity(opacity - DELTA_OPACITY);
		if (wordTip->getOpacity() <= 50) {
			trash.push_back(wordTip);
		}
	}

	for (auto& wordTip : trash) {
		this->removeChild(wordTip);
		wordsTips.erase(find(wordsTips.begin(), wordsTips.end(), wordTip));
	}
}

void Level3::updateNotes(Time currentTime) {
	for (auto& note : notes) {
		// note �ѵ��ж���
		if (currentTime > note.getTime() || currentTime == note.getTime()) {
			note.setArrived(true);
			float dis = note.getLine()->getY() - note.getPosition().y;
			if (cmp(dis, note.getHeight()) > 0) {  // Miss
				workHit(note, 0);
				continue;
			}
		}

		// note ���ж��ߺ��Ժ㶨�ٶ�����
		float speed = note.getLastSpeed();
		if (!note.getArrived()) {
			speed = note.calculateSpeed(currentTime);
		}
		note.fall(speed);
		note.setLastSpeed(speed);

		note.updateTimer();
	}

	// ɾ���� Miss �� notes
	for (auto& note : trash) {
		this->removeChild(note.getNote());
		auto it = find(notes.begin(), notes.end(), note);
		auto idx = it - notes.begin();
		if (idx != -1) {
			notes.erase(it);
		}
	}
	trash.clear();
}

void Level3::updateHits() {
	// ������Ч
	std::vector<Sprite*> trashEffects;
	for (auto& effect : hitEffects) {
		float scale = effect->getScale();
		effect->setScale(scale + DELTA_SCALE);
		float angle = effect->getRotation();
		effect->setRotation(angle + DELTA_ANGLE);
		float opacity = effect->getOpacity();
		effect->setOpacity(opacity - DELTA_OPACITY);

		if (effect->getOpacity() < 75) {
			trashEffects.push_back(effect);
		}
	}
	for (auto& effect : trashEffects) {
		this->removeChild(effect);
		hitEffects.erase(find(hitEffects.begin(), hitEffects.end(), effect));
	}

	// ��������
	std::vector<Sprite*> trashTips;
	for (auto& tip : hitTips) {
		Point position = tip->getPosition();
		tip->setPosition(Point(position.x, position.y + DELTA_POSITION_Y));
		float opacity = tip->getOpacity();
		tip->setOpacity(opacity - DELTA_OPACITY);

		if (tip->getOpacity() < 75) {
			trashTips.push_back(tip);
		}
	}
	for (auto& tip : trashTips) {
		this->removeChild(tip);
		hitTips.erase(find(hitTips.begin(), hitTips.end(), tip));
	}
}

void Level3::displayResult() {
	loadResultBoard(LEVEL3_RESULT_PATH, 10);
	displayScore();
}

void Level3::update(float dt) {
	updateWords();

	if (pause) {
		return;
	}

	// ��ײ���
	for (auto& note : notes) {
		if (note.getLocked()) {
			continue;
		}

		if (note.getNote()->getBoundingBox().intersectsRect(bean->getBoundingBox())) {
			int state = note.checkHit();
			workHit(note, state);
		}
	}

	// ����ƶ��ж��� (��)
	if (currentTime.getCs() % DELTA_TIMER == 0) {
		int direction = generateRandomInteger(0, 1);
		int distance = generateRandomInteger(5, 20);
		float targetY = hitLine.getY() + (direction ? distance : -distance);
		targetY = std::max(targetY, (float)MIN_LINE_Y);
		targetY = std::min(targetY, (float)MAX_LINE_Y);
		hitLine.updatePosition(targetY);
	}

	// ���� notes (��)
	updateNotes(currentTime);
	updateHits();

	// ����̰ʳ���ƶ�
	auto direction = m_joystick->getDirection();  // ҡ���ƶ�����
	auto destination = bean->getPosition() + direction * m_joystick->getVelocity() * 0.15;  // Ԥ��Ŀ���
	auto beanSize = bean->getContentSize();  // ̰ʳ����С
	destination.x = std::max(destination.x, BOARD_WIDTH_BIAS + beanSize.width / 2),
		destination.x = std::min(destination.x, BOARD_WIDTH_BIAS + BOARD_WIDTH - beanSize.width / 2);
	destination.y = std::max(destination.y, 0 + beanSize.height / 2),
		destination.y = std::min(destination.y, BOARD_HEIGHT - beanSize.height / 2);
	bean->setPosition(destination);

	currentTime++;

	// ���� note
	if (currentTime.getCs() % DELTA_TIMER == 0) {
		createNote(0.1f);
	}

	// ʤ���ж�
	if (score >= TARGET_SCORE || currentTime > END_TIME) {
		pause = true;
		SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
		displayResult();

		if (score >= TARGET_SCORE) {
			if (perfect_notes == perfect_notes + good_notes + miss_notes) {
				displayWords("ALL PERFECT!", 20);
			}
			else {
				displayWords("SUCCESS!", 20);
			}
		}
		else {
			displayWords("GAME OVER!", 20);
		}
	}
}

void Level3::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
	switch (keyCode) {
		case EventKeyboard::KeyCode::KEY_ESCAPE: {  // ESC: �ر�
			Director::getInstance()->end();
			break;
		}
		case EventKeyboard::KeyCode::KEY_SPACE: {  // �ո�: ��ʼ��Ϸ
			this->removeChildByTag(LEVEL3_HINT_TAG);
			pause = false;
			SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
			break;
		}
		case EventKeyboard::KeyCode::KEY_P: {  // P: ��ͣ
			pause ^= 1;
			if (pause) {
				// ��������
				SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
			}
			else {
				// ��������
				SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
			}
			break;
		}
		case EventKeyboard::KeyCode::KEY_K: {  // K: ��һ��
			Director::getInstance()->popScene();
			loginScene = Login::createScene();
			Director::getInstance()->pushScene(loginScene);
			break;
		}
	}
}

void Level3::replayButtonEvent(cocos2d::Ref* pSender) {
	Director::getInstance()->popScene();
	level3Scene = Level3::createScene();
	Director::getInstance()->pushScene(level3Scene);
}

void Level3::nextButtonEvent(cocos2d::Ref* pSender) {
	Director::getInstance()->popScene();
	loginScene = Login::createScene();
	Director::getInstance()->pushScene(loginScene);
}