/*
��̬������ɫ����
	����ϯ����i��λ�õ�Ȩֵ��Ϊ�������һ�γ��ֵ�λ�ã�Ȼ���ѯ����[L, R]�е���ɫ��ת��Ϊ
	��ѯ����[L, R]�б�LС��ֵ�ж��ٸ���������ֱ����ask������ѯ��
	����ķ�����ֱ������ϯ���ĵ�R���汾�в�ѯ��LС�����ж��ٸ���Ȼ���ȥ(L - 1)���ɡ�
*/
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <utility>
using namespace std;
const int inf = 1 << 30;
struct ZXTree
{
	static const int maxn = 100010;
	struct node
	{
		int l, r, v; //��ڵ��� �ҽڵ��� ֵ
	} T[maxn * 25];
	int n, sz, root[maxn], data[maxn]; //n��ֵ���߶����ĳ���
	void ins(int &i, int l, int r, int p) //������[l, r]�в���p 
	{
		int m = (l + r) / 2;
		T[++sz] = T[i]; i = sz;
		T[i].v++; //������ǰ������ֵ�ĸ��� 
		if (l == r) return;
		if (p <= m) ins(T[i].l, l, m, p);
		else ins(T[i].r, m + 1, r, p);
	}
	int rank(int v)
	{
		//�������Ҫ������ɢ��ֱ��return v���ɣ�ͬʱ��Ҫ�����е�data[v]��Ϊv����ʱ��ϯ����ֵ��Ϊ[1, n]��
		return lower_bound(data + 1, data + n + 1, v) - data;
	}
	void init(int *A, int length) //��������A���±��1��ʼ��length��ʾA�ĳ���
	{
		root[0] = sz = 0;
		copy(A + 1, A + length + 1, data + 1);
		sort(data + 1, data + length + 1); //���û����ɢ����Ҫ��n���и�ֵ��ָ����ϯ����ֵ��
		this->n = unique(data + 1, data + length + 1) - data - 1; //��data�����������ȥ��
		for (int i = 1; i <= length; ++i) //���ΰ�ԭ������ÿ��λ�õ��������뵽�ɳ־û��߶�����
			ins(root[i] = root[i - 1], 1, n, rank(A[i])); //����rank[i]�����û�ж�A���������ɢ�����˴�ֱ�Ӳ���A[i]���ɡ� 
														  //root[i]��ʾ��A[1]��A[i]������ֵ������Ȩֵ�߶�����
	}
	int kth(int x, int y, int k)  //��ѯԭ����������[x, y]�еĵ�kС��ֵ�����k�������䳤�Ȼ᷵����Чֵ������ 
	{
		int l = 1, r = n;
		x = root[x - 1], y = root[y];
		while (l < r)
		{
			int m = (l + r) / 2, t = T[T[y].l].v - T[T[x].l].v;
			if (k <= t)
				x = T[x].l, y = T[y].l, r = m;
			else
				x = T[x].r, y = T[y].r, l = m + 1, k -= t;
		}
		return data[r];
	}
	int ask(int x, int y, int v) //��ѯԭ����������[x, y]�б�vС��ֵ�ĸ��� 
	{
		int l = 1, r = n, k = 0;
		x = root[x - 1], y = root[y];
		int p = rank(v) - 1;
		if (p <= 0) return 0;
		while (l < r)
		{
			int m = (l + r) / 2, t = T[T[y].l].v - T[T[x].l].v;
			if (p <= m)
				x = T[x].l, y = T[y].l, r = m;
			else
				x = T[x].r, y = T[y].r, l = m + 1, k += t;
		}
		k += T[y].v - T[x].v;
		return k;
	}
	int pre(int x, int y, int l, int r, int p)
	{
		int m = (l + r) / 2, v = T[y].v - T[x].v;
		if (l == r) return v > 0 ? data[r] : -inf;
		int t = T[T[y].r].v - T[T[x].r].v;
		if (p <= m || t == 0) return pre(T[x].l, T[y].l, l, m, p); //���p���е��������������Ϊ�գ���ֱ�������������� 
		int k = pre(T[x].r, T[y].r, m + 1, r, p);
		if (k != -inf) return k;
		return pre(T[x].l, T[y].l, l, m, p);
	}
	int pre(int x, int y, int v) //������[x, y]�в�ѯv��ǰ�����Ҳ�������-inf
	{
		int p = rank(v) - 1;
		if (p <= 0) return -inf;
		return pre(root[x - 1], root[y], 1, n, p);
	}
	int pre2(int x, int y, int v) //������[x, y]�в�ѯv��ǰ�����Ҳ�������-inf
	{
		int k = ask(x, y, v);
		if (k == 0) return -inf;
		return kth(x, y, k);
	}
	int next(int x, int y, int l, int r, int p)
	{
		int m = (l + r) / 2, v = T[y].v - T[x].v;
		if (l == r) return v > 0 ? data[r] : inf;
		int t = T[T[y].l].v - T[T[x].l].v;
		if (p > m || t == 0) return next(T[x].r, T[y].r, m + 1, r, p);
		int k = next(T[x].l, T[y].l, l, m, p);
		if (k != inf) return k;
		return next(T[x].r, T[y].r, m + 1, r, p);
	}
	int next(int x, int y, int v) //������[x, y]�в�ѯv�ĺ�̣��Ҳ�������inf
	{
		int p = rank(v + 1);
		if (p > n) return inf;
		return next(root[x - 1], root[y], 1, n, p);
	}
	int next2(int x, int y, int v) //������[x, y]�в�ѯv�ĺ�̣��Ҳ�������inf
	{
		int k = ask(x, y, v + 1) + 1;
		if (k > y - x + 1) return inf;
		return kth(x, y, k);
	}
	int count(int x, int y, int v)	//��������[x, y]��v�ĸ���
	{
		int l = 1, r = n;
		x = root[x - 1], y = root[y];
		int p = rank(v);
		if (p > n || data[p] != v)
			return 0;
		while (l < r && T[y].v - T[x].v > 0)
		{
			int m = (l + r) / 2;
			if (p <= m)
				x = T[x].l, y = T[y].l, r = m;
			else
				x = T[x].r, y = T[y].r, l = m + 1;
		}
		return T[y].v - T[x].v;
	}
	bool find(int x, int y, int v)	//��ѯԭ���������[x, y]���Ƿ���Ԫ��v
	{
		return count(x, y, v) >= 1;
	}
}zxtree;

const int maxn = 100000;
int A[maxn], n, q;
int main()
{
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
	scanf("%d %d", &n, &q);
	for (int i = 1; i <= n; ++i)
		scanf("%d", &A[i]);
	zxtree.init(A, n);
	for (int i = 0; i < q; ++i)
	{
		int tp, L, R, v;
		scanf("%d %d %d %d", &tp, &L, &R, &v);
		if (tp == 0)
		{
			printf("%d\n", zxtree.pre(L, R, v));
		}
		else if (tp == 1)
		{
			printf("%d\n", zxtree.next(L, R, v));
		}
		else if (tp == 2)
		{
			printf("%d\n", zxtree.kth(L, R, v));
		}
		else if (tp == 3)
		{
			printf("%d\n", zxtree.ask(L, R, v));
		}
		else if (tp == 4)
		{
			printf("%d\n", zxtree.count(L, R, v));
		}
		else
		{
			bool result = zxtree.find(L, R, v);
			printf("%d\n", (int)result);
		}
	}
	return 0;
}















