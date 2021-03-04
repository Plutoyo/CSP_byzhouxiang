#include<bits/stdc++.h>
using namespace std;

bool visited[1010];
vector<int> edge[1010];
bool know[1010][1010];
int bP;
void dfs(int n)
{
	visited[n] = 1;
	know[bP][n] = 1;
	know[n][bP] = 1;
	for (auto kk : edge[n])
	{
		if (visited[kk]) continue;
		dfs(kk);
	}
}

int main()
{
	int  N,M;
	cin >> N >> M;
	int a, b;
	int ct = 0;
	for (int i = 0; i < M; i++)
	{
		cin >> a >> b;
		edge[a].push_back(b);
	}
	for (int i = 1; i <= N; i++)
	{
		memset(visited, 0, sizeof(visited));
		bP = i;
		dfs(i);
	}
	int i, j;
	for (i = 1; i <= N; i++)
	{
		for (j = 1; j <= N; j++)
		{
			if (know[i][j] == 0) break;
		}
		if (j == N + 1) ct++;
	}
	for (j = 1; i <= N; i++)
	{
		for (i = 1; j <= N; j++)
		{
			if (know[i][j] == 0) break;
		}
		if (i == N + 1) ct++;
	}
	cout << ct;
}