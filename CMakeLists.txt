#	 Upanix - An x86 based Operating System
#	 Copyright (C) 2011 'Prajwala Prabhakar' 'srinivasa_prajwal@yahoo.co.in'
#																			 
#	 This program is free software: you can redistribute it and/or modify
#	 it under the terms of the GNU General Public License as published by
#	 the Free Software Foundation, either version 3 of the License, or
#	 (at your option) any later version.
#																			 
#	 This program is distributed in the hope that it will be useful,
#	 but WITHOUT ANY WARRANTY; without even the implied warranty of
#	 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#	 GNU General Public License for more details.
#																			 
#	 You should have received a copy of the GNU General Public License
#	 along with this program.  If not, see <http://www.gnu.org/licenses/
cmake_minimum_required(VERSION 3.15)
project(UpanixApps)

set(CROSS_TOOL_PATH $ENV{HOME}/opt/cross)
set(OUTPUT_DIR ${PROJECT_SOURCE_DIR}/out)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})

set(CMAKE_CXX_COMPILER ${CROSS_TOOL_PATH}/bin/i686-elf-g++)
set(CMAKE_C_COMPILER ${CROSS_TOOL_PATH}/bin/i686-elf-gcc)
set(CMAKE_LINKER ${CROSS_TOOL_PATH}/i686-elf/bin/ld)
set(CMAKE_AR ${CROSS_TOOL_PATH}/i686-elf/bin/ar)

set(ENABLE_CXX_RT ON)
	
set(EXCEPTION_SUP " -fno-exceptions -fno-rtti")
if(ENABLE_CXX_RT)
	set(EXCEPTION_SUP " -fexceptions -frtti")
endif()

set(SO_COMPILE_FLAGS -shared -fPIC)
set(SO_LD_FLAGS " -Wl,-shared -Wl,-fPIC")

set(CMAKE_CXX_FLAGS " -O0 -Wall -ffreestanding -nodefaultlibs -nostdlib -nostartfiles -nostdinc -std=c++11 -nostdinc++ -fno-threadsafe-statics -fpermissive ${EXCEPTION_SUP}")
set(COMMON_COMPILE_FLAGS " -std=c11 -O0 -Wall -std=c11 -nostdlib -nodefaultlibs -ffreestanding -nostartfiles -D__GCC__")
set(CMAKE_C_FLAGS ${COMMON_COMPILE_FLAGS})
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_CXX_FLAGS} ${COMMON_COMPILE_FLAGS}")
set(CMAKE_SHARED_LINKER_FLAGS "${COMMON_COMPILE_FLAGS} ${SO_LD_FLAGS}")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(${PROJECT_SOURCE_DIR}/libc/include)
include_directories(${PROJECT_SOURCE_DIR}/libc/stdio)
include_directories(${PROJECT_SOURCE_DIR}/libc/sysdeps/mos/common)
include_directories(${PROJECT_SOURCE_DIR}/libc/sysdeps/mos/common/bits)

#LIBC
execute_process(COMMAND bash -c "cd ${PROJECT_SOURCE_DIR}; find ./libc -name '*.c' | grep -v CMakeFile | grep -v './libc/sys/'" OUTPUT_VARIABLE LIBC_SRC)
execute_process(COMMAND bash -c "cd ${PROJECT_SOURCE_DIR}; find ./libc -name '*.c' | grep -v CMakeFile | grep './libc/sys/'" OUTPUT_VARIABLE LIBC_SYS_SRC)
string(REPLACE "\n" ";" LIBC_SRC ${LIBC_SRC})
string(REPLACE "\n" ";" LIBC_SYS_SRC ${LIBC_SYS_SRC})
add_library(c SHARED ${LIBC_SRC} ${LIBC_SYS_SRC})
target_compile_options(c PRIVATE -O0 ${SO_COMPILE_FLAGS})

#LIBC static for kernel - so don't include sys-call code
add_library(upanc STATIC ${LIBC_SRC})
set_target_properties(upanc PROPERTIES OUTPUT_NAME c)

link_directories(${OUTPUT_DIR})
