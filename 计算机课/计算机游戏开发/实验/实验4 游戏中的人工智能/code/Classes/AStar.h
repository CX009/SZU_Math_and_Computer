#ifndef __A_STAR_H__
#define __A_STAR_H__

#include "Headers.h"
#include "Config.h"

class AStar {
private:
	const std::vector<int> dx = { -1, -1, 0, 1, 1, 1, 0, -1 };
	const std::vector<int> dy = { 0, 1, 1, 1, 0, -1, -1, -1 };

	int width;
	int height;
	std::vector<std::vector<bool>> accessibleMatrix;  // 0-indexed

	float minDistance;  // st �� ed �����·����
	std::vector<std::pair<int, int>> path;  // ���·

public:
	AStar(int _width, int _height, std::vector<std::vector<bool>> _accessibleMatrix, std::pair<int, int> st, std::pair<int, int> ed);
	
	~AStar();

	float getMinDistance();

	std::vector<std::pair<int, int>> getPath();

	int getManhattanDistance(std::pair<int, int> st, std::pair<int, int> ed);

	// ���� (x, y) �Ƿ�����
	bool checkAccessible(int x, int y);
	bool checkAccessible(std::pair<int, int> p);

	// A* �㷨Ѱ·
	void work(std::pair<int, int> st, std::pair<int, int> ed);	
};

#endif