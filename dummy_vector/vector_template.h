#pragma once

#include <iostream>
#include "array_bundle.h"

namespace bmstu{
    template <typename Type>
    class vector{
        public:
            struct iterator{
                using iterator_category = std::random_access_iterator_tag;
                using difference_type = std::ptrdiff_t;
                using value_type = Type;
                using pointer = Type *;
                using reference = Type &;

                iterator(pointer ptr) : m_ptr(ptr){}
                
                reference operator*() const{
                    return *m_ptr;
                }

                pointer operator->(){
                    return m_ptr;
                }

                iterator &operator++(){
                    ++m_ptr;
                    return *this;
                }

                iterator &operator--(){
                    --m_ptr;
                    return *this;
                }

                iterator &operator=(const iterator &other){
                    this->m_ptr = other.m_ptr;
                    return m_ptr;
                }

                // Оператор инкремента (post-increment)
                iterator operator++(int){
                    iterator temp = *this;
                    ++(*this);
                    return temp;
                }

                iterator operator--(int){
                    iterator temp = *this;
                    --(*this);
                    return temp;
                }

                friend bool operator==(const iterator &a, const iterator &b){
                    return (a.m_ptr == b.m_ptr);
                }

                friend bool operator!=(const iterator &a, const iterator &b){
                    return (a.m_ptr != b.m_ptr);
                }

                friend difference_type operator-(const iterator &a, const iterator &b){
                    return a.m_ptr - b.m_ptr;
                }

                iterator &operator+(size_t n) noexcept{
                    m_ptr += n;
                    return *this;
                }

                iterator &operator-(size_t n) noexcept{
                    m_ptr -= n;
                    return *this;
                }
            private:
                pointer m_ptr; 
        };

        using const_iterator = const iterator;
        vector() noexcept = default;
        vector(size_t size, const Type &value = Type{}) : size_(size), capacity_(size), data_(size){
            auto first = begin(), last = end();
            for(; first != last; ++first){
                *first = value;
            }
        }
        /// Конструктор копирования
        vector(const vector<Type> &other): size_(other.size()), capacity_(other.capacity()), data_(size_){
            std::copy(other.begin(),  other.end(), begin());
        }

        /// Конструктор перемещения
        vector(vector<Type> &&other){
            this->swap(other);
        }

        /// Конструктор через initializer_list
        vector(std::initializer_list <Type> ilist): size_(ilist.size()), capacity_(ilist.size()), data_(ilist.size()){
            std::copy(ilist.begin() , ilist.end(),  begin());
        }

        /// Очистка нашего вектора от элементов
        void clear() noexcept{
            size_ = 0;
        }
        /// Оператор копирующего присваивания
        vector &operator=(vector <Type> &other){
            if (this != &other) {
                if (other.empty()) {
                    clear();
                } else {
                    bmstu::vector<Type> copied(other);
                    this->swap(copied);
                }
            }
            return *this;
        }
        /// Оператор перемещающего присваивания(move assignment operator)
        vector &operator=(vector<Type> &&other){
            if(this == &other){
                return *this;
            }
            size_ = other.size_;
            capacity_ = other.capacity_;
            data_ = std::move(other.data_);
            other.size_ = 0;
            other.capacity_ = 0;
            return *this;
        }

        /// All Iterators
        iterator begin() noexcept{
            return data_.Get();
        }

        iterator end() noexcept{
            return data_.Get() + size_;
        }

        const_iterator begin() const noexcept{
            return data_.Get();
        }

        const_iterator end() const noexcept{
            return data_.Get() + size_;
        }

        typename iterator::reference operator[](size_t index){
            return data_[index];
        }

        typename const_iterator::reference operator[](size_t index) const noexcept{
            return const_cast<typename const_iterator::reference>(data_[index]);
        }
        
        typename iterator::reference at(size_t index){
            if(index > size_){
                throw std::out_of_range("Index out of range!");
            }
            return data_[index];
        }

        typename const_iterator::reference at(size_t index) const{
            if(index > size_){
                throw std::out_of_range("Index out of range!");
            }
            return const_cast<typename const_iterator::reference>(data_[index]);
        }

