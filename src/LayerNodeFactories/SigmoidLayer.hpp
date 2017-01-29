#pragma once

#include "ILayerOperationsFactory.hpp"
#include "Nodes/LayerNodes/SigmoidLayer.hpp"

template<class Type>
struct SigmoidLayerNodeFactory : ILayerOperationsFactory<Type>
{
    SigmoidLayerNodeFactory(std::size_t numOutputs, std::size_t beta=1.0)
        : m_numOutputs(numOutputs)
        , m_beta(beta)
    {}

    std::unique_ptr<OperationNode<Type>> create(NotNull<ComputationNode<Type>> input,
                                                NotNull<VariableNode<Type>>) override
    {
        return std::make_unique<SigmoidLayerNode<Type>>(input, m_beta);
    }

    std::size_t getNumOutputs() const override
    {
        return m_numOutputs;
    }

    std::size_t getNumVariables(std::size_t numInputs) const  override
    {
        return 0;
    }

private:
    std::size_t m_numOutputs;
    std::size_t m_beta;
};
