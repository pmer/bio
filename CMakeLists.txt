cmake_minimum_required(VERSION 2.8.9...3.19)
project(Advent C CXX)


#
# Variables
#

# Project generator
if(CMAKE_GENERATOR MATCHES Ninja)
    set(NINJA 1)
endif()

# Compiler
if(CMAKE_CXX_COMPILER_ID MATCHES Clang)
    set(CLANG 1)
endif()
if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
    set(GCC 1)
endif()
if(CMAKE_CXX_COMPILER_ID MATCHES MSVC)
    set(MSVC 1)
endif()

# OS
if(CMAKE_SYSTEM_NAME MATCHES Linux)
    set(LINUX 1)
endif()
if(CMAKE_SYSTEM_NAME MATCHES FreeBSD)
    set(FREEBSD 1)
endif()
if(CMAKE_SYSTEM_NAME MATCHES NetBSD)
    set(NETBSD 1)
endif()

# Build type
set(IS_DEBUG
    "$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>")
set(IS_RELEASE
    "$<OR:$<CONFIG:Release>,$<CONFIG:MinSizeRel>,$<CONFIG:RelWithDebInfo>>")


#
# Sources
#

set(HERE ${CMAKE_CURRENT_LIST_DIR}/Tsunagari)
set(ADVENT ${CMAKE_CURRENT_LIST_DIR})

set(TSUNAGARI_SOURCES ${TSUNAGARI_SOURCES}
    ${HERE}/src/os/c.h
    ${HERE}/src/os/chrono.h
    ${HERE}/src/os/io.h
    ${HERE}/src/os/mapped-file.h
    ${HERE}/src/os/mutex.h
    ${HERE}/src/os/thread.h
    ${HERE}/src/os/os.h
)
set(PACK_TOOL_SOURCES ${PACK_TOOL_SOURCES}
    ${HERE}/src/os/c.h
    ${HERE}/src/os/condition-variable.h
    ${HERE}/src/os/mapped-file.h
    ${HERE}/src/os/mutex.h
    ${HERE}/src/os/os.h
    ${HERE}/src/os/thread.h
)

if (WIN32)
    set(TSUNAGARI_SOURCES ${TSUNAGARI_SOURCES}
        ${HERE}/src/os/memmove.cpp
        ${HERE}/src/os/windows-c.cpp
        ${HERE}/src/os/windows-c.h
        ${HERE}/src/os/windows-chrono.cpp
        ${HERE}/src/os/windows-mapped-file.cpp
        ${HERE}/src/os/windows-mapped-file.h
        ${HERE}/src/os/windows.cpp
        ${HERE}/src/os/windows.h
        ${HERE}/src/os/windows/io.cpp
        ${HERE}/src/os/windows/io.h
    )
elseif(APPLE)
    set(TSUNAGARI_SOURCES ${TSUNAGARI_SOURCES}
        ${HERE}/src/os/mac-c.h
        ${HERE}/src/os/mac-chrono.cpp
        ${HERE}/src/os/mac-gui.mm
        ${HERE}/src/os/mac-gui.h
        ${HERE}/src/os/mac-thread.cpp
        ${HERE}/src/os/mac-thread.h
        ${HERE}/src/os/unix-mapped-file.cpp
        ${HERE}/src/os/unix-mapped-file.h
        ${HERE}/src/os/unix-mutex.h
        ${HERE}/src/os/unix.cpp
        ${HERE}/src/os/unix/io.cpp
        ${HERE}/src/os/unix/io.h
    )
else()
    set(TSUNAGARI_SOURCES ${TSUNAGARI_SOURCES}
        ${HERE}/src/os/linux-c.h
        ${HERE}/src/os/unix-chrono.cpp
        ${HERE}/src/os/unix-mapped-file.cpp
        ${HERE}/src/os/unix-mutex.h
        ${HERE}/src/os/unix-thread.h
        ${HERE}/src/os/unix.cpp
        ${HERE}/src/os/unix/io.cpp
        ${HERE}/src/os/unix/io.h
    )
endif()

