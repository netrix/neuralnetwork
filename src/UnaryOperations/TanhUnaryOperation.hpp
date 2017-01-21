#pragma once
#include "UnaryOperationNode.hpp"
#include "NotNull.hpp"
#include <cmath>

template<class Type>
struct TanhUnaryOperationNode : UnaryOperationNode<Type>
{
    TanhUnaryOperationNode(
            NotNull<ComputationNode<Type>> input)
        : m_input(*input)
    {}

    void forwardPass() override
    {
        m_outputValue = calculateTanh(m_input.getOutputValues()[0]);
    }

    ArrayView<Type const> getOutputValues() const override
    {
        return ArrayView<Type const>(m_outputValue);
    }

    void backPropagate(ArrayView<Type const> errors) override
    {
        auto error = ((Type)1.0 - m_outputValue * m_outputValue) * errors[0];
        m_input.backPropagate(error);
    }

private:
    Type calculateTanh(Type value)
    {
        auto expResult = exp(m_beta * -value);
        return (1.0f - expResult) / (1.0f + expResult);
    }

private:
    Type m_beta = 1.0f;
    ComputationNode<Type>& m_input;
    Type m_outputValue;
};