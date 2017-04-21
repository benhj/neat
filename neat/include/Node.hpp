#pragma once

#include "NodeType.hpp"
#include "NodeFunction.hpp"
#include <vector>

namespace neat {

    class Connection;

    class Node
    {
      public:
        Node(int const index, 
             NodeType const & nodeType,
             float const mutationProbability);
        Node() = delete;

        /// Adds a connection from another node
        void addIncomingConnectionFrom(Node & otherNode,
                                       float const weightBound,
                                       float const mutProb);

        /// For removing a connection
        void removeIncomingConnectionFrom(int const i);

        /// Updates the type of node with probability
        void perturbNodeFunction();

        /// The input to this node not coming from another node
        void setExternalInput(double const externalInput);

        /// Will back-track to inputs to figure out what
        /// final output current should be
        double getOutput();

        /// Retrieves the classic i,j type index of this node
        int getIndex() const;

        NodeType getNodeType() const;

        /// Indicates if this has connection from node i
        bool hasConnectionFrom(int const i);

      private:

        /// Indexes node in typical matrix i,j fashion
        int m_index;

        /// Input, hidden or output
        NodeType m_nodeType;

        /// To be used when the node type is perturbed
        float m_mutationProbability;

        /// The node function type(guassian, sigmoidal, tan, etc)
        NodeFunction m_nodeFunction;

        /// Describes all nodes connected to this node
        std::vector<Connection> m_incomingConnections;

        /// Input going into the node not coming
        /// from another node.
        double m_externalInput;
    };
}