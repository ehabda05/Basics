#include <cstddef>
#include <stdexcept>

template<typename T>
class Deque {
  public:
    Deque() : first(nullptr), last(nullptr),sz(0) {}

    ~Deque() {
        clear();
    }

    Deque(const Deque& other) : first(nullptr), last(nullptr), sz(0) {
        Node* cur = other.first;
        while (cur != nullptr) {
            push_back(cur->val);
            cur = cur->next;
        }
    }

    Deque& operator=(const Deque& other) {
        if (this == &other) return *this;

        clear();
        Node* cur = other.first;
        while (cur != nullptr) {
            push_back(cur->val);
            cur = cur->next;
        }

        return *this;
    }

    const T& front() const {
        if (empty()) {
            throw std::out_of_range("Deque empty\n");
        }
        return first->val;
    }

    const T& back() const {
        if (empty()) {
            throw std::out_of_range("Deque empty\n");
        }
        return last->val;
    }

    void push_front(const T& value) {
        Node* newNode = new Node(value);
        if (first == nullptr) {
            first = newNode;
            last = newNode;
        } else {
            first->prev = newNode;
            newNode->next = first;
            first = newNode;
        }
        sz++;
    }

    void push_back(const T& value) {
        Node* newNode = new Node(value);
        if (first == nullptr) {
            first = newNode;
            last = newNode;
        } else {
            newNode->prev = last;
            last->next = newNode;
            last = last->next;
        }
        sz++;
    }

    void pop_front() {
        if (empty()) return;
        Node* oldFirst = first;
        first = first->next;
        if (first != nullptr) first->prev = nullptr;
        delete oldFirst;
        sz--;
        if (sz == 0) last = nullptr;
    }

    void pop_back() {
        if (empty()) return;
        Node* oldLast = last;
        last = last->prev;
        if (last != nullptr) last->next = nullptr;
        delete oldLast;
        sz--;
        if (sz == 0) first = nullptr;
    }

    bool empty() const {
        return (sz == 0);
    }

    void clear() {
        while (!empty()) pop_front();
    }

  private:
    struct Node {
        T val;
        Node* next;
        Node* prev;

        Node(const T&v) : val(v), next(nullptr), prev(nullptr) {}
    };
    Node* first;
    Node* last;
    std::size_t sz;
};