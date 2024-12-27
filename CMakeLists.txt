cmake_minimum_required(VERSION 3.5.0)
project(lab9 VERSION 0.1.0 LANGUAGES C CXX)

# Укажите путь к установленной библиотеке oneTBB
set(CMAKE_PREFIX_PATH "C:/oneTBB-2022.0.0")

# Или, если у вас есть конкретный путь к TBBConfig.cmake
#set(TBB_DIR "C:/oneTBB-2022.0.0/lib/cmake/TBB")

# Поиск пакета oneTBB
find_package(TBB REQUIRED)

# Создание исполняемого файла
add_executable(lab9 main.cpp)

# Подключение импортированного таргета TBB::tbb
target_link_libraries(lab9 PRIVATE TBB::tbb)