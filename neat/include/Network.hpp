#pragma once

#include <vector>

namespace neat {

    class Node;

    class Network
    {
      public:
        Network(int const inputCount, 
                int const outputCount,
                int const maxSize,
                double const nodeAdditionProb,
                double const nodeFunctionChangeProb,
                double const weightChangeProb,
                double const weightInitBound);

      private:
        int m_inputCount;
        int m_outputCount;
        double m_nodeAdditionProb;
        double m_nodeFunctionChangeProb;
        double m_weightChangeProb;
        double m_weightInitBound;
        std::vector<Node> m_nodes;

        // fully connect all inputs to all outputs
        void initNet();
    };

}