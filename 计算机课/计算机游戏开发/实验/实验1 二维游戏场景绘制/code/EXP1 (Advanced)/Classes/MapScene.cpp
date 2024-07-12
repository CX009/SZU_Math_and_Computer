#include "MapScene.h"

Scene* MapScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = MapScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool MapScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	// Ԥ������Ч
	SimpleAudioEngine::getInstance()->preloadEffect(PICKUP_SOUND_EFFECT.c_str());
	SimpleAudioEngine::getInstance()->preloadEffect(GAMEOVER_SOUND_EFFECT.c_str());
	SimpleAudioEngine::getInstance()->preloadEffect(SUCCESS_SOUND_EFFECT.c_str());

	m_isJump = false;
	m_jumpDir = Dir::STOP;
	m_jumpSpeed = PLAYER_JUMP_MAX_SPEED;
	m_gameOver = false;
	m_pause = false;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// ���ر���
	loadBackground(BACKGROUND_FILE_PATH);

	// ���ص�ͼ
	loadMap(MAP_TMX_FILE_PATH);

	// ����Ƥ��
	for (int i = 0; i < EGG_TAGS.size(); i++)
	{
		loadEgg(EGG_FILE_PATH, EGG_TAGS[i], EGG_POSITIONS[i].x, EGG_POSITIONS[i].y);
	}

	// ��������
	for (int i = 0; i < GRAIN_TAGS.size(); i++)
	{
		loadEgg(GRAIN_FILE_PATH, GRAIN_TAGS[i], GRAIN_POSITIONS[i].x, GRAIN_POSITIONS[i].y);
	}

	// ������˷�
	for (int i = 0; i < MICROPHONE_TAGS.size(); i++)
	{
		loadMicrophone(MICROPHONE_FILE_PATH, MICROPHONE_TAGS[i], MICROPHONE_POSITIONS[i].x, MICROPHONE_POSITIONS[i].y);
	}
		
	// �������
	addPlayer(Vec2(50, 380));

	// ��Ϸ�߼�
	this->scheduleUpdate();

	// ��Ӵ�������
	addTouchListener();

	// ��Ӽ��̼���
	addKeyboardListener();

	return true;
}

// ���ر��� (z = 1)
void MapScene::loadBackground(std::string backgroundPath)
{
	auto background = Sprite::create(backgroundPath);
	if (background == nullptr)
	{
		CCLOG("Background loaded failed!");
	}
	else
	{
		auto visibleSize = Director::getInstance()->getVisibleSize();
		background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
		this->addChild(background, 1);
	}
}

// ���ص�ͼ (z = 2)
void MapScene::loadMap(std::string mapPath)
{
	auto map = TMXTiledMap::create(mapPath);
	if (map != NULL)
	{
		this->addChild(map, 2);
		map->setTag(MAP_TAG);
		map->setPosition(Vec2(0, 0));
	}
	else
	{
		CCLOG("Map loaded failed!");
		return;
	}
}

// ����Ƥ�� (z = 3)
void MapScene::loadEgg(std::string eggPath, int tag, int x, int y)
{
	auto egg = Sprite::create(eggPath);
	if (egg == nullptr)
	{
		CCLOG("Egg loaded failed!");
	}
	else
	{
		egg->setTag(tag);

		auto map = (TMXTiledMap*)getChildByTag(MAP_TAG);
		float width = map->getTileSize().width, height = map->getTileSize().height;
		egg->setPosition(Vec2(width * x + ITEM_WIDTH / 2, 
			height * (map->getMapSize().height - y) - ITEM_HEIGHT / 2));  // Tiled ��������Ļ�����ת��

		this->addChild(egg, 3);
	}
}

// ������˷� (z = 3)
void MapScene::loadMicrophone(std::string microphonePath, int tag, int x, int y)
{
	auto microphone = Sprite::create(microphonePath);
	if (microphone == nullptr)
	{
		CCLOG("Egg loaded failed!");
	}
	else
	{
		microphone->setTag(tag);

		auto map = (TMXTiledMap*)getChildByTag(MAP_TAG);
		float width = map->getTileSize().width, height = map->getTileSize().height;
		microphone->setPosition(Vec2(width * x + ITEM_WIDTH / 2,
			height * (map->getMapSize().height - y) - ITEM_HEIGHT / 2));  // Tiled ��������Ļ�����ת��

		this->addChild(microphone, 3);
	}
}

