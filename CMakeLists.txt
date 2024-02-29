cmake_minimum_required(VERSION 3.11)

project(my_tree CXX)

set(CMAKE_CXX_STANDARD 23)

# Специфичные настройки для компилятора Visual Studio
if(MSVC)
    # Генерируем статическую заглушку для динамических библиотек
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS true)

    # Включаем высокий уровень предупреждений
    if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    endif()
endif()

# Объявляем библиотеку
add_library(search_tree SHARED "include/search_tree.h" "src/search_tree.cc" )
target_include_directories(search_tree PUBLIC "include")

# Объявляем тесты
add_executable(hello "src/search_tree.cc" )
target_link_libraries(hello search_tree)