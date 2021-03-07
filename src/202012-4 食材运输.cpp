#include <bits/stdc++.h>
#define INF 0x3f3f3f3f
using namespace std;
struct node
{
	int v;
	int w;
	node(){}
	node(int v, int w){ this->w = w, this->v = v; }
};
set<int> nd[110];
vector<node> G[110];
int D[110] = { 0 };
int B[110];
int ans;
int root;
int N, M, K;
//N是点数,M是检查点数,前70%无用,K是菜的种类数
void dfs(int now, int pre,int T)
{
	for (auto &i : G[now])
	{
		if (i.v == pre) continue;
		dfs(i.v, now,T);
	}
	if (G[now].size() == 1 && now != root) return;


	for (auto &i : G[now])
	{
		if (i.v == pre) continue;
		if (D[i.v] == 0)
		{
			B[i.v] = 0;
			if (nd[i.v].count(T))
			{
				D[now] += 2 * i.w;
			}
		}
		else {
			D[now] += D[i.v] + 2 * i.w;
		}
	}
	for (auto &i : G[now])
	{
		if (i.v == pre) continue;
		if (D[i.v] == 0&&G[i.v].size()==1)
		{
			B[now] = min(D[now]-i.w,B[now]);
		}
		if (D[i.v] != 0)
			B[now] = min(D[now] - i.w - D[i.v] + B[i.v],B[now]);
	}
}

int main()
{
	cin >> N >> M >> K;
	int input;
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= K; j++)
		{
			cin >> input;
			if (input == 1) nd[i].insert(j);
		}
	}
	int u, v, w;
	for (int i = 1; i <= N-1; i++)
	{
		cin >> u >> v >> w;
		G[u].push_back(node(v, w));
		G[v].push_back(node(u, w));
	}
	//可以从所有点都跑一次dfs,选出等待最大值最小的
	
	ans = 0;
	int each;
	for (int i = 1; i <= K; i++)
	{
		each = INF;
		for (int j = 1; j <= N; j++)
		{
			fill(B, B + 110, INF);
			fill(D, D + 110, 0);
			root = j;
			dfs(j, 0, i);
			each = min(each, B[j]);
		}
		ans = max(each, ans);
	}
	cout << ans;
	
}