// �������� (z = 3)
void MapScene::loadGrain(std::string grainPath, int tag, int x, int y)
{
	auto grain = Sprite::create(grainPath);
	if (grain == nullptr)
	{
		CCLOG("Grain loaded failed!");
	}
	else
	{
		grain->setTag(tag);
		assert(tag == 300);

		auto map = (TMXTiledMap*)getChildByTag(MAP_TAG);
		float width = map->getTileSize().width, height = map->getTileSize().height;
		grain->setPosition(Vec2(width * x + ITEM_WIDTH / 2,
			height * (map->getMapSize().height - y) - ITEM_HEIGHT / 2));  // Tiled ��������Ļ�����ת��

		this->addChild(grain, 3);
	}
}

// �������
void MapScene::addPlayer(Vec2 pos)
{
	// ����ܶ�����
	Vector<SpriteFrame*> frameVector;
	for (int i = 0; i < 4; i++)
	{
		auto spriteFrame = SpriteFrame::create(PLAYER_IMG_PATH[i], Rect(0, 0, PLAYER_WIDTH, PLAYER_HEIGHT));
		frameVector.pushBack(spriteFrame);
	}
	auto animation = Animation::createWithSpriteFrames(frameVector);
	animation->setDelayPerUnit(0.07f);
	auto animate = Animate::create(animation);

	// ������
	auto player = Sprite::create();
	player->setTag(PLAYER_TAG);
	player->runAction(RepeatForever::create(animate));
	this->addChild(player, 10);
	player->setPosition(pos);
}

int PLAYER_MAP_MOVE_SPEED = 3;  // ��Һ͵�ͼ���ƶ��ٶ�

bool item_move = true;

// Ƥ��: ����
bool speed_down = false;
int speed_down_timer = 0;

// ����: ����
bool speed_up = false;
int speed_up_timer = 0;

// ��˷�: ̫������
bool floating = false;
int floating_timer = 0;

