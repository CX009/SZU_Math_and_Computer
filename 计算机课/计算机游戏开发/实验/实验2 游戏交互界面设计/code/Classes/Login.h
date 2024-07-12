#ifndef __LOGIN_H__
#define __LOGIN_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace cocos2d;
using namespace cocostudio;
using namespace cocos2d::ui;
using namespace CocosDenshion;

#include "Config.h"
#include "HelloWorldScene.h"
#include "Level1.h"
#include <cstring>

class Login : public cocos2d::Layer {
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
	
	virtual void update();
    // implement the "static create()" method manually
    CREATE_FUNC(Login);

	// ���ر�������
	void loadBackground(std::string backgroundPath, int z);

    // ���ص�¼���
    void loadLoginBoard(std::string loginBoardPath, int z);

    // �������¼��ص�����
    void sliderEvent(cocos2d::Ref* pSender, SliderEventType type);

    // Ԥ������Ч������
    void preloadSounds();

    // ��ť�¼��ص�����
    void buttonEvent(cocos2d::Ref* pSender);

protected:
    Size visibleSize;
};

#endif