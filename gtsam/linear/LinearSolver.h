/* ----------------------------------------------------------------------------

 * GTSAM Copyright 2010, Georgia Tech Research Corporation,
 * Atlanta, Georgia 30332-0415
 * All Rights Reserved
 * Authors: Frank Dellaert, et al. (see THANKS for the full author list)

 * See LICENSE for the license information

 * -------------------------------------------------------------------------- */

/**
 * @file    LinearSolver.h
 * @brief   Common Interface for Linear Solvers
 * @author  Fan Jiang
 */

#pragma once

#include <gtsam/linear/LinearSolverParams.h>
#include <gtsam/linear/VectorValues.h>

namespace gtsam {

/** Common Interface Class for all linear solvers */
class GTSAM_EXPORT LinearSolver {
 public:
  LinearSolver(LinearSolver &) = delete;

  // TODO: Remove this and use trait functions instead?
  LinearSolverParams::LinearSolverType linearSolverType =
      LinearSolverParams::MULTIFRONTAL_CHOLESKY;  ///< The type of this instance

  virtual bool isIterative() { return false; };

  virtual bool isSequential() { return false; };

  /**
   * Solve a Gaussian Factor Graph with the solver
   * @param gfg the GFG to be optimized
   * @return the optimization result in VectorValues
   */
  virtual VectorValues solve(const GaussianFactorGraph &gfg) {
    throw std::runtime_error("BUG_CHECK: Calling solve of the base class!");
  };

  /**
   * Alias for `solve`
   * @param gfg the GFG to be optimized
   * @return the optimization result in VectorValues
   */
  VectorValues operator()(const GaussianFactorGraph &gfg) { return solve(gfg); }

  /**
   * Factor method for generating a LinearSolver from LinearSolverParams
   * @param params LinearSolverParams linear optimizer parameters
   * @return pointer to a LinearSolver object
   */
  static boost::shared_ptr<LinearSolver> FromLinearSolverParams(
      const LinearSolverParams &params);

 protected:
  LinearSolver();

  virtual ~LinearSolver() = default;
};

}  // namespace gtsam