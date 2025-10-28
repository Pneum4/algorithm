#include<iostream>
#include<vector>
using namespace std;
using pii = pair<int, int>;
using ll = long long;
const ll INF = (ll)4e18;

/*
음수 간선이다 = 벨만 포드 or 플로이드 워셜
- 출발점이 정해져 있으면 벨만포드 : O(VE)
- 모든 최단 거리가 궁금하면 플로이드 워셜 : O(V^3)
이문제는 1번 도시에서만 최단거리가 필요하므로 벨만포드로 풀이
*/

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);

  int N, M; cin>>N>>M;

  vector<vector<pii>> graph(N+1, vectㅉor<pii>());
  for(int i=0; i<M; ++i) {
    int s, e, w; cin>>s>>e>>w;
    graph[s].push_back({e, w});
  }
  
  vector<ll> dist(N+1, INF);
  dist[1] = 0ll;

  // 최대 N-1번 벨만포드 반복
  for(int i=0; i<N-1; ++i) {
    bool updated = false;
    for(int s=1; s<=N; ++s) {
      if(dist[s] == INF) continue;
      for(auto &ele: graph[s]) {
        int e = ele.first;
        int w = ele.second;
        
        if(dist[e] > dist[s] + (ll)w) {
          dist[e] = dist[s] + (ll)w;
          updated = true;
        }
      }
    }
    if(!updated)
      break;
  }
  
  // 한 번 더 돌려보고 변화가 있는지 확인
  // 변화가 있으면 최단거리 없음
  bool updated = false;
  for(int s=1; s<=N; ++s) {
    if(dist[s] == INF) continue;
    for(auto &ele: graph[s]) {
      int e = ele.first;
      int w = ele.second;
  
      if(dist[e] > dist[s] + (ll)w) {
        dist[e] = dist[s] + (ll)w;
        updated = true;
        break;
      }
    }
    if(updated) break;
  }
  
  if(updated) cout<<-1<<'\n';
  else {
    for(int i=2; i<=N; ++i) {
      if(dist[i] == INF)
        cout<<-1<<'\n';
      else
        cout<<dist[i]<<'\n';
    }
  }

  return 0;
}