// �̶�������С����ͼ���ڽӾ���д��
struct MDST {
  int n;
  int w[maxn][maxn]; // ��Ȩ
  int vis[maxn];     // ���ʱ�ǣ��������ж��޽�
  int ans;           // �����
  int removed[maxn]; // ÿ�����Ƿ�ɾ��
  int cid[maxn];     // ����Ȧ���
  int pre[maxn];     // ��С��ߵ����
  int iw[maxn];      // ��С��ߵ�Ȩֵ
  int max_cid;       // ���Ȧ���

  void init(int n) {
    this->n = n;
    for(int i = 0; i < n; i++)
      for(int j = 0; j < n; j++) w[i][j] = INF;
  }

  void AddEdge(int u, int v, int cost) {
    w[u][v] = min(w[u][v], cost); // �ر�ȡȨ��С��
  }

  // ��s�����ܵ�����ٸ����
  int dfs(int s) {
    vis[s] = 1;
    int ans = 1;
    for(int i = 0; i < n; i++)
      if(!vis[i] && w[s][i] < INF) ans += dfs(i);
    return ans;
  }

  // ��u��������preָ����Ȧ
  bool cycle(int u) {
    max_cid++;
    int v = u;
    while(cid[v] != max_cid) { cid[v] = max_cid; v = pre[v]; }
    return v == u;
  }

  // ����u����С�뻡���뻡��㲻����Ȧc��
  void update(int u) {
    iw[u] = INF;
    for(int i = 0; i < n; i++)
      if(!removed[i] && w[i][u] < iw[u]) {
        iw[u] = w[i][u];
        pre[u] = i;
      }
  }

  // �����Ϊs�����ʧ���򷵻�false
  bool solve(int s) {
    memset(vis, 0, sizeof(vis));
    if(dfs(s) != n) return false;

    memset(removed, 0, sizeof(removed));
    memset(cid, 0, sizeof(cid)); //ע�⣺�ǽ�cid��գ�������pre
    for(int u = 0; u < n; u++) update(u);
    pre[s] = s; iw[s] = 0; // ��������⴦��
    ans = max_cid = 0;
    for(;;) {
      bool have_cycle = false;
      for(int u = 0; u < n; u++) if(u != s && !removed[u] && cycle(u)){
        have_cycle = true;
        // ���´�����Ȧ��Ȧ�ϳ���u֮��Ľ���ɾ��
        int v = u;
        do {
          if(v != u) removed[v] = 1;
          ans += iw[v];
          // ����Ȧ���i���ѱ�i->v�ĳ�i->u��������Ȩֵ����v->i��Ϊu->i
          // ע��Ȧ�Ͽ��ܻ���һ��v'ʹ��i->v'����v'->i���ڣ����ֻ����Ȩֵ��С��i->u��u->i
          for(int i = 0; i < n; i++) if(cid[i] != cid[u] && !removed[i]) {
            if(w[i][v] < INF) w[i][u] = min(w[i][u], w[i][v]-iw[v]);
            w[u][i] = min(w[u][i], w[v][i]);
            if(pre[i] == v) pre[i] = u;
          }
          v = pre[v];
        } while(v != u);
        update(u);
        break;
      }
      if(!have_cycle) break;
    }
    for(int i = 0; i < n; i++)
      if(!removed[i]) ans += iw[i];
    return true;
  }
};
