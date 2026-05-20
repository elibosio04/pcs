#include <iostream>
#include "gradiente_coniugato.hpp"
#include <Eigen/Dense>
#include <Eigen/SVD>
#include <cmath>
#include <cstdlib>
using namespace std;
double condA(const Eigen::MatrixXd& A){
  Eigen::JacobiSVD<Eigen::MatrixXd> svd(A);
  Eigen::VectorXd singularValuesA = svd.singularValues();
  return singularValuesA.maxCoeff() / singularValuesA.minCoeff();
}
int main(void){
const double tol = 1.0e-15;
  unsigned int n = 3;

  Eigen::MatrixXd B = Eigen::MatrixXd::Random(n, n);

  if (abs(B.determinant()) < tol) // verifico che la matrice generata non sia singolare
    return -1;

  Eigen::MatrixXd A = B.transpose() * B;
  Eigen::VectorXd x_ex = Eigen::VectorXd::Ones(n);
  Eigen::VectorXd b = A * x_ex;
  Eigen::VectorXd x = Eigen::VectorXd::Zero(n);
  //stampo i parametri del sistema:
  cout.precision(2);
  cout << "Dimensione del sistema: "<< n << "\n";
  cout<< scientific<< "Condizionamento della matrice: "<< condA(A)<< endl;
  const double err_rel_soluzione=gradiente_coniugato(A,b,x,x_ex,1.0e-12);
  //testiamo l'esito
  if (err_rel_soluzione < 1.0e-10) {
        cout << "\nTEST SUPERATO: il sistema converge \n";
        return EXIT_SUCCESS;
    } else {
        cout << "\nTEST NON SUPERATO: errore troppo grande  \n";
        return EXIT_FAILURE;
    }
  return 0;
}
