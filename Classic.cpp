#include <iostream>
#include <vector>
#include <cstdlib>
#include <chrono>
#include <fstream>

using namespace std;

vector<vector<int>> classic(const vector<vector<int>>& A, const vector<vector<int>>& B) {
  int n1 = A.size();
  int m1 = A[0].size();
  int n2 = B.size();
  int m2 = B[0].size();
  
  vector<vector<int>> C(n1, vector<int>(m2, 0));
  
  for (int i = 0; i < n1; i++) {
    for (int j = 0; j < m2; j++) {
      for (int k = 0; k < m1; k++) {
        C[i][j] += A[i][k] * B[k][j];
      }
    }
  }
  
  return C;
}

vector<vector<int>> generateMatrix(int n, int m) {
  vector<vector<int>> matrix(n, vector<int>(m));
  
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      matrix[i][j] = rand() % 100;
    }
  }
  
  return matrix;
}

int main() {
  srand(time(0));

  ofstream outputFile("matrix_multiplication_times.csv");
  outputFile << "Size,Time (seconds)\n";

  for (int size = 25; size <= 1000; size += 25) {
    vector<vector<int>> A = generateMatrix(size, size);
    vector<vector<int>> B = generateMatrix(size, size);
    
    auto start = chrono::high_resolution_clock::now();
    vector<vector<int>> C = classic(A, B);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    
    cout << "Size: " << size << "x" << size << " - Time: " << duration.count() << " seconds" << endl;
    outputFile << size << "," << duration.count() << "\n";
  }

  outputFile.close();

  // Codigo Usado en las pruebas de Valgrind 

  // int size = 1000;
  // vector<vector<int>> A = generateMatrix(size, size);
  // vector<vector<int>> B = generateMatrix(size, size);

  // vector<vector<int>> C = classic(A, B);
  return 0;
}
