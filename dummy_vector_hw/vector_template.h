#pragma once

#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>

#include "array_bundle.h"

/*
 _____  _    _ __  __ __  ____     __ __      ________ _____ _______ ____  _____
 |  __ \| |  | |  \/  |  \/  \ \   / / \ \    / /  ____/ ____|__   __/ __ \|  __ \
 | |  | | |  | | \  / | \  / |\ \_/ /   \ \  / /| |__ | |       | | | |  | | |__) |
 | |  | | |  | | |\/| | |\/| | \   /     \ \/ / |  __|| |       | | | |  | |  _  /
 | |__| | |__| | |  | | |  | |  | |       \  /  | |___| |____   | | | |__| | | \ \
 |_____/ \____/|_|  |_|_|  |_|  |_|        \/   |______\_____|  |_|  \____/|_|  \_\
*/


namespace bmstu {
template<typename Type>
class dummy_vector {
 public:
    struct iterator {
        using iterator_category = std::random_access_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = Type;
        using pointer = Type *;
        using reference = Type &;
        explicit iterator(pointer ptr) : m_ptr(ptr) { }
        reference operator*() const {
            return *m_ptr;
        }
        pointer operator->() {
            return m_ptr;
        }
        iterator &operator++() {
            ++m_ptr;
            return *this;
        }
        iterator &operator--() {
            --m_ptr;
            return *this;
        }
        iterator &operator=(const iterator &other) {
            m_ptr = other.m_ptr;
            return *this;
        }
        iterator operator++(int) {
            iterator tmp = *this;
            ++(*this);
            return tmp;
        }
        iterator operator--(int) {
            iterator tmp = *this;
            --(*this);
            return tmp;
        }
        friend bool operator==(const iterator &a, const iterator &b) {
            return a.m_ptr == b.m_ptr;
        }
        friend bool operator==(const iterator &a, const std::nullptr_t &b) {
            return a.m_ptr == b;
        }
        friend bool operator!=(const iterator &a, const iterator &b) {
            return !(a == b);
        }
        friend difference_type operator-(const iterator &a, const iterator &b) {
            return a.m_ptr - b.m_ptr;
        }
        iterator operator+(const difference_type value) noexcept {
            iterator copy(*this);
            copy.m_ptr += value;
            return copy;
        }
        iterator operator-(const difference_type value) noexcept {
            iterator copy(*this);
            copy.m_ptr -= value;
            return copy;
        }

     private:
        pointer m_ptr;
    };
    using const_iterator = const iterator;
    dummy_vector() noexcept = default;
    explicit dummy_vector(size_t size, const Type &value = Type{})
            : size_(size), capacity_(size), data_(size) {
        auto first = begin();
        auto last = end();
        for (; first != last; ++first) {
            *first = value;
        }
    }
    dummy_vector(const dummy_vector<Type> &other)
        : size_(other.size_), capacity_(other.capacity_), data_(other.size_) {
        auto first = begin();
        auto otherfirst = other.begin();
        auto otherlast = other.end();
        for (; otherfirst != otherlast; ++otherfirst, ++first) {
            *first = *otherfirst;
        }
    }

    dummy_vector(dummy_vector<Type> &&other) noexcept {
        this->swap(other);
    }

    dummy_vector(std::initializer_list<Type> ilist)
        : size_(ilist.size()), capacity_(ilist.size()), data_(ilist.size()) {
        std::copy(ilist.begin(), ilist.end(), begin());
    }

    void clear() noexcept {
        size_ = 0;
        capacity_ = 0;
    }

    dummy_vector &operator=(const dummy_vector<Type> &other) {
        if (other.empty()) {
            clear();
            return *this;
        }
        size_ = other.size_;
        capacity_ = other.capacity_;
        auto first = begin();
        auto other_first = other.begin();
        auto other_last = other.end();
        for (; other_first != other_last; ++other_first, ++first) {
            *first = *other_first;
        }
        return *this;
    }

