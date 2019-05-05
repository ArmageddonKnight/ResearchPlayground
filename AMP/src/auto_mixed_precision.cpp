

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
        /// 
        void AddWhitelistOps(std::unordered_set < int > * white_set) const;
        void PropagateBlackFwdThroughClearAndGray(
                std::unordered_set < int > * black_set) const;
        void ForceColorMatchBetweenDataStructureOps(
                const DataStructureOpsMap & object_clients_map,
                std::unordered_set < int > * white_set,
                std::unordered_set < int > * black_set) const;
        void AddClearAndGrayToWhiteIfBetweenWhite(
                const std::unordered_set < int > & black_set,
                      std::unordered_set < int > * white_set) const;
        void PropagateWhiteThroughClear(
                const std::unordered_set < int > & black_set,
                      std::unordered_set < int > * white_set) const;
        Status ForceColorMatchOnRecurrentEdges(
                std::unordered_set < int > * white_set) const;
        void MakeCastsWhiteIfAllOutputsWhite(
                std::unordered_set < int > * white_set) const;
        Status ChangeTypeAttrsAndAddCasts(const std::unordered_set < int > & white_set);
};

} // namespace anonymous
} // namespace grappler
} // namespace tensorflow
