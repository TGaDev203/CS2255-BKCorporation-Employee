#ifndef QUEUE_H
#define QUEUE_H

#include "Node.h"

template <typename Value>
class Queue
{
private:
    Node<Value> *head = nullptr;
    Node<Value> *tail = nullptr;
    int size = 0;

public:
    // Constructors
    Queue() : head{nullptr}, tail{nullptr} {};
    Queue(const Value new_tail_value);
    Queue(Node<Value> *new_tail);
    Queue(const std::initializer_list<Value> list);
    Queue(const Queue<Value> &otherQueue);
    ~Queue();

    // PROPERTIES
    int getSize() const;
    bool isEmpty() const;

    // METHODS
    void Enqueue(const Value new_tail_value);
    void Enqueue(Node<Value> *new_tail);
    Value Dequeue();
    Value Peek() const;
    void Clear();

    // OPERATORS
    friend std::ostream &operator<<(std::ostream &os, const Queue<Value> &queue)
    {
        if (!queue.isEmpty())
        {
            os << "Begin: ";
            for (auto current = queue.begin(); current != queue.end(); ++current)
            {
                os << *current << '|';
            }
            os << " End";
        }
        else
        {
            os << "Empty Value!!!";
        }
        return os;
    }
    Queue &operator=(const Queue<Value> &otherQueue);

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
        return Iterator(this->head);
    }

    Iterator end() const
    {
        if (!isEmpty())
        {
            return Iterator(this->tail->getNextNode());
        }
        return Iterator(nullptr);
    }
};

// CONSTRUCTORS
template <typename Value>
Queue<Value>::Queue(const Value new_tail_value)
{
    Node<Value> *new_tail = new Node<Value>(new_tail_value);

    // If the Queue has No Element
    if (this->size == 0)
    {
        this->head = new_tail;
        this->tail = new_tail;
        this->size++;
        return;
    }
    // If the Queue has More than 1 Elements
    else
    {
        this->tail->setNextNode(new_tail);
        this->tail = new_tail;
        this->size++;
        return;
    }
}

template <typename Value>
Queue<Value>::Queue(Node<Value> *new_tail)
{
    Node<Value> *new_tail_temp = new Node<Value>(new_tail->getValue());
    delete new_tail; // PREVENT MEMORY LEAK
    // If the Queue has No Element
    if (this->size == 0)
    {
        this->head = new_tail_temp;
        this->tail = new_tail_temp;
        this->size++;
        return;
    }
    // If the Queue has More than 1 Elements
    else
    {
        this->tail->setNextNode(new_tail_temp);
        this->tail = new_tail_temp;
        this->size++;
        return;
    }
}

template <typename Value>
Queue<Value>::Queue(const std::initializer_list<Value> list)
{
    for (const Value &value : list)
    {
        Node<Value> *new_tail = new Node<Value>(value);
        switch (this->size)
        {
        case 0:
            this->head = new_tail;
            this->tail = new_tail;
            this->size++;
            break;

        default:
            this->tail->setNextNode(new_tail);
            this->tail = new_tail;
            this->size++;
            break;
        }
    }
}

// COPY CONSTRUCTOR
template <typename Value>
Queue<Value>::Queue(const Queue<Value> &otherQueue) : size{otherQueue.getSize()}
{
    if (otherQueue.size == 0)
    {
        this->head = nullptr;
        this->tail = nullptr;
        return;
    }

    this->head = new Node<Value>(otherQueue.head->getValue());
    Node<Value> *current = head;
    Node<Value> *otherCurrent = otherQueue.head->getNextNode();

    while (otherCurrent != nullptr)
    {
        current->setNextNode(new Node<Value>(otherCurrent->getValue()));
        current = current->getNextNode();
        otherCurrent = otherCurrent->getNextNode();
    }

    this->tail = current;
}

template <typename Value>
Queue<Value>::~Queue()
{
}

// PROPERTIES
template <typename Value>
int Queue<Value>::getSize() const
{
    return this->size;
}

template <typename Value>
bool Queue<Value>::isEmpty() const
{
    return this->size == 0;
}

template <typename Value>
void Queue<Value>::Enqueue(const Value new_tail_value)
{
    Node<Value> *new_tail = new Node<Value>(new_tail_value);
    if (this->size == 0) // If the Queue Is Empty
    {
        this->head = new_tail;
        this->tail = new_tail;
        this->size++;
        return;
    }

    this->tail->setNextNode(new_tail);
    this->tail = new_tail;
    this->size++;
}

template <typename Value>
void Queue<Value>::Enqueue(Node<Value> *new_tail)
{
    Node<Value> new_tail_temp = new Node<Value>(new_tail->getValue());
    if (this->size == 0) // If the Queue Is Empty
    {
        this->head = new_tail_temp;
        this->tail = new_tail_temp;
        this->size++;
        return;
    }

    this->tail->setNextNode(new_tail_temp);
    this->tail = new_tail_temp;
    this->size++;
}

template <typename Value>
Value Queue<Value>::Dequeue()
{
    // The Size cannot be Negative
    if (this->size <= 0)
    {
        throw std::out_of_range("Queue Is Empty!!!");
    }

    Node<Value> *node_to_remove = this->head;
    Value node_to_remove_value = node_to_remove->getValue();
    Node<Value> *new_head = this->head->getNextNode();
    switch (this->size)
    {
    case 1:
        this->head = nullptr;
        this->tail = nullptr;
        this->size = 0;
        delete node_to_remove;
        break;

    default:
        this->head = new_head;
        this->size--;
        delete node_to_remove;
        break;
    }
    return node_to_remove_value;
}

template <typename Value>
Value Queue<Value>::Peek() const
{
    return this->head->getValue();
}

template <typename Value>
void Queue<Value>::Clear()
{
    int copySize = this->getSize();
    for (int time = 0; time < copySize; time++)
    {
        this->Dequeue();
    }
}

// OPERATORS
template <typename Value>
Queue<Value> &Queue<Value>::operator=(const Queue<Value> &otherQueue)
{
    if (otherQueue.size == 0)
    {
        this->head = nullptr;
        this->tail = nullptr;
        return *this;
    }

    this->head = new Node<Value>(otherQueue.head->getValue());
    Node<Value> *current = head;
    Node<Value> *otherCurrent = otherQueue.head->getNextNode();

    while (otherCurrent != nullptr)
    {
        current->setNextNode(new Node<Value>(otherCurrent->getValue()));
        current = current->getNextNode();
        otherCurrent = otherCurrent->getNextNode();
    }

    this->tail = current;

    return *this;
}

#endif