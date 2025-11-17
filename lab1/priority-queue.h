#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <vector>
#include <stdexcept>
#include <functional>


template <typename T, typename Container = std::vector<T>, typename Compare = std:: less<typename Container::value_type>>
class priority_queue {
private:
    Container container; //для хранения элементов
    Compare compare;// для сравнения элементов

//           parent (i)
//           |       |
//      left(2*i+1)  right(2*i+2)
     

    //опускает элемент кучи вниз
    void heap_down(size_t index) {
        size_t size = container.size();
        size_t left = 2 * index + 1;
        size_t right = 2 * index + 2;
        size_t largest = index;

        if (left < size && compare(container[largest], container[left])) {
            largest = left;
        }
        if (right < size && compare(container[largest], container[right])) {
            largest = right;
        }
        if (largest != index) {
            std::swap(container[index], container[largest]);
            heap_down(largest);
        }
    }

    //поднимает элемент кучи вверх
    void heap_up(size_t index) {
        if (index && compare(container[(index - 1) / 2], container[index])) {
            std::swap(container[(index - 1) / 2], container[index]);
            heap_up((index - 1) / 2);
        }
    }

public:
    priority_queue() = default;

    //проверка пустоты очереди
    bool empty() const {
        return container.empty();
    }

    //размер очереди
    size_t size() const {
        return container.size();
    }

    //добавление в конец и сравниваем 
    void push(const T& value) {
        container.push_back(value);
        heap_up(container.size() - 1);
    }
    //удаление элемента с высоким приоритетом 
    void pop() {
        if (empty()) {
            throw std::out_of_range("Очередь пуста");
        }
        std::swap(container[0], container[container.size() - 1]);
        container.pop_back();
        if (!empty()) {
            heap_down(0);
        }
    }
    //ссылка на эл-т наивысш. приоритета
    T& top() {
        if (empty()) {
            throw std::out_of_range("Очередь пуста");
        }
        return container[0];
    }

    // void print() const {
    //     for (const auto& element : container) {
    //         std::cout << element << " ";
    //     }
    //     std::cout << std::endl;
    // }
};

#endif