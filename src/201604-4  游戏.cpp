#include <bits/stdc++.h>
using namespace std;
int n, m, t;
struct loc
{
	int x;
	int y;
	int time;
	loc() {};
	loc(int x, int y,int time) {
		this->x = x;
		this->y = y;
		this->time = time;
	}
};
int dir[4][2] = { {-1,0}, {0,1}, {1,0}, {0,-1} };
bool visited[110][110][330] = { 0 };
queue<loc> q;
void bfs()
{
	q.push(loc(1, 1 ,0));
	int x, y,time;
	while (!q.empty())
	{
		loc p = q.front();
		q.pop();
		x = p.x;
		y = p.y;
		time = p.time;
		//cout << x << " " << y << " " << time << endl;
		if (x == n && y == m)
		{
			cout << time;
			break;
		}
		time++;
		
		for (int i = 0; i < 4; i++)
		{
			int xx = x + dir[i][0];
			int yy = y + dir[i][1];
			if (xx<1 || yy<1 || xx>n || yy>m) continue;
			if (visited[xx][yy][time]) continue;
			visited[xx][yy][time] = 1;
			q.push(loc(xx, yy, time));
		}
	}
}
int main()
{
	cin >> n >> m >> t;
	int r, c, a, b;
	for (int i = 0; i < t; i++)
	{
		cin >> r >> c >> a >> b;
		for (int k = a; k <= b; k++) visited[r][c][k] = 1;
	}
	bfs();
	return 0;
}