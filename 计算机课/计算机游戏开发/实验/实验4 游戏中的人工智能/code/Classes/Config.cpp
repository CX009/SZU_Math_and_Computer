#include "Config.h"

// �Ƚϸ�������С
int doubleCompare(double a, double b) {
	if (fabs(a - b) <= epsilon) {
		return 0;
	}
	return a < b ? -1 : 1;
}

// ����������� [l, r] �ڵ�����
int generateRandomInteger(int l, int r) {
	int res = abs((int)rnd()) % (r - l + 1);
	return res + l;
}