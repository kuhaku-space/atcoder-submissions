#ifndef LOCAL
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("inline")
#endif

#include <algorithm>
#include <array>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;
using ll = int64_t;
#define FOR(i, m, n) for (int i = (m); i < (n); ++i)
#define rep(i, n) FOR(i, 0, n)
template <class T, class U>
constexpr bool chmax(T &a, const U &b) noexcept {
    return a < b ? a = b, true : false;
}
template <class T, class U>
constexpr bool chmin(T &a, const U &b) noexcept {
    return b < a ? a = b, true : false;
}
constexpr int Inf = 1000000003;
constexpr int64_t INF = 1000000000000000003;

constexpr int BOARD_SIZE = 30;
constexpr int MAX_TURN = 300;

struct Position {
    int x, y;

    constexpr Position() : x(-1), y(-1) {}
    constexpr Position(int _x, int _y) : x(_x), y(_y) {}

    constexpr Position &operator+=(const Position &rhs) {
        this->x += rhs.x, this->y += rhs.y;
        return *this;
    }
    constexpr Position &operator-=(const Position &rhs) {
        this->x -= rhs.x, this->y -= rhs.y;
        return *this;
    }
    constexpr Position &operator*=(int rhs) {
        this->x *= rhs, this->y *= rhs;
        return *this;
    }

    constexpr Position operator+(const Position &rhs) const {
        return Position(*this) += rhs;
    }
    constexpr Position operator-(const Position &rhs) const {
        return Position(*this) -= rhs;
    }
    constexpr Position operator*(int rhs) const {
        return Position(*this) *= rhs;
    }

    constexpr bool operator==(const Position &rhs) {
        return this->x == rhs.x && this->y == rhs.y;
    }
    constexpr bool operator!=(const Position &rhs) {
        return !(*this == rhs);
    }

    friend istream &operator>>(istream &is, Position &rhs) {
        is >> rhs.x >> rhs.y;
        --rhs.x, --rhs.y;
        return is;
    }

    bool in_board() const {
        return 0 <= this->x && this->x < BOARD_SIZE && 0 <= this->y && this->y < BOARD_SIZE;
    }

    int dist(const Position &rhs) const {
        return abs(this->x - rhs.x) + abs(this->y - rhs.y);
    }

    Position get_next_position(int direction) const;
};

constexpr char action_string[2][5] = {"uldr", "ULDR"};
constexpr Position action_position[4] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

Position Position::get_next_position(int direction) const {
    return *this + action_position[direction];
}

namespace dog {
struct State {
    struct Action {
        int type;
        int direction;

        constexpr Action() : type(-1), direction() {}
        constexpr Action(int _type, int _direction) : type(_type), direction(_direction) {}

        Position get_position() const {
            return action_position[direction];
        }

        friend ostream &operator<<(ostream &os, const Action &rhs) {
            return os << (rhs.type == -1 ? '.' : action_string[rhs.type][rhs.direction]);
        }
    };

    struct Pet {
        Position position;
        int type;

        constexpr Pet() : position(), type() {}

        string move() {
            string str;
            cin >> str;
            for (auto ch : str) {
                Position pos;
                for (int i = 0; i < 4; ++i) {
                    if (ch == action_string[1][i])
                        pos = action_position[i];
                }
                this->position += pos;
            }
            return str;
        }

        bool exists_in_erea(int top, int bottom, int left, int right) const {
            return top <= this->position.x && this->position.x <= bottom &&
                   left <= this->position.y && this->position.y <= right;
        }

        bool exists_in_center() const {
            return this->exists_in_erea(14, 15, 14, 15);
        }

        bool is_dog() const {
            return this->type == 4;
        }

        friend istream &operator>>(istream &is, Pet &rhs) {
            return is >> rhs.position >> rhs.type;
        }
    };

    struct Human {
        struct Purpose {
            Position position;
            int direction;
            bool achieved;

            constexpr Purpose() : position(), direction(), achieved() {}

            bool has_achieved() const {
                return this->achieved;
            }

            void set_achieved() {
                this->achieved = true;
            }

            void reset_achieved() {
                this->achieved = false;
            }

            Position get_position() const {
                return action_position[this->direction];
            }

            void reverse() {
                this->direction = (this->direction + 2) % 4;
            }

            int get_reverse() const {
                return (this->direction + 2) % 4;
            }

            Position get_reverse_position() const {
                return action_position[this->get_reverse()];
            }

            void rotate(int diff = 1) {
                this->direction = (this->direction + diff) % 4;
            }

