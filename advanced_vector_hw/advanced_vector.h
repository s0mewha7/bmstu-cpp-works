#pragma once
#include <cassert>
#include <cstdlib>
#include <new>
#include <stdexcept>
#include <algorithm>
#include <sstream>
#include "raw_memory.h"
#include <vector>

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
        // Iterator
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
        private:
            pointer m_ptr;

        };

        using const_iterator = const iterator;
        advanced_vector() noexcept = default;
        explicit advanced_vector(size_t size) : size_(size), data_(size) {
            std::uninitialized_value_construct_n(data_.get_address(), size);
        }

        // Destructor
        ~advanced_vector() {
            std::destroy_n(data_.GetAddress(), size_);
        }

        advanced_vector(const advanced_vector &other) : data_(other.size_), size_(other.size_){
            std::uninitialized_copy_n(other.data_.get_address(), other.size_, data_.get_address());
        }

        advanced_vector(advanced_vector &&other) noexcept : data_(std::move(other.data_)), size_(std::move(other.size_)){
            other.size_ = 0;
        }

        [[nodiscard]] size_t size() const noexcept {
            return size_;
        }

        [[nodiscard]] size_t capacity() const noexcept {
            return data_.capacity();
        }

        advanced_vector(std::initializer_list<Type> ilist) : data_(ilist.size()), size_(ilist.size()) {
            std::copy(ilist.begin(), ilist.end(), begin());
        }

        void clear() {
            size_ = 0;
        }

        advanced_vector& operator=(const advanced_vector &other) {
            if (this != &other) {
                if (other.size_ > data_.capacity()) {
                    advanced_vector other_copy(other);
                    Swap(other_copy);
                }
                else {
                    if (other.size_ < size_) {
                        std::copy_n(other.data_.GetAddress(), other.size_, data_.GetAddress());
                        std::destroy_n(data_.GetAddress() + other.size_, size_ - other.size_);
                    }
                    else {
                        std::copy_n(other.data_.GetAddress(), size_, data_.GetAddress());
                        std::uninitialized_copy_n(other.data_.GetAddress() + size_, other.size_ - size_, data_.GetAddress() + size_);
                    }
                }
                size_ = other.size_;
            }
            return *this;
        }

        advanced_vector &operator=(advanced_vector &&other) noexcept {
            if (this != &other) {
                data_.swap(other.data_);
                std::swap(size_, other.size_);
            }
            return *this;
        }

        const_iterator begin() const noexcept {
            return const_cast<advanced_vector&>(*this).begin();
        }

        const_iterator end() const noexcept {
            return const_cast<advanced_vector&>(*this).end();
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
            return data_.get_address();
        }

        iterator end() {
            return data_.get_address() + size_;
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
            if (new_size == size_) {
                return;
            }
            if (new_size > size_) {
                reserve(new_size);
                std::uninitialized_value_construct_n(data_.get_address() + size_, new_size - size_);
                size_ = new_size;
            }
            else {
                std::destroy_n(data_.get_address() + new_size, size_ - new_size);
                size_ = new_size;
            }
        }

        void reserve(size_t new_capacity) {
            if (new_capacity <= data_.capacity()) {
                return;
            }
            raw_memory<Type> new_data(new_capacity);
            refill(new_data);
        }

        template<typename ... Args>
        Type &emplace_back(Args &&... args) {
            if (size_ == capacity()) {
                raw_memory<Type> new_data(create_new_data());
                new (new_data + size_) Type(std::forward<Args>(args)...);
                refill(new_data);
            }
            else {
                new(data_ + size_) Type(std::forward<Args>(args)...);
            }
            ++size_;
            return data_[size_ - 1];
        }

        template<typename ... Args>
        iterator emplace(const_iterator pos, Args &&... args) {
            size_t position = pos - cbegin();
            if (size_ == capacity()) {
                raw_memory<Type> new_data(create_new_data());
                new (new_data + position) Type(std::forward<Args>(args)...);
                size_t quantity = position;
                copy_or_move(new_data, 0, quantity, 0);
                quantity = size_ - position;
                copy_or_move(new_data, position, quantity, position + 1);
                replace_memory(new_data);
            }
            else {
                if (pos == cend()) {
                    new(end()) Type(std::forward<Args>(args)...);
                }
                else{
                    if (end() != begin()) {
                        Type temp(std::forward<Args>(args)...);
                        new(end()) Type(std::forward<Type>(*(end() - 1)));
                        std::move_backward(begin() + position, end() - 1, end());
                        data_[position] = std::forward<Type>(temp);
                    }
                    else {
                        new (data_.GetAddress()) Type(std::forward<Args>(args)...);
                    }
                }
            }
            ++size_;
            return begin() + position;
        }

        iterator erase(const_iterator pos) {
            iterator res_it = begin() + (pos - begin());
            std::move(res_it + 1, end() ,res_it);
            std::destroy_n(end() - 1, 1);
            --size_;
            return res_it;
        }

        template<typename iType>
        iterator insert(const_iterator pos, Type &&value) {
            return emplace(pos, std::forward<Type>(value));
        }

        template<typename pType>
        void push_back(Type &&value) {
            emplace_back(std::forward<Type>(value));
        }

        void pop_back() noexcept {
            std::destroy_n(data_.get_address(), size() - 1, 1);
            --size_;
        }

        // Bool operators
        friend bool operator!=(const advanced_vector<Type> &left, const advanced_vector<Type> &right) {
            return !(left == right);
        }
        friend bool operator<(const advanced_vector<Type> &left, const advanced_vector<Type> &right) {
            return lexicographical_compare_(left, right);
        }
        friend bool operator>(const advanced_vector<Type> &left, const advanced_vector<Type> &right) {
            return !(left <= right);
        }
        friend bool operator<=(const advanced_vector<Type> &left, const advanced_vector<Type> &right) {
            return !(right < left);
        }
        friend bool operator>=(const advanced_vector<Type> &left, const advanced_vector<Type> &right) {
            return !(left < right);
        }

        friend std::ostream &operator<<(std::ostream &os, const advanced_vector<Type> &other) {
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

        void copy_or_move(raw_memory<Type>& new_data, size_t from, size_t quantity, size_t dest_from) {
            if constexpr (std::is_nothrow_move_constructible_v<Type> || !std::is_copy_constructible_v<Type>) {
                std::uninitialized_move_n(data_.GetAddress() + from, quantity, new_data.GetAddress() + dest_from);
            }
            else {
                std::uninitialized_copy_n(data_.GetAddress() + from, quantity, new_data.GetAddress() + dest_from);
            }
        }

        void refill(raw_memory<Type> &new_data) {
            copy_or_move(new_data, 0, size_, 0);
            replace_memory(new_data);
        }

        void replace_memory(raw_memory<Type> &new_data) {
            // Destroy elements of data_
            std::destroy_n(data_.get_address(), size_);
            // Remove old raw memory, swapping with new
            data_.swap(new_data);
        }
        size_t size_ = 0;
        raw_memory<Type> data_;
    };
}  // namespace bmstu