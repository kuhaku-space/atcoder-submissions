#include <bits/stdc++.h>
using namespace std;
using ll = long long ;
using P = pair<ll, ll>;
using Vec = vector<ll>;
using VecP = vector<P>;
#define FOR(i, m, n) for(auto (i) = (m); (i) < (n); ++(i))
#define FORN(i, m, n) for(auto (i) = (m); (i) <= (n); ++(i))
#define FORR(i, m, n) for(auto (i) = (m); (i) >= (n); --(i))
#define rep(i, n) FOR(i, 0, n)
#define repn(i, n) FORN(i, 1, n)
#define repr(i, n) FORR(i, n, 0)
#define repnr(i, n) FORR(i, n, 1)
#define co(n) cout << (n) << endl
#define cosp(n) cout << (n) << ' '
#define setp(n) cout << fixed << setprecision(n);
#define all(s) (s).begin(), (s).end()
#define pf push_front
#define pb push_back
#define mp make_pair
#define fs first
#define sc second

const ll INF = 1e9+1;
const ll LINF = 1e18+1;
const ll MOD = 1e9+7;
//const ll MOD = 998244353;
const double PI = acos(-1);
const double EPS = 1e-9;
const ll MAX_V = 625;

struct Player{
	ll pos;
	ll dst;
	ll nxt;
	ll rest;
};

struct Task{
	ll dst;
	ll time;
};

ll V, E, T;
ll dist[MAX_V+1][MAX_V+1] = {};
ll traffic_jam[4][4] = {};
ll jam[4] = {};
Player player = {1, 1, 1, 0};
ll command;
unordered_map<ll, Task> task_list;
ll new_tasks = 0;
list<ll> tasks;
ll tasks_num = 0;
string car_status;
ll time_limit;
string verdict;
ll waiting_time;
ll cnt = 0;

void cancel_task(){
	ll n;
	cin >> n;
	rep(i, n){
		ll id;
		cin >> id;
		task_list.erase(id);
		tasks.remove(id);
	}
}

void new_task(ll t){
	ll n;
	cin >> n;
	new_tasks += n;
	rep(i, n){
		Task task;
		ll id;
		cin >> id >> task.dst;
		task.time = t;
		task_list[id] = task;
	} 
}

void put_task(){
	ll n;
	cin >> n;
	new_tasks -= n;
	tasks_num += n;
	rep(i, n){
		ll id;
		cin >> id;
		tasks.pb(id);
	}
}

void achieve_task(){
	ll n;
	cin >> n;
	tasks_num -= n;
	rep(i, n){
		ll id;
		cin >> id;
		task_list.erase(id);
		tasks.remove(id);
	}
}

void init(){
	repn(i, V) repn(j, V) dist[i][j] = LINF;
	repn(i, V) dist[i][i] = 0;
}

void input_s(){
	cin >> V >> E;
	init();
	rep(i, E){
		ll v1, v2, d, e1, e2;
		cin >> v1 >> v2 >> d >> e1 >> e2;
		dist[v1][v2] = d;
		dist[v2][v1] = d;
	}
	ll f;
	rep(i, V) cin >> f;
	rep(i, 4) rep(j, 4) cin >> traffic_jam[i][j];
	ll p, t;
	cin >> p >> t;
	cin >> T;
}

void input_f(ll t){
	//cin >> t;
	cin >> car_status;
	if(car_status == "WARNING") cin >> time_limit;
	rep(i, 4) cin >> jam[i];
	cancel_task();
	new_task(t);
	put_task();
}

void input_l(){
	cin >> verdict;
	if(verdict == "WAIT") cin >> waiting_time;
	if(verdict == "NG") exit(0);
	achieve_task();
}

void output(){
	co(command);
}

void wf(){
	repn(k, V) repn(i, V) repn(j, V) dist[i][j] = min(dist[i][j], dist[i][k]+dist[k][j]);
}

void dicide_dst(ll t){
	if(car_status == "WARNING"){
		player.dst = 1;
		return;
	}
	ll min_dist = LINF;
	player.dst = 1;
	if(player.pos != 1 && new_tasks > 20) min_dist = dist[player.pos][1]-new_tasks/20;
	for(ll id : tasks){
		Task task = task_list[id];
		ll d = dist[player.pos][task.dst]-(t-task.time)/400;
		if(d < min_dist){
			min_dist = d;
			player.dst = task.dst;
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

void action(ll t){
	if(player.pos == player.dst) dicide_dst(t);
	if(player.pos == player.nxt) search_nxt();
	if(car_status == "BROKEN" || verdict == "WAIT") command = -1;
	else if(player.rest){
		command = player.nxt;
	}else command = -1;
}

void move(){
	if(car_status != "BROKEN" && verdict == "OK" && player.rest){
		player.rest--;
		if(!player.rest) player.pos = player.nxt;
	}
}

void debug_a(){
  	while(true){
    	FILE *fp = fopen("flg.txt","r");
    	int flg;
    	fscanf(fp, "%d", &flg);
    	fclose(fp);
    	if(flg == 1) break;
  	}
}

void debug_b(){
  	FILE *fp = fopen("flg.txt", "w");
	fprintf(fp, "0");
  	fclose(fp);
}

int main(void){
	input_s();
	wf();
	//debug_a();
	rep(i, T){
		input_f(i);
		action(i);
		output();
		//debug_b();
		//debug_a();
		input_l();
		move();
	}
	return 0;
}
