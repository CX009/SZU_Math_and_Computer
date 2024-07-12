#include "Level1Scene.h"

Level1Scene::Level1Scene() {
}

Level1Scene::~Level1Scene() {
}

Scene* Level1Scene::createScene() {
	auto scene = Scene::create();
	auto layer = Level1Scene::create();
	scene->addChild(layer);
	return scene;
}

bool Level1Scene::init() {
	if (!Layer::init()) {
		return false;
	}

// ---------= ��ʼ������ =---------
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	// pause = true;
	pause = false;

// ---------= ���½ǹرհ�ť =---------
	auto closeItem = MenuItemImage::create(
		CLOSE_BUTTON_PATH,
		CLOSE_BUTTON_SELECTED_PATH,
		CC_CALLBACK_1(Level1Scene::closeMenuCallback, this));
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));
	auto closeMenu = Menu::create(closeItem, NULL);
	closeMenu->setPosition(Vec2::ZERO);
	this->addChild(closeMenu, 100);

// ---------= ���س��� =---------
	// ���ش�ɫ����
	loadPureBackground();

	// �����Թ���ͼ
	loadTiledMaze(MAP_WIDTH, MAP_HEIGHT, Point(visibleSize.width / 2, visibleSize.height - MAP_HEIGHT * MAP_UNIT / 2), 0, TILED_MAZE_1_PATH);  // �������Ϸ�

	// ���ػ�ͼ�ڵ�
	loadPathDrawer(5);

	// ����èβ��
	auto cattailPoint = getRandomAvailablePoint();
	Point cattailPosition = mapCoordinate2ScreenCoordinate(cattailPoint);
	loadCattail(cattailPosition, 3);
	occupyAvailablePoint(cattailPoint);

	// ���ؼ��ǽ
	loadWalnut(Point(0, 2 * visibleSize.height), 3, false);

	// ���ؽ�ֹ
	loadForbidden(Point(0, 0), 5, false);

	// ������ʾ��Ϣ
	loadPlaceTip();
	loadFindTip();
	loadNoWayTip();
	loadDangerousTip();

	// ���ز�����Ϣ
	displayLevel();

	// ������� item
	generateRandomItems();

	// ��ʼ������
	// touchingPoint = Point(0, 0);
	canPlace = true;
	walnutInDangerous = false;

// ---------= ��������Ч =---------
	preloadSounds();
	playBackgroundMusic(BGM_PATH);

// ---------= ��Ӽ��� =---------
	addKeyboardListener();  // ��Ӽ��̼���
	addTouchListener();  // ��Ӵ�������

// ---------= Update =---------
	this->scheduleUpdate();

	CCLOG("Level1Scene initialized successfully.");

	return true;
}

void Level1Scene::update(float dt) {
	if (pause) {
		return;
	}

	collisionDetection();


// ---------= ������ =---------
	// CCLOG(("(" + std::to_string(touchingPoint.x) + ", " + std::to_string(touchingPoint.y) + ")").c_str());

	/* // ����Թ��Ŀ�ͨ�������ת��
	auto accessibleMatrix = tiledMaze->getAccessibleMatrix();
	std::vector<std::string> accessibleText(MAP_WIDTH);
	for (int i = 0; i < MAP_WIDTH; i++) {
		for (int j = 0; j < MAP_HEIGHT; j++) {
			accessibleText[i] += std::to_string(accessibleMatrix[i][j]) + " ";
		}
		CCLOG(accessibleText[i].c_str());
	}
	CCLOG("");*/

	/* // ���èβ�ݵ����ǽ�����·�ĳ��Ⱥ�·���ĵ���
	auto accessibleMatrix = tiledMaze->getAccessibleMatrix();
	std::pair<int, int> st = screenCoordinate2MapCoordinate(cattail->getPosition());
	std::pair<int, int> ed = screenCoordinate2MapCoordinate(walnut->getPosition());
	AStar solver(MAP_WIDTH, MAP_HEIGHT, accessibleMatrix, st, ed);
	CCLOG((std::to_string(solver.getMinDistance())).c_str());
	CCLOG(("    " + std::to_string(solver.getPath().size())).c_str());*/
}

// Ԥ��������
void Level1Scene::preloadSounds() {
	preloadBackgroundMusic(BGM_PATH);
	preloadSoundEffect(FIND_SOUND_PATH);
	preloadSoundEffect(DANGEROUS_SOUND_PATH);
	preloadSoundEffect(SPEED_UP_SOUND_PATH);
	preloadSoundEffect(SPEED_DOWN_SOUND_PATH);
	preloadSoundEffect(VICTORY_SOUND_PATH);
}

