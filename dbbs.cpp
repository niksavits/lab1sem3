#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

template <typename T>  // создаем шаблонную структуру, которая может работать с любыми типами данных
struct Queue {  // определяем структуру очереди
    struct Node {  // внутренний элемент структуры — узел
        T value;  // значение узла, тип которого задается через шаблон
        Node* next;  // указатель на следующий элемент очереди
        Node(const T& val) : value(val), next(nullptr) {}  // конструктор для инициализации узла
    };

    Node* frontNode;  // указатель на передний элемент очереди
    Node* rearNode;   // указатель на задний элемент очереди

    Queue() : frontNode(nullptr), rearNode(nullptr) {}  // конструктор, инициализирующий пустую очередь

    void push(const T& value) {  // метод для добавления элемента в очередь
        Node* newNode = new Node(value);  // создаем новый узел с переданным значением
        if (rearNode) {  // если очередь не пуста
            rearNode->next = newNode;  // текущий последний элемент указывает на новый узел
        }
        rearNode = newNode;  // обновляем указатель на последний элемент очереди
        if (!frontNode) {  // если очередь была пустой
            frontNode = rearNode;  // передний элемент теперь тоже указывает на новый узел
        }
    }

    T pop() {  // метод для удаления и возвращения переднего элемента очереди
        if (frontNode) {  // если очередь не пуста
            Node* temp = frontNode;  // временно сохраняем указатель на передний узел
            T value = frontNode->value;  // сохраняем значение переднего узла
            frontNode = frontNode->next;  // передний узел теперь становится следующим узлом
            if (!frontNode) {  // если очередь теперь пуста
                rearNode = nullptr;  // обновляем указатель на задний узел
            }
            delete temp;  // удаляем старый передний узел
            return value;  // возвращаем значение удаленного узла
        }
        return T();  // если очередь пуста, возвращаем значение по умолчанию для типа T
    }

    T peek() const {  // метод для получения значения переднего элемента без удаления
        return frontNode ? frontNode->value : T();  // если очередь пуста, возвращаем значение по умолчанию
    }

    bool empty() const {  // метод для проверки, пуста ли очередь
        return frontNode == nullptr;  // если указатель на передний элемент равен nullptr, то очередь пуста
    }

    void print() const {  // метод для печати всех элементов очереди
        Node* current = frontNode;  // начинаем с переднего узла
        while (current) {  // пока есть элементы
            cout << current->value << " ";  // выводим значение текущего узла
            current = current->next;  // переходим к следующему узлу
        }
        cout << endl;  // после вывода всех элементов выводим перевод строки
    }

    ~Queue() {  // деструктор для очистки памяти
        while (frontNode) {  // пока в очереди есть элементы
            pop();  // удаляем передний элемент
        }
    }
};

// Пример структуры динамического массива
struct DynamicArray {
    string* data;  // указатель на массив строк
    int capacity;  // текущая емкость массива
    int count;     // текущее количество элементов в массиве

    DynamicArray() : capacity(10), count(0) {  // конструктор, инициализирующий массив с начальной емкостью 10
        data = new string[capacity];  // выделяем память под массив
    }

    void resize() {  // метод для увеличения емкости массива
        capacity *= 2;  // удваиваем емкость
        string* newData = new string[capacity];  // создаем новый массив с удвоенной емкостью
        for (int i = 0; i < count; ++i) {  // копируем старые элементы в новый массив
            newData[i] = data[i];
        }
        delete[] data;  // удаляем старый массив
        data = newData;  // перенаправляем указатель на новый массив
    }

    void add(const string& value) {  // метод для добавления элемента в массив
        if (count == capacity) {  // если массив заполнен
            resize();  // увеличиваем емкость
        }
        data[count++] = value;  // добавляем новый элемент и увеличиваем счетчик
    }
    void insert(int index, const string& value) {
        if (index < 0 || index > count) return;  // проверяем корректность индекса
        if (count == capacity) {
            resize();
        }
        for (int i = count; i > index; --i) {
            data[i] = data[i - 1];
        }
        data[index] = value;
        ++count;
    }
    void remove(int index) {
        if (index < 0 || index >= count) return;  // проверяем корректность индекса
        for (int i = index; i < count - 1; ++i) {
            data[i] = data[i + 1];
        }
        --count;
    }
    void set(int index, const string& value) {  // метод для установки значения по индексу
        if (index < 0 || index >= count) return;  // проверяем, что индекс допустимый
        data[index] = value;  // устанавливаем новое значение
    }

    string get(int index) const {  // метод для получения значения по индексу
        if (index < 0 || index >= count) return "";  // если индекс недопустим, возвращаем пустую строку
        return data[index];  // возвращаем значение по индексу
    }

    int length() const {  // метод для получения текущего размера массива
        return count;
    }

    void print() const {  // метод для печати всех элементов массива
        for (int i = 0; i < count; ++i) {  // проходим по всем элементам
            cout << data[i] << " ";  // выводим каждый элемент
        }
        cout << endl;
    }

    ~DynamicArray() {  // деструктор для освобождения памяти
        delete[] data;  // удаляем массив
    }
};

// Определяем структуру для односвязного списка
struct SinglyLinkedList {
    struct Node {  // узел списка
        string value;  // значение, хранящееся в узле
        Node* next;    // указатель на следующий узел
        Node(const string& val) : value(val), next(nullptr) {}  // конструктор узла
    };

    Node* head;  // указатель на первый элемент списка

    SinglyLinkedList() : head(nullptr) {}  // конструктор, инициализирующий пустой список

    void push_front(const string& value) {  // метод для добавления элемента в начало списка
        Node* newNode = new Node(value);  // создаем новый узел
        newNode->next = head;  // новый узел указывает на текущий первый элемент списка
        head = newNode;  // обновляем указатель на первый элемент
    }

    string pop_front() {  // метод для удаления первого элемента из списка и возвращения его значения
        if (!head) return "";  // если список пуст, возвращаем пустую строку
        Node* temp = head;  // временно сохраняем указатель на текущий первый элемент
        string value = head->value;  // сохраняем значение текущего первого узла
        head = head->next;  // перемещаем указатель на следующий узел
        delete temp;  // освобождаем память удаленного узла
        return value;  // возвращаем значение удаленного узла
    }
    string pop_back() {
    if (!head) return "";
    if (!head->next) {
        string value = head->value;
        delete head;
        head = nullptr;
        return value;
    }
    Node* current = head;
    while (current->next->next) {
        current = current->next;
    }
        string value = current->next->value;
        delete current->next;
        current->next = nullptr;
        return value;
    }
    string get(int index) const {  // метод для получения значения по индексу
        Node* current = head;  // начинаем с первого узла
        int current_index = 0;  // счетчик для текущего индекса
        while (current && current_index < index) {  // перемещаемся по списку, пока не достигнем нужного индекса
            current = current->next;
            current_index++;
        }
        if (current && current_index == index) {  // если узел найден на нужном индексе
            return current->value;  // возвращаем значение узла
        }
        return "";  // если индекс выходит за границы списка, возвращаем пустую строку
    }

    void print() const {  // метод для печати всех элементов списка
        Node* current = head;  // начинаем с первого узла
        while (current) {  // пока есть узлы
            cout << current->value << " ";  // выводим значение текущего узла
            current = current->next;  // переходим к следующему узлу
        }
        cout << endl;
    }
    void remove_by_value(const string& value) {
    if (!head) return;
    if (head->value == value) {
        pop_front();
        return;
    }
    Node* current = head;
    while (current->next && current->next->value != value) {
        current = current->next;
    }
    if (current->next) {
        Node* temp = current->next;
        current->next = current->next->next;
        delete temp;
        }
    }
    void push_back(const string& value) {
        Node* newNode = new Node(value);
        if (!head) {
            head = newNode;
            return;
        }
        Node* current = head;
        while (current->next) {
            current = current->next;
        }
        current->next = newNode;
    }
    bool find_by_value(const string& value) const {
        Node* current = head;
        while (current) {
            if (current->value == value) {
                return true;
            }
            current = current->next;
        }
        return false;
    }
    ~SinglyLinkedList() {  // деструктор для очистки памяти
        while (head) {  // пока в списке есть элементы
            pop_front();  // удаляем первый элемент
        }
    }
};

