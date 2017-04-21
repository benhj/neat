#pragma once

namespace neat {

    class Node;

    class Connection
    {
      public:  
        Connection(Node & nodeA,
                   Node & nodeB,
                   float const weightInitLower,
                   float const weightInitUpper, 
                   float const mutationProbability);

        /// Mutates the weight value
        void perturbWeight();

        Node & getNodeRefA();
        Node & getNodeRefB();

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