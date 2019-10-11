cmake_minimum_required(VERSION 3.6.2)
#set(CMAKE_C_COMPILER /cygdrive/s/program_files/cygwin/bin/gcc.exe CACHE PATH "" FORCE)
#set(CMAKE_CXX_COMPILER /cygdrive/s/program_files/cygwin/bin/g++.exe CACHE PATH "" FORCE)
project(libft_run C)
set(CMAKE_C_STANDARD 90)
include_directories(.)
include_directories(libft)
include_directories(headers)

#--------------LIB LINK EXAMPLE---------------------
#add_executable(<exe_name> sorce1 source2)
#find_library(FT ft libft)
#target_link_libraries(<exe_name> LINK_PUBLIC ${FT})
#---------------------------------------------------

add_executable(fdf
		ascii/main.c
		ascii/line.c
		ascii/ascii.c
		src/t_matrix.c
		src/t_vector.c)
include_directories(headers)
include_directories(libft)
include_directories(minilibx_macos)
#add_compile_options(-framework OpenGL -framework AppKit)
target_link_libraries(fdf
		LINK_PUBLIC ${CMAKE_SOURCE_DIR}/libft/libft.a
		LINK_PUBLIC ${CMAKE_SOURCE_DIR}/minilibx_macos/libmlx.a
		"-framework OpenGL"
		"-framework AppKit")