            int get_rotate(int diff = 1) const {
                return (this->direction + diff) % 4;
            }

            Position get_rotate_position(int diff = 1) const {
                return action_position[this->get_rotate(diff)];
            }
        };
        Position position;
        Purpose purpose;
        int id;

        constexpr Human() : position(), purpose(), id() {}

        void set_id(int id) {
            this->id = id;
        }

        void set_purpose(const State &state) {
            if (state.state == 0) {
                if (this->id < 4) {
                    this->purpose.position = Position(28 * (this->id + 1) / 4 - 1, 1);
                } else {
                    this->purpose.position = Position(28 * (this->id % 4) / 4, 0);
                }
            } else if (state.state == 1) {
                if (this->id < 4) {
                    this->purpose.position = Position(28 * this->id / 4, 1);
                    this->purpose.direction = 0;
                }
            } else if (state.state == 2) {
                if (this->id == 0) {
                    this->purpose.position = Position(0, 1);
                } else {
                    this->purpose.position = Position(0, 0);
                }
                this->purpose.direction = 2;
            } else if (state.state == 3) {
                this->purpose.position += this->purpose.get_position() * 29;
            } else if (state.state == 4) {
                vector<Position> positions = {{28, 15}, {15, 28}, {1, 16}, {14, 4}, {15, 15}};
                if (this->id < 4) {
                    this->purpose.position = positions[this->id];
                    this->purpose.direction = this->id;
                } else {
                    this->purpose.position = positions[4];
                }
            } else if (state.state == 5) {
                if (this->id == 0) {
                    this->purpose.position += this->purpose.get_position() * 13;
                } else if (this->id == 1) {
                    this->purpose.position += this->purpose.get_position() * 12;
                } else if (this->id == 2) {
                    this->purpose.position += this->purpose.get_position() * 13;
                } else if (this->id == 3) {
                    this->purpose.position += this->purpose.get_position() * 11;
                }
            } else if (state.state == 6) {
                if (this->id < 4) {
                    this->purpose.rotate();
                }
            }
        }

        void update_purpose_achieved(const State &state) {
            if (state.state == 0) {
                if (this->position == this->purpose.position)
                    this->purpose.set_achieved();
            } else if (state.state == 1) {
                if (this->id < 4) {
                    if (this->position == this->purpose.position &&
                        !state.is_space(this->position.get_next_position(3)))
                        this->purpose.set_achieved();
                } else {
                    if (this->position == this->purpose.position)
                        this->purpose.set_achieved();
                }
            } else if (state.state == 2) {
                if (this->position == this->purpose.position)
                    this->purpose.set_achieved();
            } else if (state.state == 3) {
                if (this->position == this->purpose.position)
                    this->purpose.set_achieved();
            } else if (state.state == 4) {
                if (this->position == this->purpose.position)
                    this->purpose.set_achieved();
            } else if (state.state == 5) {
                if (this->id < 4) {
                    if (this->position == this->purpose.position &&
                        !state.is_space(this->position + this->purpose.get_reverse_position()))
                        this->purpose.set_achieved();
                } else {
                    if (this->position == this->purpose.position)
                        this->purpose.set_achieved();
                }
            }
        }

        Action move(const State &state, Position destination) {
            auto dists = state.get_dist(destination);
            int dist = dists[this->position.x][this->position.y];
            for (int dir = 0; dir < 4; ++dir) {
                auto next_position = this->position.get_next_position(dir);
                if (state.is_space(next_position) &&
                    dists[next_position.x][next_position.y] < dist) {
                    return Action(1, dir);
                }
            }
            return Action();
        }

