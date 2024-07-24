#ifndef NODE_H
#define NODE_H

#include <iostream>

template <typename Value>
class Node
{
private:
    Value value = Value();
    Node *next_node = nullptr;

public:
    // CONSTRUCTORS
    Node(const Value &value, Node *next_node = nullptr) : value{value}, next_node{next_node} {};
    Node() : value(Value()), next_node(nullptr){}; // Default Value
    ~Node(){};

    Node(const Node &otherNode); // Copy constructor
    // PROPERTIES
    Value getValue() const;
    void setValue(const Value new_value);

    Node *getNextNode() const;
    void setNextNode(const Value new_value);
    void setNextNode(Node *new_next_node);

    // OPERATORS
    Node& operator=(const Node& otherNode);
    friend std::ostream &operator<<(std::ostream &os, const Node &node)
    {
        os << node.getValue();
        return os;
    }
};

// COPY CONSTRUCTOR 
// For creating Temporary object
template <typename Value>
Node<Value>::Node(const Node &otherNode) : value{otherNode.value}, next_node{nullptr}
{
    if (otherNode.getNextNode() != nullptr)
    {
        Value otherNodeValue = otherNode.getValue();
        this->next_node = new Node<Value>(otherNodeValue);
    }
}

// PROPERTIES
template <typename Value>
Value Node<Value>::getValue() const
{
    return this->value;
}

template <typename Value>
void Node<Value>::setValue(const Value new_value)
{
    this->value = new_value;
}

template <typename Value>
Node<Value> *Node<Value>::getNextNode() const
{
    return this->next_node;
}

template <typename Value>
void Node<Value>::setNextNode(const Value new_value)
{
    Node<Value> *new_next_node = new Node(new_value);
    this->next_node = new_next_node;
}

template <typename Value>
void Node<Value>::setNextNode(Node *new_next_node)
{
    this->next_node = new_next_node;
}

// OPERATORS
template <typename Value>
Node<Value>& Node<Value>::operator=(const Node& otherNode) 
{   
    // To Make Sure they are not the same Memory Address
    if (this != &otherNode)
    {
        this->value = otherNode.getValue();
        delete this->next_node;
        next_node = nullptr;

        if (otherNode.getNextNode() != nullptr)
        {
            Value next_value = otherNode.getValue();
            this->next_node = new Node<Value>(next_value);
        }
    }
    return *this;
}

#endif