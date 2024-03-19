#pragma once
#include <cassert>
#include <memory>
#include <utility>


namespace bmstu {
    template <typename rtype>
    class raw_memory {
    public:
        raw_memory() = default;
        explicit raw_memory(size_t size) : capacity_(size), buffer_(allocate_(size)) {}
        raw_memory(const raw_memory&) = delete;
        raw_memory& operator=(const raw_memory& other) = delete;

        ~raw_memory() {
            deallocate_(buffer_);
        }

        raw_memory(const raw_memory&& other)  noexcept : capacity_(std::exchange(other.capacity_, 0)),
        buffer_(std::exchange(other.buffer_,nullptr)) {}

        raw_memory& operator=(raw_memory&& other) noexcept {
            if (buffer_ != nullptr) {
                deallocate_(buffer_);
            }
            buffer_ = std::exchange(other.buffer_, nullptr);
            capacity_ = std::exchange(other.capacity_, 0);

            return *this;
        }

        rtype &operator[](size_t index) noexcept {
            assert(index < capacity_);
            return *(buffer_ + index);
        }

        const rtype& operator[](size_t index) const noexcept {
            return const_cast<raw_memory&>(*this)[index];
        }

        rtype* operator+(size_t offset) noexcept {
            assert(offset <= capacity_);
            return buffer_ + offset;
        }

        const rtype* operator+(size_t offset) const noexcept {
            return const_cast<raw_memory&>(*this) + offset;
        }

        void swap(raw_memory &other) noexcept {
            std::swap(buffer_, other.buffer_);
            std::swap(capacity_, other.capacity_);
        }

        rtype* get_address() noexcept {
            return buffer_;
        }

        const rtype* get_address() const noexcept {
            return buffer_;
        }

        [[nodiscard]] size_t capacity() const {
            return capacity_;
        }

    private:
    // Выделяет сырую память под элементы и возвращает указатель на неё (Аллоцирует память)
    static rtype* allocate_(size_t elements) {
        return elements != 0 ? static_cast<rtype*>(operator new(elements * sizeof(rtype))) : nullptr;
    }
    // Освобождает сырую память, выделенную ранее по адресу buff при помощи allocate_ (деаллоцирует)
    static void deallocate_(rtype* buff) {
        operator delete(buff);
    }
    rtype* buffer_ = nullptr;
    size_t capacity_ = 0;
    };
}

