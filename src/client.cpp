#include "client.hpp"
#include <iostream>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

// Конструктор класса Client
Client::Client(std::string_view prefix, std::string_view name)
    : m_file(std::string(prefix) + "_" + std::string(name) + ".log", std::ios::app) // Открываем файл с суффиксом ".log"
{
    if (!m_file) {
        throw std::ios_base::failure("Failed to open file");
    }
}

// Деструктор класса Client
Client::~Client() {
    if (m_file.is_open()) {
        m_file.close();
    }
}

// Метод для записи записи
void Client::putRecord(std::string_view record) {
    if (!m_file) {
        throw std::ios_base::failure("File is not open");
    }
    m_file << m_sequence << ": " << record << std::endl;
    m_sequence.increment(); // Увеличиваем номер последовательности
}

// Реализация оператора вывода для Sequence
template <typename Char, typename Traits>
std::basic_ostream<Char, Traits>& operator<<(
    std::basic_ostream<Char, Traits>& os, Client::Sequence sequence) {
    return os << sequence.m_sequenceNo;
}
