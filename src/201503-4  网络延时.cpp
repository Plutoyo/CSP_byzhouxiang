#include <bits/stdc++.h>
using namespace std;
vector<int> G[20010];
int D1[20010] = { 0 };//代表从i点出发到子节点最远的距离
int D2[20010] = { 0 };
int ans = 0;
void dfs(int k, int pre)
{
	for (auto i : G[k])
	{
		if (i == pre) continue;
		dfs(i, k);
		if (D1[i] + 1 > D1[k])
		{
			D2[k] = D1[k];
			D1[k] = D1[i] + 1;
		}
		else if (D1[i] + 1 > D2[k])
		{
			D2[k] = D1[i] + 1;
		}
	}
	ans = max(ans, D1[k] + D2[k]);
}
int main()
{
	int n, m;
	cin >> n >> m;
	int input;
	for (int i = 2; i <= n; i++)
	{
		cin >> input;
		G[input].push_back(i);
	}
	for (int i = 1; i <= m; i++)
	{
		cin >> input;
		G[input].push_back(i + n);
	}
	dfs(1, 0);
	cout << ans;
}