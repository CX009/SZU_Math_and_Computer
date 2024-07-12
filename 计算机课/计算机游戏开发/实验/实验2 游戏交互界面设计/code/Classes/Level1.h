#ifndef __LEVEL1_H__
#define __LEVEL1_H__

#include "HelloWorldScene.h"
#include "Note.h"

class Level1 : public HelloWorld {
private:
	Line hitLine;  // �ж���
	std::vector<Note> notes;
	std::vector<Sprite*> hitEffects;  // ������Ч
	std::vector<Sprite*> hitTips;  // ��������
	Time currentTime;
	std::vector<Note> trash;  // Ҫɾ���� notes
	const int DELTA_TIMER;  // ���� note ��ʱ����
	const Time END_TIME;  // ����ʱ��
	const int TARGET_SCORE;  // Ŀ���

public:
	Level1();

	~Level1();

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	virtual void update(float dt);

	// implement the "static create()" method manually
	CREATE_FUNC(Level1);

	// �����ж���
	void loadHitLine(std::string linePath, int y, int z);

	// ���� Note
	void loadNote(int type, Time time, float x);

	// �½� Note
	void createNote(float dt);

	// ��������
	void workHit(Note& note, int state);

	// ���� notes
	void updateNotes(Time currentTime);

	// ��������
	void updateHits();

	// Ԥ������Ч������
	void preloadSounds();

	// ���̼����Ļص�����
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);

	// ��ʾ���
	void displayResult();

	// ���水ť�ص�����
	void replayButtonEvent(cocos2d::Ref* pSender);

	// ��һ�ذ�ť�ص�����
	void nextButtonEvent(cocos2d::Ref* pSender);

	// �����ı�
	void updateWords();
};

#endif