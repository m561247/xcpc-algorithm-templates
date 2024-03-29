#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <ctime>
using namespace std;
const int maxn = 5000000;
struct node {
	node *ch[2]; // ��������
	int r; // ������ȼ�
	int v; // ֵ
	int s; // �������
	int cmp(int x) const {
		if (x == v) return -1;
		return x < v ? 0 : 1;
	}
	void maintain() {
		s = ch[0]->s + ch[1]->s + 1;
	}
}nodes[maxn], *cur, *nil;
node *newnode(int x)
{
	node *o = cur++;
	o->ch[0] = o->ch[1] = nil;
	o->r = rand();
	o->v = x;
	o->s = 1;
	return o;
}
void init()
{
	cur = nodes;
	nil = newnode(0);
	nil->s = 0;
}
void rotate(node* &o, int d) {
	node* k = o->ch[d^1]; o->ch[d^1] = k->ch[d]; k->ch[d] = o; 
	o->maintain(); k->maintain(); o = k;
}
void insert(node* &o, int x) {
	if(o == nil) o = newnode(x);
	else {
		int d = (x < o->v ? 0 : 1); // ��Ҫ��cmp��������Ϊ���ܻ�����ͬ���
		insert(o->ch[d], x);
		if(o->ch[d]->r > o->r) rotate(o, d^1);
	}
	o->maintain();
}
node *find(node* o, int x) {
	while (o != nil)
	{
		int d = o->cmp(x);
		if (d == -1) return o;
		else o = o->ch[d];
	}
	return nil;
}
// Ҫȷ��������
void remove(node* &o, int x) {
	int d = o->cmp(x);
	if (d == -1)
	{
		if (o->ch[0] == nil)
			o = o->ch[1];
		else if (o->ch[1] == nil)
			o = o->ch[0];
		else
		{
			int d2 = (o->ch[0]->r > o->ch[1]->r ? 1 : 0);
			rotate(o, d2); remove(o->ch[d2], x);
		}
	}
	else
		remove(o->ch[d], x);
	if(o != nil) o->maintain();
}
int kth(node* o, int k) {
	if(o == nil || k <= 0 || k > o->s) return 0;
	if(k == o->ch[0]->s+1) return o->v;
	else if(k <= o->ch[0]->s) return kth(o->ch[0], k);
	else return kth(o->ch[1], k - o->ch[0]->s - 1);
}
// ��������oΪ����������x��������û��x�򷵻�x�ĺ�̵����� 
int rank(node* o, int x) {
	if(o == nil) return 1;
	if(x <= o->v) return rank(o->ch[0], x);
	else return rank(o->ch[1], x) + o->ch[0]->s + 1;
}
// ��������oΪ����������x��ǰ��������
int rank1(node *o, int x)
{
	if (o == nil)
		return 0;
	if (x <= o->v)
		return rank1(o->ch[0], x);
	else return rank1(o->ch[1], x) + o->ch[0]->s + 1;
}
// ��������oΪ����������x�ĺ�̵�����
int rank2(node *o, int x)
{
	if (o == nil)
		return 1;
	if (x >= o->v)
		return rank2(o->ch[1], x) + o->ch[0]->s + 1;
	else return rank2(o->ch[0], x);
}
/*
����rank��rank1��rank2����⣺
��������A = {1, 2, 3, 3, 4, 4, 5}
�±�(����):  1  2  3  4  5  6  7
������A���뵽ƽ����root�С�
rank(root, 3):  ��ΪֻҪx<=o->v��һֱ�����ߣ����Ի��ߵ�����2~3��λ�ã�����nil��㷵��1�����������rank����ֵΪ3
rank1(root, 3): ��ΪֻҪx<=o->v��һֱ�����ߣ����Ի��ߵ�����2~3��λ�ã�����nil��㷵��0�����������rank����ֵΪ2
rank2(root, 3): ��ΪֻҪx>=o->v��һֱ�����ߣ����Ի��ߵ�����4~5��λ�ã�����nil��㷵��1�����������rank����ֵΪ5 
*/

int main() {
	init();
	node *root = nil;
	int A[] = {1, 2, 3, 3, 4, 4, 5};
	for (unsigned i = 0; i < sizeof(A) / sizeof(*A); ++i)
		insert(root, A[i]);
	printf("%d\n", rank(root, 3));
	printf("%d\n", rank1(root, 3));
	printf("%d\n", rank2(root, 3));
	return 0;
}