// Определяем шаблонную структуру для стека
template <typename T>
struct Stack {
    struct Node {  // внутренний элемент стека — узел
        T value;  // значение узла
        Node* next;  // указатель на следующий элемент
        Node(const T& val) : value(val), next(nullptr) {}  // конструктор узла
    };

    Node* topNode;  // указатель на верхний элемент стека

    Stack() : topNode(nullptr) {}  // конструктор, инициализирующий пустой стек

    void push(const T& value) {  // метод для добавления элемента в стек
        Node* newNode = new Node(value);  // создаем новый узел
        newNode->next = topNode;  // новый узел указывает на текущий верхний элемент
        topNode = newNode;  // обновляем указатель на верхний элемент
    }

    T pop() {  // метод для удаления и возвращения верхнего элемента стека
        if (topNode) {  // если стек не пуст
            Node* temp = topNode;  // временно сохраняем указатель на верхний элемент
            T value = topNode->value;  // сохраняем значение верхнего элемента
            topNode = topNode->next;  // перемещаем указатель на следующий элемент
            delete temp;  // освобождаем память удаленного элемента
            return value;  // возвращаем значение удаленного элемента
        }
        return T();  // если стек пуст, возвращаем значение по умолчанию для типа T
    }

    T peek() const {  // метод для получения значения верхнего элемента без его удаления
        return topNode ? topNode->value : T();  // если стек пуст, возвращаем значение по умолчанию
    }

    bool empty() const {  // метод для проверки, пуст ли стек
        return topNode == nullptr;  // если указатель на верхний элемент равен nullptr, стек пуст
    }

    void print() const {  // метод для печати всех элементов стека
        Node* current = topNode;  // начинаем с верхнего элемента
        while (current) {  // пока есть элементы в стеке
            cout << current->value << " ";  // выводим значение текущего элемента
            current = current->next;  // переходим к следующему элементу
        }
        cout << endl;
    }

    ~Stack() {  // деструктор для очистки памяти
        while (topNode) {  // пока в стеке есть элементы
            pop();  // удаляем верхний элемент
        }
    }
};

// Определяем структуру хэш-таблицы
struct HashTable {
    struct Entry {  // внутренний элемент хэш-таблицы — запись
        string key;  // ключ записи
        string value;  // значение записи
        Entry* next;  // указатель на следующую запись в случае коллизии
        Entry(const string& k, const string& v) : key(k), value(v), next(nullptr) {}  // конструктор записи
    };

    static const int SIZE = 100;  // размер хэш-таблицы
    Entry* table[SIZE];  // массив указателей на записи

    HashTable() {  // конструктор, инициализирующий пустую таблицу
        for (int i = 0; i < SIZE; ++i) {
            table[i] = nullptr;  // инициализируем все ячейки таблицы значением nullptr
        }
    }

    int hash_func(const string& key) const {  // хэш-функция для вычисления индекса по ключу
        int hash_value = 0;
        for (char ch : key) {
            hash_value = (hash_value * 31 + ch) % SIZE;  // простая хэш-функция, основанная на символах ключа
        }
        return hash_value;  // возвращаем вычисленное значение хэша
    }

    void hset(const string& key, const string& value) {  // метод для добавления или обновления записи в таблице
        int idx = hash_func(key);  // вычисляем индекс по хэш-функции
        Entry* entry = table[idx];  // получаем список записей по индексу
        while (entry) {  // если по индексу уже есть записи (коллизия)
            if (entry->key == key) {  // если ключ уже существует
                entry->value = value;  // обновляем значение
                return;
            }
            entry = entry->next;  // переходим к следующей записи
        }
        entry = new Entry(key, value);  // если ключа нет, создаем новую запись
        entry->next = table[idx];  // связываем новую запись с текущим списком записей по этому индексу
        table[idx] = entry;  // обновляем таблицу
    }

    string hget(const string& key) const {  // метод для получения значения по ключу
        int idx = hash_func(key);  // вычисляем индекс по хэш-функции
        Entry* entry = table[idx];  // получаем список записей по индексу
        while (entry) {  // ищем запись с нужным ключом
            if (entry->key == key) {
                return entry->value;  // возвращаем найденное значение
            }
            entry = entry->next;  // переходим к следующей записи
        }
        return "";  // если ключ не найден, возвращаем пустую строку
    }

    void hdel(const string& key) {  // метод для удаления записи по ключу
        int idx = hash_func(key);  // вычисляем индекс по хэш-функции
        Entry* entry = table[idx];  // получаем список записей по индексу
        Entry* prev = nullptr;  // указатель на предыдущую запись
        while (entry) {  // ищем запись с нужным ключом
            if (entry->key == key) {
                if (prev) {  // если предыдущая запись существует
                    prev->next = entry->next;  // связываем ее с записью после удаляемой
                } else {  // если удаляемая запись первая в списке
                    table[idx] = entry->next;  // обновляем указатель на первую запись
                }
                delete entry;  // удаляем запись
                return;
            }
            prev = entry;  // обновляем указатель на предыдущую запись
            entry = entry->next;  // переходим к следующей записи
        }
    }

    void print() const {  // метод для печати содержимого хэш-таблицы
        for (int i = 0; i < SIZE; ++i) {  // проходим по каждой ячейке таблицы
            if (table[i]) {  // если в ячейке есть записи
                cout << "Bucket " << i << ": ";  // выводим номер "корзины"
                Entry* entry = table[i];
                while (entry) {  // выводим все записи в этой корзине
                    cout << "[" << entry->key << " : " << entry->value << "] -> ";
                    entry = entry->next;
                }
                cout << "nullptr" << endl;  // указываем конец списка
            }
        }
    }

    ~HashTable() {  // деструктор для очистки памяти
        for (int i = 0; i < SIZE; ++i) {  // проходим по каждой ячейке таблицы
            Entry* entry = table[i];
            while (entry) {  // удаляем все записи в каждой корзине
                Entry* temp = entry;
                entry = entry->next;
                delete temp;
            }
        }
    }
};
// Структура для множества (Set)
struct Set {
    HashTable htable;  // используем хэш-таблицу для хранения элементов множества

    void add(const string& element) {  // метод для добавления элемента в множество
        htable.hset(element, "1");  // добавляем элемент в хэш-таблицу с фиктивным значением "1"
    }

    void remove(const string& element) {  // метод для удаления элемента из множества
        htable.hdel(element);  // удаляем элемент из хэш-таблицы
    }

    bool is_member(const string& element) const {  // метод для проверки, содержится ли элемент в множестве
        return htable.hget(element) != "";  // если элемент присутствует в хэш-таблице, возвращаем true
    }

    void print() const {  // метод для печати всех элементов множества
        cout << "{ ";  // начинаем вывод множества
        for (int i = 0; i < HashTable::SIZE; ++i) {  // проходим по всем "корзинам" хэш-таблицы
            HashTable::Entry* entry = htable.table[i];  // получаем записи в каждой корзине
            while (entry) {  // выводим все ключи (элементы множества)
                cout << entry->key << " ";
                entry = entry->next;
            }
        }
        cout << "}" << endl;  // закрываем вывод множества
    }
};

// Структура для полного бинарного дерева (Complete Binary Tree)
struct CompleteBinaryTree {
    struct Node {  // внутренний элемент дерева — узел
        string value;  // значение узла
        Node* left;  // указатель на левый дочерний узел
        Node* right;  // указатель на правый дочерний узел
        Node(const string& val) : value(val), left(nullptr), right(nullptr) {}  // конструктор узла
    };

    Node* root;  // указатель на корневой узел дерева

    CompleteBinaryTree() : root(nullptr) {}  // конструктор, инициализирующий пустое дерево

