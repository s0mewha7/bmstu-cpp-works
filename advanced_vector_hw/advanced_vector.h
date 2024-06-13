#pragma once
#include <cassert>
#include <cstdlib>
#include <new>
#include <stdexcept>
#include <algorithm>
#include <sstream>
#include <vector>
#include <utility>

#include "raw_memory.h"

/*
           _______      __     _   _  _____ ______ _____   __      ________ _____ _______ ____  _____
     /\   |  __ \ \    / /\   | \ | |/ ____|  ____|  __ \  \ \    / /  ____/ ____|__   __/ __ \|  __ \
    /  \  | |  | \ \  / /  \  |  \| | |    | |__  | |  | |  \ \  / /| |__ | |       | | | |  | | |__) |
   / /\ \ | |  | |\ \/ / /\ \ | . ` | |    |  __| | |  | |   \ \/ / |  __|| |       | | | |  | |  _  /
  / ____ \| |__| | \  / ____ \| |\  | |____| |____| |__| |    \  /  | |___| |____   | | | |__| | | \ \
 /_/    \_\_____/   \/_/    \_\_| \_|\_____|______|_____/      \/   |______\_____|  |_|  \____/|_|  \_\

*/

namespace bmstu {
template <typename Type>
class advanced_vector {
 public:
    struct iterator {
        using iterator_category = std::random_access_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = Type;
        using pointer = Type *;
        using reference = Type &;
        explicit iterator(pointer ptr) : m_ptr(ptr) {}
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
        // Pointer
     private:
        pointer m_ptr;
    };
    using const_iterator = const iterator;

    advanced_vector() noexcept = default;

    // WTF?? WHY IT DOESNT WORKS WITHOUT CONSTEXPR!?!!?
    explicit advanced_vector(size_t size) : size_(size), data_(size) {
        if constexpr (std::is_default_constructible_v<Type>) {
            std::uninitialized_value_construct_n(data_.get_address(), size);
        }
    }

    // Destructor
    ~advanced_vector() {
        if (size_ != 0) {
            std::destroy_n(data_.get_address(), size_);
        }
    }

    advanced_vector(const advanced_vector &other) : data_(other.size_), size_(other.size_) {
        std::uninitialized_copy_n(other.data_.get_address(), other.size_, this->data_.get_address());
    }

    advanced_vector(advanced_vector &&dying) noexcept :
            data_(std::move(dying.data_)),
            size_(std::move(dying.size_)) {
        dying.size_ = 0;
    }

    [[nodiscard]] size_t size() const noexcept {
        return size_;
    }

    [[nodiscard]] size_t capacity() const noexcept {
        return data_.capacity();
    }

    advanced_vector(std::initializer_list<Type> ilist) : data_(ilist.size()), size_(ilist.size()) {
        if constexpr (std::is_nothrow_move_constructible_v<Type> || !std::is_copy_constructible_v<Type>) {
            std::uninitialized_move_n(ilist.begin(), ilist.size(), data_.get_address());
        } else {
            std::uninitialized_copy_n(ilist.begin(), ilist.size(), data_.get_address());
        }
    }

    void clear() {
        size_ = 0;
    }

    advanced_vector& operator=(const advanced_vector &other) {
        if (this != &other) {
            if (other.size_ > data_.capacity()) {
                advanced_vector other_copy(other);
                this->swapping(other_copy);  // Copy-and-Swap idiom
            } else {
                if (other.size_ < size_) {
                    std::copy_n(other.data_.get_address(), other.size_, data_.get_address());
                    std::destroy_n(data_.get_address() + other.size_, size_ - other.size_);
                } else {
                    std::copy_n(other.data_.get_address(), size_, data_.get_address());
                    std::uninitialized_copy_n(other.data_.get_address() + size_, other.size_ - size_,
                                              data_.get_address() + size_);
                }
            }
            size_ = other.size_;
        }
        return *this;
    }

