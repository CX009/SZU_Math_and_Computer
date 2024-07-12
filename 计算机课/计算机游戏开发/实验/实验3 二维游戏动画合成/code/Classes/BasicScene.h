#ifndef __BASIC_SCENE_H__
#define __BASIC_SCENE_H__

#include "Headers.h"
#include "Config.h"

class BasicScene;

// ���������
class BasicScene : public cocos2d::Layer {
protected:
	Size visibleSize;
	Point origin;
	bool pause;

public:
	BasicScene();

	~BasicScene();

	static cocos2d::Scene* createScene();

	virtual bool init();

	// ��������
	CREATE_FUNC(BasicScene);

	virtual void update(float dt);

	void closeMenuCallback(cocos2d::Ref* pSender);

	// ��Ӽ��̼���
	void addKeyboardListener();

	// ���̼����Ļص�����
	virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);

	// ����ͼƬ
	void loadImage(std::string imagePath, Point position, int z, int tag = -1);

	// Ԥ������Ч
	void preloadSoundEffect(std::string soundEffectPath);

	// Ԥ���ر�������
	void preloadBackgroundMusic(std::string backgroundMusicPath);
	
	// Ԥ��������
	virtual void preloadSounds();

	// ������Ч
	void playSoundEffect(std::string soundEffectPath);

	// ���ű�������
	void playBackgroundMusic(std::string backgroundMusicPath);

	// ��ͣ��Ч
	void pauseSoundEffect();

	// ��ͣ��������
	void pauseBackgroundMusic();

	// �ָ���Ч
	void resumeSoundEffect();

	// �ָ���������
	void resumeBackgroundMusic();

	// ֹͣ��Ч
	void stopSoundEffect();

	// ֹͣ��������
	void stopBackgroundMusic();

	// ��ʾ��ʾ��Ϣ
	void displayWords(std::string words, Point position, int z, int tag = -1);

	// ��Ϸʤ��
	virtual void workVictory();

	// ��Ϸʧ��
	virtual void workDefeat();

	// ��Ϸʤ���ж�
	virtual void gameJudgement();

	// ���ؼ�λ��ʾ
	void loadKeyboardHint(std::string hintWords, int z, int tag = -1);
};

#endif