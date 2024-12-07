import asyncio

async def communicate_with_server(server_host: str, server_port: int, name: str, log_record: str):
    reader, writer = await asyncio.open_connection(server_host, server_port)
    
    try:
        # Отправляем имя клиента
        writer.write(f"{name}\n".encode())
        await writer.drain()  # Убедиться, что данные отправлены
        
        print(f"Sent name: {name}")
        
        # Отправляем лог-запись
        writer.write(f"{log_record}\n".encode())
        await writer.drain()
        
        print(f"Sent log record: {log_record}")
        
        # Читаем ответ сервера (если сервер что-то возвращает)
        data = await reader.read(100)
        print(f"Received from server: {data.decode()}")
        
    finally:
        # Закрываем соединение
        writer.close()
        await writer.wait_closed()

# Конфигурация сервера
SERVER_HOST = '127.0.0.1'  # Локальный сервер
SERVER_PORT = 2009  # Замените на порт вашего сервера

# Запуск клиента
if __name__ == "__main__":
    print("Input log client name: ")
    client_name = input()

    print("Input log message: ")
    log_entry = input()

    print("================================")

    
    asyncio.run(communicate_with_server(SERVER_HOST, SERVER_PORT, client_name, log_entry))
