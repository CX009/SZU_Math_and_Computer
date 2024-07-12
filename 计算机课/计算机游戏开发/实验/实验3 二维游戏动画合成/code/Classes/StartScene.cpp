#include "StartScene.h"

StartScene::StartScene() {
}

StartScene::~StartScene() {
}

Scene* StartScene::createScene() {
	auto scene = Scene::create();
	auto layer = StartScene::create();
	scene->addChild(layer);
	return scene;
}

bool StartScene::init() {
	if (!Layer::init()) {
		return false;
	}

	// ---------= ��ʼ������ =---------
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	pause = true;
	// pause = false;
	storyPercent = 0;

	// ---------= ���½ǹرհ�ť =---------
	auto closeItem = MenuItemImage::create(
		CLOSE_BUTTON_PATH,
		CLOSE_BUTTON_SELECTED_PATH,
		CC_CALLBACK_1(StartScene::closeMenuCallback, this));
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));
	auto closeMenu = Menu::create(closeItem, NULL);
	closeMenu->setPosition(Vec2::ZERO);
	this->addChild(closeMenu, 100);

	// ---------= ���س��� =---------
	loadImage(START_BACKGROUND_PATH, Point(visibleSize.width / 2, visibleSize.height / 2), 0);

	loadImage(START_STORY_PATH, Point(visibleSize.width / 2, 2 * visibleSize.height), 0, 1);  // y �ڿ���������
	story = (Sprite*)getChildByTag(1);

	loadKeyboardHint(START_AND_PAUSE_HINT, 10, START_AND_PAUSE_HINT_TAG);

	// ---------= ��Ӽ��� =---------
	addKeyboardListener();

	// ---------= Update =---------
	this->scheduleUpdate();

	CCLOG("StartScene initialized successfully.");

	return true;
}

void StartScene::update(float dt) {
	if (pause) {
		return;
	}

	if (doubleCompare(storyPercent, 1) >= 0) {
		pause = true;

		loadKeyboardHint(REPLAY_AND_NEXT_HINT, 10);

		return;
	}

	storyPercent += HINT_DELTA_PERCENT;
	story->setTextureRect(Rect(0, 0, visibleSize.width, visibleSize.height * storyPercent));
	story->setPositionY(visibleSize.height / 2 + (1 - storyPercent) * visibleSize.height / 2);
}

// ���̼����Ļص�����
void StartScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
	switch (keyCode) {
		case EventKeyboard::KeyCode::KEY_ESCAPE: {  // ESC: �ر�
			Director::getInstance()->end();
			break;
		}
		case EventKeyboard::KeyCode::KEY_SPACE: {  // �ո�: 
			pause = false;

			auto startAndPauseHint = getChildByTag(START_AND_PAUSE_HINT_TAG);
			if (startAndPauseHint) {
				removeChildByTag(START_AND_PAUSE_HINT_TAG);
			}

			// ���� bgm ״̬��
			break;
		}
		case EventKeyboard::KeyCode::KEY_P: {  // P: ��ͣ
			pause ^= 1;

			// ���� bgm ״̬��
			break;
		}
		case EventKeyboard::KeyCode::KEY_N: {  // N: ��һ��
			auto newScene = Level1Scene::createScene();
			Director::getInstance()->pushScene(newScene);

			break;
		}
		case EventKeyboard::KeyCode::KEY_R: {  // R: ����
			auto newScene = StartScene::createScene();
			Director::getInstance()->replaceScene(newScene);

			break;
		}
	}
}