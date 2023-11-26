#pragma once

#include <iostream>
#include <cstddef>
#include <sstream>
#include <fstream>

namespace bmstu {
// Forward declaration of basic_string
template <class T>
class basic_string;

// Typedefs for specific instantiations
typedef basic_string<char> string;
typedef basic_string<wchar_t> wstring;
typedef basic_string<char8_t> u8string;
typedef basic_string<char16_t> u16string;
typedef basic_string<char32_t> u32string;

// Definition of the basic_string template
template <class T>
class basic_string {
 public:
    basic_string() : size_(0), ptr_(new T[1]) {
        ptr_[0] = static_cast<T>('\0');
    }

    [[maybe_unused]] basic_string(std::initializer_list<T> list) {
        size_ = list.size();
        ptr_ = new T[size_ + 1];
        copy_(ptr_, list.begin(), size_);
    }

    explicit basic_string(size_t size) {
        ptr_ = new T[size + 1];
        for (size_t i = 0; i < size; i++) {
            ptr_[i] = static_cast<T>(' ');
        }
        ptr_[size] = static_cast<T>('\0');
        size_ = size;
    }

    /// Конструктор с параметром "cи строкой"
    explicit basic_string(const T *c_str) {
        size_ = strlen_(c_str);
        if (size_ != 0) {
            ptr_ = new T[size_ + 1];
            ptr_[size_] = static_cast<T>('\0');
            copy_(ptr_, c_str, size_);
        }
        else
        {
            ptr_ = new T[1];
            *ptr_ = static_cast<T>('\0');
            size_ = 0;
        }
    }

    /// Копирующий конструктор
    basic_string(const basic_string<T> &other) {
        if (this != &other) {
            clean_();
            size_ = other.size_;
            ptr_ = new T[size_ + 1];
            ptr_[size_] = 0;
            for (size_t i = 0; i < size_; i++) {
                *(ptr_ + i) = other.c_str()[i];
            }
        }
    }

    /// Конструктор перемещения
    basic_string(basic_string<T> &&dying) noexcept {
        clean_();
        ptr_ = dying.ptr_;
        size_ = dying.size_;
        dying.already_moved_();
    }

    /// Деструктор
    ~basic_string() {
        delete[] ptr_;
    }

    /// Геттер на си-строку
    const T *c_str() const {
        return static_cast<const T *>(ptr_);
    }

    /// Геттер на размер
    [[nodiscard]] size_t size() const {
        return size_ ;
    }

    /// Оператор копирующего присваивания
    basic_string &operator=(const basic_string &other) {
        if (this != &other) { // Проверка на самоприсваивание
            clean_(); // Очищаем текущие ресурсы
            size_ = other.size_;
            ptr_ = new T[size_ + 1];
            ptr_[size_] = 0;
            for(size_t i = 0; i < size_; i++) {
                *(ptr_ + i) = other.c_str()[i];
            }
        }
        return *this; // Возвращаем *this для поддержки цепочки присваиваний
    }

    /// Оператор перемещающего присваивания
    basic_string &operator=(basic_string<T> &&other) noexcept {
        if (this != &other) {
            clean_();  // Освобождаем текущие ресурсы
            size_ = other.size_;
            ptr_ = other.ptr_;
            other.already_moved_();
        }
        return *this;
    }

    /// Оператор присваивания си строки
    basic_string &operator=(const T *c_str) {
        if (c_str != nullptr) {
            clean_();
            size_ = strlen_(c_str);
            ptr_ = new T[size_ + 1];
            copy_(ptr_, c_str, size_);
        }
        else {
            clean_();
        }

        return *this;
    }

    /// Оператор конкатенации
    friend bmstu::basic_string<T> operator+(const bmstu::basic_string<T> &left, const bmstu::basic_string<T> &right) {
        bmstu::basic_string<T> output;
        output.size_ = left.size_ + right.size_;
        output.ptr_ = new T[output.size_ + 1];

        left.copy_(output.ptr_, left.ptr_, left.size_);
        left.copy_(output.ptr_ + left.size_, right.ptr_, right.size_);
        output.ptr_[output.size_] = static_cast<T>('\0');

        return output;
    }
    friend std::basic_ostream<T> &operator<<(std::basic_ostream<T> &os, const basic_string &obj) {
        os << obj.ptr_;
        return os;
    }

    /// Перегрузка оператора >>
    friend std::basic_istream<T> &operator>>(std::basic_istream<T> &is, basic_string &obj) {
        obj.clean_(); // Используем функцию clean_ для очистки содержимого
        T input_char;
        while (is.get(input_char)) {
            if (input_char == ' ' || input_char == '\n' || input_char == '\t') {
                break; // Прекращаем считывание при пробеле, новой строке или табуляции
            }
            obj += input_char; // Добавляем символ к обьекту
        }
        return is;
    }

    /// Перегрузка оператора +=
    basic_string &operator+=(const basic_string &other) {
        size_t new_size = size_ + other.size_;
        T *new_ptr = new T[new_size + 1];

        copy_(new_ptr, ptr_, size_);
        copy_(new_ptr + size_, other.ptr_, other.size_);
        new_ptr[new_size] = static_cast<T>('\0');
        // Освобождаем старую память и обновляем указатель и размер
        clean_();
        ptr_ = new_ptr;
        size_ = new_size;

        return *this;
    }
    basic_string &operator+=(T symbol) {
        size_t new_size = size_ + 1;
        T *new_ptr = new T[new_size + 1];

        copy_(new_ptr, ptr_, size_);
        new_ptr[size_] = symbol;
        new_ptr[new_size] = static_cast<T>('\0');

        delete[] ptr_;    // Освобождаем старую память
        ptr_ = new_ptr;   // Обновляем указатель
        size_ = new_size; // Обновляем размер

        return *this;
    }
    // Нахождение значения по индексу
    T &operator[](size_t index) {
        if(index < size_) {
            return *(ptr_ + index);
        }
        throw std::runtime_error("Index out of size");
    }

private:
    static size_t strlen_(const T *str) {
        size_t length = 0;
        while (str[length] != static_cast<T>('\0')) {
            length++;
        }
        return length;
    }

    static void copy_(T *destintaion, const T *current_c, size_t length) {
        for (size_t i = 0; i < length; ++i) {
            destintaion[i] = current_c[i];
        }
        destintaion[length] = static_cast<T>('\0');
    }

    void clean_() {
        size_ = 0;
        ptr_ = nullptr;
        delete[] ptr_;
    }

    void already_moved_() {
        ptr_ = new T[1];
        *ptr_ = static_cast<T>('\0');
        size_ = 0;
    }

    T *ptr_ = nullptr;
    size_t size_;
};
}
