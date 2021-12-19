#pragma once
#include <iostream>
#include <conio.h>
#include <stdio.h>

namespace N {
    template<typename T, typename Cmp>
    class PriorityQueue
    {
    private:
        T* arr;
        size_t num;
        size_t cnt;
        Cmp    cmp;
    public:
        PriorityQueue(void) :arr(nullptr), num(0), cnt(0) {};
        explicit PriorityQueue(const T* _f, const T* _l);

        PriorityQueue(PriorityQueue&& q) noexcept;

        ~PriorityQueue();

        PriorityQueue(const PriorityQueue&) = delete;
        PriorityQueue& operator = (const PriorityQueue&) = delete;
    public:
        //добавить
        void push1(const T& val);

        //вытолкнуть
        void pop(void);

        //копировать массив
        void copy(const T* _f, const T* _l);

        //очистка
        void clear(void);
        T& top(void) const;
        T& top(void);

        size_t size(void) const;
        bool empty(void) const;
        PriorityQueue& operator = (PriorityQueue&& q) noexcept {
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

        void _set_alloc(size_t n);

        void _heapify(size_t i);
    };
}


