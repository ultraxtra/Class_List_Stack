#include <iostream>

using namespace std;

template<typename T>
class tlist {
    struct node {
        node* prev;
        node* next;
        T     val;
        node(const T& v) :prev(NULL), next(NULL), val(v) {}
    };
private:
    node* head, * tail;
    size_t cnt;
public:
    tlist(void) :head(NULL), tail(NULL), cnt(0) {}
    ~tlist() { clear(); }
public:
    virtual void push(const T& val) = 0;
    virtual void pop(void) = 0;
protected:

    void push_front(const T& val) {
        node* p = new node(val);
        if (head == NULL)
            head = tail = p;
        else {
            head->prev = p;
            p->next = head;
            head = p;
        }
        ++cnt;
    }

    void push_back(const T& val) {
        node* p = new node(val);
        if (head == NULL)
            head = tail = p;
        else {
            p->prev = tail;
            tail = tail->next = p;
        }
        ++cnt;
    }

    void pop_front(void) {
        node* t;
        if (head != NULL) {
            t = head;
            head = head->next;
            delete t;
            if (head != NULL)
                head->prev = NULL;
            else
                tail = NULL;
            --cnt;
        }
    }

    void pop_back(void) {
        node* t;
        if (tail != NULL) {
            t = tail;
            tail = tail->prev;
            delete t;
            if (tail != NULL)
                tail->next = NULL;
            else
                head = NULL;
            --cnt;
        }
    }
public:
    void clear(void) {
        while (head != NULL)
            pop_front();
        cnt = 0;
    }

    bool empty(void)  const { return (head == NULL); }
    size_t size(void) const { return cnt; }

    const T& peek(void) const { return head->val; }
    T& peek(void) { return head->val; }
};

template<typename T>
class tstack : public tlist<T> {
public:
    virtual void push(const T& val) { tlist<T>::push_front(val); }
    virtual void pop(void) { tlist<T>::pop_front(); }
};

template<typename T>
class tqueue : public tlist<T> {
public:
    virtual void push(const T& val) { tlist<T>::push_back(val); }
    virtual void pop(void) { tlist<T>::pop_front(); }
};

int main(void) {
    tstack<char> s;
    for (char c = 'A'; c <= 'Z'; ++c)
        s.push(c);
    for (; !s.empty(); s.pop())
        cout << s.peek();
    cout << std::endl;

    tqueue<int> q;
    for (int i = 0; i < 10; ++i)
        q.push(i);
    for (; !q.empty(); q.pop())
        cout << q.peek() << ' ';
    cin.get();
    return 0;
}