set(TSUNAGARI_SOURCES ${TSUNAGARI_SOURCES}
    ${HERE}/src/util/align.h
    ${HERE}/src/util/assert.h
    ${HERE}/src/util/constexpr.h
    ${HERE}/src/util/fnv.cpp
    ${HERE}/src/util/fnv.h
    ${HERE}/src/util/function.h
    ${HERE}/src/util/hash.cpp
    ${HERE}/src/util/hash.h
    ${HERE}/src/util/hashtable.h
    ${HERE}/src/util/int.h
    ${HERE}/src/util/io.cpp
    ${HERE}/src/util/io.h
    ${HERE}/src/util/jobs.cpp
    ${HERE}/src/util/jobs.h
    ${HERE}/src/util/json.cpp
    ${HERE}/src/util/json.h
    ${HERE}/src/util/likely.h
    ${HERE}/src/util/list.h
    ${HERE}/src/util/markable.h
    ${HERE}/src/util/math2.h
    ${HERE}/src/util/meta.h
    ${HERE}/src/util/move.h
    ${HERE}/src/util/new.cpp
    ${HERE}/src/util/new.h
    ${HERE}/src/util/noexcept.h
    ${HERE}/src/util/pool.h
    ${HERE}/src/util/random.cpp
    ${HERE}/src/util/random.h
    ${HERE}/src/util/string-view.cpp
    ${HERE}/src/util/string-view.h
    ${HERE}/src/util/string.cpp
    ${HERE}/src/util/string.h
    ${HERE}/src/util/string2.cpp
    ${HERE}/src/util/string2.h
    ${HERE}/src/util/transform.cpp
    ${HERE}/src/util/transform.h
    ${HERE}/src/util/vector.h
)

if(MSVC OR ${CMAKE_VERSION} VERSION_LESS 3.1)
    # MSVC 2017 and below, and CMake 3.0 and below cannot vary source files by
    # configuration.
    set(TSUNAGARI_SOURCES ${TSUNAGARI_SOURCES}
        ${HERE}/src/util/assert.cpp
    )
    set(PACK_TOOL_SOURCES ${PACK_TOOL_SOURCES}
        ${HERE}/src/util/assert.cpp
    )
else()
    set(TSUNAGARI_SOURCES ${TSUNAGARI_SOURCES}
        $<${IS_DEBUG}:${HERE}/src/util/assert.cpp>
    )
    set(PACK_TOOL_SOURCES ${PACK_TOOL_SOURCES}
        $<${IS_DEBUG}:${HERE}/src/util/assert.cpp>
    )
endif()


#
# Targets
#

add_library(tsunagari ${TSUNAGARI_SOURCES})

add_executable(wk1-patterncount ${ADVENT}/src/wk1-patterncount.cpp)
target_link_libraries(wk1-patterncount tsunagari)
add_executable(wk1-frequentwords ${ADVENT}/src/wk1-frequentwords.cpp)
target_link_libraries(wk1-frequentwords tsunagari)
add_executable(wk1-reversecomplement ${ADVENT}/src/wk1-reversecomplement.cpp)
target_link_libraries(wk1-reversecomplement tsunagari)
add_executable(wk1-patternmatching ${ADVENT}/src/wk1-patternmatching.cpp)
target_link_libraries(wk1-patternmatching tsunagari)

include_directories(${HERE}/src)


#
# Compilation options
#