// ���̼����Ļص�����
void Level1Scene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
	switch (keyCode) {
		case EventKeyboard::KeyCode::KEY_ESCAPE: {  // ESC: �ر�
			Director::getInstance()->end();
			break;
		}
		case EventKeyboard::KeyCode::KEY_R: {  // R: ����
			Director::getInstance()->replaceScene(Level1Scene::createScene());
			break;
		}
		case EventKeyboard::KeyCode::KEY_SPACE: {  // �ո�: 
			pause = false;

			// ���� bgm ״̬��
			break;
		}
		case EventKeyboard::KeyCode::KEY_P: {  // P: ��ͣ
			pause ^= 1;

			// ���� bgm ״̬��
			break;
		}
		case EventKeyboard::KeyCode::KEY_F: {  // F: ˢ��èβ��λ��
			// �黹�ɵ�
			auto cattailPoint = screenCoordinate2MapCoordinate(cattail->getPosition());
			returnAvailablePoint(cattailPoint);

			cattailPoint = getRandomAvailablePoint();
			Point cattailPosition = mapCoordinate2ScreenCoordinate(cattailPoint);
			cattail->setPosition(cattailPosition);
			occupyAvailablePoint(cattailPoint);
			
			break;
		}
		case EventKeyboard::KeyCode::KEY_G: {  // G: ˢ�� item λ��
			// ������
			for (auto portal : portals) {
				// �黹�ɵ�
				auto portalPoint = screenCoordinate2MapCoordinate(portal->getPosition());
				returnAvailablePoint(portalPoint);

				portalPoint = getRandomAvailablePoint();
				Point portalPosition = mapCoordinate2ScreenCoordinate(portalPoint);
				portal->setPosition(portalPosition);
				occupyAvailablePoint(portalPoint);
			}

			// ͷ­
			for (auto skull : skulls) {
				// �黹�ɵ�
				auto skullPoint = screenCoordinate2MapCoordinate(skull->getPosition());
				returnAvailablePoint(skullPoint);

				skullPoint = getRandomAvailablePoint();
				Point skullPosition = mapCoordinate2ScreenCoordinate(skullPoint);
				skull->setPosition(skullPosition);
				occupyAvailablePoint(skullPoint);
			}

			// todo: ���١�����

			break;
		}
	}
}

// ������ʼ�Ļص�����
bool Level1Scene::onTouchBegan(Touch* touch, Event* event) {
	// ��Ļ����ת��ͼ����
	auto [touchX, touchY] = screenCoordinate2MapCoordinate(touch->getLocation());
	// touchingPoint = Point(touchX, touchY);

	if (!canPlace || touchX < 0 || touchX >= MAP_WIDTH || touchY < 0 || touchY >= MAP_HEIGHT || !accessibleMatrix[touchX][touchY]) {  // ���ɷ��û�Խ��򲻿ɵ���
		forbidden->setPosition(mapCoordinate2ScreenCoordinate(touchX, touchY));
		forbidden->setVisible(true);
	}
	else if (screenCoordinate2MapCoordinate(cattail->getPosition()) == std::pair<int, int>(touchX, touchY)) {  // ���ǽ��èβ���غ�
		forbidden->setPosition(mapCoordinate2ScreenCoordinate(touchX, touchY));
		forbidden->setVisible(true);
	}
	else {  // �ɹ�����
		// ������ʾ��Ϣ
		placeTip->setVisible(false);
		findTip->setVisible(false);
		noWayTip->setVisible(false);
		dangerousTip->setVisible(false);

		// ���ü��ǽ
		canPlace = false;
		walnutInDangerous = false;
		walnut->setPosition(mapCoordinate2ScreenCoordinate(touchX, touchY));
		walnut->setVisible(true);

		// Ѱ·
		std::pair<int, int> st = screenCoordinate2MapCoordinate(cattail->getPosition());
		std::pair<int, int> ed = screenCoordinate2MapCoordinate(walnut->getPosition());
		AStar solver(MAP_WIDTH, MAP_HEIGHT, accessibleMatrix, st, ed);
		
		if (doubleCompare(solver.getMinDistance(), INF / 2) >= 0) {  // ��̾��� >= INF / 2, ����ͨ
			placeTip->setVisible(false);
			noWayTip->setVisible(true);

			canPlace = true;
		}
		else {  // ��ͨ, ��ʾ·��
			Vector<FiniteTimeAction*> actionVector;  // ��������

			auto path = solver.getPath();
			auto color = COLORS[generateRandomInteger(0, (int)COLORS.size() - 1)];
			for (int i = 1; i < path.size(); i++) {
				auto currentPoint = mapCoordinate2ScreenCoordinate(path[i]);
				pathDrawer->drawLine(mapCoordinate2ScreenCoordinate(path[i - 1]), currentPoint, color);

				auto moveAction = MoveTo::create(moveSpeed, currentPoint);
				actionVector.pushBack(moveAction);
			}

			if (actionVector.empty()) {
				return true;
			}

			auto actionSequence = Sequence::create(actionVector);
			cattail->runAction(actionSequence);
		}
	}

	return true;
}

