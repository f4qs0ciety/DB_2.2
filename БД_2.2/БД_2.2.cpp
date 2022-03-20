#include <iostream>
using namespace std;

class Stack {
private:
    int size; //Размер стека
    class Element { //Класс элементов стека
    public:
        Element* pNext; //Указатель на следующий элемент
        int data; //Содержимое элемента
        Element(int data, Element* pNext = nullptr) { //Конструктор элемента
            this->data = data;
            this->pNext = pNext;
        }
    };
    Element* head; //Первый элемент стека
    
    int& operator[](const int index) {//Перегрузка для приближения стека к абстракции массива
        int counter = 0;
        Element* current = this->head;
        while (current != nullptr) {
            if (counter == index) { return current->data; }
            current = current->pNext;
            counter++;
        }
    }

    void showStack() { //Вывод стека
        cout << endl << "Текущий стек: ";
        for (int i = 0; i < size; i++) {
            cout << "[" << i << "]" << " " << this->operator[](i) << "\t";
        } cout << endl;
    }

    void addToStack() { //Добавление элемента
        int data;
        cout << endl << "Введите новый элемент стека: ";
        cin >> data;
        if (head == nullptr) { head = new Element(data); }
        else {
            Element* current = this->head;
            while (current->pNext != nullptr) {
                current = current->pNext;
            }
            current->pNext = new Element(data);
        }
        size++;
        cout << "Элемент добавлен!" << endl;
        showStack();
    }

    void deleteFromStack() { //Удаление элемента
        Element* current = this->head;
        if (current->pNext == nullptr) { 
            head = nullptr; 
            //current->pNext = nullptr; 
        } else {
            while (current->pNext->pNext != nullptr) {
                current = current->pNext;
            }
            delete current->pNext;
            current->pNext = nullptr;
        }
        size--;
        cout << endl << "Верхний элемент стека удалён!";
        showStack();
    }
public:
    Stack() { //Конструктор стека
        size = 0;
        head = nullptr;
    }

    void menu() { //Меню взаимодействия со стеком
        int option;
        bool stop = false;
        do {
            cout << endl << "Что вы хотите сделать?" << endl << "[1] Добавить элемент." << endl << "[2] Удалить элемент." << endl << "[3] Показать стек." << endl << "[4] Выйти из меню стека." << endl;
            cin >> option;
            switch (option) {
            case 1: { addToStack(); break; }
            case 2: { deleteFromStack(); break; }
            case 3: { showStack(); break; }
            case 4: stop = true;
            }
        } while (stop != true);
    }
};

class Deque {
private:
    class Element { //Класс элементов дека
    public:
        Element* pNext; //Указатель на следующий элемент
        Element* pPrev; //Указатель на предыдущий элемент
        int data; //Содержимое элемента
        Element(int data, Element* pNext = nullptr, Element* pPrev = nullptr) { //Конструктор элемента
            this->data = data;
            this->pNext = pNext;
            this->pPrev = pPrev;
        }
    };
    Element* head; //Центральный элемент дека


    void showDeque() { //Вывод дека
        cout << endl << "Текущий дек: ";
        int counter = 0;
        Element* current = this->head;
        while (current->pPrev != nullptr) {
            current = current->pPrev;
        }
        for (;;) {
            if (current == head) { cout << "[" << counter << "]" << " (" << current->data << ") " << "\t"; }
            else {
                cout << "[" << counter << "]" << " " << current->data << "\t";
            }
            if (current->pNext == nullptr) break;
            current = current->pNext;
            counter++;
        }
    }

    void addToDeque() { //Добавление элемента
        int data, option;
        cout << endl << "Куда вы ходите добавить элемент?" << endl << "[1] В левую часть." << endl << "[2] В правую часть." << endl << "Ваш выбор: ";
        cin >> option;
        cout << endl << "Введите новый элемент дека: ";
        cin >> data;
        switch (option) {
        case 1:
            if (head == nullptr) { head = new Element(data); }
            else {
                Element* current = this->head;
                while (current->pPrev != nullptr) {
                    current = current->pPrev;
                }
                current->pPrev = new Element(data, current);
            }
            cout << "Элемент добавлен!" << endl;
            showDeque();
            break;
        case 2:
            if (head == nullptr) { head = new Element(data); }
            else {
                Element* current = this->head;
                while (current->pNext != nullptr) {
                    current = current->pNext;
                }
                current->pNext = new Element(data, nullptr, current);
            }
            cout << "Элемент добавлен!" << endl;
            showDeque();
            break;
        }
    }

    void deleteFromDeque() { //Удаление элемента
        int option;
        cout << endl << "Откуда вы хотите удалить элемент?" << endl << "[1] Из левой части." << endl << "[2] Из правой части." << endl << "Ваш выбор: ";
        cin >> option;
        Element* current = this->head;
        switch (option) {
        case 1:
            while (current->pPrev != nullptr) {
                current = current->pPrev;
            }
            if (current == head) {
                head = current->pNext;
            }
            current->pNext->pPrev = nullptr;
            delete current;
            cout << endl << "Левый элемент дека удалён!";
            showDeque();
            break;
        case 2:
            while (current->pNext != nullptr) {
                current = current->pNext;
            }
            if (current == head) {
                head = current->pPrev;
            }
            current->pPrev->pNext = nullptr;
            delete current;
            cout << endl << "Правый элемент дека удалён!";
            showDeque();
            break;
        }
    }

public:
    Deque() { //Конструктор дека
        head = nullptr;
    }

    void menu() { //Меню взаимодействия с деком
        int option;
        bool stop = false;
        do {
            cout << endl << "Что вы хотите сделать?" << endl << "[1] Добавить элемент." << endl << "[2] Удалить элемент." << endl << "[3] Показать дек." << endl << "[4] Выйти из меню дека." << endl << "Ваш выбор: ";
            cin >> option;
            switch (option) {
            case 1: { addToDeque(); break; }
            case 2: { deleteFromDeque(); break; }
            case 3: { showDeque(); break; }
            case 4: stop = true;
            }
        } while (stop != true);
    }
};

void main()
{
    setlocale(LC_ALL, "Russian");
    int option; //Выбор элемента меню
    bool stop = false; //Индикатор выхода из программы
    Stack LeftStack, RightStack;
    Deque MidDeque;
    do {
        cout << endl << "С каким списком вы хотите работать?" << endl << "[1] Левый стек." << endl << "[2] Средний дек." << endl << "[3] Правый стек." << endl << "[4] Выйти из программы." << endl << "Ваш выбор: ";
        cin >> option;
        switch (option) {
        case 1: { LeftStack.menu(); break; }
        case 2: { MidDeque.menu(); break; }
        case 3: { RightStack.menu(); break; }
        case 4: stop = true;
        }
    } while (stop != true);
}