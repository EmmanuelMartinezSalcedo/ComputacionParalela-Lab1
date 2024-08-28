#include <iostream>
#include <thread>
using namespace std;

const int MAX = 10000;
double A[MAX][MAX], X[MAX], Y1[MAX], Y2[MAX];

void first() {
  for (int i = 0; i < MAX; i++) {
    for (int j = 0; j < MAX; j++) {
      Y1[i] += A[i][j] * X[j];
    }
  }
  cout << "First" << endl;
}

void second() {
  for (int j = 0; j < MAX; j++) {
    for (int i = 0; i < MAX; i++) {
      Y2[i] += A[i][j] * X[j];
    }
  }
  cout << "Second" << endl;
}

int main() {
  thread t1(first);
  thread t2(second);

  t1.join();
  t2.join();
}