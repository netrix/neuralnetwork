#pragma once

#include "NotNull.hpp"
#include "NodeBuilders/NodeBuilder.hpp"
#include "NodeBuilders/BinaryNodeBuilder.hpp"
#include "NodeBuilders/UnaryNodeBuilder.hpp"
#include "NodeBuilders/ConstSingleValueNodeBuilder.hpp"
#include "NodeBuilders/ConstBufferNodeBuilder.hpp"
#include "NodeBuilders/MultipleInputNodeBuilder.hpp"
#include "NodeBuilders/MultipleInputLayerNodeBuilder.hpp"
#include "NodeBuilders/ConnectedLayerNodeBuilder.hpp"
#include "NodeBuilders/VariableSingleValueNodeBuilder.hpp"
#include "NodeBuilders/VariableBufferNodeBuilder.hpp"       // TODO forward declare them and move it to cpp
#include "NodeBuilders/PassThroughLayerNodeBuilder.hpp"
#include <string>
#include <vector>
#include <memory>


struct BuilderStorage
{
    NotNull<MultipleInputNodeBuilder> createMultipleInputNodeBuilder(std::unique_ptr<IMultipleInputOperationNodesFactory<BNN_TYPE>>);
    NotNull<UnaryNodeBuilder> createUnaryNodeBuilder(std::unique_ptr<IUnaryOperationNodesFactory<BNN_TYPE>>);
    NotNull<BinaryNodeBuilder> createBinaryNodeBuilder(std::unique_ptr<IBinaryOperationNodesFactory<BNN_TYPE>> factory);
    NotNull<MultipleInputLayerNodeBuilder> createMultipleInputLayerNodeBuilder(std::unique_ptr<IMultipleInputLayerOperationsFactory<BNN_TYPE>> factory);
    NotNull<ConnectedLayerNodeBuilder> createConnectedLayerNodeBuilder(ConnectedLayerNodeSpecs);
    NotNull<PassThroughLayerNodeBuilder> createPassThroughLayerNodeBuilder(PassThroughLayerNodeSpecs);
    NotNull<ConstSingleValueNodeBuilder> createConstSingleValueNodeBuilder();
    NotNull<VariableSingleValueNodeBuilder> createVariableSingleValueNodeBuilder();
    NotNull<VariableBufferNodeBuilder> createVariableBufferNodeBuilder(std::size_t numVariables);
    NotNull<ConstBufferNodeBuilder> createConstBufferNodeBuilder(std::size_t numConsts);

    std::size_t getNumConsts() const
    {
        return m_numConsts;
    }

    std::size_t getNumVariables() const
    {
        return m_numVariables;
    }

    auto const& getConstBuilders() const
    {
        return consts;
    }

    auto const& getVariableBuilders() const
    {
        return variables;
    }

private:
    std::size_t m_numConsts{};
    std::size_t m_numVariables{};
    std::vector<std::unique_ptr<ConstNodeBuilder>> consts;
    std::vector<std::unique_ptr<VariableNodeBuilder>> variables;
    std::vector<std::unique_ptr<OperationNodeBuilder>> operations; // should have generic operations later
};
