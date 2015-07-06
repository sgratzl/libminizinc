/* -*- mode: C++; c-basic-offset: 2; indent-tabs-mode: nil -*- */

/*
 *  Main authors:
 *     Guido Tack <guido.tack@monash.edu>
 */

/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef __MINIZINC_Gurobi_SOLVER_INSTANCE_HH__
#define __MINIZINC_Gurobi_SOLVER_INSTANCE_HH__

#include <minizinc/solver_instance_base.hh>
#include <gurobi_c++.h>           // add -DGUROBI_HOME=/path/to/gurobi to the 1st call of cmake

namespace MiniZinc {

  class GurobiSolver {
  public:
    typedef GRBVar Variable;
    typedef MiniZinc::Statistics Statistics;
  };
  
  class GurobiSolverInstance : public SolverInstanceImpl<GurobiSolver> {
  protected:
    GRBEnv* _grb_env;
    GRBModel* _grb_model;
    std::vector<VarDecl*> _varsWithOutput;
  public:
    GurobiSolverInstance(Env& env, const Options& options);

    virtual ~GurobiSolverInstance(void);

    virtual Status next(void);

    virtual Status solve(void);

    virtual void processFlatZinc(void);

    virtual void resetSolver(void);

    void assignSolutionToOutput(void);

		/// PARAMS
		int nThreads;
		bool fVerbose;
		std::string sExportModel;
		double nTimeout;
    double nWorkMemLimit;
		
    GRBModel* getGRBModel(void);
    GRBVar exprToVar(Expression* e);
    double* exprToArray(Expression* e);
    GRBVar* exprToVarArray(Expression* e);

  protected:
    virtual Expression* getSolutionValue(Id* id);

    void registerConstraints(void);
  };
  
}

#endif
