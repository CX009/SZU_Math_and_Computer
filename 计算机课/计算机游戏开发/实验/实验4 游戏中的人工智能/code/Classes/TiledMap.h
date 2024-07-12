#ifndef __TILED_MAP_H
#define __TILED_MAP_H

#include "Headers.h"
#include "Config.h"

class TiledMap : public cocos2d::Layer {
private:
	TMXTiledMap* tiledMap;
	int mapUnit;
	int mapWidth;
	int mapHeight;

	TMXLayer* wallLayer;  // ǽ�ڲ�

	std::vector<std::vector<bool>> accessibleMatrix;  // ��ͨ������

public:
	TiledMap();
	
	~TiledMap();

	bool init(int mapWidth, int mapHeight, std::string mapPath, int mapUnit = 32, int tag = -1);

	static TiledMap* create(int mapWidth, int mapHeight, std::string mapPath, int mapUnit = 32, int tag = -1);

	void setTiledMap(TMXTiledMap* _tiledMap);

	TMXTiledMap* getTiledMap();

	int getMapUnit();

	void setMapUnit(int _mapUnit = 32);
	
	int getMapWidth();

	void setMapWidth(int _mapWidth);

	int getMapHeight();

	void setMapHeight(int _mapHeight);

	void setAccessibleMatrix(std::vector<std::vector<bool>> _accessibleMatrix);

	std::vector<std::vector<bool>> getAccessibleMatrix();

	// ���Թ���ͼת��Ϊ�Ƿ��ͨ�е� bool ���� (0-indexed)
	void transformIntoBooleanMatrix();
};

#endif