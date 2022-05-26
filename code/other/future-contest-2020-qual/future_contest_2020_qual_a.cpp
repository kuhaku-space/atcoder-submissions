#include <bits/stdc++.h>
using namespace std;

#define FOR(i, m, n) for(int (i) = (m); (i) < (n); (i)++)
#define rep(i, n) FOR(i, 0, n)
#define repn(i, n) FOR(i, 1, n+1)
#define co(n) cout << (n) << endl
#define cosp(n) cout << (n) << ' '
#define setp(n) cout << fixed << setprecision(n);
#define all(s) (s).begin(), (s).end()
#define pb push_back
#define mp make_pair
#define fs first
#define sc second
typedef long long ll;
typedef pair<int, int> P;

const ll INF = 1e9+1;
const ll LINF = 1e18+1;
const ll MOD = 1e9+7;
//const ll MOD = 998244353;
const double PI = acos(-1);
const double EPS = 1e-9;

struct Square{
	int type = 0;
	char dir;
};

struct Robot{
	int x;
	int y;
	char dir;
};

struct Goal{
	int x;
	int y;
};

struct Block{
	int x;
	int y;
};

struct Guide{
	int x;
	int y;
	char dir;
};

struct Pos{
	int x;
	int y;
};

const int N = 40;
const int M = 100;
const int B = 300;
Square board[N][N];
int step_board[N][N] = {};
Goal goal;
vector<Guide> guides;
vector<Robot> robots(M);

void init_board(){
	rep(i, N) rep(j, N) board[j][i].type = 0; 
}

void input(){
	int n, m, b;
	cin >> n >> m >> b;
	cin >> goal.y >> goal.x;
	board[goal.x][goal.y].type = 3;
	rep(i, M){
		cin >> robots[i].y >> robots[i].x >> robots[i].dir;
	}
	rep(i, B){
		Block block;
		cin >> block.y >> block.x;
		board[block.y][block.x].type = 1;
	}
}

void finput(){
	ifstream fin("teskCase_0.txt");
	int n, m, b;
	fin >> n >> m >> b;
	fin >> goal.y >> goal.x;
	board[goal.y][goal.x].type = 3;
	rep(i, M){
		fin >> robots[i].y >> robots[i].x >> robots[i].dir;
	}
	rep(i, B){
		Block block;
		fin >> block.y >> block.x;
		board[block.y][block.x].type = 1;
	}
}

void output(){
	cout << guides.size() << endl;
	rep(i, guides.size()) cout << guides[i].y << ' ' << guides[i].x  << ' ' << guides[i].dir << endl;
}

void foutput(){
	ofstream fout("answer.txt");
	fout << guides.size() << endl;
	rep(i, guides.size()) fout << guides[i].y << ' ' << guides[i].x  << ' ' << guides[i].dir << endl;
}

int warp(int n){
	if(n == -1) return N-1;
	if(n == N) return 0;
	return n;
}

bool is_space_square(int x, int y){
	return (board[warp(y)][warp(x)].type == 0);
}

void fill_board(int x, int y){
	queue<P> que;
	que.push(mp(x, y));
	while(!que.empty()){
		P pos = que.front(); que.pop();
		x = pos.fs, y = pos.sc;
		if(is_space_square(x-1, y)){
			int x_dash = warp(x-1);
			board[y][x_dash].type = 2;
			board[y][x_dash].dir = 'R';
			que.push(mp(x_dash, y));
		}
		if(is_space_square(x+1, y)){
			int x_dash = warp(x+1);
			board[y][x_dash].type = 2;
			board[y][x_dash].dir = 'L';
			que.push(mp(x_dash, y));
		}
		if(is_space_square(x, y-1)){
			int y_dash = warp(y-1);
			board[y_dash][x].type = 2;
			board[y_dash][x].dir = 'D';
			que.push(mp(x, y_dash));
		}
		if(is_space_square(x, y+1)){
			int y_dash = warp(y+1);
			board[y_dash][x].type = 2;
			board[y_dash][x].dir = 'U';
			que.push(mp(x, y_dash));
		}
	}

}

void one_step(int x, int y, char dir){
	if(x == goal.x && y == goal.y) return;
	if(dir != board[y][x].dir) step_board[y][x]++;
	switch(board[y][x].dir){
		case 'U': one_step(x, warp(y-1), 'U'); break;
		case 'D': one_step(x, warp(y+1), 'D'); break;
		case 'L': one_step(warp(x-1), y, 'L'); break;
		case 'R': one_step(warp(x+1), y, 'R'); break;
	}
}

void erease_board(){
	rep(i, M) one_step(robots[i].x, robots[i].y, robots[i].dir);

	rep(i, N){
		rep(j, N){
			if(step_board[j][i] == 0){
				board[j][i].type = 0;
			}
		}
	}
}

void answer(){
	rep(i, N){
		rep(j, N){
			if(board[j][i].type == 2){
				Guide guide = {i, j, board[j][i].dir};
				guides.pb(guide);
			}
		}
	}
}

int main(void){
	init_board();
	input();

	fill_board(goal.x, goal.y);
	erease_board();
	answer();

	output();
	return 0;
}
