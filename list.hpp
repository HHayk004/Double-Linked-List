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
    ptr = it->ptr;

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