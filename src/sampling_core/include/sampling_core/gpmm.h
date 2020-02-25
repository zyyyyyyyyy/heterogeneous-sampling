/**
 * Gaussian Process Mixture Model
 * AUTHOR: Yang Zhang
 */

#pragma once

#include <stdlib.h>
#include <Eigen/Dense>
#include <cstdlib>
#include <string>
#include <vector>

#include "gp.h"
#include "gp_utils.h"
#include "sampling_core/gmm.h"

namespace sampling {
namespace GPMM {

const int KGaussianProcessNumber = 3;
const double KGPCov1 = 0.5;
const double KGPCov2 = 0.5;
const double KGPNoise = 0.1;
const int KGPParamNumber = 3;

class GaussianProcessMixtureModel {
 private:
  // Helper function for single GP prediction
  // Apply predictions to the [GP_index] column of the output
  void GPPredict(const int& GP_index, const Eigen::MatrixXd& locations,
                 Eigen::MatrixXd& pred_mean, Eigen::MatrixXd& pred_var);

  // Helper function for get the prediction probabilities from a single GP
  Eigen::VectorXd GMMPredictForGP(const int& GP_index,
                                  const Eigen::VectorXd& gp_predictions);

 public:
  GaussianProcessMixtureModel();

  GaussianProcessMixtureModel(
      const int& gp_number,
      const std::vector<std::vector<double>> gp_hyperparams,
      const int& gp_max_iteration, const double& gp_eps);

  void Train(const Eigen::VectorXd& sample_utilities,
             const Eigen::MatrixXd& sample_positions);

  void Predict(const Eigen::MatrixXd& test_positions,
               Eigen::VectorXd& pred_mean, Eigen::VectorXd& pred_var);

 private:
  int gp_number_;
  std::unique_ptr<GMM_CV::GaussianMixtureModel> gmm_model_;
  std::vector<std::unique_ptr<libgp::GaussianProcess>> gp_model_;
};
}  // namespace GPMM
}  // namespace sampling