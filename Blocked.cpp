#include <iostream>
#include <vector>
#include <cstdlib>
#include <chrono>
#include <fstream>

using namespace std;

// vector<vector<int>> blocked(const vector<vector<int>>& A, const vector<vector<int>>& B, int blockSize) {
//   int n1 = A.size();
//   int m1 = A[0].size();
//   int n2 = B.size();
//   int m2 = B[0].size();

//   vector<vector<int>> C(n1, vector<int>(m2, 0));

//   for (int i = 0; i < n1; i += blockSize) {
//     for (int j = 0; j < m2; j += blockSize) {
//       for (int k = 0; k < m1; k += blockSize) {
//         for (int ii = i; ii < min(i + blockSize, n1); ++ii) {
//           for (int jj = j; jj < min(j + blockSize, m2); ++jj) {
//             for (int kk = k; kk < min(k + blockSize, m1); ++kk) {
//               C[ii][jj] += A[ii][kk] * B[kk][jj];
//             }
//           }
//         }
//       }
//     }
//   }

//   return C;
// }


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