// ���������Ļص�����
void Level1Scene::onTouchEnded(Touch* touch, Event* event) {
	forbidden->setVisible(false);

	// canPlace = true;
}

// ���ػ�ͼ�ڵ�
void Level1Scene::loadPathDrawer(int z) {
	pathDrawer = DrawNode::create();
	this->addChild(pathDrawer, z);

	moveSpeed = 0.1;
}

void Level1Scene::loadPlaceTip() {
	placeTip = Label::createWithBMFont(TIPS_FNT_PATH, PLACE_TIP);
	placeTip->setPosition(Point(
		placeTip->getContentSize().width / 2 + 20,
		(visibleSize.height - MAP_HEIGHT * MAP_UNIT) / 2
	));
	placeTip->setColor(Color3B::YELLOW);

	auto actionSequence = Sequence::create(
		FadeOut::create(1),
		FadeIn::create(1),
		nullptr
	);
	auto action = RepeatForever::create(actionSequence);
	placeTip->runAction(action);

	this->addChild(placeTip, 5);
}

void Level1Scene::loadFindTip() {
	findTip = Label::createWithBMFont(TIPS_FNT_PATH, FIND_TIP);
	findTip->setPosition(Point(
		findTip->getContentSize().width / 2 + 20,
		(visibleSize.height - MAP_HEIGHT * MAP_UNIT) / 2
	));
	findTip->setColor(Color3B::GREEN);
	findTip->setVisible(false);

	this->addChild(findTip, 5);
}

void Level1Scene::loadNoWayTip() {
	noWayTip = Label::createWithBMFont(TIPS_FNT_PATH, NO_WAY_TIP);
	noWayTip->setPosition(Point(
		noWayTip->getContentSize().width / 2 + 20,
		(visibleSize.height - MAP_HEIGHT * MAP_UNIT) / 2
	));
	noWayTip->setColor(Color3B::BLUE);
	noWayTip->setVisible(false);

	this->addChild(noWayTip, 5);
}

void Level1Scene::loadDangerousTip() {
	dangerousTip = Label::createWithBMFont(TIPS_FNT_PATH, DANGEROUS_TIP);
	dangerousTip->setPosition(Point(
		dangerousTip->getContentSize().width / 2 + 20,
		(visibleSize.height - MAP_HEIGHT * MAP_UNIT) / 2
	));
	dangerousTip->setColor(Color3B::RED);
	dangerousTip->setVisible(false);

	this->addChild(dangerousTip, 5);
}

// ���ز�����Ϣ
void Level1Scene::displayLevel() {
	auto levelTip = Label::createWithBMFont(TIPS_FNT_PATH, "Level 1");
	levelTip->setPosition(Point(
		visibleSize.width - levelTip->getContentSize().width / 2 - 20,
		(visibleSize.height - MAP_HEIGHT * MAP_UNIT) / 2
	));
	levelTip->setColor(Color3B::BLACK);
	this->addChild(levelTip);
}

// ���ش�ɫ����
void Level1Scene::loadPureBackground() {
	auto pureLayer = LayerColor::create(Color4B(222, 241, 254, 255), visibleSize.width, visibleSize.height);
	pureLayer->setPosition(Point(0, 0));
	this->addChild(pureLayer, -1);
}

