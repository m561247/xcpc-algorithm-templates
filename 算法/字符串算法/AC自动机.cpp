/*
ͨ��insert���ַ�������Trie֮��Ҫ���ǵ���getfail����AC�Զ�����
����AC�Զ����е�״̬u�����ܽ���ͨ��val[u] != 0���ж�u�Ƿ���ƥ�������ַ�������Ҫ���last��
����AC�Զ����е�״̬u���䲻��ƥ���κ�һ���ַ���������Ϊval[u] == 0 && last[u] == 0��
*/
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm> 
#include <queue>
using namespace std;
const int maxnode = 100000;
const int sigma_size = 26;
struct trie
{
	int ch[maxnode][sigma_size];
	int f[maxnode];		// fail����
	int val[maxnode];	// ÿ���ַ����Ľ�β��㶼��һ����0��val
	int last[maxnode]; // ����������һ�����
	int sz;
	void init()
	{
		sz = 1;
		memset(ch[0], 0, sizeof(ch[0]));
	}
	// �ַ�c�ı��
	int idx(char c)
	{
		return c - 'a';
	}
	// �����ַ�����v�����0
	void insert(const char *s, int v)
	{
		int u = 0, n = strlen(s);
		for (int i = 0; i < n; i++)
		{
			int c = idx(s[i]);
			if (!ch[u][c])
			{
				memset(ch[sz], 0, sizeof(ch[sz]));
				val[sz] = 0;
				ch[u][c] = sz++;
			}
			u = ch[u][c];
		}
		val[u] = v;
	}
	// ����fail����
	void getfail()
	{
		queue<int> Q;
		f[0] = 0;
		// ��ʼ������
		for (int c = 0; c < sigma_size; c++)
		{
			int u = ch[0][c];
			if (u) { f[u] = 0; Q.push(u); last[u] = 0; }
		}
		// ��BFS˳�����fail
		while (!Q.empty())
		{
			int r = Q.front(); Q.pop();
			for (int c = 0; c < sigma_size; c++)
			{
				int u = ch[r][c];
				if (!u)
				{
					ch[r][c] = ch[f[r]][c];
					continue;
				}
				Q.push(u);
				int v = f[r];
				while (v && !ch[v][c]) v = f[v];
				f[u] = ch[v][c];
				last[u] = val[f[u]] ? f[u] : last[f[u]];
			}
		}
	}
	// ��T����ģ��
	void find(const char *T)
	{
		int n = strlen(T);
		int j = 0; // ��ǰ����ţ���ʼΪ�����
		for (int i = 0; i < n; i++)
		{
			// �ı�����ǰָ��
			int c = idx(T[i]);
			j = ch[j][c];
			if (val[j]) print(j);
			else if (last[j]) print(last[j]); // �ҵ��ˣ�
		}
	}
	// �ݹ��ӡ�Խ��j��β�������ַ���
	void print(int j)
	{
		if (j)
		{
			//�Բ��ҵ��ı��Ϊval[j]���ַ������в���
			printf("%d\n", val[j]);
			print(last[j]);
		}
	}
}ac;
int main()
{
	ac.init();
	ac.insert("aabbc", 1);
	ac.insert("bbcff", 2);
	ac.insert("bb", 3);
	ac.getfail();
	ac.find("aabbcffbbbop");
	return 0;
}

