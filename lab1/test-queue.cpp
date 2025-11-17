#include <iostream>
#include "priority-queue.h"

int main() {
    priority_queue<int> pq;

    pq.push(9);
    pq.push(15);
    pq.push(50);
    pq.push(90);
    pq.push(4);
    int n = pq.size();
    //pq.print();

    std::cout << "верхний элемент: " << pq.top() << std::endl;
    std::cout << "Размер очереди: " << pq.size() << std::endl;    

    pq.pop();
    std::cout << "Верхний элемент после удаления: " << pq.top() << std::endl;

    pq.pop();
    pq.pop();
    
    std::cout << "Верхний элемент после удаления " << n - pq.size() << " элементов: " << pq.top() << std::endl;

    pq.pop();
    std::cout << "Очередь пуста? " << (pq.empty() ? "да" : "нет") << std::endl;

    return 0;
}    