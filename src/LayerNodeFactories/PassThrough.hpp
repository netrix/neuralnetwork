#pragma once

#include "ILayerOperationsFactory.hpp"
#include "Nodes/LayerNodes/PassThroughLayerNode.hpp"

template<class Type>
struct PassThroughLayerNodeFactory : ILayerOperationsFactory<Type>
{
    std::unique_ptr<OperationNode<Type>> create(std::vector<NotNull<ComputationNode<Type>>> const& inputs) override
    {
        return std::make_unique<PassThroughLayerNode<Type>>(inputs);
    }
};
