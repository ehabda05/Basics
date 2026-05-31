#include <cstddef>
#include <stdexcept>

template<typename T>
class Queue {
  public:
    Queue() : first(nullptr), last(nullptr),sz(0) {}

    ~Queue() {
        clear();
    }

    Queue(const Queue& other) : first(nullptr), last(nullptr), sz(0) {
        Node* cur = other.first;
        while (cur != nullptr) {
            push(cur->val);
            cur = cur->next;
        }
    }

    Queue& operator=(const Queue& other) {
        if (this == &other) return *this;

        clear();
        Node* cur = other.first;
        while (cur != nullptr) {
            push(cur->val);
            cur = cur->next;
        }

        return *this;
    }

    const T& front() const {
        if (empty()) {
            throw std::out_of_range("Queue empty\n");
        }
        return first->val;
    }

    void push(const T& value) {
        Node* newNode = new Node(value);
        if (first == nullptr) {
            first = newNode;
            last = newNode;
        } else {
            last->next = newNode;
            last = last->next;
        }
        sz++;
    }

    void pop() {
        if (empty()) return;
        Node* oldFirst = first;
        first = first->next;
        delete oldFirst;
        sz--;
        if (sz == 0) last = nullptr;
    }

    bool empty() const {
        return (sz == 0);
    }

    void clear() {
        while (!empty()) pop();
    }

  private:
    struct Node {
        T val;
        Node* next;

        Node(const T&v) : val(v), next(nullptr) {}
    };
    Node* first;
    Node* last;
    std::size_t sz;
};