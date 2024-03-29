#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
char T[] = "aaababa", P[] = "aa";
const int maxn = 10000;
int nxt[maxn], extend[maxn];
//ע�⣺�ַ���T���ַ���P�����Բ�ͬ�������ַ���β���������ַ��������ַ����ڣ��ʲ��������ַ����ĳ����
void getnext(char P[])
{
	int po = 1, m = strlen(P);
	nxt[0] = m;
	nxt[1] = mismatch(P + 1, P + m, P).second - P;
	for (int i = 2; i < m; ++i)
	{
		if (nxt[i - po] + i < nxt[po] + po)
			nxt[i] = nxt[i - po];
		else 
		{
			int j = max(nxt[po] + po - i, 0);
			nxt[i] = mismatch(P + j + i, P + m, P + j).second - P;
			po = i;
		}
	}
}
void exkmp(char T[], char P[])
{
	int po = 0, n = strlen(T), m = strlen(P);
	P[m] = 0; T[n] = 1;
	extend[0] = mismatch(T, T + n, P).second - P;
	getnext(P); //ע�⣺���ַ���P���������ַ�����0�����ַ����ĳ��Ȼ��1��next[0]����ʵ�ʲ�����
	for (int i = 1; i < n; i++)
	{
		if (nxt[i - po] + i < extend[po] + po)
			extend[i] = nxt[i - po];
		else
		{
			int j = max(extend[po] + po - i, 0);
			extend[i] = mismatch(T + i + j, T + n, P + j).second - P;
			po = i;
		}
	}
}
int main()
{
	exkmp(T, P);
	for (int i = 0; i < 15; ++i)
		printf("%d\n", extend[i]);
	return 0;
}