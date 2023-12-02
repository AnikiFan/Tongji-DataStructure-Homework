#include<iostream>
#include<map>
#include<queue>
#define MAXN 110
#define Infinity 10000
int AdjMat[MAXN][MAXN];
int Flag[MAXN][MAXN] = { 0 };
typedef struct {
	int i;
	int j;
	int w;
}road;
using namespace std;
int main()
{
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			cin >> AdjMat[i][j];
	map<int, int> Village_index;
	for (int i = 1; i <= n; i++)
		Village_index[i] = i;
	int m;
	cin >> m;
	int count = n - 1;
	int x, y;
	for (int i = 0; i < m; i++) {
		cin >> x >> y;
		AdjMat[x][y] = 0;
		AdjMat[y][x] = 0;
		if (Village_index[x] != Village_index[y]) {
			int temp = Village_index[y];
			for (int k = 1; k <= n; k++)
				if (Village_index[k] == temp)
					Village_index[k] = Village_index[x];
			count--;
		}
	}
	queue<road> Q;
	road min;
	while (1) {
		min = { -1,-1,Infinity };
		for (int i = 1; i <= n; i++)
			for (int j = i; j <= n; j++)
				if (AdjMat[i][j] && AdjMat[i][j] < min.w) {
					min.w = AdjMat[i][j];
					min.i = i;
					min.j = j;
				}
		if (min.w == Infinity)
			break;
		else {
			AdjMat[min.i][min.j] = 0;
			AdjMat[min.j][min.i] = 0;
			Q.push(min);
		}
	}
	road now;
	int cost = 0;
	while (count) {
		now = Q.front();
		Q.pop();
		if (Village_index[now.i] != Village_index[now.j]) {
			cost += now.w;
			int temp = Village_index[now.j];
			for (int k = 1; k <= n; k++)
				if (Village_index[k] == temp)
					Village_index[k] = Village_index[now.i];
			count--;
		}
	}
	cout << cost;
	return 0;
}
