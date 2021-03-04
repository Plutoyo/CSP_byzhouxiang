#include <bits/stdc++.h>
using namespace std;
//#define DEBUG
#define MAX_INT 0x3f3f3f3f
struct node
{
	int v;
	int dis;
	node(){}
	node(int v, int dis) { this->v = v; this->dis = dis; }
};
bool operator <(const node &a,const node&b)
{
	return a.dis > b.dis;
}
vector<node> G[10010];
bool vis[10010] = { 0 };
int d[10010];
int cost[10010];
priority_queue<node> q;

void dj()
{
	fill(d, d + sizeof(d)/sizeof(int), MAX_INT);
	fill(cost, cost + sizeof(cost) / sizeof(int), MAX_INT);
	d[1] = 0;
	q.push(node(1,0));
	//cost[1] = 0;
	while (!q.empty())
	{
		node k = q.top();
		q.pop();
		int u = k.v;
		if (vis[u]) continue;
		vis[u] = 1;
		//u是选出节点的编号
		for (auto zz : G[u])//G[u]代表从u号节点出发
		{
			//v是选出节点的相邻的点
			int v = zz.v;
			if (vis[v]) continue;
			//zz.dis代表u到v的距离
			if (d[u] + zz.dis < d[v])
			{
				d[v] = d[u] + zz.dis;
				cost[v] = zz.dis;
				q.push(node(v, d[v]));
			}
			else if (d[u] + zz.dis == d[v])
			{
				cost[v] = min(cost[v], zz.dis);
			}
		}
	}
}
int main()
{
	int n, m;
	cin >> n >> m;
	int a, b, c;
	for (int i = 1; i <= m; ++i)
	{
		cin >> a >> b >> c;
		G[a].push_back(node(b,c));
		G[b].push_back(node(a,c));
	}
	int z=4;
	dj();
	int res=0;
	for (int i = 2; i <= n; ++i)
	{
		res += cost[i];
	}
	cout << res;

}