void MapScene::update(float t)
{
	// ��Ϸ��ͣ
	if (m_pause)
	{
		return;
	}

	auto player = this->getChildByTag(PLAYER_TAG);
	auto map = (TMXTiledMap *)getChildByTag(MAP_TAG);

	// ����������Ļ������
	float player_screen_x = player->getPositionX();
	float player_screen_y = player->getPositionY() - player->getContentSize().height / 2;

	// ��ͼ�������Ļ������
	float map_screen_x = abs(map->getPositionX());
	float map_screen_y = 0;

	// �������ڵ�ͼ������
	float player_map_x = player_screen_x + map_screen_x;
	float player_map_y = player_screen_y + map_screen_y;

	bool update_position = true;
	// ����������ǰ���赲�� tile ʱ�����µ�ͼ����ҵ�λ��
	if ((int)(player_map_y / map->getTileSize().width) >= 0) 
	{
		int frontTiledID = map->getLayer(MAP_BG_LAYER_NAME)->getTileGIDAt(Vec2((int)(player_map_x / map->getTileSize().width),
				(int)(map->getMapSize().height - 2 - player_map_y / map->getTileSize().height)));
		
		// �����յ�
		if (isEndpoint(frontTiledID))
		{
			player->stopAllActions();  // ��Ҳ���
			this->unscheduleUpdate();
			// this->removeChildByTag(PLAYER_TAG);
			success();
			return;
		}
		
		if ((m_isJump == false) && (m_jumpDir == Dir::STOP) && isBlock(frontTiledID)) {
			// if (isBlock(frontTiledID)) {
			update_position = false;
		}
	}

	// Ƥ��: ����
	if (speed_down)
	{
		speed_down_timer++;
		if (speed_down_timer == EFFECT_TIME)
		{
			speed_down = false;
			speed_down_timer = 0;
			PLAYER_MAP_MOVE_SPEED++;
		}
	}
	
	// ����: ����
	if (speed_up)
	{
		speed_up_timer++;
		if (speed_up_timer == EFFECT_TIME)
		{
			speed_up = false;
			speed_up_timer = 0;
			PLAYER_MAP_MOVE_SPEED -= 2;
		}
	}

	// ��˷�: ̫������
	if (floating)
	{
		floating_timer++;
		if (floating_timer == 6 * EFFECT_TIME)
		{
			floating = false;
			floating_timer = 0;
		}
	}

	// �������
	if ((int)(player_map_y / map->getTileSize().width) >= 0)
	{
		int player_x = (int)(player_map_x / map->getTileSize().width), 
			player_y = (int)(map->getMapSize().height - 1 - player_map_y / map->getTileSize().height);  // -1 �� -2 ����

		bool pickup = false;  // �Ƿ�������

		// Ƥ��: ����
		for (int i = 0; i < EGG_TAGS.size(); i++)
		{
			if (player_x == EGG_POSITIONS[i].x && player_y == EGG_POSITIONS[i].y)
			{
				pickup = true;
				this->removeChildByTag(EGG_TAGS[i]);

				if (!speed_down)
				{
					PLAYER_MAP_MOVE_SPEED = max(PLAYER_MAP_MOVE_SPEED - 1, 1);
					speed_down = true;
				}
			}
		}

		// ����: ����
		for (int i = 0; i < GRAIN_TAGS.size(); i++)
		{
			if (player_x == GRAIN_POSITIONS[i].x && player_y == GRAIN_POSITIONS[i].y)
			{
				pickup = true;
				this->removeChildByTag(GRAIN_TAGS[i]);

				if (!speed_up)
				{
					PLAYER_MAP_MOVE_SPEED += 2;
					speed_up = true;
				}
			}
		}

		// ��˷�: ̫������
		for (int i = 0; i < MICROPHONE_TAGS.size(); i++)
		{
			if (player_x == MICROPHONE_POSITIONS[i].x && player_y == MICROPHONE_POSITIONS[i].y)
			{
				pickup = true;
				this->removeChildByTag(MICROPHONE_TAGS[i]);

				if (!floating)
				{
					floating = true;
				}
			}
		}

		/*if (pickup)
		{
			SimpleAudioEngine::getInstance()->playEffect(PICKUP_SOUND_EFFECT.c_str());
		}*/
	}

	// ����������
	if ((int)(player_map_y / map->getTileSize().width) >= 0)
	{
		int playerTiledID = map->getLayer(MAP_BG_LAYER_NAME)->getTileGIDAt(Vec2((int)(player_map_x / map->getTileSize().width), 
				(int)(map->getMapSize().height - 1 - player_map_y / map->getTileSize().height)));
		if ((m_isJump == false) && (m_jumpDir == Dir::STOP) && !isFloor(playerTiledID)) {  // �������ҽ����Ƿǵ���� tile ʱ����
			m_isJump = true;
			m_jumpDir = Dir::DOWN;
			m_jumpSpeed = PLAYER_JUMP_INITIAL_SPEED;
		}

		if (!update_position && !isFloor(playerTiledID)) {  // ����������б��赲ʱ����
			m_isJump = true;
			m_jumpDir = Dir::DOWN;
			m_jumpSpeed = PLAYER_JUMP_INITIAL_SPEED;
		}
	}

	// ������ҵ���Ծ
	if (m_isJump) {
		if (m_jumpDir == Dir::UP) {
			player->setPositionY(player->getPositionY() + m_jumpSpeed);
			m_jumpSpeed -= PLAYER_JUMP_INITIAL_SPEED;
			if (m_jumpSpeed <= 0)
			{
				m_jumpDir = Dir::DOWN;
			}
		}
		else if (m_jumpDir == Dir::DOWN)
		{
			// ���ڼ�¼����Ƿ��䵽������
			bool check = false;
			for (int i = 0; i < m_jumpSpeed; i += PLAYER_JUMP_INITIAL_SPEED) {
				// ���㵱ǰ�������ڵ�ͼ������
				float player_screen_x = player->getPositionX();
				float player_screen_y = player->getPositionY() - player->getContentSize().height / 2 + i;

				// ��ͼ�������Ļ�� x ����
				float map_screen_x = abs(map->getPositionX()); 
				float map_screen_y = 0;

				// �������ڵ�ͼ������
				float player_map_x = player_screen_x + map_screen_x; 
				float player_map_y = player_screen_y + map_screen_y;

				// ��ȡ��ҽ��µĵ�ͼ��ı��
				if (player_map_y / map->getTileSize().width >= 0) {
					int tiledID = map->getLayer(MAP_BG_LAYER_NAME)->getTileGIDAt(Vec2((int)(player_map_x / map->getTileSize().width), 
							(int)(map->getMapSize().height - 1 - player_map_y/map->getTileSize().height)));
					
					// �ж����µ� tile �Ƿ��Ǽ��
					if (isThorn(tiledID)) {
						gameOver();  // ��ɫ����
						return;  // �޸� game over �� sucess �� Bug
					}

					// �ж����µ� tile �Ƿ��ǵ���
					if (update_position && isFloor(tiledID)) {
						check = true;
						int visibleHeight = Director::getInstance()->getWinSize().height;
						player->setPositionY((int)(player_screen_y + player->getContentSize().height / 2));
						m_jumpSpeed = PLAYER_JUMP_MAX_SPEED;
						m_jumpDir = Dir::STOP;
						m_isJump = false;
						break;
					}
					else if (floating || !update_position) {  // ����������б��赲ʱ����
						m_isJump = true;
						m_jumpDir = Dir::DOWN;
						m_jumpSpeed = PLAYER_JUMP_INITIAL_SPEED;
					}
				}

				// ��������
				if (player_screen_y <= -150) {
					gameOver();  // ��ɫ����
					return;  // �޸� game over �� sucess �� Bug
				}
			}

			// ���������
			if (!check)	
			{
				player->setPositionY(player->getPositionY() - m_jumpSpeed);
				m_jumpSpeed += PLAYER_JUMP_INITIAL_SPEED;
				if (m_jumpSpeed > PLAYER_JUMP_MAX_SPEED)
				{  
					m_jumpSpeed = PLAYER_JUMP_MAX_SPEED;
				}
			}
		}
	}

	// ���赲ʱ��������ͼ�͵���
	if (!update_position) 
	{
		 return;
	}

	// ������ͼ
	this->getChildByTag(MAP_TAG)->setPositionX(this->getChildByTag(MAP_TAG)->getPositionX() - PLAYER_MAP_MOVE_SPEED);

	if (item_move)
	{
		// ����Ƥ��
		for (auto EGG_TAG : EGG_TAGS)
		{
			auto tmp = this->getChildByTag(EGG_TAG);
			if (tmp)
			{
				tmp->setPositionX(this->getChildByTag(EGG_TAG)->getPositionX() - PLAYER_MAP_MOVE_SPEED);
			}
		}

		// ��������
		for (auto GRAIN_TAG : GRAIN_TAGS)
		{
			auto tmp = this->getChildByTag(GRAIN_TAG);
			if (tmp)
			{
				tmp->setPositionX(this->getChildByTag(GRAIN_TAG)->getPositionX() - PLAYER_MAP_MOVE_SPEED);
			}
		}

		// ������˷�
		for (auto MICROPHONE_TAG : MICROPHONE_TAGS)
		{
			auto tmp = this->getChildByTag(MICROPHONE_TAG);
			if (tmp)
			{
				tmp->setPositionX(this->getChildByTag(MICROPHONE_TAG)->getPositionX() - PLAYER_MAP_MOVE_SPEED);
			}
		}
	}

	// ��ͼ������ƶ����
	int mapWidth = map->getMapSize().width * map->getTileSize().width;
	int visibleWidth = Director::getInstance()->getWinSize().width;
	if (map->getPositionX() < -(mapWidth - visibleWidth))
	{
		map->setPositionX(-(mapWidth - visibleWidth));
		item_move = false;
		player->setPositionX(player->getPositionX() + PLAYER_MAP_MOVE_SPEED);

		// �ɳ���ͼ�߽�Ҳ��ʧ��
		if (player->getPositionX() > visibleWidth)
		{
			// player->setPositionX(visibleWidth);
			this->unscheduleUpdate();
			this->removeChildByTag(PLAYER_TAG);
			gameOver();
			return;
		}
	}
}

