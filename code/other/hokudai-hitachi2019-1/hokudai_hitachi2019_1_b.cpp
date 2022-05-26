#include <bits/stdc++.h>
using namespace std;

#define FOR(i, m, n) for(int (i) = (m); (i) < (n); (i)++)
#define FORN(i, m, n) for(int (i) = (m); (i) <= (n); (i)++)
#define FORR(i, m, n) for(int (i) = (m); (i) >= (n); (i)--)
#define rep(i, n) FOR(i, 0, n)
#define repn(i, n) FORN(i, 1, n)
#define repr(i, n) FORR(i, n, 0)
#define repnr(i, n) FORR(i, n, 1)
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

const ll INF = 1e9+5;
const ll LINF = 1e18+5;
const ll MOD = 1e9+7;
//const ll MOD = 998244353;
const double PI = acos(-1);
const double EPS = 1e-9;
const int MAX_T = 1e5;
const int MAX_V = 400;

struct Player{
	int pos;
	int dst;
	int nxt;
	int rest;
};

struct Task{
	int id;
	int dst;
	int time;
};

int V, E, T;
int dist[MAX_V+1][MAX_V+1] = {};
Player player = {1, 1, 1, 0};
vector<vector<Task> > task_list(MAX_T);
int command;
vector<Task> ordered_tasks;
vector<vector<Task> > recieved_tasks(MAX_V+1);

void print_vec(const vector<Task> v){
	for(Task i : v) cosp(i.id);
	cout << endl;
}

void print_dist(){
	repn(i, V){
		repn(j, V) cosp(dist[i][j]);
		cout << endl;
	}
}

void list_tasks(int t){
	int n;
	cin >> n;
	rep(i, n){
		Task tmp;
		cin >> tmp.id >> tmp.dst;
		tmp.time = t;
		task_list[t].pb(tmp);
	} 
}

void init(){
	repn(i, V) repn(j, V) dist[i][j] = INF;
	repn(i, V) dist[i][i] = 0;
}

void input_a(){
	cin >> V >> E;
	init();
	rep(i, E){
		int v1, v2, d;
		cin >> v1 >> v2 >> d;
		dist[v1][v2] = d;
		dist[v2][v1] = d;
	}
	int f;
	rep(i, V) cin >> f;
	cin >> T;
}

void input_b(int t){
	list_tasks(t);
	int n, id;
	cin >> n;
	rep(i, n) cin >> id;
}

void input_c(int t){
	string verdict;
	cin >> verdict;
	if(verdict == "NG") exit(0);
	int n, id;
	cin >> n;
	rep(i, n) cin >> id;
}

void output(){
	co(command);
}

void wf(){
	repn(k, V) repn(i, V) repn(j, V) dist[i][j] = min(dist[i][j], dist[i][k]+dist[k][j]);
}

void order_task(int t){
	ordered_tasks.insert(ordered_tasks.end(), all(task_list[t]));
}

void recieve_task(){
	rep(i, ordered_tasks.size()){
		Task tmp = ordered_tasks[i];
		recieved_tasks[tmp.dst].pb(tmp);
	}
	ordered_tasks.clear();
}

void dicide_dst(int t){
	if(!recieved_tasks[player.pos].empty()) recieved_tasks[player.pos].clear();
	player.dst = 1;
	int min_dist = INF;
	if(player.pos != 1 && !ordered_tasks.empty()) min_dist = dist[player.pos][1]-ordered_tasks.size()/20;
	repn(i, V){
		if(recieved_tasks[i].empty()) continue;
		int d = dist[player.pos][i];
		rep(j, recieved_tasks[i].size()) d -= (t-recieved_tasks[i][j].time)/1000;
		if(d < min_dist){
			min_dist = d;
			player.dst = i;
		}
	}
}

void search_nxt(){
	player.nxt = player.dst;
	bool flg = true;
	while(flg){
		flg = false;
		repn(i, V){
			if(i == player.nxt || i == player.pos) continue;
			if(dist[player.pos][player.nxt] == dist[player.pos][i]+dist[i][player.nxt]){
				player.nxt = i;
				flg = true;
				break;
			}
		}
	}

	player.rest = dist[player.pos][player.nxt];
}

void move(int t){
	if(player.pos == player.nxt) search_nxt();
	if(player.rest){
		player.rest--;
		command = player.nxt;
		if(!player.rest) player.pos = player.nxt;
	}else command = -1;
}

void action(int t){
	order_task(t);
	if(player.pos == 1 && player.nxt) recieve_task();
	if(player.pos == player.dst) dicide_dst(t);
	move(t);
}

int main(void){
	input_a();
	wf();
	rep(i, T){
		input_b(i);
		action(i);
		output();
		input_c(i);
	}
	return 0;
}
