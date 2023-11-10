#pragma once

#include <iostream>
#include <cstddef>

// порнушка ) писать 4 символа вместо 1 - это не круто
#define SIZE 1

namespace bmstu {
    template<class T>
    class basic_string;

    typedef basic_string<char> string; // это наш обычный однобайтный string
    typedef basic_string<wchar_t> wstring; // это наш двухбайтный string
    typedef basic_string<char8_t> u8string; // это наш однобайтный string для UTF-8
    typedef basic_string<char16_t> u16string; // это наш двухбайтный string для UTF-16
    typedef basic_string<char32_t> u32string; // это наш четырехбайтный string для UTF-32

    template<class T>
    class basic_string {
    public:
        /// Конструктор по умолчанию
        basic_string() {
            ptr_ = new T[SIZE];
            *ptr_ = static_cast<T>('\0');
            size_ = 0;
        }

        /// По-хорошему могли бы и сами реализовать, но пусть будет так
        basic_string(std::initializer_list<T> list) {
            size_ = list.size();
            ptr_ = new T[size_ + 1];
            copy_(ptr_, list.begin(), size_);
        }

        basic_string(size_t size) {
            size_ = size;
            ptr_ = new T[size_ + 1];
            ptr_[size_] = static_cast<T>('\0');
        }

        /// Конструктор с параметром "cи строкой"
        /// тут была ошибка !  basic_string(const char *c_str) -> basic_string(const T *c_str)
        basic_string(const T *c_str) {
            size_ = strlen_(c_str);
            if (size_ != 0) {
                ptr_ = new T[size_ + 1];
                ptr_[size_] = static_cast<T>('\0');
                copy_(ptr_, c_str, size_);
            } else {
                ptr_ = new T[SIZE];
                *ptr_ = static_cast<T>('\0');
                size_ = 0;
            }
        }

        /// Копирующий конструктор
        basic_string(const basic_string &other) {
            size_ = other.size_;
            ptr_ = new T[size_ + 1];
            copy_(ptr_, other.ptr_, size_);
        }

        /// Конструктор перемещения
        basic_string(basic_string &&dying) noexcept {
            size_ = dying.size_;
            ptr_ = dying.ptr_;

            dying.ptr_ = nullptr;
            dying.size_ = 0;
        }

        /// Деструктор
        ~basic_string() { clean_(); }

        /// Геттер на си-строку
        const T *c_str() const { return ptr_; }

        /// Геттер на размер
        size_t size() const { return size_; }

        /// Оператор копирующего присваивания
        basic_string &operator=(const basic_string &other) {
            if (this != &other) { // Проверка на самоприсваивание
                clean_(); // Очищаем текущие ресурсы
                size_ = other.size_;
                ptr_ = new T[size_ + 1];
                copy_(ptr_, other.ptr_, size_);
            }
            return *this; // Возвращаем *this для поддержки цепочки присваиваний
        }

        /// Оператор перемещающего присваивания
        basic_string &operator=(basic_string &&other) {
            if (this != &other) {
                clean_();
                size_ = other.size_;
                ptr_ = new T[size_ + 1];
                other.size_ = 0;
                other.ptr_ = nullptr;
            }
            return *this;
        }

        /// Оператор присваивания си строки
        basic_string &operator=(const char *c_str) {
            if (c_str != nullptr) {
                clean_();
                size_ = strlen_(c_str);
                ptr_ = new T[size_ + 1];
                copy_(ptr_, c_str, size_);
            } else {
                clean_();
            }

            return *this;
        }

        /// Оператор конкатенации
        friend bmstu::basic_string<T>
        operator+(const bmstu::basic_string<T> &left, const bmstu::basic_string<T> &right) {
            bmstu::basic_string<T> output;
            output.size_ = left.size_ + right.size_;
            output.ptr_ = new T[output.size_ + 1];

            left.copy_(output.ptr_, left.ptr_, left.size_);
            left.copy_(output.ptr_ + left.size_, right.ptr_, right.size_);
            output.ptr_[output.size_] = static_cast<T>('\0');

            return output;
        }

        /// А теперь жуть ostream для вывода 1 байтного string
        /// wstream для вывода 2 байтного string
        /// u8stream для вывода 1 байтного string для UTF-8
        /// u16stream для вывода 2 байтного string для UTF-16

        /// Оператор вывода std::basic_ostream<T> и почему система типов сработает
        /// и сматчит типы std::ostream и std::basic_ostream<char> ... можете погуглить
        /// почему так происходит и почему так сделано, в следущем семестре узнаем
        /// ПОЛНОЦЕННОЕ ООП 2 семестр
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
                    break;  // Прекращаем считывание при пробеле, новой строке или табуляции
                }
                obj += input_char; // Добавляем символ к обьекту
            }
            return is;
        }

        /// Перегрузка оператора +=
        basic_string &operator+=(const basic_string &other) {
            int new_size = size_ + other.size_;
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

        /// тут T
        basic_string &operator+=(T symbol) {
            int new_size = size_ + 1;
            T *new_ptr = new T[new_size + 1];

            copy_(new_ptr, ptr_, size_);
            new_ptr[size_] = symbol;
            new_ptr[new_size] = static_cast<T>('\0');

            delete[] ptr_;  // Освобождаем старую память
            ptr_ = new_ptr;  // Обновляем указатель
            size_ = new_size;  // Обновляем размер

            return *this;
        }

        // Нахождение значения по индексу
        T &operator[](size_t index) {
            return ptr_[index];
        }

    private:
        static size_t strlen_(const T *str) {
            size_t length = 0;
            while (str[length] != '\0') {
                length++;
            }
            return length;
        }

        static void copy_(T *destintaion, const T *current_c, size_t length) {
            for (size_t i = 0; i < length; ++i) {
                destintaion[i] = current_c[i];
            }
            destintaion[length] = '\0';
        }

        void clean_() {
            size_ = 0;
            ptr_ = nullptr;
            delete[] ptr_;
        }

        //// КАКОЙ БЛИН char
        T *ptr_ = nullptr;
        size_t size_;

    };
}
