#pragma once

#include <iostream>
#include <cstddef>
#define SIZE 1

namespace bmstu {
template <class T> class string {
    public:
        /// Конструктор по умолчанию
        string() {
            ptr_ = new T[SIZE];
            *ptr_ = static_cast<T>('\0');
            size_ = 0;
        }

        /// Конструктор с параметром "cи строкой"
        string(const char *c_str) {
            size_ = strlen_(c_str);
            if(size_!= 0){
                ptr_ = new T[size_ + 1];
                ptr_[size_] = static_cast<T>('\0');
                copy_(ptr_,  c_str, size_);
            }
            else{
                ptr_ = new T[SIZE];
                *ptr_ = static_cast<T>('\0');
                size_ = 0;
            }
        }

        /// Копирующий конструктор
        string(const string &other) {
            size_ = other.size_;
            ptr_ = new T[size_ + 1];
            copy_(ptr_,  other.ptr_, size_);
        }

        /// Конструктор перемещения
        string(string &&dying) noexcept {
            size_ = dying.size_;
            ptr_ = dying.ptr_;

            dying.ptr_ = nullptr;
            dying.size_ = 0;
        }

        /// Деструктор
        ~string() { clean_();}

        /// Геттер на си-строку
        const char *c_str() const { return ptr_; }

        /// Геттер на размер
        size_t size() const { return size_;}

        /// Оператор копирующего присваивания
        string &operator=(const string &other) {
            if(this != &other){ // Проверка на самоприсваивание
                clean_(); // Очищаем текущие ресурсы 
                size_ = other.size_;
                ptr_ = new T[size_ + 1];
                copy_(ptr_, other.ptr_, size_); 
            }
            return *this; // Возвращаем *this для поддержки цепочки присваиваний
        }

        /// Оператор перемещающего присваивания
        string &operator=(string &&other) {
            if(this != &other){
                clean_();
                size_ = other.size_;
                ptr_ = new T[size_ + 1];
                other.size_ = 0;
                other.ptr_ = nullptr;
            }
            return *this;
        }

        /// Оператор присваивания си строки
        string &operator=(const char *c_str) {
            if(c_str != nullptr){
                clean_();
                size_ = strlen_(c_str);
                ptr_ = new T[size_ + 1];
                copy_(ptr_, c_str, size_);
            }
            else{
                clean_();
            }

            return *this;
        }

        /// Оператор конкатенации
        friend bmstu::string<T> operator+(const bmstu::string<T> &left, const bmstu::string<T> &right) {
            bmstu::string<T> output;
            output.size_ = left.size_ + right.size_;
            output.ptr_ = new T[output.size_ + 1];

            left.copy_(output.ptr_, left.ptr_, left.size_);
            left.copy_(output.ptr_ + left.size_, right.ptr_, right.size_);
            output.ptr_[output.size_] = static_cast<T>('\0');

            return output;
        }   

        /// Оператор вывода
        friend std::ostream &operator<<(std::ostream &os, const string &obj) {
            os << obj.ptr_;
            return os;
        }

        /// Перегрузка оператора >>
        friend std::istream &operator>>(std::istream &is, string &obj) {
            obj.clean_(); // Используем функцию clean_ для очистки содержимого

            char input_char;
            while(is.get(input_char)){
                if (input_char == ' ' || input_char == '\n' || input_char == '\t') {
                    break;  // Прекращаем считывание при пробеле, новой строке или табуляции
                }
                obj += input_char; // Добавляем символ к обьекту
            }
            return is;
        }

        /// Перегрузка оператора +=
        string &operator+=(const string &other) {
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

        string &operator+=(char symbol) {
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
        char &operator[](size_t index) {
            if(index < size_){
                return ptr_[index];
            }
            else{
                static T nullchar = '\0';
                return nullchar;
            }
        }
        
    private:
        static size_t strlen_(const char *str) {
            size_t length = 0;
            while(str[length] != '\0'){
                length++; 
            }
            return length;
        }
        static void copy_(T *destintaion,  const T *current_c, size_t length){
            for(size_t i = 0; i < length; ++ i){
                destintaion[i] = current_c[i];
            }
            destintaion[length] = '\0';       
        }
        void clean_() {
            size_ = 0;
            ptr_ = nullptr;
            delete[] ptr_;
        }
        char *ptr_ = nullptr;
        size_t size_;

    };
}