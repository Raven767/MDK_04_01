#include "Queue.h"
#include <iostream>
using namespace N;
template<typename T, typename Cmp>
inline PriorityQueue<T, Cmp>::PriorityQueue(const T* _f, const T* _l)
{
    copy(_f, _l);
}
template<typename T, typename Cmp>
N::PriorityQueue<T, Cmp>::PriorityQueue(PriorityQueue&& q) noexcept
{
    *this = std::forward<decltype(q)>(q);
}

template<typename T, typename Cmp>
N::PriorityQueue<T, Cmp>::~PriorityQueue()
{
    clear();
}

template<typename T, typename Cmp>
void N::PriorityQueue<T, Cmp>::push1(const T& val)
{
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

template<typename T, typename Cmp>
void N::PriorityQueue<T, Cmp>::pop(void)
{
    if (cnt > 0) {
        arr[0] = arr[--cnt];
        _heapify(0);
    }
}

template<typename T, typename Cmp>
void N::PriorityQueue<T, Cmp>::copy(const T* _f, const T* _l)
{
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

template<typename T, typename Cmp>
void N::PriorityQueue<T, Cmp>::clear(void)
{
    if (arr != nullptr)
        delete[] arr;
    arr = nullptr;
    cnt = num = 0;
}

template<typename T, typename Cmp>
T& N::PriorityQueue<T, Cmp>::top(void) const
{
    return arr[0];
    // TODO: вставьте здесь оператор return
}

template<typename T, typename Cmp>
T& N::PriorityQueue<T, Cmp>::top(void)
{
    return arr[0];
    // TODO: вставьте здесь оператор return
}

template<typename T, typename Cmp>
size_t N::PriorityQueue<T, Cmp>::size(void) const
{
    return cnt;
}

template<typename T, typename Cmp>
bool N::PriorityQueue<T, Cmp>::empty(void) const
{
    return (cnt == 0);
}

template<typename T, typename Cmp>
void N::PriorityQueue<T, Cmp>::_set_alloc(size_t n)
{
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

template<typename T, typename Cmp>
void N::PriorityQueue<T, Cmp>::_heapify(size_t i)
{
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