// ��Ӵ�������
void MapScene::addTouchListener()
{
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(MapScene::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

// ���������Ļص�����
bool MapScene::onTouchBegan(Touch* touch, Event* unused_event)
{
	if (!this->m_isJump) {
		m_isJump = true;
		m_jumpDir = Dir::UP;
	}
	return true;
}

// ��Ӽ��̼���
void MapScene::addKeyboardListener()
{
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(MapScene::onKeyPressed, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

// ���̼����Ļص�����
void MapScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode)
	{
		case EventKeyboard::KeyCode::KEY_ESCAPE:  // ESC: �ر�
		{
			Director::getInstance()->end();
			break;
		}
		case EventKeyboard::KeyCode::KEY_SPACE:  // �ո�: ��Ծ
		{
			if (!this->m_isJump) {
				m_isJump = true;
				m_jumpDir = Dir::UP;
			}
			break;
		}
		case EventKeyboard::KeyCode::KEY_P:  // P: ��ͣ
		{
			m_pause ^= 1;
			break;
		}
	}
}

void MapScene::gameOver()
{
	SimpleAudioEngine::getInstance()->playEffect(GAMEOVER_SOUND_EFFECT.c_str());

	auto tips = Label::createWithBMFont(TIPS_FNT_PATH, GAME_OVER_TIPS);
	Size visibleSize = Director::getInstance()->getVisibleSize();
	tips->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(tips, 10);
}

void MapScene::success()
{
	SimpleAudioEngine::getInstance()->playEffect(SUCCESS_SOUND_EFFECT.c_str());

	auto tips = Label::createWithBMFont(TIPS_FNT_PATH, GAME_SUCCESS);
	Size visibleSize = Director::getInstance()->getVisibleSize();
	tips->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(tips,10);
}
