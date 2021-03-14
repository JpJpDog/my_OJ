//保证剩余城市的连接
#include<iostream>
#include<algorithm>
using namespace std;
bool vis[1001];
int G[1001][1001];
int n;
void dfs(int node){
  vis[node]=true;
  for(int i=1;i<=n;i++){
     if(vis[i]==false&&G[node][i]==1){
     dfs(i);
  }
}
 
}
int main(){
  int m,k;
  scanf("%d%d%d", &n, &m, &k);
  int u,v;
  for(int i=0;i<m;i++){
    scanf("%d%d", &u, &v);
    G[u][v]=G[v][u]=1;
  }
  for(int i=0;i<k;i++){//输入被去除的城市
    fill(vis,vis+1001,false);
    int a;
    scanf("%d",&a);
    vis[a]=true;
    //去除选中点与其他点的连接
    int cnt=0;
    for(int j=1;j<=n;j++){//找去除点后的入口1⃣️
      if(vis[j]==false){
        dfs(j);//未访问的就是入口，找到一个入口后进入迭代
        cnt++;
      }
    }
    //dfs内，判断入口和其余的点是否联通，尽量走完所有节点
    //若未访问完全部节点退出迭代，退回仍有未访问分支的岔路口，即进入1⃣️换一个入口
     printf("%d\n",cnt-1);
  }
  return 0;
}