#ifndef CIRCLE_LIST_HPP
#define CIRCLE_LIST_HPP

#include <iostream>
#include <stdexcept>
#include <initializer_list>
#include <cstddef>

template <typename T>
class Circle_list {
private:
    struct Node {
        T data;       // шаблонное значение
        Node* next;   // ссылка на следующий узел

        explicit Node(const T& value)
            : data(value), next(nullptr) {}
        explicit Node(T&& value)
            : data(std::move(value)), next(nullptr) {}
    };

    Node* head = nullptr;   // указатель на первый элемент
    Node* tail = nullptr;   // указатель на последний элемент
    std::size_t size = 0;   // количество элементов

public:
    // Конструкторы
    Circle_list() = default;

    Circle_list(std::initializer_list<T> init) {
        for (auto& x : init) {
            append(x);
        }
    }

    // Конструктор копирования
    Circle_list(const Circle_list& other) {
        for (auto& x : other) {
            append(x);
        }
    }

    // Конструктор перемещения
    Circle_list(Circle_list&& other) noexcept
        : head(other.head), tail(other.tail), size(other.size)
    {
        other.head = nullptr;
        other.tail = nullptr;
        other.size = 0;
    }

    // Деструктор
    ~Circle_list() {
        clear();
    }

    // Присваивание копированием
    Circle_list& operator=(const Circle_list& other) {
        if (this != &other) {
            clear();
            for (auto& x : other) {
                append(x);
            }
        }
        return *this;
    }

    // Присваивание перемещением
    Circle_list& operator=(Circle_list&& other) noexcept {
        if (this != &other) {
            clear();
            head = other.head;
            tail = other.tail;
            size = other.size;

            other.head = nullptr;
            other.tail = nullptr;
            other.size = 0;
        }
        return *this;
    }

    // Проверка на пустоту
    [[nodiscard]] bool empty() const noexcept {
        return size == 0;
    }

    // Получить размер
    [[nodiscard]] std::size_t get_size() const noexcept {
        return size;
    }

    // Очистка списка (удаляет все узлы)
    void clear() {
        if (!head) return;

        // Если только один узел, просто удалить его
        if (size == 1) {
            delete head;
            head = tail = nullptr;
            size = 0;
            return;
        }

        // чтобы можно было пройти весь список линейно
        tail->next = nullptr;

        Node* cur = head;
        while (cur) {
            Node* next = cur->next;
            delete cur;
            cur = next;
        }

        head = tail = nullptr;
        size = 0;
    }

    // Добавить в конец
    void append(const T& value) {
        Node* node = new Node(value);
        if (empty()) {
            head = tail = node;
            node->next = node;  
        } else {
            node->next = head;
            tail->next = node;
            tail = node;
        }
        ++size;
    }

    void append(T&& value) {
        Node* node = new Node(std::move(value));
        if (empty()) {
            head = tail = node;
            node->next = node;
        } else {
            node->next = head;
            tail->next = node;
            tail = node;
        }
        ++size;
    }

    // Добавить в начало
    void prepend(const T& value) {
        Node* node = new Node(value);
        if (empty()) {
            head = tail = node;
            node->next = node;
        } else {
            node->next = head;
            head = node;
            tail->next = head;  
        }
        ++size;
    }

    void prepend(T&& value) {
        Node* node = new Node(std::move(value));
        if (empty()) {
            head = tail = node;
            node->next = node;
        } else {
            node->next = head;
            head = node;
            tail->next = head;
        }
        ++size;
    }

    // Удалить первый элемент
    void remove_first() {
        if (empty()) {
            throw std::out_of_range("List is empty");
        }

        if (size == 1) {
            delete head;
            head = tail = nullptr;
            size = 0;
            return;
        }

        Node* old_head = head;
        head = head->next;
        tail->next = head;  
        delete old_head;
        --size;
    }

    // Доступ к первому элементу
    [[nodiscard]] T& front() {
        if (empty()) {
            throw std::out_of_range("List is empty");
        }
        return head->data;
    }
    [[nodiscard]] const T& front() const {
        if (empty()) {
            throw std::out_of_range("List is empty");
        }
        return head->data;
    }

    // Доступ к последнему элементу
    [[nodiscard]] T& back() {
        if (empty()) {
            throw std::out_of_range("List is empty");
        }
        return tail->data;
    }
    [[nodiscard]] const T& back() const {
        if (empty()) {
            throw std::out_of_range("List is empty");
        }
        return tail->data;
    }

    // Итераторы 
    class Iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = std::remove_cv_t<T>;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        Iterator(Node* cur, Node* head_ptr, bool done_flag)
            : current(cur), head(head_ptr), done(done_flag) {}

        reference operator*() const {
            return current->data;
        }
        pointer operator->() const {
            return &current->data;
        }

        Iterator& operator++() {
            if (current->next == head) {
                done = true;  
            }
            current = current->next;
            return *this;
        }

        Iterator operator++(int) {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        bool operator==(const Iterator& other) const {
            return (done == other.done && current == other.current);
        }
        bool operator!=(const Iterator& other) const {
            return !(*this == other);
        }

    private:
        Node* current;
        Node* head;
        bool done;
    };

    [[nodiscard]] Iterator begin() const {
        if (empty()) {
            return end();
        }
        return Iterator(head, head, false);
    }

    [[nodiscard]] Iterator end() const {
        if (empty()) {
            return Iterator(nullptr, nullptr, true);
        }
        return Iterator(head, head, true);
    }

    // поэлементнотое сравнение
    [[nodiscard]] bool operator==(const Circle_list& other) const { 
    if (size != other.size) return false;

    auto it1 = begin();
    auto it2 = other.begin();
    auto e1  = end();
    auto e2  = other.end();

    while (it1 != e1 && it2 != e2) {
        if (*it1 != *it2) return false;
        ++it1;
        ++it2;
    }
    return true; 
    }

};

#endif 
