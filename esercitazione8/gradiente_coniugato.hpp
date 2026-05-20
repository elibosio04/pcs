#include <iostream>
#include <Eigen/Dense>
#include <Eigen/SVD>
using namespace std;

const double gradiente_coniugato(const Eigen::MatrixXd& A, const Eigen::VectorXd& b, Eigen::VectorXd& x, const Eigen::VectorXd& x_ex, const double& res_tol){
  Eigen::VectorXd res = b - A * x;
  double res_norm_0 = res.norm();
  const unsigned int it_max = 100;
  unsigned int it = 0;
  Eigen::VectorXd p=res;

  while (it < it_max &&
         res.norm() > res_tol * res_norm_0)
  {
    const double alpha_k = ((p.transpose() * res) / (p.transpose() * A * p)).value();

    x = x + alpha_k * p;
    res = b - A * x;
    const double beta_k=((p.transpose()*A*res)/(p.transpose()*A*p)).value();
    p=res-beta_k*p;
    it++;
  }

  const auto err_rel = (x_ex.norm() == 0.0) ? (x - x_ex).norm() :
                                              (x - x_ex).norm() / x_ex.norm();
  cout.precision(4);
  cout<< scientific<< "it"<< "/"<< "it_max: "<< it<< "/"<< it_max<< endl;;
  cout<< scientific<< "res"<< "/"<< "res_tol: "<< res.norm() / res_norm_0<< "/"<< res_tol<< endl;
  cout<< scientific<< "errore relativo soluzione: "<< err_rel << endl;
  cout<< scientific<< "soluzione: \n"<< x << endl;

  return err_rel;
}