    // Метод для вставки узла в дерево в соответствии с правилами полного бинарного дерева
    void insert(const string& value) {
        if (!root) {  // если дерево пустое
            root = new Node(value);  // создаем корневой узел
            return;
        }

        // Используем очередь для уровневого обхода
        Queue<Node*> q;  // создаем очередь для узлов
        q.push(root);  // помещаем корневой узел в очередь

        while (!q.empty()) {  // пока очередь не пуста
            Node* current = q.pop();  // извлекаем узел из очереди

            if (!current->left) {  // если у узла нет левого потомка
                current->left = new Node(value);  // вставляем новый узел слева
                break;
            } else {
                q.push(current->left);  // если левый потомок есть, добавляем его в очередь
            }

            if (!current->right) {  // если у узла нет правого потомка
                current->right = new Node(value);  // вставляем новый узел справа
                break;
            } else {
                q.push(current->right);  // если правый потомок есть, добавляем его в очередь
            }
        }
    }
    bool search(const string& value) const {
        if (!root) return false;
        Queue<Node*> q;
        q.push(root);
        while (!q.empty()) {
            Node* current = q.pop();
            if (current->value == value) return true;
            if (current->left) q.push(current->left);
            if (current->right) q.push(current->right);
        }
        return false;
    }

    // Метод для проверки, является ли дерево полным (полное бинарное дерево)
    bool isFull() const {
        if (!root) return true;  // если дерево пустое, оно считается полным

        // Используем рекурсивную вспомогательную функцию для проверки каждого узла
        return isFullUtil(root);
    }

    bool isFullUtil(Node* node) const {
        if (!node) return true;  // пустое поддерево считается полным

        // Если узел является листом (нет детей)
        if (!node->left && !node->right) return true;

        // Если у узла есть оба потомка, проверяем их рекурсивно
        if (node->left && node->right) {
            return isFullUtil(node->left) && isFullUtil(node->right);
        }

        // Если у узла только один потомок, дерево неполное
        return false;
    }

    // Метод для проверки, является ли дерево полным (complete)
    bool isComplete() const {
        if (!root) return true;  // пустое дерево считается полным

        Queue<Node*> q;  // создаем очередь для узлов
        q.push(root);  // помещаем корневой узел в очередь
        bool end = false;  // флаг, сигнализирующий о том, что после узлов без детей больше не должно быть потомков

        while (!q.empty()) {
            Node* current = q.pop();  // извлекаем узел из очереди

            if (current->left) {  // если есть левый потомок
                if (end) return false;  // если флаг уже установлен, дерево не полное
                q.push(current->left);  // добавляем левого потомка в очередь
            } else {
                end = true;  // если нет левого потомка, устанавливаем флаг
            }

            if (current->right) {  // аналогично для правого потомка
                if (end) return false;
                q.push(current->right);
            } else {
                end = true;
            }
        }

        return true;  // если все проверки пройдены, дерево полное
    }

    // Метод для печати элементов дерева (уровневый обход)
    void print() const {
        if (!root) {  // если дерево пустое
            cout << "Empty Tree." << endl;
            return;
        }

        Queue<Node*> q;  // создаем очередь для узлов
        q.push(root);  // помещаем корневой узел в очередь

        while (!q.empty()) {  // пока очередь не пуста
            Node* current = q.pop();  // извлекаем узел из очереди
            cout << current->value << " ";  // выводим значение узла

            if (current->left) q.push(current->left);  // добавляем левого потомка в очередь
            if (current->right) q.push(current->right);  // добавляем правого потомка в очередь
        }
        cout << endl;
    }

    ~CompleteBinaryTree() {  // деструктор для очистки памяти
        // Очищаем дерево с использованием постордного обхода
        deleteSubtree(root);
    }

    void deleteSubtree(Node* node) {  // рекурсивный метод для удаления поддерева
        if (!node) return;
        deleteSubtree(node->left);  // удаляем левое поддерево
        deleteSubtree(node->right);  // удаляем правое поддерево
        delete node;  // удаляем сам узел
    }
};

// Структура для хранения имени и указателя на хэш-таблицу
struct NamedHashTable {
    string name;  // имя хэш-таблицы
    HashTable* htable;  // указатель на хэш-таблицу
    NamedHashTable* next;  // указатель на следующую именованную хэш-таблицу (для хранения в виде списка)

    NamedHashTable(const string& n) : name(n), htable(new HashTable()), next(nullptr) {}  // конструктор, создающий новую хэш-таблицу с именем
};

// Структуры для хранения имени и указателей на другие структуры данных
// По аналогии с NamedHashTable:
struct NamedStack {  // для стека
    string name;
    Stack<string>* stack;
    NamedStack* next;

    NamedStack(const string& n) : name(n), stack(new Stack<string>()), next(nullptr) {}
};

struct NamedQueue {  // для очереди
    string name;
    Queue<string>* queue;
    NamedQueue* next;

    NamedQueue(const string& n) : name(n), queue(new Queue<string>()), next(nullptr) {}
};

struct NamedSet {  // для множества
    string name;
    Set* set;
    NamedSet* next;

    NamedSet(const string& n) : name(n), set(new Set()), next(nullptr) {}
};

struct NamedLinkedList {  // для односвязного списка
    string name;
    SinglyLinkedList* list;
    NamedLinkedList* next;

    NamedLinkedList(const string& n) : name(n), list(new SinglyLinkedList()), next(nullptr) {}
};

struct NamedDynamicArrayStruct {  // для динамического массива
    string name;
    DynamicArray* array;
    NamedDynamicArrayStruct* next;

    NamedDynamicArrayStruct(const string& n) : name(n), array(new DynamicArray()), next(nullptr) {}
};

struct NamedCompleteBinaryTree {  // для полного бинарного дерева
    string name;
    CompleteBinaryTree* tree;
    NamedCompleteBinaryTree* next;

    NamedCompleteBinaryTree(const string& n) : name(n), tree(new CompleteBinaryTree()), next(nullptr) {}
};

// Структура для хранения списка именованных хэш-таблиц
struct NamedHashTableList {
    NamedHashTable* head;  // указатель на первую хэш-таблицу в списке

    NamedHashTableList() : head(nullptr) {}  // конструктор, инициализирующий пустой список

    HashTable* get(const string& name) const {  // метод для получения хэш-таблицы по имени
        NamedHashTable* current = head;  // начинаем с первой хэш-таблицы
        while (current) {  // проходим по всем таблицам в списке
            if (current->name == name) return current->htable;  // если найдено совпадение по имени, возвращаем хэш-таблицу
            current = current->next;  // переходим к следующей таблице
        }
        return nullptr;  // если таблица не найдена, возвращаем nullptr
    }

    HashTable* create(const string& name) {  // метод для создания новой хэш-таблицы с заданным именем
        HashTable* existing = get(name);  // проверяем, существует ли уже таблица с таким именем
        if (existing) return existing;  // если существует, возвращаем ее
        NamedHashTable* newNode = new NamedHashTable(name);  // создаем новую хэш-таблицу
        newNode->next = head;  // вставляем новую таблицу в начало списка
        head = newNode;  // обновляем указатель на голову списка
        return newNode->htable;  // возвращаем новую таблицу
    }

    ~NamedHashTableList() {  // деструктор для освобождения памяти
        NamedHashTable* current = head;
        while (current) {  // проходим по списку таблиц
            NamedHashTable* temp = current;
            current = current->next;
            delete temp->htable;  // удаляем каждую хэш-таблицу
            delete temp;  // удаляем узел
        }
    }
};

// Структура для списка именованных стеков
struct NamedStackList {
    NamedStack* head;  // указатель на первый стек в списке

    NamedStackList() : head(nullptr) {}  // конструктор, инициализирующий пустой список

    Stack<string>* get(const string& name) const {  // метод для получения стека по имени
        NamedStack* current = head;  // начинаем с первого стека
        while (current) {  // проходим по всем стекам в списке
            if (current->name == name) return current->stack;  // если найден стек с нужным именем, возвращаем его
            current = current->next;  // переходим к следующему стеку
        }
        return nullptr;  // если стек не найден, возвращаем nullptr
    }