        Action solve(const State &state) {
            if (this->purpose.has_achieved())
                return Action();
            if (state.state == 0) {
                return this->move(state, this->purpose.position);
            } else if (state.state == 1) {
                if (this->id < 4) {
                    if (state.is_space(this->position + this->purpose.get_rotate_position(3))) {
                        if (state.can_block(this->position + this->purpose.get_rotate_position(3)))
                            return Action(0, this->purpose.get_rotate(3));
                    } else
                        return this->move(state, this->purpose.position);
                }
            } else if (state.state == 2) {
                return this->move(state, this->purpose.position);
            } else if (state.state == 3) {
                if (this->id == 0) {
                    if (state.can_block(Position(this->position.x - 1, 0)) &&
                        state.can_block(Position(this->position.x - 1, 1)) &&
                        state.exists_all_dogs_in_erea(0, this->position.x - 2, 0, 1)) {
                        return Action(0, 0);
                    }
                } else if (this->id == 1) {
                    if (!state.is_space(Position(this->position.x - 1, 1)) &&
                        state.can_block(Position(this->position.x - 1, 0))) {
                        return Action(0, 0);
                    }
                }
                return this->move(state, this->purpose.position);
            } else if (state.state == 4) {
                return this->move(state, this->purpose.position);
            } else if (state.state == 5) {
                if (this->id < 4) {
                    auto next_position = this->position + this->purpose.get_reverse_position();
                    if (state.is_space(next_position)) {
                        return state.can_block(next_position)
                                   ? Action(0, this->purpose.get_reverse())
                                   : Action();
                    } else {
                        return Action(1, this->purpose.direction);
                    }
                }
            } else if (state.state == 6) {
                if (this->id < 4) {
                    auto count = state.count_pet();
                    int min_pet_index = min_element(count.begin(), count.end()) - count.begin();
                    int index = this->id;
                    auto block_position = this->position + this->purpose.get_position();
                    if (count[index] != count[min_pet_index] && state.can_block(block_position))
                        return Action(0, this->purpose.direction);
                }
            }
            return Action();
        }

        Position act(Action action) {
            cout << action;
            if (action.type == 0) {
                return this->position + action.get_position();
            }
            if (action.type == 1) {
                this->position += action.get_position();
            }
            return Position();
        }

        friend istream &operator>>(istream &is, Human &rhs) {
            return is >> rhs.position;
        }
    };

    struct Input {
        int pet_size, human_size;
        vector<Pet> pets;
        vector<Human> humans;

        void input() {
            cin >> pet_size;
            pets.resize(pet_size);
            for (auto &pet : pets) cin >> pet;
            cin >> human_size;
            humans.resize(human_size);
            for (auto &human : humans) {
                cin >> human;
            }
        }

        bool contains_some_dogs() const {
            for (auto pet : pets) {
                if (pet.is_dog())
                    return true;
            }
            return false;
        }
    };

    int state, turn;
    array<array<int, BOARD_SIZE>, BOARD_SIZE> board;
    int pet_size, human_size;
    vector<Pet> pets;
    vector<Human> humans;

    State() : state() {}

    void init(const Input &input) {
        for (int i = 0; i < BOARD_SIZE; ++i) {
            board[i].fill(0);
        }
        this->pet_size = input.pet_size;
        this->pets = input.pets;
        this->human_size = input.human_size;
        this->humans = input.humans;
        int count = 0;
        for (auto &human : humans) {
            human.set_id(count++);
            human.set_purpose(*this);
        }
    }

    bool is_space(Position position) const {
        return this->can_move(position);
    }

    bool can_move(Position position) const {
        return position.in_board() && board[position.x][position.y] == 0;
    }

    bool can_block(Position position) const {
        bool flag = this->can_move(position);
        for (auto human : humans) {
            flag &= position.dist(human.position) >= 1;
        }
        for (auto pet : pets) {
            flag &= position.dist(pet.position) >= 2;
        }
        return flag;
    }

    bool should_block(Position position) const {
        bool flag = this->can_block(position);
        for (auto human : humans) {
            flag &= position.x != human.position.x;
        }
        return flag;
    }

    vector<int> count_pet() const {
        vector<int> count(4);
        vector<Position> positions = {{15, 13}, {16, 15}, {14, 16}, {13, 14}};
        for (int i = 0; i < 4; ++i) {
            if (!this->is_space(positions[i]))
                count[i] = 100;
        }
        for (auto pet : pets) {
            int index = -1;
            if (pet.exists_in_erea(15, 29, 3, 15))
                index = 0;
            else if (pet.exists_in_erea(15, 29, 16, 29))
                index = 1;
            else if (pet.exists_in_erea(0, 14, 16, 29))
                index = 2;
            else if (pet.exists_in_erea(0, 14, 0, 15))
                index = 3;
            if (index != -1)
                ++count[index];
        }
        return count;
    }

    int count_dog() const {
        int count = 0;
        for (auto pet : pets) {
            count += pet.is_dog();
        }
        return count;
    }

    array<array<int, BOARD_SIZE>, BOARD_SIZE> get_dist(Position start) const {
        array<array<int, BOARD_SIZE>, BOARD_SIZE> dists;
        for (auto &arr : dists) arr.fill(1000);
        queue<pair<Position, int>> que;

        auto get_dist = [&dists](Position position) {
            return dists[position.x][position.y];
        };
        auto set_dist = [&dists, &que](Position position, int dist) {
            dists[position.x][position.y] = dist;
            que.emplace(position, dist);
        };

        set_dist(start, 0);
        while (!que.empty()) {
            auto [position, dist] = que.front();
            for (auto pos : action_position) {
                auto next_position = position + pos;
                if (this->is_space(next_position) && dist + 1 < get_dist(next_position)) {
                    set_dist(next_position, dist + 1);
                }
            }
            que.pop();
        }
        return dists;
    }

