#pragma once

#include<fstream>
#include<string_view>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>

class Client {
    class Sequence{
        template<typename Char, typename Traits>
        friend std::basic_ostream<Char, Traits>& operator<<(
            std::basic_ostream<Char, Traits>& os,Sequence);

        friend class Client;

        std::size_t m_sequenceNo = 1;

        void increment() { m_sequenceNo++; }
    };

        template<typename Char, typename Traits>
        friend std::basic_ostream<Char, Traits>& operator<<(
            std::basic_ostream<Char, Traits>& os,Client::Sequence);


public:
Client(std::string_view prefix, std::string_view name);
~Client();

Client(Client&) = delete;
Client(Client&&) = default;

Client& operator=(const Client&) = delete;
Client& operator=(Client&&) = default;

void putRecord(std::string_view record);

private:
Sequence m_sequence;
std::ofstream m_file;

};