    Stack<string>* create(const string& name) {  // метод для создания нового стека с заданным именем
        Stack<string>* existing = get(name);  // проверяем, существует ли стек с таким именем
        if (existing) return existing;  // если существует, возвращаем его
        NamedStack* newNode = new NamedStack(name);  // создаем новый стек
        newNode->next = head;  // вставляем его в начало списка
        head = newNode;  // обновляем указатель на голову списка
        return newNode->stack;  // возвращаем новый стек
    }

    ~NamedStackList() {  // деструктор для освобождения памяти
        NamedStack* current = head;
        while (current) {  // проходим по списку стеков
            NamedStack* temp = current;
            current = current->next;
            delete temp->stack;  // удаляем каждый стек
            delete temp;  // удаляем узел
        }
    }
};

// Структура для списка именованных очередей
struct NamedQueueList {
    NamedQueue* head;  // указатель на первую очередь в списке

    NamedQueueList() : head(nullptr) {}  // конструктор, инициализирующий пустой список

    Queue<string>* get(const string& name) const {  // метод для получения очереди по имени
        NamedQueue* current = head;  // начинаем с первой очереди
        while (current) {  // проходим по всем очередям в списке
            if (current->name == name) return current->queue;  // если найдена очередь с нужным именем, возвращаем ее
            current = current->next;  // переходим к следующей очереди
        }
        return nullptr;  // если очередь не найдена, возвращаем nullptr
    }

    Queue<string>* create(const string& name) {  // метод для создания новой очереди с заданным именем
        Queue<string>* existing = get(name);  // проверяем, существует ли очередь с таким именем
        if (existing) return existing;  // если существует, возвращаем ее
        NamedQueue* newNode = new NamedQueue(name);  // создаем новую очередь
        newNode->next = head;  // вставляем ее в начало списка
        head = newNode;  // обновляем указатель на голову списка
        return newNode->queue;  // возвращаем новую очередь
    }

    ~NamedQueueList() {  // деструктор для освобождения памяти
        NamedQueue* current = head;
        while (current) {  // проходим по списку очередей
            NamedQueue* temp = current;
            current = current->next;
            delete temp->queue;  // удаляем каждую очередь
            delete temp;  // удаляем узел
        }
    }
};

// Структура для списка именованных множеств
struct NamedSetList {
    NamedSet* head;  // указатель на первое множество в списке

    NamedSetList() : head(nullptr) {}  // конструктор, инициализирующий пустой список

    Set* get(const string& name) const {  // метод для получения множества по имени
        NamedSet* current = head;  // начинаем с первого множества
        while (current) {  // проходим по всем множествам в списке
            if (current->name == name) return current->set;  // если найдено множество с нужным именем, возвращаем его
            current = current->next;  // переходим к следующему множеству
        }
        return nullptr;  // если множество не найдено, возвращаем nullptr
    }

    Set* create(const string& name) {  // метод для создания нового множества с заданным именем
        Set* existing = get(name);  // проверяем, существует ли множество с таким именем
        if (existing) return existing;  // если существует, возвращаем его
        NamedSet* newNode = new NamedSet(name);  // создаем новое множество
        newNode->next = head;  // вставляем его в начало списка
        head = newNode;  // обновляем указатель на голову списка
        return newNode->set;  // возвращаем новое множество
    }

    ~NamedSetList() {  // деструктор для освобождения памяти
        NamedSet* current = head;
        while (current) {  // проходим по списку множеств
            NamedSet* temp = current;
            current = current->next;
            delete temp->set;  // удаляем каждое множество
            delete temp;  // удаляем узел
        }
    }
};

// Структура для списка именованных односвязных списков
struct NamedLinkedListList {
    NamedLinkedList* head;  // указатель на первый список в списке

    NamedLinkedListList() : head(nullptr) {}  // конструктор, инициализирующий пустой список

    SinglyLinkedList* get(const string& name) const {  // метод для получения списка по имени
        NamedLinkedList* current = head;  // начинаем с первого списка
        while (current) {  // проходим по всем спискам в списке
            if (current->name == name) return current->list;  // если найден список с нужным именем, возвращаем его
            current = current->next;  // переходим к следующему списку
        }
        return nullptr;  // если список не найден, возвращаем nullptr
    }

    SinglyLinkedList* create(const string& name) {  // метод для создания нового списка с заданным именем
        SinglyLinkedList* existing = get(name);  // проверяем, существует ли список с таким именем
        if (existing) return existing;  // если существует, возвращаем его
        NamedLinkedList* newNode = new NamedLinkedList(name);  // создаем новый список
        newNode->next = head;  // вставляем его в начало списка
        head = newNode;  // обновляем указатель на голову списка
        return newNode->list;  // возвращаем новый список
    }
    ~NamedLinkedListList() {  // деструктор для освобождения памяти
        NamedLinkedList* current = head;
        while (current) {  // проходим по списку списков
            NamedLinkedList* temp = current;
            current = current->next;
            delete temp->list;  // удаляем каждый список
            delete temp;  // удаляем узел
        }
    }
};

// Структура для списка именованных динамических массивов
struct NamedDynamicArrayList {
    NamedDynamicArrayStruct* head;  // указатель на первый массив в списке

    NamedDynamicArrayList() : head(nullptr) {}  // конструктор, инициализирующий пустой список

    DynamicArray* get(const string& name) const {  // метод для получения массива по имени
        NamedDynamicArrayStruct* current = head;  // начинаем с первого массива
        while (current) {  // проходим по всем массивам в списке
            if (current->name == name) return current->array;  // если найден массив с нужным именем, возвращаем его
            current = current->next;  // переходим к следующему массиву
        }
        return nullptr;  // если массив не найден, возвращаем nullptr
    }

    DynamicArray* create(const string& name) {  // метод для создания нового массива с заданным именем
        DynamicArray* existing = get(name);  // проверяем, существует ли массив с таким именем
        if (existing) return existing;  // если существует, возвращаем его
        NamedDynamicArrayStruct* newNode = new NamedDynamicArrayStruct(name);  // создаем новый массив
        newNode->next = head;  // вставляем его в начало списка
        head = newNode;  // обновляем указатель на голову списка
        return newNode->array;  // возвращаем новый массив
    }

    ~NamedDynamicArrayList() {  // деструктор для освобождения памяти
        NamedDynamicArrayStruct* current = head;
        while (current) {  // проходим по списку массивов
            NamedDynamicArrayStruct* temp = current;
            current = current->next;
            delete temp->array;  // удаляем каждый массив
            delete temp;  // удаляем узел
        }
    }
};

// Структура для списка именованных полных бинарных деревьев
struct NamedCompleteBinaryTreeList {
    NamedCompleteBinaryTree* head;  // указатель на первое дерево в списке

    NamedCompleteBinaryTreeList() : head(nullptr) {}  // конструктор, инициализирующий пустой список

    CompleteBinaryTree* get(const string& name) const {  // метод для получения дерева по имени
        NamedCompleteBinaryTree* current = head;  // начинаем с первого дерева
        while (current) {  // проходим по всем деревьям в списке
            if (current->name == name) return current->tree;  // если найдено дерево с нужным именем, возвращаем его
            current = current->next;  // переходим к следующему дереву
        }
        return nullptr;  // если дерево не найдено, возвращаем nullptr
    }

    CompleteBinaryTree* create(const string& name) {  // метод для создания нового дерева с заданным именем
        CompleteBinaryTree* existing = get(name);  // проверяем, существует ли дерево с таким именем
        if (existing) return existing;  // если существует, возвращаем его
        NamedCompleteBinaryTree* newNode = new NamedCompleteBinaryTree(name);  // создаем новое дерево
        newNode->next = head;  // вставляем его в начало списка
        head = newNode;  // обновляем указатель на голову списка
        return newNode->tree;  // возвращаем новое дерево
    }

