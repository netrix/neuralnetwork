#include "BackPropagationNetwork.hpp"


BackPropagationNetwork::BackPropagationNetwork(
        OperationNodes && operationNodes,
        ConstNodes && constNodes,
        VariableNodes && variableNodes,
        std::unique_ptr<ConstStorage<BNN_TYPE>> constStorage,
        std::unique_ptr<VariableStorage<BNN_TYPE>> variableStorage)
    : m_operationNodes(std::move(operationNodes))
    , m_constNodes(std::move(constNodes))
    , m_variableNodes(std::move(variableNodes))
    , m_constStorage(std::move(constStorage))
    , m_variableStorage(std::move(variableStorage))
{}

ArrayView<BNN_TYPE> BackPropagationNetwork::forwardPass(ArrayView<BNN_TYPE> input)
{
    // 1. set input into m_constStorage (verify length!!!)
    // 2. run all operations one by one
    // 3. return arrayView to last operation outputs
}

void BackPropagationNetwork::backPropagate(ArrayView<BNN_TYPE> errors)
{

}
