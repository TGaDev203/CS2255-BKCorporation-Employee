#ifndef STACK_H
#define STACK_H

#include "Node.h"

template <typename Value>
class Stack
{
private:
    int size = 0;
    Node<Value> *top_item = nullptr;

public:
    // CONSTRUCTORS
    Stack() : size{0}, top_item{nullptr} {};
    Stack(const Value first_top_value);
    Stack(Node<Value> *first_node);
    Stack(const Stack<Value> &otherStack);
    Stack(std::initializer_list<Value> list);
    ~Stack();

    // PROPERTIES
    int getSize() const;

    // CHECKING METHODS
    bool isEmpty() const;

    // METHOD
    void Push(const Value top_value);
    void Push(const Node<Value> *top_node);
    Value Pop();
    Value Peek() const;
    void Clear();

    // ITERABLE (for Read-only Purpose)
    class Iterator
    {
    private:
        Node<Value> *current = nullptr;

    public:
        Iterator(Node<Value> *iterator) : current{iterator} {};
        Node<Value> &operator*() const
        {
            return *current;
        }

        Iterator operator++()
        {
            this->current = this->current->getNextNode();
            return *this;
        }

        // Define COMPARISON for Iterator
        bool operator!=(const Iterator &otherNode) const
        {
            return this->current != otherNode.current;
        }

        bool operator==(const Iterator &otherNode) const
        {
            return this->current == otherNode.current;
        }
    };

    Iterator begin() const // Beginning of the Queue
    {
        return Iterator(this->top_item);
    }

    Iterator end() const
    {
        return Iterator(nullptr);
    }

    // OPERATORS
    Stack &operator=(const Stack<Value> &otherStack);
    friend std::ostream &operator<<(std::ostream &os, const Stack<Value> &stack)
    {
        if (!stack.isEmpty())
        {
            os << "Top: " << std::endl;
            for (auto current = stack.begin(); current != stack.end(); ++current)
            {
                os << *current << '\n';
            }
            os << "End";
        }
        else
        {
            os << "Empty Value!!!";
        }

        return os;
    }

    friend std::ostream &operator<<(std::ostream &os, const Stack<Value> *stack)
    {
        if (stack != nullptr)
        {
            if (!stack.isEmpty())
            {
                os << "Top: " << std::endl;
                for (auto current = stack.begin(); current != stack.end(); ++current)
                {
                    os << *current << '\n';
                }
                os << "End";
            }
            else
            {
                os << "Empty Value!!!";
            }
        }
        else
            os << "Empty Stack!!!";

        return os;
    }
};

// CONSTRUCTORS
template <typename Value>
Stack<Value>::Stack(const Value first_top_value)
{
    this->top_item = new Node<Value>(first_top_value);
    this->size++;
}

template <typename Value>
Stack<Value>::Stack(Node<Value> *first_node)
{
    Node<Value> *first_node_temp = new Node<Value>(first_node->getValue());

    this->top_item = first_node_temp;
    this->size++;
}

template <typename Value>
Stack<Value>::Stack(std::initializer_list<Value> list)
{
    for (const Value &value : list)
    {
        Node<Value> *new_top_node = new Node<Value>(value);
        new_top_node->setNextNode(this->top_item);
        this->top_item = new_top_node;
        this->size++;
    }
}

template <typename Value>
Stack<Value>::Stack(const Stack<Value> &otherStack) : size{otherStack.size}
{
    if (otherStack.isEmpty())
    {
        this->top_item = nullptr;
        return;
    }

    // If the otherStack has more than 0 element
    this->top_item = new Node<Value>(otherStack.top_item->getValue());
    Node<Value> *current_node = otherStack.top_item;
    Node<Value> *other_next_node = otherStack.top_item->getNextNode();

    while (other_next_node != nullptr)
    {
        current_node->setNextNode(new Node<Value>(other_next_node->getValue()));
        current_node = current_node->getNextNode();
        other_next_node = other_next_node->getNextNode();
    }
}

template <typename Value>
Stack<Value>::~Stack()
{
}

// PROPERTIES
template <typename Value>
int Stack<Value>::getSize() const
{
    return this->size;
}

// CHECKING METHODS
template <typename Value>
bool Stack<Value>::isEmpty() const
{
    return this->size == 0;
}

// METHODS
template <typename Value>
void Stack<Value>::Push(const Value top_value)
{
    Node<Value> *new_top_node = new Node<Value>(top_value);
    new_top_node->setNextNode(this->top_item);
    this->top_item = new_top_node;
    this->size++;
}

template <typename Value>
void Stack<Value>::Push(const Node<Value> *new_top_node)
{
    Node<Value> *new_top_node_temp = new Node<Value>(new_top_node->getValue());
    new_top_node_temp->setNextNode(this->top_item);
    this->top_item = new_top_node_temp;
    this->size++;
}

template <typename Value>
Value Stack<Value>::Pop()
{
    if (isEmpty())
    {
        throw std::out_of_range("The Stack is Empty!!!");
    }

    Node<Value> *node_to_remove = this->top_item;
    Value node_to_remove_value = node_to_remove->getValue();

    this->top_item = node_to_remove->getNextNode();
    delete node_to_remove;

    this->size--;
    return node_to_remove_value;
}

template <typename Value>
Value Stack<Value>::Peek() const
{
    if (isEmpty())
    {
        throw std::out_of_range("The Stack is Empty!!!");
    }

    return this->top_item->getValue();
}

template <typename Value>
void Stack<Value>::Clear()
{
    if (!isEmpty())
    {
        Node<Value> *current_node = this->top_item;
        while (current_node != nullptr)
        {
            Node<Value> *node_to_remove = current_node;
            current_node = current_node->getNextNode();
            delete node_to_remove;
            this->size--;
        }
    }
}

// OPERATORS
template <typename Value>
Stack<Value> &Stack<Value>::operator=(const Stack<Value> &otherStack)
{
    if (otherStack.isEmpty())
    {
        this->top_item = nullptr;
        return *this;
    }

    // If the otherStack has more than 0 element
    this->top_item = new Node<Value>(otherStack.top_item->getValue());
    Node<Value> *current_node = otherStack.top_item;
    Node<Value> *other_next_node = otherStack.top_item->getNextNode();

    while (other_next_node != nullptr)
    {
        current_node->setNextNode(new Node<Value>(other_next_node->getValue()));
        current_node = current_node->getNextNode();
        other_next_node = other_next_node->getNextNode();
    }
    return *this;
}

#endif