    ~NamedCompleteBinaryTreeList() {  // деструктор для освобождения памяти
        NamedCompleteBinaryTree* current = head;
        while (current) {  // проходим по списку деревьев
            NamedCompleteBinaryTree* temp = current;
            current = current->next;
            delete temp->tree;  // удаляем каждое дерево
            delete temp;  // удаляем узел
        }
    }
};

// Структура для хранения массива токенов (строк), полученных после разбиения строки на слова
struct TokenArray {
    string* tokens;  // динамический массив строк (токенов)
    int capacity;    // текущая емкость массива
    int count;       // текущее количество токенов в массиве

    TokenArray() : capacity(10), count(0) {  // конструктор инициализирует массив с начальной емкостью 10
        tokens = new string[capacity];  // выделяем память под массив
    }

    void add(const string& token) {  // метод для добавления токена в массив
        if (count == capacity) {  // если текущий массив заполнен
            // Увеличиваем емкость в два раза
            capacity *= 2;
            string* newTokens = new string[capacity];  // создаем новый массив с увеличенной емкостью
            for (int i = 0; i < count; ++i) {  // копируем старые токены в новый массив
                newTokens[i] = tokens[i];
            }
            delete[] tokens;  // удаляем старый массив
            tokens = newTokens;  // обновляем указатель на новый массив
        }
        tokens[count++] = token;  // добавляем новый токен и увеличиваем счетчик
    }

    ~TokenArray() {  // деструктор для освобождения памяти
        delete[] tokens;  // удаляем динамический массив строк
    }
};


// Функция для разбиения строки на токены (слова), игнорируя пробелы вне кавычек
TokenArray tokenize(const string& str) {
    TokenArray tokenArray;  // создаем объект структуры TokenArray для хранения токенов
    string token;  // временная строка для сборки текущего токена
    bool in_quotes = false;  // флаг для отслеживания нахождения внутри кавычек
    for (size_t i = 0; i < str.size(); ++i) {  // проходим по каждому символу строки
        char ch = str[i];
        if (ch == '\'') {  // если встречаем символ кавычки
            in_quotes = !in_quotes;  // переключаем состояние флага (начало или конец кавычек)
            continue;  // пропускаем сам символ кавычки
        }
        if (ch == ' ' && !in_quotes) {  // если это пробел и мы не находимся внутри кавычек
            if (!token.empty()) {  // если токен не пуст
                tokenArray.add(token);  // добавляем токен в массив
                token.clear();  // очищаем временную строку для следующего токена
            }
        } else {
            token += ch;  // добавляем символ к текущему токену
        }
    }
    if (!token.empty()) {  // если после цикла остался непустой токен
        tokenArray.add(token);  // добавляем его в массив
    }
    return tokenArray;  // возвращаем массив токенов
}


