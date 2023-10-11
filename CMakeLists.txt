cmake_minimum_required(VERSION 3.22.1) # Укажите версию CMake

project(Module_15) # Замените "MyProject" на имя вашего проекта

# Укажите исходные файлы вашего проекта
set(SOURCES
    src/main.cpp            #папка и название файла
    src/Chat.cpp
    src/ClientCode.cpp
    src/Messages.cpp
    src/User.cpp
    src/sha1.cpp
)

# Добавьте исполняемый файл
add_executable(project_2 ${SOURCES})
target_compile_options(project_2 PRIVATE -g -O0)


# Укажите дополнительные настройки и библиотеки, если необходимо
# target_link_libraries(my_app your_library)

# Укажите директории для поиска заголовочных файлов, если необходимо
# target_include_directories(my_app PUBLIC include)

# Установите параметры компиляции, если необходимо
# target_compile_options(my_app PRIVATE -Wall -Wextra)