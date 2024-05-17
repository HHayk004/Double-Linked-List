template <typename T>
std::ostream& operator<<(std::ostream& os, const DoubleList<T>& list)
{
    for (auto it = list.begin(); it != list.end(); ++it)
    {
        os << *it << ' ';
    }

    return os;
}

template <typename T>
DoubleList<T>::Node::Node(T val) : prev(nullptr), next(nullptr), val(val){}

template <typename T>
DoubleList<T>::Iterator::Iterator(Node* node) : ptr(node){}

template <typename T>
typename DoubleList<T>::Iterator& DoubleList<T>::Iterator::operator=(const Iterator& it)
{
    ptr = it.ptr;

    return *this;
}

template <typename T>
typename DoubleList<T>::Iterator DoubleList<T>::Iterator::operator++()
{
    ptr = ptr->next;

    return *this;
}

template <typename T>
typename DoubleList<T>::Iterator DoubleList<T>::Iterator::operator++(int)
{
    Iterator it(ptr);
    ptr = ptr->next;

    return it;
}

template <typename T>
typename DoubleList<T>::Iterator DoubleList<T>::Iterator::operator--()
{
    ptr = ptr->prev;

    return *this;
}

template <typename T>
typename DoubleList<T>::Iterator DoubleList<T>::Iterator::operator--(int)
{
    Iterator it(ptr);
    ptr = ptr->prev;

    return it;
}

template <typename T>
T& DoubleList<T>::Iterator::operator*() const
{
    return ptr->val;
}

template <typename T>
typename DoubleList<T>::Node* DoubleList<T>::Iterator::operator->() const
{
    return ptr;
}
		
template <typename T>        
bool DoubleList<T>::Iterator::operator==(const Iterator& it) const
{
    return ptr == it.ptr;
}

template <typename T>
bool DoubleList<T>::Iterator::operator!=(const Iterator& it) const
{
    return ptr != it.ptr;
}

template <typename T>
DoubleList<T>::DoubleList() : head(nullptr), tail(nullptr){}

template <typename T>
DoubleList<T>::DoubleList(size_t size, T val) : head(nullptr), tail(nullptr)
{
    for (size_t i = 0; i < size; ++i)
    {
        push_back(val);
    }
}

template <typename T>
DoubleList<T>::DoubleList(const std::initializer_list<T>& list) : head(nullptr), tail(nullptr)
{
    for (T elem : list)
    {
        push_back(elem);
    }
}

template <typename T>
DoubleList<T>::DoubleList(const DoubleList& list) : head(nullptr), tail(nullptr)
{
    copy(list);
}

template <typename T>
DoubleList<T>::DoubleList(DoubleList&& list) : head(nullptr), tail(nullptr)
{
    copy(std::move(list));
}

template <typename T>
DoubleList<T>::~DoubleList()
{
    clear();
}

template <typename T>
void DoubleList<T>::push_front(T val)
{
    if (head)
    {
        head->prev = new Node(val);
        head->prev->next = head;
        head = head->prev;
    }

    else
    {
        head = new Node(val);
        tail = head;
    }
}

template <typename T>
void DoubleList<T>::push_back(T val)
{
    if (tail)
    {
        tail->next = new Node(val);
        tail->next->prev = tail;
        tail = tail->next;
    }

    else
    {
        head = new Node(val);
        tail = head;
    }
}

template <typename T>
void DoubleList<T>::pop_front()
{
    if (head == tail)
    {
        delete head;
        head = nullptr;
        tail = nullptr;
    }

    else
    {
        head = head->next;
        delete head->prev;
        head->prev = nullptr;
    }
}

template <typename T>
void DoubleList<T>::pop_back()
{
    if (head == tail)
    {
        delete head;
        head = nullptr;
        tail = nullptr;
    }

    else
    {
        tail = tail->prev;
        delete tail->next;
        tail->next = nullptr;
    }
}

template <typename T>
typename DoubleList<T>::Iterator DoubleList<T>::insert(Iterator it, const T& val)
{
    if (it.ptr == head)
    {
        push_front(val);
    }

    else if (!(it.ptr))
    {
        push_back(val);
    }

    else
    {
        Node* prev = it.ptr->prev;
        Node* new_node = new Node(val);
        prev->next = new_node;
        it.ptr->prev = new_node;

        new_node->next = it.ptr;
        new_node->prev = prev;
    }

    return it;
}

template <typename T>
typename DoubleList<T>::Iterator DoubleList<T>::insert(Iterator it, const std::initializer_list<T>& list)
{
    for (T elem : list)
    {
        it = insert(it, elem);
    }

    return it;
}

template <typename T>
typename DoubleList<T>::Iterator DoubleList<T>::erase(Iterator it)
{
    if (it.ptr == head)
    {
        pop_front();
        return Iterator(head);
    }

    else if (it.ptr == tail)
    {
        pop_back();
        return Iterator(tail);
    }

    Node* prev = it.ptr->prev;
    Node* next = it.ptr->next;

    prev->next = next;
    next->prev = prev;
    
    delete it.ptr;
    return Iterator(next);
}

template <typename T>
typename DoubleList<T>::Iterator DoubleList<T>::erase(Iterator start, Iterator end)
{
    for (; start != end;)
    {
        start = erase(start);
    }
    
    return start;
}

template <typename T>
void DoubleList<T>::copy(const DoubleList& list)
{
    clear();

    for (Iterator it = list.begin(); it != list.end(); ++it)
    {
        push_back(*it);
    }
}

template <typename T>
void DoubleList<T>::copy(DoubleList&& list)
{
    clear();

    head = list.head;
    tail = list.tail;

    list.head = nullptr;
    list.tail = nullptr;
}

template <typename T>
void DoubleList<T>::clear()
{
    while (head)
    {
        Node* tmp_next = head->next;
        
        delete head;

        head = tmp_next; 
    }

    tail = nullptr;
}

template <typename T>
void DoubleList<T>::reverse()
{
    Node* node = head;
    while (node)
    {
        std::swap(node->prev, node->next);
        node = node->prev;
    }

    std::swap(head, tail);
}

template <typename T>
void DoubleList<T>::swap(DoubleList<T>& list)
{
    std::swap(head, list.head);
    std::swap(tail, list.tail);
}

template <typename T>
typename DoubleList<T>::Iterator DoubleList<T>::begin() const
{
    return Iterator(head);
}

template <typename T>
typename DoubleList<T>::Iterator DoubleList<T>::end() const
{
    return Iterator(nullptr);
}

template <typename T>
bool DoubleList<T>::empty() const
{
    return !head;
}

template <typename T>
size_t DoubleList<T>::size() const
{
    size_t size = 0;
    
    Node* node = head;
    while (node)
    {
        ++size;
        node = node->next;
    }

    return size;
}