#include <iostream>
template<typename T, typename Cmp>

class CPriorQueue {
private:
    T* arr;
    size_t num;
    size_t cnt;
    Cmp    cmp;
public:
    CPriorQueue(void) :arr(nullptr), num(0), cnt(0) {}
    explicit CPriorQueue(const T* _f, const T* _l) :arr(nullptr), num(0), cnt(0) {
        copy(_f, _l);
    }

    CPriorQueue(CPriorQueue&& q) noexcept {
        *this = std::forward<decltype(q)>(q);
    }

    ~CPriorQueue() { clear(); }

    CPriorQueue(const CPriorQueue&) = delete;
    CPriorQueue& operator = (const CPriorQueue&) = delete;
public:
    //добавить
    void push1(const T& val) {
        _set_alloc(1);

        arr[cnt++] = val;
        size_t   i = cnt - 1;
        size_t   p = (i - 1) >> 1;

        while ((i > 0) && cmp(val, arr[p])) {
            std::swap(arr[i], arr[p]);
            i = p;
            p = (p - 1) >> 1;
        }
    }

    //вытолкнуть
    void pop(void) {
        if (cnt > 0) {
            arr[0] = arr[--cnt];
            _heapify(0);
        }
    }

    //копировать массив
    void copy(const T* _f, const T* _l) {
        if (_f >= _l)
            return;

        size_t n = static_cast<size_t>(_l - _f);
        _set_alloc(n);

        cnt = n;
        for (T* p = arr; _f != _l; ++_f)
            *p++ = *_f;

        for (size_t i = (cnt >> 1) + 1; i > 0; --i)
            _heapify(i - 1);
    }

    //очистка
    void clear(void) {
        if (arr != nullptr)
            delete[] arr;
        arr = nullptr;
        cnt = num = 0;
    }

    T& top(void) const { return arr[0]; }
    T& top(void) { return arr[0]; }

    size_t size(void) const {
        return cnt;
    }

    bool empty(void) const {
        return (cnt == 0);
    }

    CPriorQueue& operator = (CPriorQueue&& q) noexcept {
        if (this != &q) {
            arr = q.arr;
            cnt = q.cnt;
            num = q.num;
            q.arr = nullptr;
            q.cnt = q.num = 0;
        }
        return *this;
    }

private:

    void _set_alloc(size_t n) {
        T* tmp;
        size_t tnum;
        if (arr == NULL) {
            tnum = (n == 1) ? 16 : n;
            arr = new T[tnum];
            num = tnum;
        }
        else if ((cnt + n) > num) {
            tnum = cnt + n + (num >> 1);
            tmp = new T[tnum];

            T* i = tmp, * e = arr + cnt;
            for (T* p = arr; p != e; ++p)
                *i++ = *p;

            delete[] arr;
            arr = tmp;
            num = tnum;
        }
    }

    void _heapify(size_t i) {
        size_t r, l, h;
        while (1) {
            l = (i << 1) + 1;
            r = l + 1;
            if ((l < cnt) && cmp(arr[l], arr[i]))
                h = l;
            else
                h = i;

            if ((r < cnt) && cmp(arr[r], arr[h]))
                h = r;

            if (h != i) {
                std::swap(arr[h], arr[i]);
                i = h;
            }
            else
                break;
        }
    }
};

//от большего к меньшему
template<typename T> struct hcmp {
    bool operator () (const T& a, const T& b) const {
        return (a > b);
    }
};

//от меньшему к большему
template<typename T> struct lcmp {
    bool operator () (const T& a, const T& b) const {
        return (a < b);
    }
};

int main(void) {
    int a[] = { 3, 4, 9, 7, 8, 2, 0, 1, 6 };
    CPriorQueue<int, hcmp<int> > pq1;

    for (int i : a)
        pq1.push1(i);

    while (!pq1.empty()) {
        std::cout << pq1.top() << ' ';
        pq1.pop();
    }
    std::cout << std::endl;

    CPriorQueue<int, lcmp<int> > pq2(std::cbegin(a), std::cend(a));

    while (!pq2.empty()) {
        std::cout << pq2.top() << ' ';
        pq2.pop();
    }
    std::cout << std::endl;
    std::cin.get();
    return 0;
}