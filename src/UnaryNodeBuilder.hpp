#pragma once

#include "NodeBuilder.hpp"
#include "ArrayView.hpp"
#include "NotNull.hpp"
#include "NodeTags.hpp"
#include <array>
#include <cassert>
#include <string>
#include "BinaryOperationNode.hpp"
#include "BuilderToNodeMaps.hpp"

struct BuilderStorage;
struct BinaryNodeBuilder;

struct UnaryNodeBuilder : OperationNodeBuilder
{
    UnaryNodeBuilder(BuilderStorage& builderStorage, std::string const& operation);

    NotNull<BinaryNodeBuilder> setInput(BinaryNodeTag, std::string const& operation);
    NotNull<UnaryNodeBuilder> setInput(UnaryNodeTag, std::string const& operation);
    NotNull<VariableNodeBuilder> setInput(VariableTag);
    NotNull<ConstNodeBuilder> setInput(ConstTag);

    void setInput(NotNull<ConstNodeBuilder>);

    ArrayView<OperationNodeBuilder*> getOperations();

    std::unique_ptr<OperationNode<BNN_TYPE>> build(BuilderToNodeMaps<BNN_TYPE> const& builderToNodeMaps);

private:
    NotNull<ComputationNode<BNN_TYPE>> getComputationNodeFromMaps(BuilderToNodeMaps<BNN_TYPE> const&, NotNull<NodeBuilder>) const;

    BuilderStorage& m_builderStorage;
    std::string m_operation;

    OperationNodeBuilder* m_operationBuilder{};
    NodeBuilder* m_inputBuilder{};
};
