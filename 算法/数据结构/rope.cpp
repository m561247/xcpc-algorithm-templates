/*
// #include <ext/rope>
// using namespace __gnu_cxx;
rope<int> r;
1. r.push_back(a) �������a
   r.pop_back() ɾ�����һ��Ԫ��
2. r.insert(idx, a) ���±�idx������a
   r.insert(idx, rope) ���±�idx������rope����ʱ�临�Ӷ�O(log(n))
3. r.erase(idx, length) ɾ����idx��ʼ��length���ַ�
4. r.replace(idx, a) ���±�idx��λ����Ϊa
5. r.substr(pos, length) ���ش�pos��ʼ����Ϊlength���Ӵ���ʱ�临�Ӷ�O(log(n))��
   �޸�substr���ص�rope����ı�ԭrope��
6. ֧�ֻ������ַ����������==��+=��<��ƴ�ӵ�ʱ�临�Ӷ�ΪO(log(n))
7. rope�Ŀ�����O(1)�ģ��޸���O(log(n))�ġ�
8. ע��r[i]����ֵ����ֵ�������޸ġ��޸������replace������
*/
#include <bits/stdc++.h>
#include <ext/rope>
using namespace __gnu_cxx;
const int maxn = 110000;
rope<int> version[maxn];
int main() {
    const int n = 100000;
    for (int i = 0; i < n; ++i)
        version[0].push_back(i);
    for (int i = 1; i < n; ++i) {
        version[i] = version[i - 1];
        version[i].replace(i, i * 10);
    }
    const int pos = 88888;
    printf("%d %d %d\n", version[pos][pos], version[pos][pos + 1], version[pos + 1][pos + 1]);

    rope<int> r;
    r.push_back(0); r.push_back(1);
    for (int i = 0; i < 32; ++i)
        r += r;
    int total = 0;
    for (int i = 0; i < n; ++i)
        total += r[998244353 + i];
    printf("%d\n", total);
    return 0;
}
