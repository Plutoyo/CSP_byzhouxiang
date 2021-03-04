#include <bits/stdc++.h>
using namespace std;

struct node {
	int sumX;
	int high;
}Stack[1010];

int main()
{
	int n;
	int Top=0;
	int res=0,cRes;
	int  high;
	int sumX;
	//memset(nodes, 0, sizeof(nodes));
	cin >> n;
	memset(Stack, 0, sizeof(Stack));
	for (int i = 0; i < n; i++)
	{
		cin >> high;
		if (Stack[Top].high < high)
		{
			Stack[++Top].sumX = 1;
			Stack[Top].high = high;
		}
		else
		{
			sumX = 0;
			while (Top != 0 && Stack[Top].high >= high) 
			{
				sumX += Stack[Top].sumX;
				cRes = sumX * Stack[Top].high;
				if (cRes > res) res = cRes;
				Top--;
			}
			Stack[++Top].high = high;
			Stack[Top].sumX = sumX+1;
		}
	}
	sumX = 0;
	while (Top != 0)
	{
		sumX += Stack[Top].sumX;
		cRes = Stack[Top].high*sumX;
		if (cRes > res) res = cRes;
		Top--;
	}
	cout << res;
	return 0;
}