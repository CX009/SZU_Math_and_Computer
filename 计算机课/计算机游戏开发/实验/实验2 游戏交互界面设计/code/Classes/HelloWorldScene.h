#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

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
#include "Joystick.h"
#include <algorithm>
#include <cstring>

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
	void addBall1(float dt);
	void addBall2(float dt);
	void addBall3(float dt);
	void removeBall(Sprite* ball);
	
	virtual void update(float dt);
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	// ���¼Ʒְ庯��
	void modifyScore(int _score);

	// ���ر�������
	void loadBackground(std::string backgroundPath, int z);

	// ������庯��
	void loadBoard(std::string boardPath, int z);

	// ��Ӽ��̼���
	void addKeyboardListener();

	// ���̼����Ļص�����
	virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);

	// ������ʾ
	void loadHint(std::string hintPath, int tag, int z);

	// ���ؽ�����
	void loadResultBoard(std::string resultBoardPath, int z);

	// ���水ť�ص�����
	virtual void replayButtonEvent(cocos2d::Ref* pSender);

	// ��һ�ذ�ť�ص�����
	virtual void nextButtonEvent(cocos2d::Ref* pSender);

	// չʾ����
	void displayScore();

	// չʾ�ı�
	void displayWords(std::string words, int z);

protected:
	Sprite* bean;
	Size visibleSize;
	Joystick* m_joystick;
	Vector<Sprite*> ballVector;
	bool pause;

	int score;

	int total_notes;  // �� note ��
	int perfect_notes;  // Perfect �� note ��
	int good_notes;  // Good �� note ��
	int miss_notes;  // Miss �� note ��
	int bad_notes;  // Bad �� note ��

	std::vector<Label*> wordsTips;  // �ı�
};

#endif // __HELLOWORLD_SCENE_H__