if(CLANG OR GCC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

# Disable C++ exceptions
if(CLANG OR GCC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-exceptions")
elseif(MSVC)
    string(REPLACE "/EHsc" "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
endif()

# Disable C++ run-time type information
if(CLANG OR GCC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti")
elseif(MSVC)
    string(REPLACE "/GR" "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /GR-")
endif()

# Hide most symbols
if(CLANG OR GCC)
    set(CMAKE_CXX_FLAGS_RELEASE
        "${CMAKE_CXX_FLAGS_RELEASE} -fvisibility=hidden")
    set(CMAKE_CXX_FLAGS_MINSIZEREL
        "${CMAKE_CXX_FLAGS_MINSIZEREL} -fvisibility=hidden")
endif()

# Reduce code size
if(CLANG)
    set(CMAKE_CXX_FLAGS_MINSIZEREL "${CMAKE_CXX_FLAGS_MINSIZEREL} -Oz")
endif()

# Enable floating point optimizations
if(CLANG OR GCC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ffast-math")
elseif(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /fp:fast")
endif()

# Disable stack canary
if(CLANG OR GCC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-stack-protector")
elseif(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /GS-")
endif()

# Optimize at link time
if(CLANG OR GCC)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -flto")
    set(CMAKE_CXX_FLAGS_MINSIZEREL "${CMAKE_CXX_FLAGS_MINSIZEREL} -flto")
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO
        "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -flto")
endif()

# Enable NDEBUG anything not a debug build.
if(${CMAKE_VERSION} VERSION_LESS 2.8.10)
    set(CMAKE_CXX_FLAGS_MINSIZEREL "${CMAKE_CXX_FLAGS_MINSIZEREL} -DNDEBUG")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DNDEBUG")
else()
    target_compile_definitions(tsunagari PUBLIC $<$<NOT:${IS_DEBUG}>:NDEBUG>)
endif()

# Enable color within compiler's output
if(NOT DEFINED ENV{CI})
    if(NINJA AND CLANG)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fcolor-diagnostics")
    endif()
    if(NINJA AND GCC AND NOT CMAKE_CXX_COMPILER_VERSION VERSION_LESS 4.9)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fdiagnostics-color=always")
    endif()
endif()


#
# Linking and externally-managed dependencies
#

# Optimize at link time
if(CLANG OR GCC)
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE
        "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -flto=full")
    set(CMAKE_EXE_LINKER_FLAGS_MINSIZEREL
        "${CMAKE_EXE_LINKER_FLAGS_MINSIZEREL} -flto=full")
    set(CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO
        "${CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO} -flto=thin")
endif()

# Do not link to libstdc++ or libc++
if(APPLE OR LINUX OR FREEBSD OR NETBSD)
    set(CMAKE_CXX_LINK_EXECUTABLE
        "<CMAKE_C_COMPILER> <FLAGS> <CMAKE_CXX_LINK_FLAGS> <LINK_FLAGS> <OBJECTS> -o <TARGET> <LINK_LIBRARIES>")
endif()

# Strip symbols
if(LINUX OR FREEBSD OR NETBSD)
    # GNU binutils
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE
        "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -Wl,--strip-all")
    set(CMAKE_EXE_LINKER_FLAGS_MINSIZEREL
        "${CMAKE_EXE_LINKER_FLAGS_MINSIZEREL} -Wl,--strip-all")
elseif(APPLE)
    # macOS linker
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE
        "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -Wl,-x -Wl,-dead_strip")
    set(CMAKE_EXE_LINKER_FLAGS_MINSIZEREL
        "${CMAKE_EXE_LINKER_FLAGS_MINSIZEREL} -Wl,-x -Wl,-dead_strip")
endif()

if(APPLE)
    set(CMAKE_EXE_LINKER_FLAGS
        "${CMAKE_EXE_LINKER_FLAGS} --no-standard-libraries -lSystem")
endif()

if(LINUX AND NOT AV_EM)
    execute_process(COMMAND ldd --version
                    OUTPUT_VARIABLE LDD_OUT
                    ERROR_VARIABLE LDD_ERR)

    set(LDD_VERSION "${LDD_OUT}${LDD_ERR}")

    if("${LDD_VERSION}" MATCHES "GLIBC (2.[0-9]*)")
        set(GLIBC_VERSION "${CMAKE_MATCH_1}")
    elseif("${LDD_VERSION}" MATCHES "GNU libc. (2.[0-9]*)")
        set(GLIBC_VERSION "${CMAKE_MATCH_1}")
    elseif("${LDD_VERSION}" MATCHES "Version ([1-9][0-9.]*)")
        set(MUSL_VERSION "${CMAKE_MATCH_1}")
    else()
        message(WARNING "Could not determine libc version")
        message(WARNING "${LDD_VERSION}")
    endif()

    if("${GLIBC_VERSION}" VERSION_LESS "2.17")
        target_link_libraries(tsunagari rt)
    endif()

    if(GLIBC_VERSION)
        target_link_libraries(tsunagari m pthread)
    endif()
endif()

if(FREEBSD OR NETBSD)
    target_link_libraries(tsunagari PUBLIC  m pthread)
endif()
if(AV_EM)
    target_link_libraries(tsunagari PUBLIC  pthread)
endif()


#
# Policies
#

# Do not turn on -rdynamic. Also solved with CMP0065 in CMake 3.4
# FIXME: Apply it only to local targets, or possibly just try to
#        remove -rdynamic from these.
set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")
set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "")
