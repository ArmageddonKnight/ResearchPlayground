#include <vector>
#include <memory>

namespace nnvm {

class Op;
class Node;
class NodeEntry;
class Graph;

/// @brief   Default Gradient Aggregate Function
/// @param v List of Gradients to be Aggregated
/// @return  Aggregated Gradient
NodeEntry DefaultAggregateGradient(std::vector < NodeEntry > && v);
/// @brief          Check whether all gradients are zero or not.
/// @param grads    List of Gradient to be Aggregated
/// @param zero_ops List of Zero Ops
/// @return         True if all the Gradients are Zero, False Otherwise
bool CheckGradAllZero(const std::vector  < NodeEntry > & grads,
                      const std::vector < const Op * > & zero_ops);

Graph Gradient(Graph src)
{

}

}  // namespace nnvm