        size_t size() const noexcept { return size_; }

        size_t capacity() const noexcept{ return capacity_; }

        bool empty() const noexcept{
            return (size_ == 0);
        }

        void swap(vector<Type> &other){
            if(this == &other){
                return;
            }
            std::swap(size_, other.size_);
            std::swap(capacity_, other.capacity_);
            data_.swap(other.data_);
        }

        friend void swap(vector<Type> &lhs, vector<Type> &rhs) {
            if (&lhs == &rhs) {
                return;
            }
            std::swap(lhs.size_, rhs.size_);  
            std::swap(lhs.capacity_, rhs.capacity_);
            lhs.data_.swap(rhs.data_); 
        }
        
        void resize(size_t new_size){
            if(new_size > capacity_){
                reserve(new_size);
            }
            size_ = new_size;
        }

        void reserve(size_t new_capacity){
            if(new_capacity > capacity_){
                // Создаем временный объект с новой емкостью
                array_bundle<Type> new_data(new_capacity);

                for(std::size_t i = 0; i < size_; ++i){
                    new_data[i] = data_[i];
                }

                data_.swap(new_data);

                capacity_ = new_capacity;
            }
        }
        iterator insert(const_iterator pos, Type &&value) {
            size_t n = pos - begin();
            if (capacity_ == 0) {
                reserve(1);
            }
            if (size_ == capacity_) {
                capacity_ *= 2;
            }
            array_bundle<Type> tmp(capacity_);
            Type *tmp_ptr = tmp.Get();
            for (auto first = begin(); first != begin() + n; ++first, ++tmp_ptr) {
                *tmp_ptr = std::move(*first);
            }

            tmp.Get()[n] = std::move(value);
            tmp_ptr = tmp.Get() + n + 1;
            for (auto first = begin() + n; first != end(); ++first, ++tmp_ptr) {
                *tmp_ptr = std::move(*first);
            }
            data_.swap(tmp);
            size_++;
            return begin() + n;
        }

        iterator insert(const_iterator pos, const Type &value){
            Type copied  = value;
            return insert(pos, std::move(copied));
        }

        void push_back(const Type &value){
            Type temp = value;
            push_back(std::move(temp));
        }

        void push_back(Type &&value){
            insert(end(), std::move(value));
        }

        void pop_back() noexcept{
            if(!empty()){
                --size_;
            }
        }

        friend bool operator==(const vector<Type> &l, const vector<Type> &r){
            if(l.size_ == r.size_){
                for(auto fl = l.begin(), fr = r.begin(); fl != l.end(); ++fl, ++fr){
                    if(*fl != *fr){
                        return false;
                    }
                }
                return true;
            }
            return false;
        }

        friend bool operator!=(const vector<Type> &l, const vector<Type> &r){
            return !(l == r);
        }

        friend bool operator<(const vector<Type> &l, const vector<Type> &r){
            return lexicographical_compare_(l , r);
        }

        friend bool operator>(const vector<Type> &l, const vector<Type> &r){
            return (r < l);
        }

        friend bool operator<=(const vector<Type> &l, const vector<Type> &r){
            return !(r < l);
        }

        friend bool operator>=(const vector<Type> &l, const vector<Type> &r){
            return !(l < r);
        }

        friend std::ostream &operator<<(std::ostream &os, const vector<Type> &other){
            os << "[";
            if(other.size_){
                for(std::size_t i = 0; i < other.size_ - 1; ++i){
                    os << other[i] << ", ";
                }
                os << other[other.size_ - 1];
            }
            os << "]";
            return os;
        }

        private:
            static bool lexicographical_compare_(const vector<Type> &l, const vector<Type> &r) {
                auto fl = l.begin(),  fr = r.begin();
                for(; (fl !=  l.end()) && (fr !=  r.end()); ++fl, ++fr){
                    if(*fr < *fr){
                        return true;
                    }
                    if(*fr < *fl){
                        return false;
                    }
                }
                return ((fr != r.end()) && (fl == l.end()));
            }
            size_t size_ = 0;
            size_t capacity_ = 0;
            array_bundle<Type> data_;
    };
}