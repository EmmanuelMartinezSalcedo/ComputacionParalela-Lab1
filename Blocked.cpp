#include <iostream>
#include <vector>
#include <cstdlib>
#include <chrono>
#include <fstream>

using namespace std;

vector<vector<int>> blocked(vector<vector<int>> A, vector<vector<int>> B, int blockSize) {
  int size = A.size();
  vector<vector<int>> C(size, vector<int>(size, 0));

  for (int jj = 0; jj < size; jj += blockSize) {
    for (int kk = 0; kk < size; kk += blockSize) {
      for (int i = 0; i < size; i++) {
        for (int j = jj; j < min(jj + blockSize, size); j++) {
          int tmp = 0.0f;
          for (int k = kk; k < min(kk + blockSize, size); k++) {
            tmp += A[i][k] * B[k][j];
          }
          C[i][j] += tmp;
        }
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

  ofstream outputFile("matrix_multiplication_times_b.csv");
  outputFile << "Size,Time (seconds)\n";

  for (int size = 100; size <= 1000; size += 25) {
    vector<vector<int>> A = generateMatrix(size, size);
    vector<vector<int>> B = generateMatrix(size, size);
    
    auto start = chrono::high_resolution_clock::now();
    vector<vector<int>> C = blocked(A, B, 75);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    
    cout << "Size: " << size << "x" << size << " - Time: " << duration.count() << " seconds" << endl;
    outputFile << size << "," << duration.count() << "\n";
  }

  outputFile.close();

  // Codigo Usado en las pruebas de Valgrind 
  
  // int size = 100;
  // vector<vector<int>> A = generateMatrix(size, size);
  // vector<vector<int>> B = generateMatrix(size, size);

  // vector<vector<int>> C = blocked(A, B, 75);
  return 0;
}