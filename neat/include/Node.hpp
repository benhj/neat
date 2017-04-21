#pragma once

#include "NodeType.hpp"
#include <vector>

namespace neat {

    class Connection;

    class Node
    {
      public:
        explicit Node(float const mutationProbability);
        Node() = delete;

        /// Adds a connection from another node
        void addIncomingConnectionFrom(Node & otherNode,
                                       float const lowerWeightInit,
                                       float const upperWeightInit,
                                       float const mutProb);

        /// Updates the type of node with probability
        void perturbNodeType();

        /// The input to this node not coming from another node
        void setExternalInput(double const externalInput);

        /// Will back-track to inputs to figure out what
        /// final output current should be
        double getOuput() const;

      private:

        /// To be used when the node type is perturbed
        float m_mutationProbability;

        /// The type of the node (guassian, sigmoidal, tan, etc)
        NodeType nodeType;

        /// Describes all nodes connected to this node
        std::vector<Connection> m_incomingConnections;

        /// Input going into the node not coming
        /// from another node.
        double m_externalInput;

        /// When we loop incoming connections, we accumulate
        /// input on the post-node using this function
        void accumulateInput(double const input);
    };
}