    bool exists_all_dogs_in_erea(int top, int bottom, int left, int right) const {
        static bool start = true;
        bool flag = start;
        for (auto pet : pets) {
            if (pet.type == 4) {
                flag &= pet.exists_in_erea(top, bottom, left, right);
            }
        }
        if (flag) {
            start = false;
            return true;
        }
        return false;
    }

    bool exists_some_dogs_in_erea(int top, int bottom, int left, int right) const {
        bool flag = false;
        for (auto pet : pets) {
            if (pet.type == 4) {
                flag |= pet.exists_in_erea(top, bottom, left, right);
            }
        }
        return flag;
    }

    void act(Human &human, Action action) {
        Position positon = human.act(action);
        if (positon.in_board())
            this->board[positon.x][positon.y] = 1;
    }

    void update_state() {
        bool flag = true;
        for (auto human : humans) {
            flag &= human.purpose.has_achieved();
        }
        if (this->state == 2) {
            for (auto pet : pets) {
                if (pet.type == 4) {
                    flag &= pet.exists_in_erea(0, 1, 0, 1);
                }
            }
        }
        if (flag) {
            ++state;
            for (auto &human : humans) {
                human.purpose.reset_achieved();
                human.set_purpose(*this);
            }
        }
    }

    void reverse_state() {
        if (this->state == 3) {
            int top = this->humans[0].position.x;
            if (top == 28 && this->exists_some_dogs_in_erea(26, 29, 0, 1)) {
                this->state = 2;
                for (auto &human : humans) {
                    human.purpose.reset_achieved();
                    human.set_purpose(*this);
                }
            }
        }
    }

    void solve() {
        for (this->turn = 0; this->turn < MAX_TURN; ++this->turn) {
            for (int i = 0; i < human_size; ++i) {
                auto action = humans[i].solve(*this);
                this->act(humans[i], action);
                humans[i].update_purpose_achieved(*this);
            }
            cout << endl;

            for (auto &pet : pets) {
                pet.move();
            }

            this->update_state();
            this->reverse_state();
        }
    }
};

}  // namespace dog

namespace no_dog {
struct State : dog::State {
    struct Human : dog::State::Human {
        Position position;
        Purpose purpose;
        int id;

        constexpr Human(dog::State::Human human)
            : position(human.position), purpose(human.purpose), id(human.id) {}

        void set_id(int id) {
            this->id = id;
        }

        void set_purpose(const State &state) {
            if (state.state == 0) {
                if (this->id == 0) {
                    this->purpose.position = Position(28, 14);
                } else if (this->id == 1) {
                    this->purpose.position = Position(15, 28);
                } else if (this->id == 2) {
                    this->purpose.position = Position(1, 15);
                } else if (this->id == 3) {
                    this->purpose.position = Position(14, 1);
                } else if (this->id == 4 && state.count_dog() >= 1) {
                    this->purpose.position = Position(0, 0);
                } else if (this->id == 5 && state.count_dog() >= 5) {
                    this->purpose.position = Position(29, 29);
                } else {
                    this->purpose.position = Position(15, 15);
                }
                if (this->id < 4) {
                    this->purpose.direction = this->id;
                }
            } else if (state.state == 1) {
                if (this->id < 4) {
                    this->purpose.position += this->purpose.get_position() * 13;
                }
            } else if (state.state == 2) {
                if (this->id < 4) {
                    this->purpose.rotate();
                }
            }
        }

        void update_purpose(const State &state) {
            if (state.state == 0) {
                if (this->position == this->purpose.position)
                    this->purpose.set_achieved();
            } else if (state.state == 1) {
                if (this->id < 4) {
                    if (this->position == this->purpose.position &&
                        !state.is_space(this->position + this->purpose.get_reverse_position()))
                        this->purpose.set_achieved();
                } else {
                    if (this->position == this->purpose.position)
                        this->purpose.set_achieved();
                }
            }
        }

        Action move(Position destination) {
            int dist = destination.dist(this->position);
            for (int dir = 0; dir < 4; ++dir) {
                if (destination.dist(this->position + action_position[dir]) < dist)
                    return Action(1, dir);
            }
            return Action();
        }

