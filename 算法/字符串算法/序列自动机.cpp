/*
�����Զ������ܹ�ʶ��������е����������У������������У�
last[c]��ʾ�ַ�c�����������һ�γ��ֵ�λ�ö�Ӧ���Զ������
par[i]��ʾ�±�i�����ַ�����һ�εĳ���λ�ö�Ӧ���Զ������
ch[i][x]��ʾ���±�iΪ��㣬�ַ�x�ĵ�һ�γ���λ�ö�Ӧ���Զ������
������build�������Զ������Զ��������ԭ�����е�λ��һһ��Ӧ���Զ������±�i��λ�ö�Ӧԭ�������±�i��λ�ã���
������extend�����������Զ������Զ��������ԭ�����е�λ���г���ֵ��ƫ�ơ�
����ԭ��
���ڸ�������A��B�ж�B�Ƿ�ΪA�������У�ֻҪ���������ҵ��ַ�B[0]��A�еĵ�һ�γ���λ��A[i]��Ȼ���ٴ�i + 1��ʼ�ҵ�B[1]�ĵ�һ�γ���λ�ã�
�Դ����ơ������������㷨���ҵ�B֮ǰ�Ѿ�������A�Ľ�β����B����A�������У�����B��A�������С�
*/
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <iostream>
const int maxn = 110000;
const int sigma_size = 26;
int cur, root, par[maxn], last[sigma_size], ch[maxn][sigma_size];
void init()
{
	cur = root = 1;
	memset(ch, 0, sizeof(ch));
	for (int i = 0; i < sigma_size; ++i)
		last[i] = root;
}
void extend(int x) {
	par[++cur] = last[x];
	for (int c = 0; c < sigma_size; ++c)
		for (int i = last[c]; i && !ch[i][x]; i = par[i])
			ch[i][x] = cur;
	last[x] = cur;
}
void build(int A[], int n)	//��������֪�������ֱ�ӹ��������Զ�������ʱroot = 0.
{							//ע�⣺����A���±��1��ʼ
	for (int i = n; i > 0; --i)
	{
		memcpy(ch[i - 1], ch[i], sizeof(ch[i]));
		ch[i - 1][A[i]] = i;
	}
}
int main()
{
	int A[] = { 0, 1, 1, 2, 3, 5, 1, 2 }, B[] = { 1, 1, 2, 5, 1 };
	//init();
	//for (int i = 0; i < sizeof(A) / sizeof(*A); ++i)
	//	extend(A[i]);
	//int st = root;
	build(A, sizeof(A) / sizeof(*A) - 1);
	int st = 0;
	for (int i = 0; i < sizeof(B) / sizeof(*B); ++i)
		st = ch[st][B[i]];
	printf("%d\n", st);
	return 0;
}