    advanced_vector &operator=(advanced_vector &&other) noexcept {
        if (this != &other) {
            data_ = std::move(other.data_);
            size_ = other.size_;
            other.size_ = 0;
        }
        return *this;
    }

    // Iterators
    const_iterator begin() const noexcept {
        return const_iterator(const_cast<advanced_vector&>(*this).begin());
    }

    const_iterator end() const noexcept {
        return const_iterator(const_cast<advanced_vector&>(*this).end());
    }

    const_iterator cbegin() const noexcept {
        return const_cast<advanced_vector&>(*this).begin();
    }

    const_iterator cend() const noexcept {
        return const_cast<advanced_vector&>(*this).end();
    }

    void Swap(advanced_vector& other) noexcept {
        std::swap(data_, other.data_);
        std::swap(size_, other.size_);
    }

    // Iterators
    iterator begin() {
        return iterator(data_.get_address());
    }

    iterator end() {
        return iterator(data_.get_address() + size_);
    }

    typename iterator::reference operator[](size_t index) noexcept {
        return *(data_ + index);
    }

    typename const_iterator::reference operator[](size_t index) const noexcept {
        return const_cast <typename const_iterator::reference> (*(data_ + index));
    }

    typename iterator::reference at(size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Index out of range! Need another index < size of vector");
        }
        return *(data_ + index);
    }

    typename const_iterator::reference at(size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("Index out of range! Need another index < size of vector");
        }

