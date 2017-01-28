#pragma once

#include "OperationNodeBuilder.hpp"
#include "BuilderToNodeMaps.hpp"
#include "NodeBuilders/MultipleInputLayerNodeBuilder.hpp"
#include "ILayerOperationsFactory.hpp"
#include "NodeTags.hpp"
#include <string>

struct BuilderStorage;
struct BinaryNodeBuilder;
struct VariableBufferNodeBuilder;

struct LayerNodeBuilder : OperationNodeBuilder
{
    LayerNodeBuilder(BuilderStorage& builderStorage,
                     std::unique_ptr<ILayerOperationsFactory<BNN_TYPE>> factory);

    NotNull<MultipleInputLayerNodeBuilder> setInput(MultipleInputLayerNodeTag, std::unique_ptr<IMultipleInputLayerOperationsFactory<BNN_TYPE>> factory); // TODO can be done by template with traits MultipleInputTag -> MultipleInputNodeBuilder
    NotNull<LayerNodeBuilder> setInput(LayerNodeTag, std::unique_ptr<ILayerOperationsFactory<BNN_TYPE>> factory);

    ArrayView<OperationNodeBuilder*> getOperations();

    std::unique_ptr<OperationNode<BNN_TYPE>> build(BuilderToNodeMaps<BNN_TYPE> const& builderToNodeMaps);

private:
    VariableBufferNodeBuilder* allocateVariableNodeBuilder(std::size_t numInputs);

private:
    BuilderStorage& m_builderStorage;
    std::unique_ptr<ILayerOperationsFactory<BNN_TYPE>> m_factory;

    VariableBufferNodeBuilder* m_variablesNodeBuilder;
    OperationNodeBuilder* m_inputOperationBuilder{};
    NodeBuilder* m_inputBuilder{};
};