// �����Թ���ͼ
void Level1Scene::loadTiledMaze(int mapWidth, int mapHeight, Point position, int z, std::string mapPath, int mapUnit, int tag) {
	tiledMaze = TiledMap::create(mapWidth, mapHeight, mapPath, mapUnit, tag);
	tiledMaze->setPosition(position);
	if (~tag) {
		tiledMaze->setTag(tag);
	}
	this->addChild(tiledMaze, z);

	// Ԥ������õ�
	accessibleMatrix = tiledMaze->getAccessibleMatrix();
	for (int i = 0; i < MAP_WIDTH; i++) {
		for (int j = 0; j < MAP_HEIGHT; j++) {
			if (accessibleMatrix[i][j]) {
				availablePoints.insert({ i, j });
			}
		}
	}
}

// ��Ļ����ת��ͼ����
std::pair<int, int> Level1Scene::screenCoordinate2MapCoordinate(Point screenPoint) {
	return screenCoordinate2MapCoordinate(screenPoint.x, screenPoint.y);
}

// ��Ļ����ת��ͼ����
std::pair<int, int> Level1Scene::screenCoordinate2MapCoordinate(float screenX, float screenY) {
	int mapX = screenX / MAP_UNIT;
	int mapY = (visibleSize.height - screenY) / MAP_UNIT;
	return std::pair<int, int>(mapX, mapY);
}

// ��ͼ����ת��Ļ���� (tile ������)
Point Level1Scene::mapCoordinate2ScreenCoordinate(std::pair<int, int> mapPoint) {
	return mapCoordinate2ScreenCoordinate(mapPoint.first, mapPoint.second);
}

// ��ͼ����ת��Ļ���� (tile ������)
Point Level1Scene::mapCoordinate2ScreenCoordinate(int mapX, int mapY) {
	float screenX = mapX * MAP_UNIT + 0.5 * MAP_UNIT;
	float screenY = visibleSize.height - mapY * MAP_UNIT - 0.5 * MAP_UNIT;
	return Point(screenX, screenY);
}

// ���� Tile (�������øþ���)
void Level1Scene::loadTile(std::string path, Point position, int z, bool visible, int tag) {
	auto sprite = Sprite::create(path);
	sprite->setPosition(position);
	sprite->setVisible(visible);
	if (~tag) {
		sprite->setTag(tag);
	}
	this->addChild(sprite, z);
}

// ����èβ��
void Level1Scene::loadCattail(Point position, int z, bool visible, int tag) {
	cattail = Sprite::create(CATTAIL_TILE_PATH);
	cattail->setPosition(position);
	cattail->setVisible(visible);
	if (~tag) {
		cattail->setTag(tag);
	}
	this->addChild(cattail, z);
}

// ���ؼ��ǽ
void Level1Scene::loadWalnut(Point position, int z, bool visible, int tag) {
	walnut = Sprite::create(WALNUT_TILE_PATH);
	walnut->setPosition(position);
	walnut->setVisible(visible);
	if (~tag) {
		walnut->setTag(tag);
	}
	this->addChild(walnut, z);
}

// ���ؽ�ֹ
void Level1Scene::loadForbidden(Point position, int z, bool visible, int tag) {
	forbidden = Sprite::create(FORBIDDEN_TILE_PATH);
	forbidden->setPosition(position);
	forbidden->setVisible(visible);
	if (~tag) {
		forbidden->setTag(tag);
	}
	this->addChild(forbidden, z);
}

// ���ش�����
void Level1Scene::loadPortal(Point position, int z, bool visible, int tag) {
	auto portal = Sprite::create(PORTAL_TILE_PATH);
	portal->setPosition(position);
	portal->setVisible(visible);
	if (~tag) {
		portal->setTag(tag);
	}
	this->addChild(portal, z);

	portals.push_back(portal);
}

// ����ͷ­
void Level1Scene::loadSkull(Point position, int z, bool visible, int tag) {
	auto skull = Sprite::create(SKULL_TILE_PATH);
	skull->setPosition(position);
	skull->setVisible(visible);
	if (~tag) {
		skull->setTag(tag);
	}
	this->addChild(skull, z);

	skulls.push_back(skull);
}

// ���ؼ���
void Level1Scene::loadSpeedDown(Point position, int z, bool visible, int tag) {
	auto speedDown = Sprite::create(SPEED_DOWN_TILE_PATH);
	speedDown->setPosition(position);
	speedDown->setVisible(visible);
	if (~tag) {
		speedDown->setTag(tag);
	}
	this->addChild(speedDown, z);

	speedDowns.push_back(speedDown);
}

