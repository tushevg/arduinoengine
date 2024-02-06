#ifndef QUEUE_H
#define QUEUE_H

#include <Arduino.h>

template<class T>
class Queue
{
public:
    Queue(uint8_t maxitems = 64) : m_first(0), m_last(0), m_count(0), m_maxitems(maxitems), m_data(new T[maxitems + 1]) {}
    ~Queue(){delete[] m_data;}

    inline uint8_t count();
    inline uint8_t first();
    inline uint8_t last();
    bool push(const T &item);
    T peek();
    T pop();
    void clear();

private:
    uint8_t m_first;
    uint8_t m_last;
    uint8_t m_count;
    uint8_t m_maxitems;
    T* m_data;

};


template <class T>
inline uint8_t Queue<T>::first()
{
    return m_first;
}


template <class T>
inline uint8_t Queue<T>::last()
{
    return m_last;
}


template <class T>
inline uint8_t Queue<T>::count()
{
    return m_count;
}


template <class T>
bool Queue<T>::push(const T &item)
{
    bool done = false;
    if (m_count < m_maxitems)
    {
        m_data[m_last++] = item;
        m_count++;
        done = true;

        // check if index is outside array
        if (m_last > m_maxitems)
            m_last -= (m_maxitems + 1);

    }

    // drops out when array is full and returns false
    return done;
}


template <class T>
T Queue<T>::pop()
{
    if (m_count <= 0)
        return T(); // returns empty

    T retval = m_data[m_first];
    m_first++;
    m_count--;

    // check if index is outside array
    if (m_first > m_maxitems)
        m_first -= (m_maxitems + 1);

   return retval;
}


template <class T>
T Queue<T>::peek()
{
    if (m_count <= 0)
        return T(); // returns empty

    return m_data[m_first];
}


template <class T>
void Queue<T>::clear()
{
    m_first = m_last;
    m_count = 0;
}

#endif /* QUEUE_H */
