#include <iostream>
#include <vector>
#include <math.h>


using namespace std;
void printV(vector<vector <double>> const &a);
vector <vector <int>> getValues (vector <vector <int>> &a, int n);
vector <double> getSolutions(int n);
int d_determinant(vector <vector <int>> &a, int n);
vector <vector <int>> getCofactors(vector <vector <int>> &a, int n);
vector <vector <int>> transpose(vector <vector <int>> &a, int n);
vector <double> multiplyMatrix (vector <vector <int>> &a, vector <double> &b, int n, int determinant);
void printvector(vector <double> const &a);

int main() {

//    Define all variables
    int n;
    int determinant;
    vector<vector<int>> matrice;
    vector <vector <int>> cofactors;
    vector <vector <int>> transposed;
    vector <vector <double>> inverseMatrix;
    vector <double> solutions;
    vector <double> solutionMatrix;

    //Enter size of linear system:;
    cout << "Enter size of linear system: " << endl;
    cin >> n;
    matrice.resize(n, std::vector<int>(n, 0)); //resize the vector to n rows and n columns

    //  Get values for matrix
    matrice = getValues(matrice, n);

    // Get solutions for matrix
    solutions = getSolutions(n);

    //  Get determinant of matrix
    determinant = d_determinant(matrice, n);

    //  Get cofactors for linear system
    cofactors = getCofactors(matrice, n);

    transposed = transpose(cofactors, n);

//    inverseMatrix = calcInverse(transposed, determinant, n);

    solutionMatrix = multiplyMatrix(transposed, solutions, n, determinant);
    printvector(solutionMatrix);

    return 0;
}

int d_determinant(vector <vector <int>> &a, int n){
    vector <vector <int>> temp;
    temp.resize(n, std::vector<int>(n, 0));
    int det = 0;
    if (n > 2){
        for(int r = 0; r < n; r++){
            int row = 0;
            for(int c = 1; c < n; c++){
                int column =0;
                for(int x = 0; x < n; x++){
                    if (x == r)
                        continue;
                    temp[row][column] = a[c][x];
                    column++;
                }
                row++;
            }
            det = det + (pow(-1, r) * a[0][r] * d_determinant(temp, n - 1));
        }
        return det;
    }
    else{
        return (a[0][0] * a[1][1] - a[0][1] * a[1][0]);
    }
}

vector <vector <int>> getValues(vector <vector <int>> &a, int n){
    cout << "Enter values for  (not soluton):" << endl;
    for(int r = 0; r < n ; r++){
        for(int c = 0; c < n; c++){
            cin >> a[r][c];
        }
    }
    return a;
}

void printV(vector <vector <double>> const &a) {
    for ( int r = 0; r < a.size(); r++) {
        for (int c = 0; c < a[r].size(); c++) {
            cout << a[r][c] << " ";
        }
        cout << endl;
    }
}

vector <vector <int>> getCofactors(vector <vector <int>> &a, int n){
    vector <vector <int>> temp;
    vector <vector <int>> cofactors;
    cofactors.resize(n,vector<int>(n, 0));
    temp.resize(n,vector<int>(n, 0));
    temp = a;
    int neg;
    for(int r = 0; r < n; r++){
        for(int c = 0; c < n; c++){
            temp.erase(temp.begin() + r);
            for (vector<int> &row : temp)
            {
                row.erase(row.begin() + c);
            }
            if((c+ 1 + r) % 2 == 0){
                neg = -1;
            }
            else{
                neg = 1;
            }
            cofactors[r][c] = neg * d_determinant(temp, n - 1);
            temp = a;
        }
    }
    return cofactors;
}

vector <vector <int>> transpose(vector <vector <int>> &a, int n){
    vector <vector <int>> transpose;
    transpose.resize(n,vector<int>(n, 0));
    for(int r = 0; r < n; r++){
        for(int c = 0; c < n; c++){
            transpose[r][c] = a[c][r];
        }
    }
    return transpose;
}

vector <double> getSolutions(int n){
    vector <double> solutions(n);
    cout << "Input the solutions for the linear system:" << endl;
    for(int i = 0; i < n; i++){
        cin >> solutions[i];
    }
    return solutions;
}

vector <double> multiplyMatrix (vector <vector <int>> &a, vector <double> &b, int n, int determinant){
    vector <double> matrix;
//    matrix.resize(n,vector<double>(n, 0));

    double temp_total;
    for(int r = 0; r < n; r++){
        for(int c = 0; c < n; c++){
            temp_total += a[r][c] * b[c];
        }
        matrix.push_back(temp_total / determinant);
        temp_total = 0;
    }
    return matrix;
}

void printvector(vector <double> const &a) {

    cout << "The solution to the linear system is: " << endl;
    for(int i=0; i < a.size(); i++)
        cout << a.at(i) << ' ';
}