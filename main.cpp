#include <iostream>
#include <utility>
#include <vector>

using namespace std;

void printTable(const vector<vector<int>> &table) {
  for (size_t i = 0; i < table.size(); i++) {
    cout << "|";
    for (size_t j = 0; j < table[i].size(); j++) {
      cout << " " << (table[i][j] >= 0 ? " " : "") << table[i][j] << " |";
    }
    cout << endl;
  }
}

void printVector(vector<int> vect) {
  cout << "|";
  for (size_t i = 0; i < vect.size(); i++) {
    cout << " " << vect[i] << " |";
  }
  cout << endl;
}

pair<int, int> getPair(const vector<vector<int>> &table) {
  pair<int, int> ret;
  ret.first = 100000;
  ret.second = -100000;
  for (int i = 0; i < table.size(); i++) {
    for (int j = i; j < table[i].size(); j++) {
      if (table[i][j] == 1 && j - i > ret.second - ret.first) {
        ret.first = i;
        ret.second = j;
      }
    }
  }
  return ret;
}

int checkMaxOneMultiply(const vector<int> &elementVector,
                        vector<vector<int>> &table, int start, int end) {
  cout << "starting [" << start << ".." << end << "]" << endl;
  int ret1 = 0;
  int ret2 = 0;
  if (start == end) {
    cout << "diagonal[" << start << "]: " << elementVector[start] << endl;
    return elementVector[start];
  }
  if (start < end) {
    table[start + 1][end] =
        table[start + 1][end] == 0
            ? checkMaxOneMultiply(elementVector, table, start + 1, end)
            : table[start + 1][end];
    ret1 = elementVector[start] * table[start + 1][end];
  }
  if (end > start) {
    table[start][end - 1] =
        table[start][end - 1] == 0
            ? checkMaxOneMultiply(elementVector, table, start, end - 1)
            : table[start][end - 1];
    ret2 = table[start][end - 1] * elementVector[end];
  }
  cout << "ret1: " << ret1 << endl;
  cout << "ret2: " << ret2 << endl;
  printTable(table);
  return ret1 != 0 ? ret1 : ret2;
}

pair<int, int> checkMaxOneMultiply(const vector<int> &elementVector,
                                   vector<vector<int>> &table) {
  int first = 0, end = elementVector.size() - 1;
  table[first][end] = checkMaxOneMultiply(elementVector, table, first, end);
  printTable(table);
  pair<int, int> ret = getPair(table);

  return ret;
}

vector<int> readVector(int size) {
  vector<int> elementVector(size);
  for (int i = 0; i < size; i++) {
    cin >> elementVector[i];
  }
  return elementVector;
}

int main() {

  int qtd = 0;
  cin >> qtd;
  for (int i = 0; i < qtd; i++) {
    int size = 0;
    cin >> size;
    vector<int> elementVector = readVector(size);
    vector<vector<int>> table(size, vector<int>(size, 0));
    cout << "pass read elements" << endl;
    printTable(table);
    printVector(elementVector);
    pair<int, int> ret = checkMaxOneMultiply(elementVector, table);
    cout << "Max element vector [" << ret.first << ".." << ret.second << "]"
         << endl;
  }
}
