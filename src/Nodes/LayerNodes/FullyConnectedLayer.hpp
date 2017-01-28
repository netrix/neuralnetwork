#pragma once
#include "LayerNode.hpp"
#include "Nodes/VariableNode.hpp"
#include "NotNull.hpp"
#include <algorithm>

template<class Type>
struct FullyConnectedLayerNode : LayerNode<Type>
{
    FullyConnectedLayerNode(NotNull<ComputationNode<Type>> inputLayer,
                            NotNull<VariableNode<Type>> variables,
                            std::size_t numOutputs)
        : m_inputLayer(inputLayer)
        , m_weights(variables)
        , m_errorsForInput(inputLayer.getNumOutputs())
        , m_errorsForWeights(variables.getNumOutputs())
        , m_outputs(numOutputs)
    {
    }

    void forwardPass() override
    {
        for(auto i = 0u; i < m_outputs.size(); ++i)
        {
            m_outputs[i]  = calculateSingleOutput(m_inputLayer->getOutputValues(), getNthLayerWeights(i));
        }
    }

    std::size_t getNumOutputs() const override
    {
        return m_outputs.size();
    }

    ArrayView<Type const> getOutputValues() const override
    {
        return m_outputs;
    }

    void backPropagate(ArrayView<Type const> errors) override
    {
        resetErrorsForInput();
        for(std::size_t i = 0; i < errors.size(); ++i)
        {
            backPropagateSingleError(errors[0], getNthLayerWeights(i), getNthLayerWeightsErrors(i));
        }
        m_inputLayer->backPropagate(m_errorsForInput);
        m_weights->backPropagate(m_errorsForWeights);  // maybe there is a way to update some variables from VariableNode selectively?
    }

private:
    void resetErrorsForInput()
    {
        std::fill(std::begin(m_errorsForInput), std::end(m_errorsForInput), Type{});
        std::fill(std::begin(m_errorsForWeights), std::end(m_errorsForWeights), Type{});
    }

    void backPropagateSingleError(Type error, ArrayView<Type> weights, ArrayView<Type> deltas)
    {
        auto inputs = m_inputLayer->getOutputValues();
        m_errorsForWeights[0] += error;
        for(auto i = 0u; i < m_inputLayer.size(); ++i)
        {
            m_errorsForInput[i] += error * weights[i];
            m_errorsForWeights[i + 1] += error * inputs[i];
        }
    }

    Type calculateSingleOutput(ArrayView<Type const> input, ArrayView<Type const> weights) const
    {
        Type output = weights[0];
        for(auto i = 0; i < input.size(); ++i)
        {
            output += input[i] * weights[i + 1];
        }
        return output;
    }

    ArrayView<Type> getNthLayerWeights(std::size_t layerIndex) const
    {
        auto layerSize =(m_inputLayer.size() + 1);
        auto layerStart = layerSize * layerIndex;
        return m_weights(layerStart, layerStart + layerSize);
    }

    ArrayView<Type> getNthLayerWeightsErrors(std::size_t layerIndex) const
    {
        auto layerSize =(m_inputLayer.size() + 1);
        auto layerStart = layerSize * layerIndex;
        return ArrayView<Type>(m_errorsForWeights)(layerStart, layerStart + layerSize);
    }

private:
    NotNull<ComputationNode<Type>> m_inputLayer;
    NotNull<VariableNode<Type>> m_weights;
    std::vector<Type> m_errorsForInput;
    std::vector<Type> m_errorsForWeights;
    std::vector<Type> m_outputs;
};