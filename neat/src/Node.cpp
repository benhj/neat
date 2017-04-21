#include "Node.hpp"
#include "Connection.hpp"

namespace neat {
    Node::Node(float const mutationProbability)
      : m_mutationProbability(mutationProbability)
      , m_externalInput(0)
    {
    }

    void Node::addIncomingConnectionFrom(Node & otherNode,
                                         float const lowerWeightInit,
                                         float const upperWeightInit,
                                         float const mutProb)
    {
        m_incomingConnections.emplace_back(*this, 
                                           otherNode, 
                                           lowerWeightInit, 
                                           upperWeightInit, 
                                           mutProb);
    }

    void Node::perturbNodeType()
    {
    }

    void Node::setExternalInput(double const externalInput)
    {
        m_externalInput = externalInput;
    }

    double Node::getOutput() const
    {
        // back-tracks over all nodes to get final output
        double accumulator = 0;
        for (auto const & con : m_incomingConnections) {
            auto & nodeRef = con.getNodeRefA();
            accumulator += nodeRef.getOutput();
        }
        accumulator += m_externalInput;
        m_externalInput = 0;
        return detail::applyNodeFunction(m_nodeType, accumulator);
    }
}