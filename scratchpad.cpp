#include <iostream>
#include <vector>
#include <functional>

enum class Direction { kForward, kBackward };

template <typename TDomainElem, typename TDomainElemRepr, typename TMeetOp,
          typename TFrameworkSubclass>
class FrameworkDirAgnosticBase {
protected:
  FrameworkDirAgnosticBase() = default;
};

/**
 * @brief  Dataflow Analysis Framework
 *
 * @tparam TDomainElem      Domain Element
 * @tparam TDomainElemRepr  Domain Element Representation
 * @tparam TDirection       Direction of Analysis
 * @tparam TMeetOp          Meet Operator
 */
template <typename TDomainElem, typename TDomainElemRepr, Direction TDirection,
          typename TMeetOp>
class Framework {};

template <typename TDomainElem, typename TDomainElemRepr,
          typename TMeetOp>
class Framework<TDomainElem, TDomainElemRepr, Direction::kForward, TMeetOp> :
    public FrameworkDirAgnosticBase<TDomainElem, TDomainElemRepr, TMeetOp,
                                    Framework<TDomainElem, TDomainElemRepr, Direction::kForward, TMeetOp>> {

};

int main()
{
        Framework<int, bool, Direction::kForward, int> A;

        return 0;
}
