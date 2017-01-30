#include <iostream>
#include <vector>
#include <memory>
#include <cassert>
#include <random>
#include <iomanip>
#include "NotNull.hpp"
#include "NodeTags.hpp"
#include "NodeBuilders/NodeBuilder.hpp"
#include "NodeBuilders/BinaryNodeBuilder.hpp"
#include "BuilderStorage.hpp"
#include "NetworkBuilder.hpp"
#include "LayeredNetworkBuilder.hpp"
#include "LayeredNetworkBuilders/FullyConnectedLayerSpecs.hpp"
#include "LayeredNetworkBuilders/FullyConnectedLayerBuilder.hpp"
#include "LayeredNetworkBuilders/InputLayerSpecs.hpp"
#include "MathVectorAdapter.hpp"
#include "StreamOperators.hpp"
#include "Datasets/MnistLoader.hpp"
#include <set>
#include "NormalDistributionGenerator.hpp"
#include "MnistPreprocessedDataSet.hpp"
#include "LearnUtils.hpp"
#include "PassThroughLayerNodeFactories/ReLULayer.hpp"

int main()
{
    std::string imagesPath = "../../../data/train-images-idx3-ubyte";
    std::string labelsPath = "../../../data/train-labels-idx1-ubyte";

    auto mnistDataset = MnistPreprocessedDataSet<float>(loadMnistDataset(imagesPath, labelsPath));
    std::cout << mnistDataset.getInputSampleSize() << " " << mnistDataset.getNumSamples() << " " << mnistDataset.getOutputSampleSize() << std::endl;

    LayeredNetworkBuilder layeredNetworkBuilder;
    auto outLayer = layeredNetworkBuilder.setOutputLayer(FullyConnectedLayerSpecs{
                                                             std::make_unique<ReLULayerNodeFactory<BNN_TYPE>>(), mnistDataset.getOutputSampleSize()});
    auto hiddenLayer = outLayer->setInputLayer(FullyConnectedLayerSpecs{
                                                   std::make_unique<ReLULayerNodeFactory<BNN_TYPE>>(), 32});
    hiddenLayer->setInputLayer(InputLayerSpecs{mnistDataset.getInputSampleSize()});
    auto network = layeredNetworkBuilder.buildBackPropagationNetwork(0.01f);

    network->setVariables(NormalDistributionGenerator<BNN_TYPE>(17, 0, 1e-1));

    for(auto i = 0u; i < 500u; ++i)
    {
        auto errorSum = learnEpochParallel(layeredNetworkBuilder, network, mnistDataset, 256, 0.01f, i);
        std::cout << "epoch: " << i << " errorSum: " << errorSum <<  std::endl;

    }

    // TODO
    // 4. abstract backprop
    //
    // zero-centering data! mean centering

    // im2col for convolution
}