    dummy_vector &operator=(dummy_vector<Type> &&other) {
        this->swap(other);
        return *this;
    }
    dummy_vector operator+(const dummy_vector& other) const {
        dummy_vector result(size_ + other.size_);
        std::move(begin(), end(), result.begin());
        std::move(other.begin(), other.end(), result.begin() + size_);
        return result;
    }
    iterator begin() noexcept {
        return iterator(data_.Get());
    }
    iterator end() noexcept {
        return iterator(data_.Get() + size_);
    }
    iterator begin() const noexcept {
        return iterator(data_.Get());
    }
    iterator end() const noexcept {
        return iterator(data_.Get() + size_);
    }
    const_iterator cbegin() const noexcept {
        return const_iterator(data_.Get());
    }
    const_iterator cend() const noexcept {
        return const_iterator(data_.Get() + size_);
    }
    typename iterator::reference operator[](size_t index) noexcept {
        return data_[index];
    }
    typename const_iterator::reference operator[](size_t index) const noexcept {
        return const_cast<typename const_iterator::reference>(data_[index]);
    }
    typename iterator::reference at(size_t index) {
        return data_[index];
    }
    typename const_iterator::reference at(size_t index) const {
        return const_cast<typename const_iterator::reference>(data_[index]);
    }
    [[nodiscard]] size_t size() const noexcept {
        return size_;
    }
    [[nodiscard]] size_t capacity() const noexcept {
        return capacity_;
    }
    [[nodiscard]] bool empty() const noexcept {
        return (size_ == 0);
    }
    void swap(dummy_vector &other) noexcept {
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
        data_.swap(other.data_);
    }
    friend void swap(dummy_vector<Type> &lhs, dummy_vector<Type> &rhs) {
        lhs.swap(rhs);
    }
    void resize(size_t new_size) {
        if (new_size > capacity_) {
            size_t new_capacity = std::max(new_size, capacity_ * 2);
            reserve(new_capacity);
        }
        if (size_ > new_size) {
            size_ = new_size;
            return;
        }
        for (auto it = end(); it != begin() + new_size; ++it) {
            *it = Type{};
        }
        size_ = new_size;
    }
    void reserve(size_t new_capacity) {
        if (new_capacity > capacity_) {
            new_capacity = std::max(new_capacity, capacity_ * 2);
            array_bundle<Type> new_data(new_capacity);
            for (auto it = begin(), nit = iterator(new_data.Get()); it != end();
                 ++it, ++nit) {
                *nit = std::move(*it);
            }
            data_.swap(new_data);
            capacity_ = new_capacity;
        }
    }
    iterator insert(const_iterator pos, Type &&value) {
        auto n = pos - begin();
        if (capacity_ == 0) {
            reserve(1);
        }
        if (size_ == capacity_) {
            capacity_ *= 2;
        }
        array_bundle<Type> temp(capacity_);
        Type *temp_ptr = temp.Get();
        for (auto first = begin(); first != begin() + n; ++first, ++temp_ptr) {
            *temp_ptr = std::move(*first);
        }
        temp[n] = std::move(value);
        temp_ptr = temp.Get() + n + 1;
        if (n + 1 < size_) {
            for (auto first = begin() + n; first != end(); ++first, ++temp_ptr) {
                *temp_ptr = std::move(*first);
            }
        }
        data_.swap(temp);
        ++size_;
        return begin() + n;
    }
    iterator insert(const_iterator pos, const Type &value) {
        auto n = pos - begin();
        if (capacity_ == 0) {
            reserve(1);
        }
        if (size_ == capacity_) {
            capacity_ *= 2;
        }
        array_bundle<Type> temp(capacity_);
        Type *temp_ptr = temp.Get();
        for (auto first = begin(); first != begin() + n; ++first, ++temp_ptr) {
            *temp_ptr = std::move(*first);
        }
        temp[n] = std::move(value);
        temp_ptr = temp.Get() + n + 1;
        if (++n < size_) {
            for (auto first = begin() + n; first != end(); ++first, ++temp_ptr) {
                *temp_ptr = std::move(*first);
            }
        }
        data_.swap(temp);
        ++size_;
        return begin() + n;
    }
    iterator erase(iterator pos) {
        size_t index = pos - cbegin();
        if (!empty()) {
            std::move(begin() + index + 1, end(), begin() + index);
            --size_;
        }
        return begin() + index;
    }
    void push_back(const Type &value) {
        insert(end(), value);
    }
    void push_back(Type &&value) {
        insert(end(), std::move(value));
    }
    void pop_back() noexcept {
        if (size_ == 0) return;
        (*this)[--size_] = {};
    }
    friend bool operator==(const dummy_vector<Type> &l,
                           const dummy_vector<Type> &r) {
        if (l.size() != r.size()) return false;
        for (auto l_it = l.begin(), r_it = r.begin(); l_it != l.end();
             ++l_it, ++r_it) {
            if (*l_it != *r_it) {
                return false;
            }
        }
        return true;
    }
    friend bool operator!=(const dummy_vector<Type> &left, const dummy_vector<Type> &right) {
        return !(left == right);
    }
    friend bool operator<(const dummy_vector<Type> &left, const dummy_vector<Type> &right) {
        return lexicographical_compare_(left, right);
    }
    friend bool operator>(const dummy_vector<Type> &left, const dummy_vector<Type> &right) {
        return !(left <= right);
    }
    friend bool operator<=(const dummy_vector<Type> &left, const dummy_vector<Type> &right) {
        return !(right < left);
    }
    friend bool operator>=(const dummy_vector<Type> &left, const dummy_vector<Type> &right) {
        return !(left < right);
    }
    friend std::ostream &operator<<(std::ostream &os, const dummy_vector<Type> &other) {
        os << "[ ";
        for (size_t i = 0; i < other.size(); ++i) {
            os << other[i];
            if (i < other.size() - 1) {
                os << ", ";
            }
        }
        os << " ]";
        return os;
    }

 private:
    static bool lexicographical_compare_(const dummy_vector<Type> &left, const dummy_vector<Type> &right) {
        auto fl = left.begin(), fr = right.begin();
        for (; (fl != left.end()) && (fr != right.end()); ++fl, ++fr) {
            if (*fl < *fr) {
                return true;
            }
            if (*fr < *fl) {
                return false;
            }
        }
        return ((fr != right.end()) && (fl == left.end()));
    }
    size_t size_ = 0;
    size_t capacity_ = 0;
    array_bundle<Type> data_;
};
}  // namespace bmstu
