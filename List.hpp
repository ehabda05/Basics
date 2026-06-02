#ifndef LIST_HPP
#define LIST_HPP

#include <cstddef>
#include <stdexcept>

template<typename T>
class List {
  public:
    List();
    ~List();
    List(const List<T>& other);
    List<T>& operator=(const List<T>& other);
    T& front();
    T& back();
    const T& front() const;
    const T& back() const;
    void push_front(const T& value);
    void push_back(const T& value);
    void pop_front();
    void pop_back();
    void clear();
    bool empty() const;
    std::size_t size() const;
    class Iterator;
    Iterator begin();
    Iterator end();
    void erase(const T& value);
    Iterator erase(Iterator pos);
  private:
    struct Node {
        T val;
        Node* next;
        Node* prev;

        Node(const T& v) : val(v), next(nullptr), prev(nullptr) {}
    };
    Node* head;
    Node* tail;
    std::size_t sz;
};

template<typename T>
class List<T>::Iterator{
  public:
    Iterator(Node* p) : ptr(p) {}
    T& operator*() {
        return ptr->val;
    }
    const T& operator*() const {
        return ptr->val;
    }
    Iterator& operator++() {
        ptr = ptr->next;
        return *this;
    }
    Iterator& operator--() {
        ptr = ptr->prev;
        return *this;
    }
    bool operator==(const Iterator& other) const {
        return ptr == other.ptr;
    }
    bool operator!=(const Iterator& other) const {
        return ptr != other.ptr;
    }

  private:
    Node* ptr;
    friend class List<T>;
};

template<typename T>
List<T>::List() : head(nullptr), tail(nullptr), sz(0) {}

template<typename T>
List<T>::~List() {
    clear();
}

template<typename T>
List<T>::List(const List<T>& other) : head(nullptr), tail(nullptr), sz(0) {
    Node* cur = other.head;
    while (cur != nullptr) {
        push_back(cur->val);
        cur = cur->next;
    }
}

template<typename T>
List<T>& List<T>::operator=(const List<T>& other) {
    if (this == &other) return *this;
    clear();
    Node* cur = other.head;
    while (cur != nullptr) {
        push_back(cur->val);
        cur = cur->next;
    }
    return *this;
}

template<typename T>
T& List<T>::front() {
    if (empty()) {
        throw std::out_of_range("List Empty\n");
    }
    return head->val;
}

template<typename T>
T& List<T>::back() {
    if (empty()) {
        throw std::out_of_range("List Empty\n");
    }
    return tail->val;
}

template<typename T>
const T& List<T>::front() const {
    if (empty()) {
        throw std::out_of_range("List Empty\n");
    }
    return head->val;
}

template<typename T>
const T& List<T>::back() const {
    if (empty()) {
        throw std::out_of_range("List Empty\n");
    }
    return tail->val;
}

template<typename T>
void List<T>::push_front(const T& value) {
    Node* newNode = new Node(value);
    if (empty()) {
        head = newNode;
        tail = newNode;
    } else {
        head->prev = newNode;
        newNode->next = head;
        head = newNode;
    }
    sz++;
}

template<typename T>
void List<T>::push_back(const T& value) {
    Node* newNode = new Node(value);
    if (empty()) {
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    sz++;
}

template<typename T>
void List<T>::pop_front() {
    if (empty()) return;
    Node* oldHead = head;
    head = head->next;

    if (head != nullptr) head->prev = nullptr;
    else tail = nullptr;

    delete oldHead;
    sz--;
}

template<typename T>
void List<T>::pop_back() {
    if (empty()) return;
    Node* oldTail = tail;
    tail = tail->prev;

    if (tail != nullptr) tail->next = nullptr;
    else head = nullptr;

    delete oldTail;
    sz--;
}

template<typename T>
void List<T>::clear() {
    while (!empty()) {
        pop_back();
    }
}

template<typename T>
bool List<T>::empty() const {
    return sz == 0;
}

template<typename T>
void List<T>::erase(const T& value) {
    Node* cur = head;
    while (cur != nullptr && cur->val != value) {
        cur = cur->next;
    }
    if (cur == nullptr) return;

    if (cur == head) {
        pop_front();
    } else if (cur == tail) {
        pop_back();
    } else {
        cur->next->prev = cur->prev;
        cur->prev->next = cur->next;
        delete cur;
        sz--;
    }
}

template<typename T>
std::size_t List<T>::size() const {
    return sz;
}

template<typename T>
typename List<T>::Iterator List<T>::begin() {
    return Iterator(head);
}

template<typename T>
typename List<T>::Iterator List<T>::end() {
    return Iterator(nullptr);
}

template<typename T>
typename List<T>::Iterator List<T>::erase(Iterator pos) {
    Node* cur = pos.ptr;
    if (cur == nullptr) return end();

    Node* nextNode = cur->next;

    if (cur == head) {
        pop_front();
    } else if (cur == tail) {
        pop_back();
    } else {
        cur->prev->next = cur->next;
        cur->next->prev = cur->prev;
        delete cur;
        sz--;
    }

    return Iterator(nextNode);
}

#endif // LIST_HPP