#include "hash-map.h"
#include <iostream>
#include <string>

int main() {
    hash_map<std::string, int> map;

    std::cout << "Добавление элементов...\n";
    map.insert("apple", 3);
    map.insert("banana", 5);
    map.insert("cherry", 7);

    std::cout << "Получение значений:\n";
    std::cout << "apple: " << map["apple"] << "\n";
    std::cout << "banana: " << map["banana"] << "\n";

    std::cout << "Обновление значения banana -> 10\n";
    map.insert("banana", 10);
    std::cout << "banana: " << map["banana"] << "\n";

    std::cout << "Текущий размер: " << map.size() << "\n";

    std::cout << "Удаление элемента cherry...\n";
    map.erase("cherry");
    std::cout << "Текущий размер: " << map.size() << "\n";

    std::cout << "Добавление новых элементов для триггера перехеширования...\n";
    for (int i = 0; i < 20; ++i) {
        map.insert("key" + std::to_string(i), i);
    }

    std::cout << "Текущий уровень загруженности: " << map.load_factor() << "\n";
    std::cout << "Максимально допустимый уровень загруженности: " << map.get_load_factor_limit() << "\n";

    return 0;
}
