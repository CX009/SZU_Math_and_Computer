#ifndef __LEVEL2_SCENE_H
#define __LEVEL2_SCENE_H

#include "Headers.h"
#include "Config.h"
#include "BasicScene.h"
#include "TiledMap.h"
#include "AStar.h"
#include "Level1Scene.h"

class BasicScene;

class Level2Scene : public BasicScene {
private:
	// �Թ���ͼ
	TiledMap* tiledMaze;  // �Թ���ͼ
	std::vector<std::vector<bool>> accessibleMatrix;  // ��ͨ������
	std::set<std::pair<int, int>> availablePoints;  // δռ�õĵ�
	std::set<std::pair<int, int>> usedAvailablePoints;  // ��ռ�õ�δռ�õĵ�

	// ���ӻ�·��
	DrawNode* pathDrawer;  // ·���Ļ�ͼ�ڵ�
	float moveSpeed;  // �ƶ���(��)���ڽڵ��ʱ����

	// ��ɫ
	Sprite* cattail;  // èβ��
	Sprite* walnut;  // ���ǽ

	// item
	Sprite* forbidden;
	std::vector<Sprite*> portals;
	std::vector<Sprite*> skulls;
	std::vector<Sprite*> speedDowns;
	std::vector<Sprite*> speedUps;

	bool canPlace;  // �ܷ���ü��ǽ
	bool walnutInDangerous;  // ���ǽ�Ƿ���Σ��λ��

	Label* placeTip;
	Label* findTip;
	Label* noWayTip;
	Label* dangerousTip;

// ---------= ������ =---------
	Point touchingPoint;  // ��ǰ�����ĵ��Ӧ��ͼ�ϵ����� (������)

public:
	Level2Scene();

	~Level2Scene();

	static Scene* createScene();

	bool init();

	CREATE_FUNC(Level2Scene);

	void update(float dt);

	// Ԥ��������
	void preloadSounds();

	// ���̼����Ļص�����
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);

	// ������ʼ�Ļص�����
	bool onTouchBegan(Touch* touch, Event* event);

	// ���������Ļص�����
	void onTouchEnded(Touch* touch, Event* event);

	// ���ػ�ͼ�ڵ�
	void loadPathDrawer(int z);

	// ������ʾ��Ϣ
	void loadPlaceTip();
	void loadFindTip();
	void loadNoWayTip();
	void loadDangerousTip();

	// ���ز�����Ϣ
	void displayLevel();

	// ���ش�ɫ����
	void loadPureBackground();

	// �����Թ���ͼ
	void loadTiledMaze(int mapWidth, int mapHeight, Point position, int z, std::string mapPath, int mapUnit = 32, int tag = -1);

	// ��Ļ����ת��ͼ����
	std::pair<int, int> screenCoordinate2MapCoordinate(Point screenPoint);
	std::pair<int, int> screenCoordinate2MapCoordinate(float screenX, float screenY);

	// ��ͼ����ת��Ļ���� (tile ������)
	Point mapCoordinate2ScreenCoordinate(std::pair<int, int> mapPoint);
	Point mapCoordinate2ScreenCoordinate(int mapX, int mapY);

	// ���� Tile (�������øþ���)
	void loadTile(std::string path, Point position, int z, bool visible = true, int tag = -1);

	// ����èβ��
	void loadCattail(Point position, int z, bool visible = true, int tag = -1);

	// ���ؼ��ǽ
	void loadWalnut(Point position, int z, bool visible = true, int tag = -1);

	// ���ؽ�ֹ
	void loadForbidden(Point position, int z, bool visible = false, int tag = -1);

	// ���ش�����
	void loadPortal(Point position, int z, bool visible = false, int tag = -1);

	// ����ͷ­
	void loadSkull(Point position, int z, bool visible = false, int tag = -1);

	// ���ؼ���
	void loadSpeedDown(Point position, int z, bool visible = false, int tag = -1);

	// ���ؼ���
	void loadSpeedUp(Point position, int z, bool visible = false, int tag = -1);

	// ���ȡһ�����õĵ�
	std::pair<int, int> getRandomAvailablePoint();
	
	// ռ��һ�����õĵ�
	void occupyAvailablePoint(std::pair<int, int> point);

	// �黹һ�����õĵ�
	void returnAvailablePoint(std::pair<int, int> point);

	// �ָ����õĵ�
	void recoverAvailablePoints();

	// ��ײ���
	void collisionDetection();
	
	// �����δռ�õĵ������� item
	void generateRandomItems();
};

#endif