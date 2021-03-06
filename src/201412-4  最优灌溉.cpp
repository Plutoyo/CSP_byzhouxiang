#include <bits/stdc++.h>
using namespace std;
struct Gnode
{
	int v;
	int c;
	Gnode() {};
	Gnode(int v, int c)
	{
		this->v = v;
		this->c = c;
	}
};
struct node
{
	int u;
	int v;
	int c;
	node() {};
	node(int u, Gnode &a)
	{
		this->u = u;
		this->v = a.v;
		this->c = a.c;
	}
};

bool operator < (const node&a, const node&b)
{
	return a.c > b.c;
}
bool operator < (const Gnode&a, const Gnode&b)
{
	return a.c > b.c;
}
bool visited[1010] = { 0 };
priority_queue<Gnode> G[1010];
priority_queue<node> q;
int n, m,cost;
void prim()
{
	visited[1] = 1;
	Gnode gn;
	while (!G[1].empty())
	{
		gn = G[1].top();
		G[1].pop();
		q.push(node(1, gn));
	}
	//q的第一个就是到已经访问的最短的边
	while (!q.empty())
	{
		//现在的点就是t.v
		node t = q.top();
		q.pop();
		if (visited[t.v]) continue;
		visited[t.v] = 1;
		cost += t.c;
		while (!G[t.v].empty())
		{
			gn = G[t.v].top();
			G[t.v].pop();
			if (visited[gn.v]) continue;
			else q.push(node(t.v, gn));
		}
	}
}
int main()
{
	cost = 0;
	cin >> n >> m;
	int a, b, c;
	for (int i = 1; i <= m; i++)
	{
		cin >> a >> b >> c;
		G[a].push(Gnode(b, c));
		G[b].push(Gnode(a, c));
	}
	prim();
	cout << cost;
}