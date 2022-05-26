#include <bits/stdc++.h>
using namespace std;

#define FOR(i, m, n) for(int (i) = (m); (i) < (n); (i)++)
#define FORN(i, m, n) for(int (i) = (m); (i) <= (n); (i)++)
#define FORR(i, m, n) for(int (i) = (m); (i) >= (n); (i)--)
#define rep(i, n) FOR(i, 0, n)
#define repn(i, n) FOR(i, 1, (n)+1)
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

const ll INF = 1e9+1;
const ll LINF = 1e18+1;
const ll MOD = 1e9+7;
//const ll MOD = 998244353;
const double PI = acos(-1);
const double EPS = 1e-9;

const int T = 1000;
const int N = 10;
const int M = 30000;

struct Task{
	int since;
	int until;
	int money;
	int skill[N+1];
	bool completed = false;
};
vector<Task> tasks(M+1);
vector<vector<int> > task_list(T+1);
int turn[T+1][3];
int player_level[N+1] = {};
int training_time[N+1] = {};
int skill_table[N+1][12] = {};
ll wallet = 0;

bool asc(const Task left, const Task right){
	return left.until < right.until;
}

void input(){
	int t, n, m;
	cin >> t >> n >> m;

	repn(i, M){
		cin >> tasks[i].since >> tasks[i].until >> tasks[i].money;
		repn(j, N) cin >> tasks[i].skill[j];
	}
}

void output(){
	repn(i, T){
		if(turn[i][0] == 3) co(turn[i][0]);
		else{
			cosp(turn[i][0]);
			co(turn[i][1]);
		}
	}
}

void finput(){
	ifstream fin("example_01.txt");
	int t = 0, n = 0, m = 0;
	fin >> t >> n >> m;

	repn(i, M){
		fin >> tasks[i].since >> tasks[i].until >> tasks[i].money;
		repn(j, N) fin >> tasks[i].skill[j];
	}
}

void foutput(){
	ofstream fout("anser.txt");
	repn(i, T){
		if(turn[i][0] == 3) fout << turn[i][0] << "\r\n";
		else fout << turn[i][0] << ' ' << turn[i][1] << "\r\n";
	}
}

int skill_lack(int m){
	int res = 0;
	repn(i, N) res += max(0, tasks[m].skill[i]-player_level[i]);
	return res;
}

ll get_reward(int m, int t){
	double reward = tasks[m].money;
    reward *= (1 + 9 * (double)(t - tasks[m].since) / (tasks[m].until - tasks[m].since));
    int SkillLack = 0;
    SkillLack = skill_lack(m);
    if (SkillLack == 0) reward *= 10;
    else {
        reward *= pow(0.5, SkillLack);
        reward += EPS;
    }
	return (ll)reward;
}

ll expenses(int n){
	double cost = 10000.0;
	cost *= pow(2, player_level[n]+1);
	cost += EPS;
	return (ll)cost;
}

void fill_skill_table(){
	repn(i, M) repn(j, N) repr(k, tasks[i].skill[j]) skill_table[j][k]++;
}

int define_level_up(){
	int n = 0;
	repn(i, N) if(skill_table[i][player_level[i]+1] > skill_table[n][player_level[n]+1]) n = i;
	return n;
}

void training(int n){
	wallet -= expenses(n);
	if(training_time[n] == player_level[n]){
		player_level[n]++;
		training_time[n] = 0;
	}else training_time[n]++;
}

void debug(){
	rep(i, N+1) rep(j, 11) skill_table[i][j] = 0;
	repn(i, T) if(turn[i][0] == 2) repn(j, N) skill_table[j][tasks[turn[i][1]].skill[j]]++;

	repn(i, N){
		rep(j, 11) cosp(skill_table[i][j]);
		cout << endl;
	}
}

int main(void){
	input();

	repn(i, T) turn[i][0] = 3;
	repn(i, M) task_list[tasks[i].until].pb(i);
	fill_skill_table();

	repn(i, T){
		int level_up = define_level_up();
		if(level_up && player_level[level_up] < 10 && expenses(level_up) <= wallet){
			turn[i][0] = 1;
			turn[i][1] = level_up;
		}else if(!task_list[i].empty()){
			rep(j, task_list[i].size()){
				if(turn[i][0] == 3){
					if(get_reward(task_list[i][j], i) > 1000){
						turn[i][0] = 2;
						turn[i][1] = task_list[i][j];
					}
				}else if(turn[i][0] == 2){
					if(get_reward(task_list[i][j], i) > get_reward(turn[i][1], i)){
						turn[i][1] = task_list[i][j];
					}
				}
			}
		}

		if(turn[i][0] == 3) wallet += 1000;
		else if(turn[i][0] == 1) training(turn[i][1]);
		else wallet += get_reward(turn[i][1], i);
	}

	repn(i, T) task_list[i].clear();
	repn(i, M) FORN(j, tasks[i].since, tasks[i].until) task_list[j].pb(i);
	repr(i, T){
		if(turn[i][0] == 2){
			rep(j, task_list[i].size()) if(!tasks[task_list[i][j]].completed && get_reward(task_list[i][j], i) > get_reward(turn[i][1], i)) turn[i][1] = task_list[i][j];
			tasks[turn[i][1]].completed = true;
		}else break;
	}

	output();

	return 0;
}