// Функция для обработки пользовательского запроса и выполнения соответствующей операции
void process_query(const string& query,
                   NamedHashTableList& hash_tables,
                   NamedStackList& stacks,
                   NamedQueueList& queues,
                   NamedSetList& sets,
                   NamedLinkedListList& linked_lists,
                   NamedDynamicArrayList& dynamic_arrays,
                   NamedCompleteBinaryTreeList& trees) {
    TokenArray tokens = tokenize(query);  // разбиваем запрос на токены
    if (tokens.count == 0) {  // если запрос пуст
        cout << "Empty query." << endl;
        return;
    }

    string command = tokens.tokens[0];  // первый токен — это команда
    if (command == "PRINT") {
        if (tokens.count != 2) {
            cout << "Usage: PRINT structure_name" << endl;
            return;
        }
        string structure_name = tokens.tokens[1];

        // Проверка и вывод для хэш-таблицы
        HashTable* htable = hash_tables.get(structure_name);
        if (htable) {
            htable->print();
            return;
        }

        // Проверка и вывод для стека
        Stack<string>* stack = stacks.get(structure_name);
        if (stack) {
            stack->print();
            return;
        }

        // Проверка и вывод для очереди
        Queue<string>* queue = queues.get(structure_name);
        if (queue) {
            queue->print();
            return;
        }

        // Проверка и вывод для множества
        Set* set = sets.get(structure_name);
        if (set) {
            set->print();
            return;
        }

        // Проверка и вывод для односвязного списка
        SinglyLinkedList* list = linked_lists.get(structure_name);
        if (list) {
            list->print();
            return;
        }

        // Проверка и вывод для динамического массива
        DynamicArray* array = dynamic_arrays.get(structure_name);
        if (array) {
            array->print();
            return;
        }

        // Проверка и вывод для полного бинарного дерева
        CompleteBinaryTree* tree = trees.get(structure_name);
        if (tree) {
            tree->print();
            return;
        }

        cout << "Structure '" << structure_name << "' does not exist." << endl;
    }
    // Команды для работы с хэш-таблицами
    if (command == "HSET") {
        if (tokens.count != 4) {  // проверяем, что количество аргументов соответствует формату команды
            cout << "Usage: HSET hash_name key value" << endl;
            return;
        }
        string hash_name = tokens.tokens[1];  // имя хэш-таблицы
        string key = tokens.tokens[2];  // ключ
        string value = tokens.tokens[3];  // значение
        HashTable* htable = hash_tables.create(hash_name);  // создаем или получаем существующую хэш-таблицу
        htable->hset(key, value);  // добавляем ключ и значение в хэш-таблицу
        cout << "HSET executed: [" << key << " : " << value << "] in hash '" << hash_name << "'" << endl;
    }
    // Команда для получения значения по ключу из хэш-таблицы
    else if (command == "HGET") {
        if (tokens.count != 3) {  // проверяем, что передано нужное количество аргументов
            cout << "Usage: HGET hash_name key" << endl;
            return;
        }
        string hash_name = tokens.tokens[1];  // имя хэш-таблицы
        string key = tokens.tokens[2];  // ключ
        HashTable* htable = hash_tables.get(hash_name);  // получаем хэш-таблицу по имени
        if (!htable) {  // если таблица не существует
            cout << "Hash '" << hash_name << "' does not exist." << endl;
            return;
        }
        string value = htable->hget(key);  // получаем значение по ключу
        if (value.empty()) {  // если ключ не найден
            cout << "Key '" << key << "' not found in hash '" << hash_name << "'." << endl;
        } else {
            cout << value << endl;  // выводим значение
        }
    }
    // Команда для удаления ключа из хэш-таблицы
    else if (command == "HDEL") {
        if (tokens.count != 3) {  // проверяем количество аргументов
            cout << "Usage: HDEL hash_name key" << endl;
            return;
        }
        string hash_name = tokens.tokens[1];  // имя хэш-таблицы
        string key = tokens.tokens[2];  // ключ
        HashTable* htable = hash_tables.get(hash_name);  // получаем хэш-таблицу
        if (!htable) {  // если таблица не существует
            cout << "Hash '" << hash_name << "' does not exist." << endl;
            return;
        }
        htable->hdel(key);  // удаляем ключ
        cout << "HDEL executed: Key '" << key << "' deleted from hash '" << hash_name << "'" << endl;
    }
    // Команды для Стеков
    else if (command == "SPUSH") {
        if (tokens.count != 3) {
            cout << "Usage: SPUSH stack_name item" << endl;
            return;
        }
        string stack_name = tokens.tokens[1];
        string item = tokens.tokens[2];
        Stack<string>* stack = stacks.create(stack_name);
        stack->push(item);
        cout << "SPUSH executed: Pushed '" << item << "' to stack '" << stack_name << "'" << endl;
    }
    else if (command == "SPOP") {
        if (tokens.count != 2) {
            cout << "Usage: SPOP stack_name" << endl;
            return;
        }
        string stack_name = tokens.tokens[1];
        Stack<string>* stack = stacks.get(stack_name);
        if (!stack || stack->empty()) {
            cout << "Stack '" << stack_name << "' is empty or does not exist." << endl;
            return;
        }
        string item = stack->pop();
        cout << "SPOP executed: Popped '" << item << "' from stack '" << stack_name << "'" << endl;
    }
    else if (command == "SGET") { // Для стека
        if (tokens.count != 2) {
            cout << "Usage: SGET stack_name" << endl;
            return;
        }
        string stack_name = tokens.tokens[1];
        Stack<string>* stack = stacks.get(stack_name);
        if (!stack) {
            cout << "Stack '" << stack_name << "' does not exist." << endl;
            return;
        }
        if (stack->empty()) {
            cout << "Stack '" << stack_name << "' is empty." << endl;
        }
        else {
            cout << stack->peek() << endl;
        }
    }
    // Команды для Очередей
    else if (command == "QPUSH") {
        if (tokens.count != 3) {
            cout << "Usage: QPUSH queue_name item" << endl;
            return;
        }
        string queue_name = tokens.tokens[1];
        string item = tokens.tokens[2];
        Queue<string>* queue = queues.create(queue_name);
        queue->push(item);
        cout << "QPUSH executed: Enqueued '" << item << "' to queue '" << queue_name << "'" << endl;
    }
    else if (command == "QPOP") {
        if (tokens.count != 2) {
            cout << "Usage: QPOP queue_name" << endl;
            return;
        }
        string queue_name = tokens.tokens[1];
        Queue<string>* queue = queues.get(queue_name);
        if (!queue || queue->empty()) {
            cout << "Queue '" << queue_name << "' is empty or does not exist." << endl;
            return;
        }
        string item = queue->pop();
        cout << "QPOP executed: Dequeued '" << item << "' from queue '" << queue_name << "'" << endl;
    }
    else if (command == "QGET") { // Для очереди
        if (tokens.count != 2) {
            cout << "Usage: QGET queue_name" << endl;
            return;
        }
        string queue_name = tokens.tokens[1];
        Queue<string>* queue = queues.get(queue_name);
        if (!queue) {
            cout << "Queue '" << queue_name << "' does not exist." << endl;
            return;
        }
        if (queue->empty()) {
            cout << "Queue '" << queue_name << "' is empty." << endl;
        }
        else {
            cout << queue->peek() << endl;
        }
    }
    // Команды для Множеств
    else if (command == "SADD") {
        if (tokens.count != 3) {
            cout << "Usage: SADD set_name value" << endl;
            return;
        }
        string set_name = tokens.tokens[1];
        string value = tokens.tokens[2];
        Set* set = sets.create(set_name);
        set->add(value);
        cout << "SADD executed: Added '" << value << "' to set '" << set_name << "'" << endl;
    }
    else if (command == "SREM") {
        if (tokens.count != 3) {
            cout << "Usage: SREM set_name value" << endl;
            return;
        }
        string set_name = tokens.tokens[1];
        string value = tokens.tokens[2];
        Set* set = sets.get(set_name);
        if (!set) {
            cout << "Set '" << set_name << "' does not exist." << endl;
            return;
        }
        set->remove(value);
        cout << "SREM executed: Removed '" << value << "' from set '" << set_name << "'" << endl;
    }
    else if (command == "SISMEMBER") {
        if (tokens.count != 3) {
            cout << "Usage: SISMEMBER set_name value" << endl;
            return;
        }
        string set_name = tokens.tokens[1];
        string value = tokens.tokens[2];
        Set* set = sets.get(set_name);
        if (!set) {
            cout << "Set '" << set_name << "' does not exist." << endl;
            return;
        }
        bool is_member = set->is_member(value);
        cout << (is_member ? "TRUE" : "FALSE") << endl;
    }
    else if (command == "SGETALL") { // Для множества - получение всех элементов
        if (tokens.count != 2) {
            cout << "Usage: SGETALL set_name" << endl;
            return;
        }
        string set_name = tokens.tokens[1];
        Set* set = sets.get(set_name);
        if (!set) {
            cout << "Set '" << set_name << "' does not exist." << endl;
            return;
        }
        cout << "{ ";
        for (int i = 0; i < HashTable::SIZE; ++i) {
            HashTable::Entry* entry = set->htable.table[i];
            while (entry) {
                cout << entry->key << " ";
                entry = entry->next;
            }
        }
        cout << "}" << endl;
    }
    // Команды для Односвязного Списка
    else if (command == "LPUSH") {
        if (tokens.count != 3) {
            cout << "Usage: LPUSH list_name value" << endl;
            return;
        }
        string list_name = tokens.tokens[1];
        string value = tokens.tokens[2];
        SinglyLinkedList* list = linked_lists.create(list_name);
        list->push_front(value);
        cout << "LPUSH executed: Pushed '" << value << "' to front of list '" << list_name << "'" << endl;
    }
    else if (command == "LPUSHBACK") {
    if (tokens.count != 3) {
        cout << "Usage: LPUSHBACK list_name value" << endl;
        return;
    }
        string list_name = tokens.tokens[1];
        string value = tokens.tokens[2];
        SinglyLinkedList* list = linked_lists.create(list_name);
        list->push_back(value);
        cout << "LPUSHBACK executed: Pushed '" << value << "' to back of list '" << list_name << "'" << endl;
    }
    else if (command == "LPOPBACK") {
    if (tokens.count != 2) {
        cout << "Usage: LPOPBACK list_name" << endl;
        return;
    }
        string list_name = tokens.tokens[1];
        SinglyLinkedList* list = linked_lists.get(list_name);
    if (!list || !list->head) {
        cout << "List '" << list_name << "' is empty or does not exist." << endl;
        return;
    }
        string value = list->pop_back();
        cout << "LPOPBACK executed: Popped '" << value << "' from back of list '" << list_name << "'" << endl;
    }
    else if (command == "LPOP") {
        if (tokens.count != 2) {
            cout << "Usage: LPOP list_name" << endl;
            return;
        }
        string list_name = tokens.tokens[1];
        SinglyLinkedList* list = linked_lists.get(list_name);
        if (!list || !list->head) {
            cout << "List '" << list_name << "' is empty or does not exist." << endl;
            return;
        }
        string value = list->pop_front();
        cout << "LPOP executed: Popped '" << value << "' from front of list '" << list_name << "'" << endl;
    }
    else if (command == "LREMOVE") {
    if (tokens.count != 3) {
        cout << "Usage: LREMOVE list_name value" << endl;
        return;
    }
        string list_name = tokens.tokens[1];
        string value = tokens.tokens[2];
        SinglyLinkedList* list = linked_lists.get(list_name);
    if (!list) {
        cout << "List '" << list_name << "' does not exist." << endl;
        return;
    }
        list->remove_by_value(value);
        cout << "LREMOVE executed: Removed '" << value << "' from list '" << list_name << "'" << endl;
    }
    else if (command == "LSEARCH") {
    if (tokens.count != 3) {
        cout << "Usage: LSEARCH list_name value" << endl;
        return;
    }
    string list_name = tokens.tokens[1];
    string value = tokens.tokens[2];
    SinglyLinkedList* list = linked_lists.get(list_name);
    if (!list) {
        cout << "List '" << list_name << "' does not exist." << endl;
        return;
    }
        bool found = list->find_by_value(value);
        cout << (found ? "TRUE" : "FALSE") << endl;
    }
    else if (command == "LGET") {
        if (tokens.count != 3) {
            cout << "Usage: LGET list_name index" << endl;
            return;
        }
        string list_name = tokens.tokens[1];
        int index;
        try {
            index = stoi(tokens.tokens[2]);
        }
        catch (...) {
            cout << "Invalid index." << endl;
            return;
        }
        SinglyLinkedList* list = linked_lists.get(list_name);
        if (!list) {
            cout << "List '" << list_name << "' does not exist." << endl;
            return;
        }
        string value = list->get(index);
        if (value.empty()) {
            cout << "Index out of range." << endl;
        }
        else {
            cout << value << endl;
        }
    }
    // Команды для Динамического Масссива
    else if (command == "AADD") {
        if (tokens.count != 3) {
            cout << "Usage: AADD array_name value" << endl;
            return;
        }
        string array_name = tokens.tokens[1];
        string value = tokens.tokens[2];
        DynamicArray* array = dynamic_arrays.create(array_name);
        array->add(value);
        cout << "AADD executed: Added '" << value << "' to array '" << array_name << "'" << endl;
    }
    else if (command == "AINSERT") {
    if (tokens.count != 4) {
        cout << "Usage: AINSERT array_name index value" << endl;
        return;
    }
        string array_name = tokens.tokens[1];
        int index;
    try {
        index = stoi(tokens.tokens[2]);
    } catch (...) {
        cout << "Invalid index." << endl;
        return;
    }
        string value = tokens.tokens[3];
        DynamicArray* array = dynamic_arrays.get(array_name);
    if (!array) {
        cout << "Array '" << array_name << "' does not exist." << endl;
        return;
    }
        array->insert(index, value);
        cout << "AINSERT executed: Inserted '" << value << "' at index " << index << " in array '" << array_name << "'" << endl;
    }
    else if (command == "AREMOVE") {
    if (tokens.count != 3) {
        cout << "Usage: AREMOVE array_name index" << endl;
        return;
    }
        string array_name = tokens.tokens[1];
        int index;
    try {
        index = stoi(tokens.tokens[2]);
    } catch (...) {
        cout << "Invalid index." << endl;
        return;
    }
        DynamicArray* array = dynamic_arrays.get(array_name);
    if (!array) {
        cout << "Array '" << array_name << "' does not exist." << endl;
        return;
    }
        array->remove(index);
        cout << "AREMOVE executed: Removed element at index " << index << " from array '" << array_name << "'" << endl;
    }
    else if (command == "AGET") {
        if (tokens.count != 3) {
            cout << "Usage: AGET array_name index" << endl;
            return;
        }
        string array_name = tokens.tokens[1];
        int index;
        try {
            index = stoi(tokens.tokens[2]);
        }
        catch (...) {
            cout << "Invalid index." << endl;
            return;
        }
        DynamicArray* array = dynamic_arrays.get(array_name);
        if (!array) {
            cout << "Array '" << array_name << "' does not exist." << endl;
            return;
        }
        string value = array->get(index);
        if (value.empty()) {
            cout << "Index out of range or element is empty." << endl;
        }
        else {
            cout << value << endl;
        }
    }
    else if (command == "ASET") {
        if (tokens.count != 4) {
            cout << "Usage: ASET array_name index value" << endl;
            return;
        }
        string array_name = tokens.tokens[1];
        int index;
        try {
            index = stoi(tokens.tokens[2]);
        }
        catch (...) {
            cout << "Invalid index." << endl;
            return;
        }
        string value = tokens.tokens[3];
        DynamicArray* array = dynamic_arrays.get(array_name);
        if (!array) {
            cout << "Array '" << array_name << "' does not exist." << endl;
            return;
        }
        array->set(index, value);
        cout << "ASET executed: Set element at index " << index << " to '" << value << "' in array '" << array_name << "'" << endl;
    }
    // Команды для Complete Binary Tree
    else if (command == "CBINSERT") {
        if (tokens.count != 3) {
            cout << "Usage: CBINSERT tree_name value" << endl;
            return;
        }
        string tree_name = tokens.tokens[1];
        string value = tokens.tokens[2];
        CompleteBinaryTree* tree = trees.create(tree_name);
        tree->insert(value);
        cout << "CBINSERT executed: Inserted '" << value << "' into tree '" << tree_name << "'" << endl;
    }
    else if (command == "CBISFULL") {
        if (tokens.count != 2) {
            cout << "Usage: CBISFULL tree_name" << endl;
            return;
        }
        string tree_name = tokens.tokens[1];
        CompleteBinaryTree* tree = trees.get(tree_name);
        if (!tree) {
            cout << "Complete Binary Tree '" << tree_name << "' does not exist." << endl;
            return;
        }
        bool full = tree->isFull();
        cout << (full ? "TRUE" : "FALSE") << endl;
    }
    else if (command == "CBSEARCH") {
    if (tokens.count != 3) {
        cout << "Usage: CBSEARCH tree_name value" << endl;
        return;
    }
        string tree_name = tokens.tokens[1];
        string value = tokens.tokens[2];
        CompleteBinaryTree* tree = trees.get(tree_name);
        if (!tree) {
        cout << "Complete Binary Tree '" << tree_name << "' does not exist." << endl;
        return;
        }
        bool found = tree->search(value);
        cout << (found ? "TRUE" : "FALSE") << endl;
    }
    else if (command == "CBISCOMPLETE") {
        if (tokens.count != 2) {
            cout << "Usage: CBISCOMPLETE tree_name" << endl;
            return;
        }
        string tree_name = tokens.tokens[1];
        CompleteBinaryTree* tree = trees.get(tree_name);
        if (!tree) {
            cout << "Complete Binary Tree '" << tree_name << "' does not exist." << endl;
            return;
        }
        bool complete = tree->isComplete();
        cout << (complete ? "TRUE" : "FALSE") << endl;
    }
    else if (command == "PRINT") {
    if (tokens.count != 2) {
        cout << "Usage: PRINT structure_name" << endl;
        return;
    }
    string structure_name = tokens.tokens[1];

    // Проверка для хэш-таблицы
    HashTable* htable = hash_tables.get(structure_name);
    if (htable) {
        htable->print();
        return;
    }

    // Проверка для стека
    Stack<string>* stack = stacks.get(structure_name);
    if (stack) {
        stack->print();
        return;
    }

    // Проверка для очереди
    Queue<string>* queue = queues.get(structure_name);
    if (queue) {
        queue->print();
        return;
    }

    // Проверка для множества
    Set* set = sets.get(structure_name);
    if (set) {
        set->print();
        return;
    }

    // Проверка для односвязного списка
    SinglyLinkedList* list = linked_lists.get(structure_name);
    if (list) {
        list->print();
        return;
    }

    // Проверка для динамического массива
    DynamicArray* array = dynamic_arrays.get(structure_name);
    if (array) {
        array->print();
        return;
    }

    // Проверка для полного бинарного дерева
    CompleteBinaryTree* tree = trees.get(structure_name);
    if (tree) {
        tree->print();
        return;
    }

    cout << "Structure '" << structure_name << "' does not exist." << endl;
    }
}

