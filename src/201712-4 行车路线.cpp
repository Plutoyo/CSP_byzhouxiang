#include <bits/stdc++.h>
using namespace std;
int n, m;
#define MAX_INT 0x3f3f3f3f
struct node
{
	int v;
	bool type;
	int dis;
	node(){}
	node(bool t, int b, int c) {
		this->dis = c;
		this->v = b;
		this->type = t;
	}
};
int u;//代表出发点
bool operator <(const node &a, const node & b)
{
	return a.dis > b.dis;
}
vector<node> G[510];
int d[510];//代表疲劳值
bool vis[510] = { 0 };
priority_queue<node> q;
int sr[510];
void dijkstra()
{
	fill(d, d + sizeof(d) / sizeof(int), MAX_INT);
	fill(sr, sr + sizeof(sr) / sizeof(int), 0);
	d[1] = 0;
	q.push(node(0, 1, 0));
	while (!q.empty())
	{
		node nd = q.top();
		q.pop();
		u = nd.v;
		if (vis[u]) continue;
		vis[u] = 1;
		for (auto i : G[u])
		{
			int j = i.v;
			if (vis[j]) continue;
			if (i.type)//是小路
			{
				long long temp = d[u] - pow(sr[u],2)+pow(sr[u]+i.dis,2);
				if (temp < d[j])
				{
					d[j] = temp;
					sr[j] = sr[u] + i.dis;
					q.push(node(0, j, d[j]));
				}
			}
			else
			{
				if (d[u]+i.dis < d[j])
				{
					d[j] = d[u] + i.dis;
					sr[j] = 0;
					q.push(node(0, j, d[j]));
				}
			}
		}
	}
}
int main()
{
	cin >> n >> m;
	int t, a, b, c;
	for (int i = 1; i <= m; ++i)
	{
		cin >> t >> a >> b >> c;
		G[a].push_back(node(t, b, c));
		G[b].push_back(node(t, a, c));
	}
	dijkstra();
	cout << d[n];
	return 0;
}