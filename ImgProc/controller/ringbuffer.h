#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#include <QDebug>
#include <opencv2/core.hpp>

template <class T>
class RingBuffer
{
public:
    RingBuffer(int bufferSize=10);
    ~RingBuffer();
    T * dataArray;  //data
    int arraySize;
    int head;
    int tail;
    int cursor;
    int prevVldNum;
    int nextVldNum;

    void setTail(int pos);
    void tailForward(int steps=1);
    void headForward(int steps=1);
    void cursorForward(int steps=1);
    void cursorRecede(int steps=1);
    bool isEmpty();
    bool isFull();
    void reset();

    void push(T newData);
    void add(T newData);
    bool getCursor(T &rtValue);
    bool getPrev(int prevSteps, T &rtValue);
    bool getNext(int nextSteps, T &rtValue);

};

template <class T>
RingBuffer<T>::RingBuffer(int bufferSize)
{
    arraySize = (bufferSize + 1) >=2 ? (bufferSize + 1) : 2;
    head = 0;
    tail = 0;
    cursor = -1;
    prevVldNum = -1;
    nextVldNum = 0;
    dataArray = new T[arraySize];
    for (int i=0; i<arraySize; i++){
        dataArray[i] = 0;
    }
}

template <class T>
RingBuffer<T>::~RingBuffer()
{
    for (int i=0; i<arraySize; i++){
        dataArray[i] = 0;
    }
    delete []dataArray;
}

template <class T>
void RingBuffer<T>::setTail(int pos)
{
    pos = pos%arraySize;
    tail = pos;
}

template <class T>
void RingBuffer<T>::tailForward(int steps)
{
    tail = (tail + steps) % arraySize;
}

template <class T>
void RingBuffer<T>::headForward(int steps)
{
    head = (head + steps) % arraySize;
}

template <class T>
void RingBuffer<T>::cursorForward(int steps)
{
    steps = steps <= nextVldNum ? steps : nextVldNum;
    cursor = (cursor + steps) % arraySize;
    nextVldNum = 0;
    prevVldNum = prevVldNum + steps;
//    prevVldNum = prevVldNum <= arraySize - 2 ? prevVldNum : arraySize - 2;
}

template <class T>
void RingBuffer<T>::cursorRecede(int steps)
{
    steps = steps % arraySize;
    steps = steps <= prevVldNum ? steps : prevVldNum;
    cursor = (cursor + (arraySize - steps)) % arraySize;
    prevVldNum = prevVldNum - steps;
    nextVldNum = nextVldNum + steps;
}

template <class T>
bool RingBuffer<T>::isEmpty()
{
    if (tail == head)
        return true;
    else
        return false;
}

template <class T>
bool RingBuffer<T>::isFull()
{
    if ((tail + 1)%arraySize == head)
        return true;
    else
        return false;
}

template <class T>
void RingBuffer<T>::reset()
{
    for (int i=0; i<arraySize; i++)
        dataArray[i] = 0;
    head = 0;
    tail = 0;
    cursor = -1;
    prevVldNum = -1;
    nextVldNum = 0;
}

template <class T>
void RingBuffer<T>::push(T newData)
{
    dataArray[tail] = newData;
    tailForward(1);
}

template <class T>
void RingBuffer<T>::add(T newData)
{
    if ((cursor + 1) % arraySize != tail){
        tail = (cursor + 1) % arraySize;
    }
    if (isFull()){
        headForward(1);
        prevVldNum = arraySize - 2;
    }else{
        prevVldNum ++;
    }
    push(newData);
    cursor = (cursor + 1) % arraySize;
    nextVldNum = 0;
}

template <class T>
bool RingBuffer<T>::getCursor(T &rtValue)
{
    if (cursor < 0){
        return false;
    }else{
        rtValue = dataArray[cursor];
        return true;
    }
}

template <class T>
bool RingBuffer<T>::getPrev(int prevSteps, T & rtValue)
{
    if (prevSteps > prevVldNum){
        return false;
    }else{
        int index = (cursor + arraySize - prevSteps) % arraySize;
        qDebug() << "prev index:" << index;
        rtValue = dataArray[index];
        return true;
    }
}

template <class T>
bool RingBuffer<T>::getNext(int nextSteps, T &rtValue)
{
    if (nextSteps > nextVldNum){
        return false;
    }else{
        int index = (cursor + nextSteps) % arraySize;
        rtValue = dataArray[index];
        return true;
    }
}


#endif // RINGBUFFER_H
