/**
 * 
 * 
 * 
 *   \todo Given that matrix multiplies are also doing reduction, 
 *           why are we allowed to put them into white-list?
 *         Especially given that summation is put into the black-list.
 *   \todo What is the point of forcing the Batch-Normalization to be **V2**?
 */

#include <string>
#include <unordered_set>
#include <unordered_map>

namespace tensorflow {
namespace grappler {

struct Cluster;

struct NodeDef;
struct NodeTypeId;

struct GraphDef;
struct TypeAttrId;
struct Status;

namespace {

class AutoMixedPrecisionImpl
{
private:
public:
        /// Construct an implementation that does automatic mixed-precision training.
        /// \param cluster A collection of hardware resources available 
        ///                  to run the TensorFlow model.
        /// \param nodes_to_preserve Set of Nodes to **Preserve**
        /// \param graph Graph to be Optimized, Member of `GrapplerItem`
        AutoMixedPrecisionImpl(Cluster * cluster, 
                const std::unordered_set < std::string > & 
                        nodes_to_preserve,
                GraphDef * graph, std::string id);

        /// Top-Level Optimization Interface
        Status Optimize();

private:
        Status PrintDebugLogs(bool preop, size_t timestamp);

        /// \brief Log the skipped node
        void LogSkippedNode     (const NodeDef & node) const;
        
        bool MustPreserve       (const NodeDef & node) const;
        bool IsOnGPU            (const NodeDef & node) const;
        bool IsOnSuitableGPUArch(const NodeDef & node) const;
        bool ShouldProcess      (const NodeDef & node) const;
        bool IsIdentityAfterVariable(const NodeDef & node) const;
        /// \brief Convert all batch-normalization ops to `V2`.
        void ConvertBatchNormOpsToV2();
        // =====================================================================
        /// \name FP16-Support Check
        /// @{
        // =====================================================================
        /// \brief Helper Function, invoked by `SupportsFloat16`
        bool NodeHasFP16KernelForTypeAttr(const NodeDef & node, 
                TypeAttrId taid) const;
        bool SupportsFloat16(const NodeTypeId & node_type) const;
        /// @}
        const NodeDef * GetTailOfChain(const NodeDef & node, 
                const std::string & op) const;

        typedef std::unordered_map <
                        std::unordered_set < NodeTypeId >,
                        std::unordered_set < NodeTypeId >
                > DataStructureOpsMap;
        Status AddDataStructureOpsToMap(
                const std::string & data_structure_op, 
                TypeAttrId data_structure_type_attr,
                const std::unordered_map < std::string, TypeAttrId > & write_ops,
                const std::unordered_map < std::string, TypeAttrId > &  read_ops,
                DataStructureOpsMap * object_clients_map) const;
        /// \brief Make sure that colors are consistent between data structure ops.
        ///        This method is invoked after every color propagation.
        void ForceColorMatchBetweenDataStructureOps(
                const DataStructureOpsMap & object_clients_map,
                std::unordered_set < int > * white_set,
                std::unordered_set < int > * black_set) const;
        // =====================================================================
        /// \name Pass \#1. Add the white-list ops.
        /// @{
        // =====================================================================
        /// \brief Initialize the set of **white** nodes.
        void AddWhitelistOps(std::unordered_set < int > * white_set) const;
        /// @}
        // =====================================================================
        /// \name Pass \#2. Propagate **black** nodes through **clear** and **grey** nodes.
        /// @{
        // =====================================================================
        void PropagateBlackFwdThroughClearAndGray(
                      std::unordered_set < int > * black_set) const;
        /// @}
        // =====================================================================
        /// \name Pass \#3. Set **clear** and **grey** nodes to white 
        ///                   if they are between **white** nodes.
        /// @{
        // =====================================================================
        void AddClearAndGrayToWhiteIfBetweenWhite(
                const std::unordered_set < int > & black_set,
                      std::unordered_set < int > * white_set) const;
        /// @}
        // =====================================================================
        /// \name Pass \#4. Propagate **whites** nodes through **clear** nodes.
        /// @{
        // =====================================================================
        void PropagateWhiteThroughClear(
                const std::unordered_set < int > & black_set,
                      std::unordered_set < int > * white_set) const;
        // =====================================================================
        Status ForceColorMatchOnRecurrentEdges(
                std::unordered_set < int > * white_set) const;
        void MakeCastsWhiteIfAllOutputsWhite(
                std::unordered_set < int > * white_set) const;
        Status ChangeTypeAttrsAndAddCasts(const std::unordered_set < int > & white_set);
};

} // namespace anonymous
} // namespace grappler
} // namespace tensorflow
