#pragma once

namespace neat {

    class Node;

    class Connection
    {
      public:  
        Connection(Node & nodeA,
                   Node & nodeB,
                   float const weightBound, 
                   float const mutationProbability);

        // Since we have references as member vars,
        // we need explicit copy and assignment operators.
        // Applying rule of 4, also have the move equivalents.
        Connection(Connection const & other);
        Connection(Connection && other);
        Connection & operator=(Connection const & other);
        Connection & operator=(Connection && other);

        /// Mutates the weight value
        void perturbWeight(float const weightStep);

        Node & getNodeRefA();
        Node & getNodeRefB();

        float weight() const;

      private:
        /// The connection end-points
        Node & m_nodeA;
        Node & m_nodeB;

        /// Probability of weight changing when updated
        float m_mutationProbability;

        /// The actual connection weight between nodes
        float m_weight;
    };
}