@echo off
setlocal

:: Путь к директории сборки
set BUILD_DIR=build

:: Проверка и создание директории сборки
if not exist "%BUILD_DIR%" (
    mkdir "%BUILD_DIR%" || (
        echo Error: can't create %BUILD_DIR%. Directory already exists.
        exit /b 1
    )
) else (
    echo Directory %BUILD_DIR% already exists. Recreating...
    rmdir /s /q "%BUILD_DIR%"
    mkdir "%BUILD_DIR%"
)

:: Переход в директорию сборки
cd "%BUILD_DIR%"

:: Запуск CMake для генерации файлов сборки
echo CMake files generation...
cmake .. || (
    echo Error: CMake scripts ends with error.
    exit /b 1
)

:: Сборка проекта
echo Build project...
cmake --build . --config Release || (
    echo Error: build step ends with error.
    exit /b 1
)

:: Завершение
echo Building and installation successfully ends.
exit /b 0
