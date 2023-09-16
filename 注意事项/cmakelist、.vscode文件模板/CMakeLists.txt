cmake_minimum_required(VERSION 3.10)
project(MYSWAP)
add_executable(my_cmake_swap main.cpp swap.cpp)//这里第一个写你生成程序调试的可执行文件的名称，后面则是要编译的多个cpp文件
add_definitions("-Wall -g")//使可执行文件能调试

📌改进版，自动添加所有cpp，h文件
cmake_minimum_required(VERSION 3.10)
project(main)
add_executable(main)
file(GLOB sources CONFIGURE_DEPENDS *.cpp *.h)
target_sources(main PUBLIC ${sources})
add_definitions("-Wall -g") #带警告信息和调试信息的`