/**
 * Author: Niko Hastrich
 * Source: https://web.stanford.edu/~ashishg/msande111/notes/chapter4.pdf
 * License: MIT
 * Description: 
 *
 * \begin{align*}
 * 	\text{Primal:} \max v=&b^Tx &\text{Dual:} \min u=c^Ty\\
 * 	s.t.\quad x\gtreqless& 0& s.t.\quad y\gtreqless&0\\
 * 	Ax \gtreqless& c&A^Ty\gtreqless&b\\
 * \end{align*}
 *
 * The dual of a linear program has the same optimum. If one of the programs is unbound the other is infeasible.
 * Each primal constraint becomes a dual variable, each primal variable becomes a dual constraint.
 * Relations might flip. Only take dual of maximization problem (which can be obtained from
 * minimization by maximizing $-b^Tx$). This can sometimes be useful to transform a problem to a flow problem.
 *
 * \begin{tabular}{|c|c||c|c|}
 * \hline
 * PRIMAL& maximize & minimize & DUAL\\\hline
 *  & $\leq b_i$ & $\geq 0$ &\\
 * constraint & $\geq b_i$ & $\leq 0$ & variable\\
 * & $=b_i$& unconstraint&\\
 * & $\geq 0$& $\geq c_j$&\\
 * variable& $\leq 0$& $\leq c_j$&constraint\\
 * &$unconstraint$& $=c_j$&\\\hline
 * \end{tabular}
 *~\\
 */

