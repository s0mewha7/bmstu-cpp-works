#pragma once
#include <cassert>
#include <cstdlib>
#include <new>
#include <algorithm>

#include "raw_memory.h"


namespace bmstu {
    template <typename T>
    class advanced_vector {
    public:
        using iterator = T*;
        using const_iterator = const T*;

        advanced_vector() = default;

        explicit advanced_vector(size_t size) : data_(size), size_(size) {
            std::uninitialized_value_construct_n(data_.get_address(), size);
        }

        advanced_vector(const advanced_vector& other) {
            std::uninitialized_copy_n(o                                                                                                                                                                                                                                                         ther.data_.get_address(), other.size_, data_.get_address());
        }

        advanced_vector(advanced_vector&& other)  noexcept : data_(std::move(other.data_)), size_(std::move(other.size_)){
            other.size_ = 0;
        }

        [[nodiscard]] size_t Size() const noexcept {
            return size_;
        }

        [[nodiscard]] size_t Capacity() const noexcept {
            return data_.capacity();
        }

        const T& operator[](size_t index) const noexcept {
            return const_cast<advanced_vector&>(*this)[index];
        }

        advanced_vector& operator=(const advanced_vector& rhs) {
            if (this != &rhs) {
                if (rhs.size_ > data_.Capacity()) {
                    advanced_vector rhs_copy(rhs);
                    Swap(rhs_copy);
                }
                else {
                    if (rhs.size_ < size_) {
                        std::copy_n(rhs.data_.GetAddress(), rhs.size_, data_.GetAddress());
                        std::destroy_n(data_.GetAddress() + rhs.size_, size_ - rhs.size_);
                    }
                    else {
                        std::copy_n(rhs.data_.GetAddress(), size_, data_.GetAddress());
                        std::uninitialized_copy_n(rhs.data_.GetAddress() + size_, rhs.size_ - size_, data_.GetAddress() + size_);
                    }
                }
                size_ = rhs.size_;
            }
            return *this;
        }

        // move assingment operator
        advanced_vector& operator=(advanced_vector&& other) noexcept {
            if (this != &other) {
                data_.swap(other.data_);
                std::swap(size_, other.size_);
            }
            return *this;
        }

        void Swap(advanced_vector &other) {
            std::swap(data_, other.data_);
            std::swap(size_, other.size_);
        }
        
    private:
        raw_memory<T> data_;
        size_t size_ = 0;

    };
}