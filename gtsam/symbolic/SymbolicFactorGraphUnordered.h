/* ----------------------------------------------------------------------------

 * GTSAM Copyright 2010, Georgia Tech Research Corporation, 
 * Atlanta, Georgia 30332-0415
 * All Rights Reserved
 * Authors: Frank Dellaert, et al. (see THANKS for the full author list)

 * See LICENSE for the license information

 * -------------------------------------------------------------------------- */

/**
 * @file SymbolicFactorGraph.h
 * @date Oct 29, 2009
 * @author Frank Dellaert
 * @author Richard Roberts
 */

#pragma once

#include <gtsam/symbolic/SymbolicFactorUnordered.h>
#include <gtsam/inference/FactorGraphUnordered.h>
#include <gtsam/inference/EliminateableFactorGraph.h>
#include <gtsam/base/types.h>

namespace gtsam {

  class SymbolicFactorGraphUnordered;
  class SymbolicConditionalUnordered;
  class SymbolicBayesNetUnordered;
  class SymbolicEliminationTreeUnordered;
  class SymbolicBayesTreeUnordered;
  class SymbolicJunctionTreeUnordered;

  /* ************************************************************************* */
  template<> struct EliminationTraits<SymbolicFactorGraphUnordered>
  {
    typedef SymbolicFactorUnordered FactorType;                   ///< Type of factors in factor graph
    typedef SymbolicFactorGraphUnordered FactorGraphType;         ///< Type of the factor graph (e.g. GaussianFactorGraph)
    typedef SymbolicConditionalUnordered ConditionalType;         ///< Type of conditionals from elimination
    typedef SymbolicBayesNetUnordered BayesNetType;               ///< Type of Bayes net from sequential elimination
    typedef SymbolicEliminationTreeUnordered EliminationTreeType; ///< Type of elimination tree
    typedef SymbolicBayesTreeUnordered BayesTreeType;             ///< Type of Bayes tree
    typedef SymbolicJunctionTreeUnordered JunctionTreeType;       ///< Type of Junction tree
    /// The default dense elimination function
    static std::pair<boost::shared_ptr<ConditionalType>, boost::shared_ptr<FactorType> >
      DefaultEliminate(const FactorGraphType& factors, const OrderingUnordered& keys) {
        return EliminateSymbolicUnordered(factors, keys); }
  };

  /* ************************************************************************* */
  /** Symbolic Factor Graph
   *  \nosubgrouping
   */
  class GTSAM_EXPORT SymbolicFactorGraphUnordered :
    public FactorGraphUnordered<SymbolicFactorUnordered>,
    public EliminateableFactorGraph<SymbolicFactorGraphUnordered>
  {
  public:

    typedef SymbolicFactorGraphUnordered This; ///< Typedef to this class
    typedef FactorGraphUnordered<SymbolicFactorUnordered> Base; ///< Typedef to base factor graph type
    typedef EliminateableFactorGraph<This> BaseEliminateable; ///< Typedef to base elimination class
    typedef boost::shared_ptr<This> shared_ptr; ///< shared_ptr to this class

    /// @name Standard Constructors
    /// @{

    /** Construct empty factor graph */
    SymbolicFactorGraphUnordered() {}

    /** Constructor from a BayesTree */
    SymbolicFactorGraphUnordered(const SymbolicBayesTreeUnordered& bayesTree) {
      push_back_bayesTree(bayesTree); }

    /** Construct from iterator over factors */
    template<typename ITERATOR>
    SymbolicFactorGraphUnordered(ITERATOR firstFactor, ITERATOR lastFactor) : Base(firstFactor, lastFactor) {}

    /** Construct from container of factors (shared_ptr or plain objects) */
    template<class CONTAINER>
    SymbolicFactorGraphUnordered(const CONTAINER& factors) : Base(factors) {}

    /** Implicit copy/downcast constructor to override explicit template container constructor */
    template<class DERIVEDFACTOR>
    SymbolicFactorGraphUnordered(const FactorGraphUnordered<DERIVEDFACTOR>& graph) : Base(graph) {}

    /// @}
    
    /// @name Testable
    /// @{
    
    bool equals(const This& fg, double tol = 1e-9) const;

    /// @}

    /// @name Standard Interface
    /// @{

    /** Push back unary factor */
    void push_factor(Key key);

    /** Push back binary factor */
    void push_factor(Key key1, Key key2);

    /** Push back ternary factor */
    void push_factor(Key key1, Key key2, Key key3);

    /** Push back 4-way factor */
    void push_factor(Key key1, Key key2, Key key3, Key key4);

    /** push back a BayesTree as a collection of factors. */
    void push_back_bayesTree(const SymbolicBayesTreeUnordered& bayesTree);

    /// @}
  };

} // namespace gtsam
