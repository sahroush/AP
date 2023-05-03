#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

const int SIDE_LENGTH = 7;
const string DIRS[4] = {"LEFT", "RIGHT", "UP", "DOWN"};
const int DIRDX[4] = {0, 0, -1, 1};
const int DIRDY[4] = {-1, 1, 0, 0};
const int EMPTY = 0;
const int FULL = 1;
const int BLOCKED = 2;

struct Move {
  char row;
  int col;
  string direction;
  Move(char row, int col, string direction)
      : row(row), col(col), direction(direction) {}
  Move(int x, int y, int dir)
      : row(char('A' + x)), col(y), direction(DIRS[dir]) {}
  void print() { cout << row << col + 1 << ' ' << direction << endl; }
};

bool is_in_grid(int x, int y) {
  return x >= 0 and x < SIDE_LENGTH and y >= 0 and y < SIDE_LENGTH;
}

struct State {
  int bead_count = 0;
  int condition[SIDE_LENGTH]
               [SIDE_LENGTH]; // 0 means empty, 1 means full and 2 means blocked
  State(string s[SIDE_LENGTH]) {
    for (int i = 0; i < SIDE_LENGTH; i++)
      for (int j = 0; j < SIDE_LENGTH; j++)
        if (s[i][j] == 'O')
          condition[i][j] = EMPTY;
        else if (s[i][j] == 'N')
          condition[i][j] = FULL, bead_count++;
        else if (s[i][j] == 'X')
          condition[i][j] = BLOCKED;
        else
          assert(false);
  }
  int *operator[](int i) { return condition[i]; }
  vector<int> possible_moves(int x, int y) {
    vector<int> moves;
    if (condition[x][y] != FULL)
      return moves;
    for (int dir = 0; dir < 4; dir++) {
      if (is_in_grid(x + DIRDX[dir] * 2, y + DIRDY[dir] * 2) and
          condition[x + DIRDX[dir]][y + DIRDY[dir]] == FULL and
          condition[x + DIRDX[dir] * 2][y + DIRDY[dir] * 2] == EMPTY) {
        moves.push_back(dir);
      }
    }
    return moves;
  }
  bool done() {
    if (bead_count > 1)
      return false;
    if (condition[SIDE_LENGTH / 2][SIDE_LENGTH / 2] == FULL)
      return true;
    return false;
  }
};

State apply_move(State st, int x, int y, int dir) {
  st[x][y] = EMPTY;
  st[x + DIRDX[dir] * 2][y + DIRDY[dir] * 2] = FULL;
  st[x + DIRDX[dir]][y + DIRDY[dir]] = EMPTY;
  st.bead_count--;
  return st;
}

bool solve(State st, vector<Move> &moves) {
  if (st.done())
    return true;
  for (int i = 0; i < SIDE_LENGTH; i++)
    for (int j = 0; j < SIDE_LENGTH; j++)
      for (int mv : st.possible_moves(i, j)) {
        moves.push_back(Move(i, j, mv));
        if (solve(apply_move(st, i, j, mv), moves))
          return true;
        moves.pop_back();
      }
  return false;
}

int main() {
  string s[SIDE_LENGTH];
  for (int i = 0; i < SIDE_LENGTH; i++)
    cin >> s[i];
  State initial(s);
  vector<Move> moves;
  if (!solve(initial, moves))
    cout << "Loser";
  else
    for (Move m : moves)
      m.print();
  return 0;
}
