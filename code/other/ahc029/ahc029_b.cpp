#include <cassert>
#include <cmath>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

namespace lib {

template <class T, class U>
constexpr bool chmax(T &a, const U &b) {
    return a < (T)b ? a = (T)b, true : false;
}
template <class T, class U>
constexpr bool chmin(T &a, const U &b) {
    return (T)b < a ? a = (T)b, true : false;
}

}  // namespace lib
using namespace lib;

constexpr int MAX_INVEST_LEVEL = 20;

struct Project {
    int64_t remaining_work;
    int64_t value;
};

enum class CardType {
    WORK_SINGLE = 0,
    WORK_ALL = 1,
    CANCEL_SINGLE = 2,
    CANCEL_ALL = 3,
    INVEST = 4,
};

ostream &operator<<(ostream &os, CardType ct) {
    switch (ct) {
        case CardType::WORK_SINGLE: os << "WORK_SINGLE"; break;
        case CardType::WORK_ALL: os << "WORK_ALL"; break;
        case CardType::CANCEL_SINGLE: os << "CANCEL_SINGLE"; break;
        case CardType::CANCEL_ALL: os << "CANCEL_ALL"; break;
        case CardType::INVEST: os << "INVEST"; break;
    }
    return os;
}

struct Card {
    CardType type;
    int64_t power;
    int64_t point;

    bool is_regular_work_card() const { return type == CardType::WORK_SINGLE; }
    bool is_hard_work_card() const { return type == CardType::WORK_ALL; }
    bool is_cancel_card() const { return type == CardType::CANCEL_SINGLE; }
    bool is_restructuring_card() const { return type == CardType::CANCEL_ALL; }
    bool is_investment_card() const { return type == CardType::INVEST; }

    bool can_buy(int64_t money) const { return point <= money; }
};

struct Judge {
    const int n;
    const int m;
    const int k;

    Judge(int n, int m, int k) : n(n), m(m), k(k) {}

    vector<Card> read_initial_cards() {
        vector<Card> cards;
        for (int i = 0; i < n; i++) {
            int64_t t, w;
            cin >> t >> w;
            cards.push_back(Card{(CardType)t, w, 0ll});
        }
        return cards;
    }

    vector<Project> read_projects() {
        vector<Project> projects;
        for (int i = 0; i < m; i++) {
            int64_t h, v;
            cin >> h >> v;
            projects.push_back(Project{h, v});
        }
        return projects;
    }

    void use_card(int c, int m) { cout << c << " " << m << endl; }

    int64_t read_money() {
        int64_t money;
        cin >> money;
        return money;
    }

    vector<Card> read_next_cards() {
        vector<Card> cards;
        for (int i = 0; i < k; i++) {
            int64_t t, w, p;
            cin >> t >> w >> p;
            cards.push_back(Card{(CardType)t, w, p});
        }
        return cards;
    }

    void select_card(int r) { cout << r << endl; }

    void comment(const string &message) { cout << "# " << message << endl; }
};

struct Solver {
    const int n;
    const int m;
    const int k;
    const int t;
    Judge judge;
    int turn;
    int invest_level;
    int64_t money;
    vector<Project> projects;
    vector<Card> cards;

    Solver(int n, int m, int k, int t)
        : n(n), m(m), k(k), t(t), judge(n, m, k), turn(0), invest_level(0), money(0) {}

    int64_t solve() {
        cards = judge.read_initial_cards();
        projects = judge.read_projects();
        for (turn = 0; turn < t; ++turn) {
            auto [use_card_i, use_target] = select_action();
            const Card &use_card = cards[use_card_i];
            if (use_card.type == CardType::INVEST) { invest_level++; }
            // example for comments
            stringstream msg;
            msg << "used Card(type=" << use_card.type << " power=" << use_card.power
                << " point=" << use_card.point << ") to target " << use_target;
            judge.comment(msg.str());
            judge.use_card(use_card_i, use_target);
            assert(invest_level <= MAX_INVEST_LEVEL);

            projects = judge.read_projects();
            money = judge.read_money();

            vector<Card> next_cards = judge.read_next_cards();
            int select_card_i = select_next_card(next_cards);
            cards[use_card_i] = next_cards[select_card_i];
            judge.select_card(select_card_i);
            money -= next_cards[select_card_i].point;
            assert(money >= 0);
            msg = stringstream();
            msg << "Score = " << money;
            judge.comment(msg.str());
        }
        return money;
    }

    bool has_regular_work_card() const {
        for (Card card : cards) {
            if (card.is_regular_work_card()) return true;
        }
        return false;
    }

    int64_t calc_rest_turn(const Card &card, const Project &project) const {
        if (project.remaining_work <= card.power) return 0;
        return ((project.remaining_work - card.power - 1) >> invest_level) + 1;
    }

    double calc_score(const Card &card, const Project &project) const {
        int64_t value = project.value - card.point;
        return (double)value / pow(1 + calc_rest_turn(card, project), 0.4);
    }

    pair<int, int> select_action() const {
        double max_score = 0;
        int max_card_i = 0, max_target = 0;
        for (int card_i = 0; card_i < n; ++card_i) {
            if (cards[card_i].is_investment_card()) return {card_i, 0};
            if (!cards[card_i].is_regular_work_card()) continue;
            // if (!cards[card_i].can_buy(money)) continue;
            for (int target = 0; target < m; ++target) {
                int64_t score = projects[target].value - cards[card_i].point;
                if (chmax(max_score, calc_score(cards[card_i], projects[target]))) {
                    max_card_i = card_i;
                    max_target = target;
                }
            }
        }
        return {max_card_i, max_target};
    }

    int select_next_card(const vector<Card> &next_cards) const {
        if (turn == t - 1) return 0;
        double max_score = 0;
        int max_card_i = 0;
        for (int card_i = 0; card_i < k; ++card_i) {
            if (t - turn > 160 && next_cards[card_i].is_investment_card() &&
                next_cards[card_i].can_buy(money))
                return card_i;
            if (!next_cards[card_i].is_regular_work_card()) continue;
            if (!next_cards[card_i].can_buy(money)) continue;
            for (int target = 0; target < m; ++target) {
                // if (projects[target].remaining_work - next_cards[card_i].power >= t - turn)
                // continue;
                int64_t score = projects[target].value - next_cards[card_i].point;
                if (chmax(max_score, calc_score(next_cards[card_i], projects[target]))) {
                    max_card_i = card_i;
                }
            }
        }
        return max_card_i;
    }
};

int main() {
    int n, m, k, t;
    cin >> n >> m >> k >> t;
    Solver solver(n, m, k, t);
    int64_t score = solver.solve();
    // cerr << "score:" << score << endl;
}
