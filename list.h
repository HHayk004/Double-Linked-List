#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <initializer_list>
#include <utility>

template <typename T>
class DoubleList
{
private:
    struct Node
    {
        Node* prev;
        Node* next;
        T val;

        Node(T val = T());
        ~Node() = default;
    };

public:
    class Iterator {
	public:
		Iterator(Node* node = nullptr);

		Iterator& operator=(const Iterator& it);
		Iterator operator++();
		Iterator operator++(int);
		Iterator operator--();
		Iterator operator--(int);
					
		T& operator*() const;
		Node* operator->() const;
		bool operator==(const Iterator& it) const;
		bool operator!=(const Iterator& it) const;

    private:
		Node* ptr;
};

public:
    DoubleList();
    explicit DoubleList(size_t size, T val = T());
    DoubleList(const std::initializer_list<T>& list);
    DoubleList(const DoubleList& list);
    DoubleList(DoubleList&& list);

    ~DoubleList();

    void push_front(T val);
    void push_back(T val);
    
    void pop_back();
    void pop_front();

    void copy(const DoubleList& list);
    void copy(DoubleList&& list);

    void clear();

    Iterator begin() const;
    Iterator end() const;

    bool empty() const;
    size_t size() const;

private:
    Node* head;
    Node* tail;

    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const DoubleList<U>& list);
};

#include "list.hpp"

#endif