void save_to_file(const string& filename,
                  const NamedHashTableList& hash_tables,
                  const NamedStackList& stacks,
                  const NamedQueueList& queues,
                  const NamedSetList& sets,
                  const NamedLinkedListList& linked_lists,
                  const NamedDynamicArrayList& dynamic_arrays,
                  const NamedCompleteBinaryTreeList& trees) {
    ofstream ofs(filename);
    if (!ofs.is_open()) {
        cerr << "Не удалось открыть файл для сохранения: " << filename << endl;
        return;
    }
    // Сохранение Хеш-таблиц
    ofs << "# HashTables\n";
    NamedHashTable* current_hash = hash_tables.head;
    while (current_hash) {
        for (int i = 0; i < HashTable::SIZE; ++i) {
            HashTable::Entry* entry = current_hash->htable->table[i];
            while (entry) {
                ofs << "HSET " << current_hash->name << " " << entry->key << " " << entry->value << "\n";
                entry = entry->next;
            }
        }
        current_hash = current_hash->next;
    }
    // Сохранение Стеков
    ofs << "# Stacks\n";
    NamedStack* current_stack = stacks.head;
    while (current_stack) {
        Stack<string>* original = current_stack->stack;
        // Временный стек для сохранения порядка
        Stack<string> temp_stack;
        Stack<string> reverse_stack;
        while (!original->empty()) {
            string val = original->pop();
            reverse_stack.push(val);
        }
        while (!reverse_stack.empty()) {
            string val = reverse_stack.pop();
            original->push(val);
            ofs << "SPUSH " << current_stack->name << " " << val << "\n";
        }
        current_stack = current_stack->next;
    }
    // Сохранение Очередей
    ofs << "# Queues\n";
    NamedQueue* current_queue = queues.head;
    while (current_queue) {
        Queue<string>* original = current_queue->queue;
        Queue<string> temp_queue;
        Queue<string> helper_queue;
        while (!original->empty()) {
            string val = original->pop();
            helper_queue.push(val);
            ofs << "QPUSH " << current_queue->name << " " << val << "\n";
            temp_queue.push(val);
        }
        while (!helper_queue.empty()) {
            string val = helper_queue.pop();
            original->push(val);
        }
        current_queue = current_queue->next;
    }
    // Сохранение Множеств
    ofs << "# Sets\n";
    NamedSet* current_set = sets.head;
    while (current_set) {
        for (int i = 0; i < HashTable::SIZE; ++i) {
            HashTable::Entry* entry = current_set->set->htable.table[i];
            while (entry) {
                ofs << "SADD " << current_set->name << " " << entry->key << "\n";
                entry = entry->next;
            }
        }
        current_set = current_set->next;
    }
    // Сохранение Односвязных Списков
    ofs << "# LinkedLists\n";
    NamedLinkedList* current_list = linked_lists.head;
    while (current_list) {
        SinglyLinkedList* list = current_list->list;
        SinglyLinkedList::Node* node = list->head;
        // Сохраняем элементы списка с помощью LPUSH (обратный порядок)
        // Чтобы сохранить исходный порядок, используем временный стек
        Stack<string> temp_stack;
        while (node) {
            temp_stack.push(node->value);
            node = node->next;
        }
        // Теперь сохраняем элементы в обратном порядке
        while (!temp_stack.empty()) {
            string val = temp_stack.pop();
            ofs << "LPUSH " << current_list->name << " " << val << "\n";
        }
        current_list = current_list->next;
    }
    // Сохранение Динамических Массивов
    ofs << "# DynamicArrays\n";
    NamedDynamicArrayStruct* current_array = dynamic_arrays.head;
    while (current_array) {
        DynamicArray* array = current_array->array;
        for (int i = 0; i < array->count; ++i) {
            ofs << "AADD " << current_array->name << " " << array->data[i] << "\n";
        }
        current_array = current_array->next;
    }
    // Сохранение Complete Binary Trees
    ofs << "# CompleteBinaryTrees\n";
    NamedCompleteBinaryTree* current_tree = trees.head;
    while (current_tree) {
        // Выполняем уровневый обход и сохраняем вставки
        // Для восстановления дерева достаточно сохранить команды CBINSERT в порядке уровней
        // Используем очередь для обхода
        Queue<CompleteBinaryTree::Node*> q;
        if (current_tree->tree->root) {
            q.push(current_tree->tree->root);
        }
        while (!q.empty()) {
            CompleteBinaryTree::Node* node = q.pop();
            ofs << "CBINSERT " << current_tree->name << " " << node->value << "\n";
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        current_tree = current_tree->next;
    }

    ofs.close();
    cout << "Данные успешно сохранены в файл: " << filename << endl;
}

void load_from_file(const string& filename,
                    NamedHashTableList& hash_tables,
                    NamedStackList& stacks,
                    NamedQueueList& queues,
                    NamedSetList& sets,
                    NamedLinkedListList& linked_lists,
                    NamedDynamicArrayList& dynamic_arrays,
                    NamedCompleteBinaryTreeList& trees) {
    ifstream ifs(filename);
    if (!ifs.is_open()) {
        cerr << "Не удалось открыть файл для загрузки: " << filename << endl;
        return;
    }

    string line;
    while (getline(ifs, line)) {
        // Игнорируем пустые строки и комментарии
        if (line.empty() || line[0] == '#') continue;

        TokenArray tokens = tokenize(line);
        if (tokens.count == 0) continue;

        string command = tokens.tokens[0];

        // Обработка команд для восстановления состояния
        if (command == "HSET") {
            if (tokens.count != 4) continue;
            string hash_name = tokens.tokens[1];
            string key = tokens.tokens[2];
            string value = tokens.tokens[3];
            HashTable* htable = hash_tables.create(hash_name);
            htable->hset(key, value);
        }
        else if (command == "SPUSH") {
            if (tokens.count != 3) continue;
            string stack_name = tokens.tokens[1];
            string item = tokens.tokens[2];
            Stack<string>* stack = stacks.create(stack_name);
            stack->push(item);
        }
        else if (command == "SPOP") {
            // В текущем формате сохранения нет необходимости обрабатывать SPOP
            // Так как SPOP удаляет элементы, а мы сохраняем состояние после всех операций
            // Поэтому можно пропустить
            continue;
        }
        else if (command == "SGET") {
            // Аналогично, пропускаем
            continue;
        }
        else if (command == "QPUSH") {
            if (tokens.count != 3) continue;
            string queue_name = tokens.tokens[1];
            string item = tokens.tokens[2];
            Queue<string>* queue = queues.create(queue_name);
            queue->push(item);
        }
        else if (command == "QPOP") {
            // Пропускаем, аналогично SPOP
            continue;
        }
        else if (command == "QGET") {
            // Пропускаем, аналогично SGET
            continue;
        }
        else if (command == "SADD") {
            if (tokens.count != 3) continue;
            string set_name = tokens.tokens[1];
            string value = tokens.tokens[2];
            Set* set = sets.create(set_name);
            set->add(value);
        }
        else if (command == "SREM") {
            // Пропускаем, так как мы не сохраняем удаления
            continue;
        }
        else if (command == "SISMEMBER") {
            // Пропускаем, это команда для пользователя
            continue;
        }
        else if (command == "SGETALL") {
            // Пропускаем, это команда для пользователя
            continue;
        }
        else if (command == "LPUSH") {
            if (tokens.count != 3) continue;
            string list_name = tokens.tokens[1];
            string value = tokens.tokens[2];
            SinglyLinkedList* list = linked_lists.create(list_name);
            list->push_front(value);
        }
        else if (command == "LPOP") {
            // Пропускаем, аналогично SPOP
            continue;
        }
        else if (command == "LGET") {
            // Пропускаем, это команда для пользователя
            continue;
        }
        else if (command == "AADD") {
            if (tokens.count != 3) continue;
            string array_name = tokens.tokens[1];
            string value = tokens.tokens[2];
            DynamicArray* array = dynamic_arrays.create(array_name);
            array->add(value);
        }
        else if (command == "AGET") {
            // Пропускаем, это команда для пользователя
            continue;
        }
        else if (command == "ASET") {
            // Пропускаем, это команда для пользователя
            continue;
        }
        // Команды для Complete Binary Tree
        else if (command == "CBINSERT") {
            if (tokens.count != 3) continue;
            string tree_name = tokens.tokens[1];
            string value = tokens.tokens[2];
            CompleteBinaryTree* tree = trees.create(tree_name);
            tree->insert(value);
        }
        else if (command == "CBISFULL") {
            // Пропускаем, это команда для пользователя
            continue;
        }
        else if (command == "CBISCOMPLETE") {
            // Пропускаем, это команда для пользователя
            continue;
        }
    }

    ifs.close();
    cout << "Данные успешно загружены из файла: " << filename << endl;
}

int main(int argc, char* argv[]) {
    if (argc < 5) {
        cout << "Usage: ./dbms --file file.data --query 'QUERY'" << endl;
        return 1;
    }

    string file_option = argv[1];
    string file = argv[2];
    string query_option = argv[3];
    string query = argv[4];

    if (file_option != "--file" || query_option != "--query") {
        cout << "Invalid arguments." << endl;
        cout << "Usage: ./dbms --file file.data --query 'QUERY'" << endl;
        return 1;
    }

    NamedHashTableList hash_tables;
    NamedStackList stacks;
    NamedQueueList queues;
    NamedSetList sets;
    NamedLinkedListList linked_lists;
    NamedDynamicArrayList dynamic_arrays;
    NamedCompleteBinaryTreeList trees;

    // Загрузка данных из файла
    load_from_file(file, hash_tables, stacks, queues, sets, linked_lists, dynamic_arrays, trees);

    // Обработка команды
    process_query(query, hash_tables, stacks, queues, sets, linked_lists, dynamic_arrays, trees);

    // Сохранение данных в файл
    save_to_file(file, hash_tables, stacks, queues, sets, linked_lists, dynamic_arrays, trees);

    return 0;
}
