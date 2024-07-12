#include "AStar.h"

AStar::AStar(int _width, int _height, std::vector<std::vector<bool>> _accessibleMatrix, std::pair<int, int> st, std::pair<int, int> ed) {
	width = _width;
	height = _height;
	accessibleMatrix = _accessibleMatrix;

	work(st, ed);
}

AStar::~AStar() {

}

float AStar::getMinDistance() {
	return minDistance;
}

std::vector<std::pair<int, int>> AStar::getPath() {
	return path;
}

int AStar::getManhattanDistance(std::pair<int, int> st, std::pair<int, int> ed) {
	return std::abs(st.first - ed.first) + std::abs(st.second - ed.second);
}

// ���� (x, y) �Ƿ�����
bool AStar::checkAccessible(int x, int y) {
	return 0 <= x && x < width && 0 <= y && y < height && accessibleMatrix[x][y];
}

bool AStar::checkAccessible(std::pair<int, int> p) {
	return checkAccessible(p.first, p.second);
}

void AStar::work(std::pair<int, int> st, std::pair<int, int> ed) {
	path.clear();
	std::vector<std::vector<float>> dis(width, std::vector<float>(height, INF));
	std::vector<std::vector<std::pair<int, int>>> pre(width, std::vector<std::pair<int, int>>(height));  // ǰ��
	dis[st.first][st.second] = 0;
	pre[st.first][st.second] = std::pair<int, int>(0, 0);

	using T = std::tuple<float, float, std::pair<int, int>>;  // { ���յ�Ĺ��ƾ���, ������ʵ�ʾ���, �ڵ����� }
	std::priority_queue<T, std::vector<T>, std::greater<T>> heap;
	heap.push({ getManhattanDistance(st, ed), 0, st });

	// A* �㷨
	while (heap.size()) {
		auto [_, real, cur] = heap.top();
		heap.pop();

		auto [curX, curY] = cur;

		// �����յ�
		if (curX == ed.first && curY == ed.second) {
			break;
		}

		for (int i = 0; i < 8; i++) {
			int tmpX = curX + dx[i], tmpY = curY + dy[i];
			if (checkAccessible(tmpX, tmpY)) {
				float distance = (i & 1) ? std::sqrt(2) : 1;  // б���߳��ȹ涨Ϊ ��2
				if (dis[tmpX][tmpY] > real + distance) {
					dis[tmpX][tmpY] = real + distance;
					heap.push({ dis[tmpX][tmpY] + getManhattanDistance(std::pair<int, int>(tmpX, tmpY), ed), 
						dis[tmpX][tmpY], std::pair<int, int>(tmpX, tmpY) });
					pre[tmpX][tmpY] = cur;
				}
			}
		}
	}

	minDistance = dis[ed.first][ed.second];

	// ����ͨ
	if (!doubleCompare(minDistance, INF)) {
		return;
	}

	// ��·��
	for (std::pair<int, int> cur = ed; cur != std::pair<int, int>(0, 0); cur = pre[cur.first][cur.second]) {
		path.push_back(cur);
	}
	std::reverse(path.begin(), path.end());
}
