#include<boost/algorithm/string/trim_all.hpp>
#include<boost/asio/co_spawn.hpp>
#include<boost/asio/detached.hpp>
#include<boost/asio/io_context.hpp>
#include<boost/asio/ip/tcp.hpp>
#include<boost/asio/read_until.hpp>
#include<boost/asio/signal_set.hpp>
#include<boost/asio/streambuf.hpp>

#include<iostream>
#include<thread>
#include "settings.hpp"
#include "client.hpp"

namespace asio = boost::asio;
using tcp = asio::ip::tcp;

namespace{


    asio::awaitable<void> worksWithClient(tcp::socket socket) {
        asio::streambuf buffer;
        co_await asio::async_read_until(socket, buffer, "\n", asio::use_awaitable);

        std::istream inputStream(&buffer);
        std::string name;
        std::getline(inputStream, name);
        boost::trim(name);

        Client client("co", name);

        buffer.consume(buffer.size());
        co_await asio::async_read_until(socket, buffer, "\n", asio::use_awaitable);

        std::istream logStream(&buffer);
        std::string logRecord;
        std::getline(logStream, logRecord);
        boost::trim(logRecord);

    // Передача данных клиенту
    client.putRecord(logRecord);
        
    }

    asio::awaitable<void> listen(){
        const auto executor = co_await asio::this_coro::executor;

        tcp::acceptor acceptor{executor, {tcp::v4(), port}};

        for(;;) {
            tcp::socket socket = co_await acceptor.async_accept(asio::use_awaitable);
            asio::co_spawn(executor, worksWithClient(std::move(socket)), asio::detached);
        }
    }

    void runServer(){
        std::cout<<std::this_thread::get_id() << "Running server..." << std::endl;

        asio::io_context ioContext;

        asio::co_spawn(ioContext, listen, asio::detached);

        ioContext.run();

        std::cout << std::this_thread::get_id() << "Server stopped." << std::endl;
    }
}

auto main() -> int{
    try{
        runServer();
        return EXIT_SUCCESS;
    } catch (const std::exception& ex){
        std::cerr << "Fatal error \"" <<ex.what() << "\"." << std::endl;
    } catch (...){
        std::cerr << "Fatal UNKNOWN error." << std::endl;
    }

    return EXIT_FAILURE;
}

