#ifndef __START_SCENE_H__
#define __START_SCENE_H__

#include "Headers.h"
#include "Config.h"
#include "BasicScene.h"
#include "Level1Scene.h"

class BasicScene;

class StartScene : public BasicScene {
private:
	Sprite* story;

	float storyPercent;  // ������ʾ�ٷֱ�

public:
	StartScene();

	~StartScene();

	static Scene* createScene();

	bool init();

	CREATE_FUNC(StartScene);

	void update(float dt);

	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
};

#endif