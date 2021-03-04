#include <bits/stdc++.h>
using namespace std;
//NOT == 1,AND == 2,OR==3,XOR==4,NAND==5,NOR==6
struct node {
	int type;
	set<int> ip;
	set<int> op;
	bool value;
}nodes[510];
bool dataInput[10010][3000];
set<int> visited;
queue<int> q;
queue<int> res;
void clear(queue<int> &q)
{
	queue<int> empty;
	swap(empty, q);
}
int Topsort(int N)
{
	node *bk;
	bk = new node[N + 1];
	for (int i = 1; i <= N; i++)
	{
		bk[i] = nodes[i];
	}
	int point;
	while (!q.empty())
	{
		point=q.front();
		q.pop();
		N--;
		res.push(point);
		visited.erase(point);
		for (auto &kk : visited)
		{
			if (bk[kk].op.count(point))
			{
				bk[kk].op.erase(point);
				if (bk[kk].op.empty())
					q.push(kk);
			}
		}
	}
	if (N != 0) return 1;
	else return 0;
}
int main() {
	int Q;
	int M, N;
	int k;
	cin >> Q;
	string type;
	string output;
	char IO;
	int num;
	int loopFlag = 0;
	for (int mm = 0; mm < Q; mm++)
	{
		loopFlag = 0;
		output = "";
		cin >> M >> N;
		for (int i = 1; i <= N; i++)
		{
			visited.insert(i);
			cin >> type;
			if (type == "NOT")	nodes[i].type = 1;
			else if (type == "AND") nodes[i].type = 2;
			else if (type == "OR") nodes[i].type = 3;
			else if (type == "XOR") nodes[i].type = 4;
			else if (type == "NAND") nodes[i].type = 5;
			else if (type == "NOR") nodes[i].type = 6;
			cin >> k;
			for (int j = 1; j <= k; j++)
			{
				cin >> IO >> num;
				if (IO == 'I') {
					nodes[i].ip.insert(num);
				}
				else {
					nodes[i].op.insert(num);
				}
			}
			if (nodes[i].op.empty()) q.push(i);
		}
		//这里把电路结构读入完之后,应该使用拓扑排序,对输入的顺序进行排序,如果存在环那么直接输出loop
		loopFlag = Topsort(N);
		int S;
		cin >> S;
		for (int i = 1; i <= S; ++i)
		{
			for (int j = 1; j <= M; j++)
			{
				cin >> dataInput[i][j];
			}
		}
		int point;
		vector<int> vc;
		int si;
		int temp;
		for (int i = 1; i <= S; ++i)
		{
			cin >> si;
			for (int uu = 1; uu <= si; uu++)
			{
				cin >> temp;
				vc.push_back(temp);
			}
			queue<int> bk = res;
			while (!bk.empty()&& loopFlag==0)
			{
				point = bk.front();
				bk.pop();
				if (nodes[point].type == 1) {
					nodes[point].value = false;
					for (auto &it : nodes[point].ip)//非
					{
						nodes[point].value = !dataInput[i][it];
					}
					for (auto &it : nodes[point].op)
					{
						nodes[point].value = !nodes[it].value;
					}
				}
				else if (nodes[point].type == 2) {//与
					nodes[point].value = 1;
					for (auto &it : nodes[point].ip)
					{
						nodes[point].value = nodes[point].value&&dataInput[i][it];
					}
					for (auto &it : nodes[point].op)
					{
						nodes[point].value = nodes[point].value&&nodes[it].value;
					}
				}
				else if (nodes[point].type == 3) {//或
					nodes[point].value = 0;
					for (auto &it : nodes[point].ip)
					{
						nodes[point].value = nodes[point].value || dataInput[i][it];
					}
					for (auto &it : nodes[point].op)
					{
						nodes[point].value = nodes[point].value || nodes[it].value;
					}
				}
				else if (nodes[point].type == 4) {//异或
					nodes[point].value = false;
					for (auto &it : nodes[point].ip)
					{
						nodes[point].value = (nodes[point].value != dataInput[i][it]);
					}
					for (auto &it : nodes[point].op)
					{
						nodes[point].value = (nodes[point].value != nodes[it].value);
					}
				}
				else if (nodes[point].type == 5) {//与非
					nodes[point].value = 1;
					for (auto &it : nodes[point].ip)
					{
						nodes[point].value = nodes[point].value&&dataInput[i][it];
					}
					for (auto &it : nodes[point].op)
					{
						nodes[point].value = nodes[point].value && nodes[it].value;
					}
					nodes[point].value = !nodes[point].value;
				}
				else if (nodes[point].type == 6) {//或非
					nodes[point].value = 0;
					for (auto &it : nodes[point].ip)
					{
						nodes[point].value = nodes[point].value || dataInput[i][it];
					}
					for (auto &it : nodes[point].op)
					{
						nodes[point].value = nodes[point].value || nodes[it].value;
					}
					nodes[point].value = !nodes[point].value;
				}
			}
			if (loopFlag == 0) {
				
				for (auto &kk : vc) { output+= to_string(nodes[kk].value)+ " "; }
				output += "\n";
			}
			vc.clear();
		}
		if (loopFlag == 1) cout << "LOOP" << endl;
		else cout << output;
		for (int zz = 1; zz <= N; zz++)
		{
			nodes[zz].ip.clear();
			nodes[zz].op.clear();
		}
		clear(res);
		clear(q);
		visited.clear();
	}
	//system("Pause");
	return 0;
}