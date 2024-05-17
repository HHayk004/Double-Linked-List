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

    protected:
		Node* ptr;
    
        friend class DoubleList;
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

    Iterator insert(Iterator it, const T& val);
    Iterator insert(Iterator it, const std::initializer_list<T>& list);
    Iterator erase(Iterator it);
    Iterator erase(Iterator start, Iterator end);

    void copy(const DoubleList& list);
    void copy(DoubleList&& list);

    void clear();

    void reverse();

    void swap(DoubleList& list);

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