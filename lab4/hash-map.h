#ifndef HASH_MAP_H
#define HASH_MAP_H

#include <vector>
#include <list>
#include <functional>
#include <stdexcept>
#include <utility>

template <typename K, typename V, typename Hash = std::hash<K>>
class hash_map {
private:
    std::vector<std::list<std::pair<K, V>>> table;
    size_t num_elements;
    double max_load_factor; // Максимальный коэффициент заполнения
    Hash hasher;

    // перераспределение в новый массив
    void rehash(size_t new_bucket_count) {
        if (new_bucket_count <= table.size()) return;

        std::vector<std::list<std::pair<K, V>>> new_table(new_bucket_count);
        for (const auto& bucket : table) {
            for (const auto& pair : bucket) {
                size_t new_index = hasher(pair.first) % new_bucket_count;
                new_table[new_index].emplace_back(pair);
            }
        }

        table = std::move(new_table);
    }

    // расширение хэш-таблицы
    void check_load_factor_and_rehash() {
        if (load_factor() > max_load_factor) {
            rehash(table.size() * 2 + 1);
        }
    }

public:
    hash_map(size_t bucket_count = 8, double load_factor_limit = 2.0)
        : table(bucket_count), num_elements(0), max_load_factor(load_factor_limit) {}

    void clear() {
        for (auto& bucket : table) {
            bucket.clear();
        }
        num_elements = 0;
    }

    void insert(const K& key, const V& value) {
        size_t index = hasher(key) % table.size();
        for (auto& pair : table[index]) {  // Обход цепочки в найденной корзине
            if (pair.first == key) {      // Проверка коллизий
                pair.second = value;      // Обновление значения при совпадении ключа
                return;
            }
        }
        table[index].emplace_back(key, value);  // Добавление нового элемента в цепочку
        ++num_elements;

        check_load_factor_and_rehash();
    }

    V& operator[](const K& key) {
        size_t index = hasher(key) % table.size();
        for (auto& pair : table[index]) {
            if (pair.first == key) {
                return pair.second;
            }
        }
        table[index].emplace_back(key, V{});
        ++num_elements;

        check_load_factor_and_rehash();
        index = hasher(key) % table.size(); // Возможно изменилась таблица
        for (auto& pair : table[index]) {
            if (pair.first == key) {
                return pair.second;
            }
        }

        throw std::logic_error("Unreachable code");
    }

    bool erase(const K& key) {
        size_t index = hasher(key) % table.size();  // Находим корзину
        auto& bucket = table[index];                // Получаем ссылку на цепочку
        for (auto it = bucket.begin(); it != bucket.end(); ++it) {  // Ищем ключ
            if (it->first == key) {                
                bucket.erase(it);                  //    Удаляем элемент
                --num_elements;             
                return true;                      
            }
        }
        return false; 
    }

    size_t size() const {
        return num_elements;
    }

    double get_load_factor_limit() const {
        return max_load_factor;
    }

    void set_load_factor_limit(double factor) {
        max_load_factor = factor;
        check_load_factor_and_rehash();
    }

    double load_factor() const {
        return static_cast<double>(num_elements) / table.size();
    }
};

#endif // HASH_MAP_H
