#include "Node.hpp"
#include "Connection.hpp"
#include <cstdlib> // rand()
#include <algorithm>
#include <cmath>
#include <cassert>

namespace {

    float const PI = 3.14159265359f;

    neat::NodeFunction initNodeFunction()
    {
        return static_cast<neat::NodeFunction>(rand() % 8);
    }

    double applyNodeFunction(neat::NodeFunction const & nodeFunction, double const in)
    {
        if (nodeFunction == neat::NodeFunction::HyperbolicTangent) {
            return ::tanh(in);
        } else if (nodeFunction == neat::NodeFunction::Absolute) {
            return std::abs(in);
        } else if (nodeFunction == neat::NodeFunction::Gaussian) {
            return ::exp(-((in*in)/(2*2)));
        } else if (nodeFunction == neat::NodeFunction::Sin) {
            return ::sin(in*((2*PI)/4.0));
        } else if (nodeFunction == neat::NodeFunction::Cos) {
            return ::cos(in*((2*PI)/4.0));
        } else if (nodeFunction == neat::NodeFunction::Clipped) {
            return std::min(std::max(in,-3.0),3.0) / 3.0;
        } else if (nodeFunction == neat::NodeFunction::Step) {
            return (in > 0) - (in < 0);
        } else {
            return in;
        }
    }
}

namespace neat {
    Node::Node(int const index, 
               NodeType const & nodeType,
               float const mutationProbability)
      : m_index(index)
      , m_nodeType(nodeType)
      , m_mutationProbability(mutationProbability)
      , m_nodeFunction(initNodeFunction())
      , m_externalInput(0)
    {
    }

    void Node::addIncomingConnectionFrom(Node & otherNode,
                                         float const weightBound,
                                         float const mutProb)
    {
        // Sanity A: Input nodes can't having incoming connections
        assert(m_nodeType != NodeType::Input);

        // Sanity B: Output nodes can't connect to hidden nodes
        if (m_nodeType == NodeType::Hidden) {
            assert(otherNode.getNodeType() != NodeType::Output);
        }

        m_incomingConnections.emplace_back(*this, 
                                           otherNode, 
                                           weightBound, 
                                           mutProb);
    }

    void Node::removeIncomingConnectionFrom(int const i)
    {
        auto it = std::find_if(std::begin(m_incomingConnections),
                               std::end(m_incomingConnections),
                               [i](Connection const & con) {
                                   return con.getNodeRefA().getIndex() == i;
                               });

        if (it != std::end(m_incomingConnections)) {
            m_incomingConnections.erase(it);
        }
    }

    int Node::getIndex() const
    {
        return m_index;
    }

    NodeType Node::getNodeType() const
    {
        return m_nodeType;
    }

    bool Node::hasConnectionFrom(int const i) const
    {
        return std::find_if(std::begin(m_incomingConnections),
                            std::end(m_incomingConnections),
                            [i](Connection const & con) {
                               return con.getNodeRefA().getIndex() == i;
                            }) != std::end(m_incomingConnections);
    }

    void Node::perturbNodeFunction()
    {
        if (((double) rand() / (RAND_MAX)) < m_mutationProbability) {
            m_nodeFunction = initNodeFunction();
        }
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
            auto const & nodeRef = con.getNodeRefA();
            accumulator += nodeRef.getOutput() * con.weight();
        }
        accumulator += m_externalInput;
        return applyNodeFunction(m_nodeFunction, accumulator);
    }
}