// ���ؼ���
void Level1Scene::loadSpeedUp(Point position, int z, bool visible, int tag) {
	auto speedUp = Sprite::create(SPEED_UP_TILE_PATH);
	speedUp->setPosition(position);
	speedUp->setVisible(visible);
	if (~tag) {
		speedUp->setTag(tag);
	}
	this->addChild(speedUp, z);

	speedUps.push_back(speedUp);
}

// ���ȡһ�����õĵ�
std::pair<int, int> Level1Scene::getRandomAvailablePoint() {
	std::vector<std::pair<int, int>> candidates;
	for (auto availablePoint : availablePoints) {
		candidates.push_back(availablePoint);
	}

	return candidates[generateRandomInteger(0, (int)candidates.size() - 1)];
}

// ռ��һ�����õĵ�
void Level1Scene::occupyAvailablePoint(std::pair<int, int> point) {
	availablePoints.erase(point);
	usedAvailablePoints.insert(point);
}

// �黹һ�����õĵ�
void Level1Scene::returnAvailablePoint(std::pair<int, int> point) {
	usedAvailablePoints.erase(point);
	availablePoints.insert(point);
}

// �ָ����õĵ�
void Level1Scene::recoverAvailablePoints() {
	for (auto availablePoint : usedAvailablePoints) {
		availablePoints.insert(availablePoint);
	}
	usedAvailablePoints.clear();
}

// ��ײ���
void Level1Scene::collisionDetection() {
	// èβ����ͷ­ (���ж�Σ��)
	for (auto skull : skulls) {
		if (screenCoordinate2MapCoordinate(cattail->getPosition()) == screenCoordinate2MapCoordinate(skull->getPosition())) {
			dangerousTip->setVisible(true);

			cattail->stopAllActions();

			canPlace = false;

			playSoundEffect(DANGEROUS_SOUND_PATH);
		}

		// ���ǽ��ͷ­λ��
		if (screenCoordinate2MapCoordinate(skull->getPosition()) == screenCoordinate2MapCoordinate(walnut->getPosition())) {
			walnutInDangerous = true;
			return;
		}
	}

	// èβ������ǽ
	if (!walnutInDangerous && screenCoordinate2MapCoordinate(cattail->getPosition()) == screenCoordinate2MapCoordinate(walnut->getPosition())) {
		findTip->setVisible(true);

		walnut->setPosition(Point(0, 2 * visibleSize.height));
		walnut->setVisible(false);

		canPlace = true;

		playSoundEffect(FIND_SOUND_PATH);
	}

	// èβ���봫����
	for (auto portal : portals) {
		if (screenCoordinate2MapCoordinate(cattail->getPosition()) == screenCoordinate2MapCoordinate(portal->getPosition())) {
			Director::getInstance()->replaceScene(Level2Scene::createScene());
		}
	}

	/* // èβ�������
	for (auto speedDown : speedDowns) {
		if (screenCoordinate2MapCoordinate(cattail->getPosition()) == screenCoordinate2MapCoordinate(speedDown->getPosition())) {

		}
	}

	// èβ�������
	for (auto speedUp : speedUps) {
		if (screenCoordinate2MapCoordinate(cattail->getPosition()) == screenCoordinate2MapCoordinate(speedUp->getPosition())) {

		}
	}*/
}

// �����δռ�õĵ������� item
void Level1Scene::generateRandomItems() {
	std::vector<std::pair<int, int>> candidates;
	for (auto availablePoint : availablePoints) {
		candidates.push_back(availablePoint);
	}
	shuffle(candidates.begin(), candidates.end(), rnd);

	assert(candidates.size());

	// ������������� item , ���� 1 ��
	int cnt = generateRandomInteger(1, std::max((int)(candidates.size() * 0.1) - 1, 1));
	for (int i = 0; i < cnt; i++) {
		Point position = mapCoordinate2ScreenCoordinate(candidates[i]);

		// �������һ�� item
		// int randomItemIndex = generateRandomInteger(1, 4);
		int randomItemIndex = generateRandomInteger(1, 2);  // Ŀǰֻ֧�ִ����ź�ͷ­
		if (randomItemIndex == 1) {
			loadPortal(position, 3, true);
		}
		else if (randomItemIndex == 2) {
			loadSkull(position, 3, true);
		}
		else if (randomItemIndex == 3) {
			loadSpeedDown(position, 3, true);
		}
		else {
			loadSpeedUp(position, 3, true);
		}

		occupyAvailablePoint(candidates[i]);
	}
}



