// ��5������
#ifndef __MAPSCENE_H__
#define __MAPSCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Config.h"
USING_NS_CC;
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

using namespace cocos2d::ui; 

class MapScene : public cocos2d::Layer
{
public:

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(MapScene);

	// ���ر���
	void loadBackground(std::string backgroundPath);

	// ����Ƥ��
	void loadEgg(std::string eggPath, int tag, int x, int y);

	// ��������
	void loadGrain(std::string grainPath, int tag, int x, int y);

	// ������˷�
	void loadMicrophone(std::string microphonePath, int tag, int x, int y);

	// ���ص�ͼ
	void loadMap(std::string mapPath);

	// ��ʾ����
	void addPlayer(Vec2 pos);

	// ��Ӵ�������
	void addTouchListener();
	bool onTouchBegan(Touch *touch, Event *unused_event);

	// ��Ӽ��̼���
	void addKeyboardListener();
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);

	// ��Ϸ�߼�
	void update(float t);

	void gameOver();
	void success();

	bool m_gameOver; // ��Ϸ�Ƿ����
	bool m_pause;  // ��Ϸ�Ƿ���ͣ
	Dir m_jumpDir;   // ��ʾ����ķ��� 1��up 2 down
	int m_jumpSpeed; // ��Ծ�ٶ�
	bool m_isJump;   // ��ʾ�Ƿ�������Ծ�������Ծ��������Ļ�Ĵ���
};

#endif // __HELLOWORLD_SCENE_H__
