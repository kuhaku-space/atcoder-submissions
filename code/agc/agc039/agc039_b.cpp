#include <bits/stdc++.h>
using namespace std;

#define REP(i, n) for(int (i) = 0; (i) < (n); (i)++)
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define INF 100000

typedef long long ll;

#define N_MAX 200

int dist[N_MAX][N_MAX];
int color[N_MAX];

bool dfs(int node){
	bool flg  = true;

	REP(i, N_MAX){
		if(dist[node][i] == 1){
			if(color[i] == 0){
				color[i] = -1*color[node];
				flg = flg && dfs(i);
			}else if(color[i] == color[node]) return false;
		}
	}

	return flg;
}

int main(void){
	int n;
	cin >> n;

	REP(i, n) REP(j, n) dist[i][j] = INF;
	REP(i, n) dist[i][i] = 0;

	string s;
	REP(i, n){
		cin >> s;
		REP(j, n){
			if(s[j] == '1') dist[i][j] = 1;
		}
	}

	memset(color, 0, sizeof(color));

	color[0] = 1;
	if(!dfs(0)){
		cout << -1 << endl;
		return 0;
	}

	REP(k, n) REP(i, n) REP(j, n) dist[i][j] = MIN(dist[i][j], dist[i][k]+dist[k][j]);

	int max = 0;
	REP(i, n) REP(j, n) if(dist[i][j] != INF) max = MAX(max, dist[i][j]);

	cout << max+1 << endl;

	return 0;
}
