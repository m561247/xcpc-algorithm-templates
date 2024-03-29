#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <utility>
#define lowbit(x) ((x) & (-x))
using namespace std;
const int inf = 1 << 30;
struct Dynamic_ZXTree {
	static const int maxn = 51000;
	struct node {
		int l, r, v; //��ڵ��� �ҽڵ��� ֵ
	} T[maxn * 100]; //size(T) = maxn * logmaxn * logmaxn, size(data) = maxn + maxq
	int n, sz, length, nx, ny, data[maxn * 3], seq[maxn], X[maxn], Y[maxn], C[maxn]; //n��ֵ���߶����ĳ���
	void sum(int x, int y) {
		nx = ny = 0;
		for (int i = x; i > 0; i -= lowbit(i))
			X[nx++] = C[i];
		for (int i = y; i > 0; i -= lowbit(i))
			Y[ny++] = C[i];
	}
	void add(int x, int value, int v) { //�ڲ���������Ҫ��������ʣ�
		int p = rank(value);
		for (int i = x; i <= length; i += lowbit(i))
			ins(C[i], 1, n, p, v);
	}
	void set(int x, int value) { //���������±�Ϊx��λ�õ����޸�Ϊvalue
		add(x, seq[x], -1);
		add(x, value, 1);
		seq[x] = value;
	}
	void ins(int& i, int l, int r, int p, int v = 1) {
		int m = (l + r) / 2;
		if (i == 0) { 
			T[++sz] = T[i];
			i = sz; 
		}
		T[i].v += v;
		if (l == r) return;
		if (p <= m) ins(T[i].l, l, m, p, v);
		else ins(T[i].r, m + 1, r, p, v);
	}
	int rank(int v) {
		//�������Ҫ������ɢ��ֱ��return v���ɣ�ͬʱ��Ҫ�����е�data[v]��Ϊv����ʱ�߶�����ֵ��Ϊ[1, n]��
		return lower_bound(data + 1, data + n + 1, v) - data;
	}
	void init(int* A, int length, int* all, int size)	//��������A���±��1��ʼ��length��ʾA�ĳ���
	{													//����all��¼���п��ܳ��ֵ�ֵ�����������޸�Ϊ��ֵ�����±��1��ʼ��sizeΪ����all�ĳ���
		this->length = length;
		copy(A + 1, A + length + 1, seq + 1);
		copy(all + 1, all + size + 1, data + 1);	//data[i]����ԭ���������п��ܳ��ֵ�ֵ�����������޸ĳɵ�ֵ����ɢ��֮���iС��ֵ
		sort(data + 1, data + size + 1);			//���������ɢ������ֵdata[i] = i
		n = unique(data + 1, data + size + 1) - data - 1;
		for (int i = 1; i <= length; ++i)
			add(i, rank(seq[i]), 1);
	}
	void left() {
		for (int i = 0; i < ny; ++i)
			Y[i] = T[Y[i]].l;
		for (int i = 0; i < nx; ++i)
			X[i] = T[X[i]].l;
	}
	void right() {
		for (int i = 0; i < ny; ++i)
			Y[i] = T[Y[i]].r;
		for (int i = 0; i < nx; ++i)
			X[i] = T[X[i]].r;
	}
	int left_value() {
		int tot = 0;
		for (int i = 0; i < ny; ++i)
			tot += T[T[Y[i]].l].v;
		for (int i = 0; i < nx; ++i)
			tot -= T[T[X[i]].l].v;
		return tot;
	}
	int value() {
		int tot = 0;
		for (int i = 0; i < ny; ++i)
			tot += T[Y[i]].v;
		for (int i = 0; i < nx; ++i)
			tot -= T[X[i]].v;
		return tot;
	}
	int kth(int x, int y, int k) { //��ѯԭ����������[x, y]�еĵ�kС��ֵ�����k�������䳤�Ȼ᷵����Чֵ������ 
		int l = 1, r = n;
		sum(x - 1, y);
		while (l < r) {
			int m = (l + r) / 2, t = left_value();
			if (k <= t)
				left(), r = m;
			else
				right(), l = m + 1, k -= t;
		}
		return data[r];
	}
	int ask(int x, int y, int v) { //��ѯԭ����������[x, y]�б�vС��ֵ�ĸ��� 
		int l = 1, r = n, k = 0;
		sum(x - 1, y);
		int p = rank(v) - 1;
		if (p <= 0) return 0;
		while (l < r) {
			int m = (l + r) / 2;
			if (p <= m)
				left(), r = m;
			else {
				k += left_value();
				right();
				l = m + 1;
			}
		}
		k += value();
		return k;
	}
	int pre(int x, int y, int v) { //������[x, y]�в�ѯv��ǰ�����Ҳ�������-inf
		int k = ask(x, y, v);
		if (k == 0) return -inf;
		return kth(x, y, k);
	}
	int next(int x, int y, int v) { //������[x, y]�в�ѯv�ĺ�̣��Ҳ�������inf
		int k = ask(x, y, v + 1) + 1;
		if (k > y - x + 1) return inf;
		return kth(x, y, k);
	}
	int count(int x, int y, int v) { //��������[x, y]��v�ĸ���
		int l = 1, r = n;
		sum(x - 1, y);
		int p = rank(v);
		if (p > n || data[p] != v)
			return 0;
		while (l < r) {
			int m = (l + r) / 2;
			if (p <= m)
				left(), r = m;
			else
				right(), l = m + 1;
		}
		return value();
	}
	bool find(int x, int y, int v) {	//��ѯԭ���������[x, y]���Ƿ���Ԫ��v
		return count(x, y, v) >= 1;
	}
}tree;
const int maxn = 100000;
int A[maxn], B[maxn], n, q;
int main() {
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
	scanf("%d %d", &n, &q);
	for (int i = 1; i <= n; ++i)
		scanf("%d", &A[i]);
	for (int i = 1; i <= n; i++)
		B[i] = i;
	tree.init(A, n, B, n);
	for (int i = 0; i < q; ++i) {
		int tp, L, R, v;
		scanf("%d %d %d %d", &tp, &L, &R, &v);
		if (tp == 0) {
			printf("%d\n", tree.pre(L, R, v));
		}
		else if (tp == 1) {
			printf("%d\n", tree.next(L, R, v));
		}
		else if (tp == 2) {
			printf("%d\n", tree.kth(L, R, v));
		}
		else if (tp == 3) {
			printf("%d\n", tree.ask(L, R, v));
		}
		else if (tp == 4) {
			printf("%d\n", tree.count(L, R, v));
		}
		else if (tp == 5) {
			bool result = tree.find(L, R, v);
			printf("%d\n", (int)result);
		}
		else {
			tree.set(L, v);
		}
	}
	return 0;
}


