/*
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
// using namespace __gnu_pbds;
tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> t;
1. �ڶ���ģ�����Ϊֵ������ͣ����ֻҪʵ��set�Ĺ��ܣ�����null_type����
2. ����������std::map/std::set����
3. t.erase(val) ��ƽ������ɾ��ֵΪval�Ľ��
4. t.order_of_key(val) ����ƽ�����б�valС�����ж��ٸ�
5. t.find_by_order(k) ��������Ϊk��λ�õĵ�������������0��ʼ��
6. ��֧�ֶ���ֵ�������Ҫ����ֵ�������ٿ�һ��unordered_map����¼ֵ���ֵĴ�����
   ��val<<32����ϳ��ֵĴ��������tree��ע���ʱӦ��Ϊlong long���͡�
*/
#include <cstdio>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
const int maxn = 110000;
tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> t;
int main() {
    for (int i = 1; i <= 5; ++i)
        t.insert(i);
    printf("=>%d\n", *t.find_by_order(2));
    return 0;
}