        Action solve(const State &state) {
            if (this->purpose.has_achieved())
                return Action();
            if (state.state == 0) {
                if (!this->purpose.has_achieved()) {
                    return this->move(this->purpose.position);
                }
            } else if (state.state == 1) {
                if (this->id < 4) {
                    auto next_position = this->position + this->purpose.get_reverse_position();
                    if (state.is_space(next_position)) {
                        return state.can_block(next_position)
                                   ? Action(0, this->purpose.get_reverse())
                                   : Action();
                    } else {
                        return Action(1, this->purpose.direction);
                    }
                }
            } else if (state.state == 2) {
                if (this->id < 4) {
                    auto count = state.count_pet();
                    int min_pet_index = min_element(count.begin(), count.end()) - count.begin();
                    int index = this->id;
                    auto block_position = this->position + this->purpose.get_position();
                    if (count[index] != count[min_pet_index] && state.can_block(block_position))
                        return Action(0, this->purpose.direction);
                }
            }
            return Action();
        }

        Position act(Action action) {
            cout << action;
            if (action.type == 0) {
                return this->position + action.get_position();
            }
            if (action.type == 1) {
                this->position += action.get_position();
            }
            return Position();
        }

        friend istream &operator>>(istream &is, Human &rhs) {
            return is >> rhs.position;
        }
    };

    struct Input : dog::State::Input {};

    int state, turn;
    int pet_size, human_size;
    array<array<int, BOARD_SIZE>, BOARD_SIZE> board;
    vector<Pet> pets;
    vector<Human> humans;

    State() : state() {}

    void init(const Input &input) {
        this->pet_size = input.pet_size;
        for (auto &pet : input.pets) {
            this->pets.emplace_back(pet);
        }
        this->human_size = input.human_size;
        for (auto &human : input.humans) {
            this->humans.emplace_back(human);
        }

        for (int i = 0; i < BOARD_SIZE; ++i) {
            board[i].fill(0);
        }
        int count = 0;
        for (auto &human : this->humans) {
            human.set_id(count++);
            human.set_purpose(*this);
        }
    }

    bool is_space(Position position) const {
        return this->can_move(position);
    }

    bool can_move(Position position) const {
        return position.in_board() && board[position.x][position.y] == 0;
    }

    bool can_block(Position position) const {
        bool flag = this->can_move(position);
        for (auto human : humans) {
            flag &= position.dist(human.position) >= 1;
        }
        for (auto pet : pets) {
            flag &= position.dist(pet.position) >= 2;
        }
        return flag;
    }

    bool should_block(Position position) const {
        bool flag = this->can_block(position);
        for (auto human : humans) {
            flag &= position.x != human.position.x;
        }
        return flag;
    }

    vector<int> count_pet() const {
        vector<int> count(4);
        vector<Position> positions = {{15, 13}, {16, 15}, {14, 16}, {13, 14}};
        for (int i = 0; i < 4; ++i) {
            if (!this->is_space(positions[i]))
                count[i] = 100;
        }
        for (auto pet : pets) {
            int index = 0;
            if (pet.position.x < 15) {
                if (pet.position.y < 15)
                    index = 3;
                else
                    index = 2;
            } else {
                if (pet.position.y < 15)
                    index = 0;
                else
                    index = 1;
            }
            ++count[index];
        }
        return count;
    }

    int count_dog() const {
        int count = 0;
        for (auto pet : pets) {
            count += pet.is_dog();
        }
        return count;
    }

    void act(Human &human, Action action) {
        Position positon = human.act(action);
        if (positon.in_board())
            this->board[positon.x][positon.y] = 1;
    }

    void update_state() {
        bool flag = true;
        for (auto human : humans) {
            flag &= human.purpose.has_achieved();
        }
        if (flag) {
            ++state;
            for (auto &human : humans) {
                human.purpose.reset_achieved();
                human.set_purpose(*this);
            }
        }
    }

    void solve() {
        for (this->turn = 0; this->turn < MAX_TURN; ++this->turn) {
            for (int i = 0; i < human_size; ++i) {
                auto action = humans[i].solve(*this);
                this->act(humans[i], action);
                humans[i].update_purpose(*this);
            }
            cout << endl;
            this->update_state();

            for (auto &pet : pets) {
                pet.move();
            }
        }
    }
};

}  // namespace no_dog

int main(void) {
    no_dog::State::Input input;
    input.input();

    if (input.contains_some_dogs()) {
        dog::State state;
        state.init(input);
        state.solve();
    } else {
        no_dog::State state;
        state.init(input);
        state.solve();
    }

    return 0;
}