        return *(data_ + index);
    }

    [[nodiscard]] bool empty() const noexcept {
        return size_ == 0;
    }

    friend void swap(advanced_vector &lhs,  advanced_vector &rhs) {
        lhs.swap(rhs);
    }

    void resize(size_t new_size) {
        if (new_size > size_) {
            if (new_size > data_.capacity()) {
                reserve(new_size);
            }
            if constexpr (std::is_default_constructible_v<Type>) {
                std::uninitialized_value_construct_n(data_.get_address() + size_, new_size - size_);
            } else {
                for (size_t index = size_; index < new_size; ++index) {
                    new (data_.get_address() + index) Type(0);
                }
            }
            size_ = new_size;
        } else if (new_size < size_) {
            std::destroy_n(data_.get_address() + new_size, size_ - new_size);
            size_ = new_size;
        }
    }

    void reserve(size_t new_capacity) {
        if (new_capacity <= data_.capacity()) {
            return;
        }
        raw_memory<Type> new_data(new_capacity);
        if constexpr (std::is_nothrow_move_constructible_v<Type> || !std::is_copy_constructible_v<Type>) {
            std::uninitialized_move_n(data_.get_address(), size_, new_data.get_address());
        } else {
            std::uninitialized_copy_n(data_.get_address(), size_, new_data.get_address());
        }
        std::destroy_n(data_.get_address(), size_);
        data_.swap(std::move(new_data));
    }

    template<typename... Args>
    Type &emplace_back(Args &&... args) {
        if (size_ == data_.capacity()) {
            auto new_capacity = (size_ == 0) ? 1 : size_ * 2;
            this->reserve(new_capacity);
        }
        new(data_.get_address() + size_)Type(std::forward<Args>(args)...);
        ++size_;
        return data_[size_ - 1];
    }

    template<typename... Args>
    iterator emplace(const_iterator pos, Args &&... args) {
        iterator res_pos = begin();
        if (pos == cend()) {
            push_back(std::forward<Args>(args)...);
            res_pos = end() - 1;
        } else if (size_ == data_.capacity()) {
            auto new_capacity = (size_ == 0) ? 1 : size_ * 2;
            raw_memory<Type> new_data(new_capacity);
            const size_t dest_pos = pos - begin();
            new(new_data.get_address() + dest_pos)Type(std::forward<Args>(args)...);
            if constexpr (std::is_nothrow_move_constructible_v<Type> || !std::is_copy_constructible_v<Type>) {
                std::uninitialized_move_n(data_.get_address(), dest_pos, new_data.get_address());
            } else {
                try {
                    std::uninitialized_copy_n(data_.get_address(), dest_pos, new_data.get_address());
                } catch (...) {
                    std::destroy_n(new_data.get_address() + dest_pos, 1);
                    throw;
                }
            }
            if constexpr (std::is_nothrow_move_constructible_v<Type> || !std::is_copy_constructible_v<Type>) {
                std::uninitialized_move_n(data_.get_address() + dest_pos, size_ - dest_pos,
                                          new_data.get_address() + dest_pos + 1);
            } else {
                try {
                    std::uninitialized_copy_n(data_.get_address() + dest_pos,
                                              size_ - dest_pos, new_data.get_address() + dest_pos + 1);
                } catch (...) {
                    std::destroy_n(new_data.get_address() + dest_pos, 1);
                    throw;
                }
            }
            std::destroy_n(data_.get_address(), size_);
            data_.swap(std::move(new_data));
            res_pos = begin() + dest_pos;
            ++size_;
        } else {
            Type tmp(std::forward<Args>(args)...);
            new(data_.get_address() + size_) Type(std::move(data_[size_ - 1]));
            res_pos = begin() + (pos - begin());
            std::move_backward(res_pos, end() - 1, end());
            *res_pos = std::move(tmp);
            ++size_;
        }
        return res_pos;
    }

    iterator erase(const_iterator pos) {
        iterator res_it = begin() + (pos - begin());
        std::move(res_it + 1, end(), res_it);
        std::destroy_n(end() - 1, 1);
        --size_;
        return res_it;
    }

    template<typename iType>
    void insert(const_iterator pos, iType &&value) {
        emplace(pos, std::forward<iType>(value));
    }

    template<typename pType>
    void push_back(pType &&value) {
        emplace_back(std::forward<pType>(value));
    }

    void pop_back() noexcept {
        assert(size_ != 0);
        std::destroy_at(data_.get_address() + --size_);
    }

    // Bool operators
    bool operator==(const advanced_vector &other) const {
        if (size_ != other.size_) {
            return false;
        }
        for (size_t i = 0; i < size_; ++i) {
            if (data_[i] != other.data_[i]) {
                return false;
            }
        }
        return true;
    }

    friend std::ostream &operator<<(std::ostream &os, const advanced_vector<Type> &other) {
        os << "[";
        for (size_t i = 0; i < other.size(); ++i) {
            os << other[i];
            if (i < other.size() - 1) {
                os << ", ";
            }
        }
        os << "]";
        return os;
    }


 private:
    static bool lexicographical_compare_(const advanced_vector<Type> &left, const advanced_vector<Type> &right) {
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

    size_t create_new_data() {
        size_t new_capacity = size_;
        size_ == 0 ? ++new_capacity : new_capacity = size_ * 2;
        return new_capacity;
    }

    void copy_or_move(const raw_memory<Type>& new_data, size_t from, size_t quantity, size_t dest_from) {
        if constexpr (std::is_nothrow_move_constructible_v<Type> || !std::is_copy_constructible_v<Type>) {
            std::uninitialized_move_n(data_.get_address() + from, quantity, new_data.get_address() + dest_from);
        } else {
            std::uninitialized_copy_n(data_.get_address() + from, quantity, new_data.get_address() + dest_from);
        }
    }

    void refill(const raw_memory<Type> &new_data) {
        copy_or_move(new_data, 0, size_, 0);
        replace_memory(new_data);
    }

    void swapping(const advanced_vector<Type> &other) {
        std::swap(*this, other);
    }

    void replace_memory(const raw_memory<Type> &new_data) {
        // Destroy elements of data_
        std::destroy_n(data_.get_address(), size_);
        // Remove old raw memory, swapping with new
        data_.swap(new_data);
    }
    size_t size_ = 0;
    raw_memory<Type> data_;
};
}  // namespace bmstu
