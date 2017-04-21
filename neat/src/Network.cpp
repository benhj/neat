// Copyright (c) 2017 Ben Jones

#include "Network.hpp"
#include "NodeType.hpp"
#include "Node.hpp"
#include "Connection.hpp"

namespace neat {
    Network::Network(int const inputCount, 
                     int const outputCount,
                     int const maxSize,
                     double const nodeAdditionProb,
                     double const nodeFunctionChangeProb,
                     double const weightChangeProb,
                     double const weightInitBound)
      : m_inputCount(inputCount)
      , m_outputCount(outputCount)
      , m_nodeAdditionProb(nodeAdditionProb)
      , m_nodeFunctionChangeProb(nodeFunctionChangeProb)
      , m_weightChangeProb(weightChangeProb)
      , m_weightInitBound(weightInitBound)
    {
        m_nodes.reserve(maxSize);
        initNet();
    }

    void Network::initNet()
    {
        // Input and output node creation. 
        for (auto i = 0; i < m_inputCount; ++i) {
            m_nodes.emplace_back(i, NodeType::Input, m_nodeFunctionChangeProb);
            // Also set bias to each input to 1
            m_nodes[i].setExternalInput(1.0);
        }
        for (auto i = m_inputCount; i < m_inputCount + m_outputCount; ++i) {
            m_nodes.emplace_back(i, NodeType::Output, m_nodeFunctionChangeProb);
        }

        // Fully connect from inputs to outputs (i.e. feed-forward)
        for (auto i = 0; i < m_inputCount; ++i) {
            for (auto j = m_inputCount; j < m_inputCount + m_outputCount; ++j) {
                m_nodes[j].addIncomingConnectionFrom(m_nodes[i], 
                                                     m_weightInitBound, 
                                                     m_weightChangeProb);
            }
        }
    }

    void Network::addNodeInPlaceOf(Connection & con)
    {
        // Create a new node
        auto id = m_nodes.size() - 1;
        m_nodes.emplace_back(id, NodeType::Hidden, m_nodeFunctionChangeProb);

        // Find out original connectivity
        auto & nodePre = con.getNodeRefA();
        auto & nodePost = con.getNodeRefB();
        
        // Remove old connection from nodePre to nodePost
        auto nodePreIndex = nodePre.getIndex();
        nodePost.removeIncomingConnectionFrom(nodePreIndex);

        // Add new connection from nodePre to new node
        m_nodes[id].addIncomingConnectionFrom(nodePre, 
                                              m_weightInitBound, 
                                              m_weightChangeProb);

        // ..and from new node to node post
        nodePost.addIncomingConnectionFrom(m_nodes[id], 
                                           m_weightInitBound, 
                                           m_weightChangeProb);
    }

    void Network::perturbWeights(double const byAmount)
    {
        for(auto i = m_inputCount; i < m_nodes.size(); ++i) {
            m_nodes[i].perturbIncomingWeights(byAmount);
        }
    }
}