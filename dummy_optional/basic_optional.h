#pragma once

#include <cstdint>
#include <exception>
#include <type_traits>

namespace bmstu {
class bad_optional_access : public std::exception {
 public:
    using exception::exception;
    [[nodiscard]] const char *what() const noexcept override {
        return "Bad optional access";
    }
};
template<typename T>
class optional {
 public:
    optional() = default;

    explicit optional(const T &value) {
        is_initialized_ = true;
        T *val = new(&data_[0]) T{value};
        (void) (&val);
    }

    explicit optional(T &&value) {
        is_initialized_ = true;
        T *val = new(&data_[0]) T(std::move(value));
        (void) (&val);
    }

    //  Operators and etc

    optional(const optional &other) {
        if (other.is_initialized_) {
            is_initialized_ = true;
            T *val = new(&data_[0]) T(other.value());
            (void) &val;
        } else {
            (void) (&data_[0]);
        }
    }

    optional &operator=(const T &value) {
        if (is_initialized_) {
            this->value() = value;
        } else {
            is_initialized_ = true;
            T *val = new(&data_[0]) T(value);
            (void) (&val);
        }
        return *this;
    }

    optional &operator=(const T &&value) {
        if (is_initialized_) {
            this->value() = std::move(value);
        } else {
            is_initialized_ = true;
            T *val = new(&data_[0]) T(std::move(value));
            (void) (&val);
        }
        return *this;
    }

    optional &operator=(const optional &other) {
        if (this != &other) {
            if (is_initialized_ && other.is_initialized_) {
                this->value() = other.value();
            } else if (!is_initialized_ && other.is_initialized_) {
                is_initialized_ = true;
                T *val = new(&data_[0]) T(other.value());
                (void) (&val);
            } else if (is_initialized_ && !other.is_initialized_) {
                this->reset();
            }
        }
        return *this;
    }

    optional &operator=(const optional &&other) {
        if (this != &other) {
            if (is_initialized_ && other.is_initialized_) {
                this->value() = std::move(other.value());
            } else if (!is_initialized_ && other.is_initialized_) {
                is_initialized_ = true;
                T *val = new(&data_[0]) T(std::move(other.value()));
                (void) (&val);
            } else if (is_initialized_ && !other.is_initialized_) {
                this->reset();
            }
        }
        return *this;
    }

    T &operator*() & {
        return *(static_cast<T *>((void *) &data_[0]));
    }

    const T &operator*() const & {
        return *(static_cast<const T *>((void *) &data_[0]));
    }

    T *operator->() {
        return static_cast<T *>((void *) &data_[0]);
    }

    const T *operator->() const {
        return static_cast<const T *>((void *) &data_[0]);
    }

    T &&operator*() && {
        return std::move(reinterpret_cast<T &>(*(T *) &data_[0]));
    }

    T &value() & {
        if (!is_initialized_) {
            throw bad_optional_access();
        }
        return reinterpret_cast<T &>(*(T *) &data_[0]);
    }

    const T &value() const & {
        if (!is_initialized_) {
            throw bad_optional_access();
        }
        return reinterpret_cast<const T &>(*(T *) &data_[0]);
    }

    T &&value() && {
        if (!is_initialized_) {
            throw bad_optional_access();
        }
        return reinterpret_cast<T &&>(*(T *) &data_[0]);
    }

    template<typename ...Args>
    void emplace(Args &&... args) {
        if (is_initialized_) reset();
        is_initialized_ = true;
        T *val = new(&data_[0])T(std::forward<Args>(args)...);
        (void) (&val);
    }

    void reset() {
        if (is_initialized_) {
            static_cast<T *>((void *) &data_[0])->~T();
            is_initialized_ = false;
        }
    }

    //  Destructor
    ~optional() {
        if (is_initialized_) {
            T *pointer = static_cast<T *> ((void *) &data_[0]);
            pointer->~T();
        }
    }

    [[nodiscard]] bool has_value() const {
        return is_initialized_;
    }

 private:
    alignas(T) uint8_t data_[sizeof(T)]{};
    bool is_initialized_ = false;
};
} // namespace bmstu