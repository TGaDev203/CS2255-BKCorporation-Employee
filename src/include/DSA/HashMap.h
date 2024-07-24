#ifndef HASHMAP_H
#define HASHMAP_H

#include <vector>
#include <functional>
#include <math.h>
#include <utility>

template <typename Key, typename Value>
struct Bucket
{
    Key key;
    Value value;
    bool operator==(const Bucket<Key, Value> &otherBucket)
    {
        return this->key == otherBucket.key && this->value == otherBucket.value;
    }
};

template <typename Key, typename Value>
class HashMap
{
private:
    int size_array = 20;
    std::vector<Bucket<Key, Value>> array;
    int amount_value_occupy = 0;

public:
    // CONSTRUCTORS
    HashMap(int size_array);
    HashMap();
    HashMap(std::initializer_list<std::pair<const Key, Value>> list);
    HashMap(const HashMap<Key, Value> &otherHashMap); // COPY CONSTRUCTOR
    ~HashMap();

    // PROPERTIES
    int getSizeArray() const;
    int getAmountValueOccupy() const;

    // METHODS FOR HASH PURPOSE
    void expandArraySize(int space);
    int hash(Key key) const;
    int compressor(int hash_code) const;
    void assign(Key, Value);
    Value retrieve(Key);

    // OPERATORS
    Value &operator[](const Key &key);
    HashMap &operator=(const HashMap<Key, Value> &otherHashMap);
    friend std::ostream &operator<<(std::ostream &os, const HashMap<Key, Value> &hashMap)
    {
        if (hashMap.getAmountValueOccupy() != 0)
        {
            int amountValuesFind = 0; // To Prevent Time Complexity O(n)
            os << "Begin: ";
            for (int index = 0; index < hashMap.getSizeArray(); index++)
            {
                if (hashMap.array[index].key != Key())
                {
                    amountValuesFind++;
                    os << hashMap.array[index].value << '|';
                    if (amountValuesFind == hashMap.getAmountValueOccupy())
                    {
                        break;
                    }
                }
            }
            os << " End";
        }
        else
        {
            os << "Empty Value!!!";
        }
        return os;
    }
};

template <typename Key, typename Value>
int HashMap<Key, Value>::getSizeArray() const
{
    return this->size_array;
}

template <typename Key, typename Value>
int HashMap<Key, Value>::getAmountValueOccupy() const
{
    return this->amount_value_occupy;
}

// Space: number of slot it need to be add in
template <typename Key, typename Value>
void HashMap<Key, Value>::expandArraySize(int space)
{
    if (space < 0)
    {
        throw std::out_of_range("Cannot Shrink Array Size!!!");
    }

    int old_size = this->getSizeArray();
    int new_size = old_size + space;

    this->size_array = new_size;
    this->array.resize(new_size);
}

template <typename Key, typename Value>
HashMap<Key, Value>::HashMap(int size_array) : size_array(size_array)
{
    this->array.resize(size_array);
}

template <typename Key, typename Value>
HashMap<Key, Value>::HashMap() : size_array(20)
{
    this->array.resize(size_array);
}

//! CURRENTLY WORKING ON
template <typename Key, typename Value>
HashMap<Key, Value>::HashMap(std::initializer_list<std::pair<const Key, Value>> list)
{
    this->size_array = 20;
    this->array.resize(20);
    for (const auto &pair : list)
    {
        Key key = pair.first;
        Value value = pair.second;
        this->assign(key, value);
        this->amount_value_occupy++;
    }
}

template <typename Key, typename Value>
HashMap<Key, Value>::HashMap(const HashMap<Key, Value> &otherHashMap) // COPY CONSTRUCTOR
{
    this->amount_value_occupy = otherHashMap.amount_value_occupy;
    // RESIZE THE ARRAY SIZE AND UPDATE THE SIZE
    this->size_array = otherHashMap.size_array;
    this->array.resize(otherHashMap.getSizeArray());

    for (int index = 0; index < otherHashMap.getSizeArray(); index++)
    {
        this->array[index] = otherHashMap.array[index];
    }
}

template <typename Key, typename Value>
HashMap<Key, Value>::~HashMap()
{
}

template <typename Key, typename Value>
int HashMap<Key, Value>::hash(Key key) const
{
    int hash_value = 0;
    std::hash<Key> hashFunc;
    hash_value = hashFunc(key);
    return std::abs(hash_value); // To Prevent Negative Number
}

template <typename Key, typename Value>
int HashMap<Key, Value>::compressor(int hash_code) const
{
    return hash_code % this->getSizeArray();
}

template <typename Key, typename Value>
void HashMap<Key, Value>::assign(Key key, Value value)
{
    this->amount_value_occupy++;
    // Using Hash Collision: Linear Probing
    int hash_value = this->hash(key);
    int array_index = this->compressor(hash_value);
    int flag_index = array_index;

    Bucket<Key, Value> bucket;
    bucket.key = key;
    bucket.value = value;

    Bucket<Key, Value> default_bucket;
    do
    {
        if (this->array[array_index] == default_bucket)
        {
            this->array[array_index] = bucket;
            return;
        }
        else if (this->array[array_index].key == key)
        {
            this->array[array_index].value = value;
            return;
        }
        else
        {
            array_index++;
        }

        // To Prevent the array index is out or Range
        if (array_index < 0 || array_index >= this->getSizeArray())
        {
            this->expandArraySize(1);
        }

    } while (flag_index != array_index);
}

template <typename Key, typename Value>
Value HashMap<Key, Value>::retrieve(Key key)
{
    // Using Hash Collision: Linear Probing
    int hash_value = this->hash(key);
    int array_index = this->compressor(hash_value);
    int flag_index = array_index;

    do
    {
        if (this->array[array_index].key == key)
        {
            return this->array[array_index].value;
        }
        else // If that is not the Correct Key
        {
            array_index++;
        }

        // To Prevent the array index is out or Range
        if (array_index < 0 || array_index >= this->getSizeArray())
        {
            throw std::out_of_range("Key Was Not Found!!!");
        }

    } while (flag_index != array_index);

    return this->array[array_index].value;
}

// OPERATORS
template <typename Key, typename Value>
Value &HashMap<Key, Value>::operator[](const Key &key)
{
    // Using Hash Collision: Linear Probing
    int hash_value = this->hash(key);
    int array_index = this->compressor(hash_value);

    //? SEARCH FOR THE KEY IN THE ARRAY
    for (int index = array_index; index < this->getSizeArray(); index++)
    {
        if (this->array[index].key == key) // If that is the Key
        {
            this->array[index].key = key;
            return this->array[index].value;
            array_index = index;
        }
        else if (this->array[index].key == Key()) // If the Key is default key -> That is the Key
        {
            this->array[index].key = key;
            this->amount_value_occupy++;
            return this->array[index].value;
        }
    }

    // If the key is not found, insert it into the HashMap
    // By expand the Array and then put it into that array_index
    this->expandArraySize(1);

    array_index++;
    this->array[array_index].key = key;
    this->amount_value_occupy++;
    return this->array[array_index].value;
}

template <typename Key, typename Value>
HashMap<Key, Value> &HashMap<Key, Value>::operator=(const HashMap<Key, Value> &otherHashMap)
{
    this->amount_value_occupy = otherHashMap.amount_value_occupy;
    // RESIZE THE ARRAY SIZE AND UPDATE THE SIZE
    this->size_array = otherHashMap.size_array;
    this->array.resize(otherHashMap.getSizeArray());

    for (int index = 0; index < otherHashMap.getSizeArray(); index++)
    {
        this->array[index] = otherHashMap.array[index];
    }

    return *this;
}

#endif