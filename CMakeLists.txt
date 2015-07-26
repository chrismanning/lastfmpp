project(lastfmpp CXX)
cmake_minimum_required(VERSION 3.0)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

set(LASTFM lastfmpp)

option(LASTFMPP_BUILD_TESTS "" ON)
option(LASTFMPP_ENABLE_TESTING "" OFF)
option(LASTFMPP_ENABLE_LTO "" ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED 14)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z -Wno-c++1z-extensions")

if(LASTFMPP_ENABLE_LTO)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -flto")
  set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -flto")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -flto")
endif(LASTFMPP_ENABLE_LTO)

set(LASTFMPP_LIBDIR_SUFFIX "" CACHE STRING "Suffix for library installation directory")

if(CMAKE_BUILD_TYPE MATCHES Release)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden")
endif(CMAKE_BUILD_TYPE MATCHES Release)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

macro(add_src src)
  set(LASTFM_SRC ${LASTFM_SRC} ${CMAKE_CURRENT_SOURCE_DIR}/src/${LASTFM}/${src})
endmacro()

add_src(service.cpp)
add_src(service_impl.cpp)
add_src(tag.cpp)
add_src(user.cpp)
add_src(artist.cpp)
add_src(album.cpp)
add_src(track.cpp)
add_src(error.cpp)
add_src(wiki.cpp)
add_src(shout.cpp)
add_src(affiliation.cpp)
add_src(image.cpp)
add_src(event.cpp)
add_src(venue.cpp)
add_src(location.cpp)

add_library(${LASTFM} SHARED ${LASTFM_SRC})

FILE(GLOB_RECURSE LASTFM_COMMON_SRC_LIST include/*.hpp)

add_custom_target(lastfm_heads ALL SOURCES ${LASTFM_COMMON_SRC_LIST})

add_definitions(-DOPENSSL_NO_SSL2)

include(ExternalProject)

ExternalProject_Add(
    hana_${PROJECT_NAME}
    GIT_REPOSITORY https://github.com/ldionne/hana.git
    GIT_TAG e0b56a3d187447a870cd2a4d7246f07d7baa3e2f
    TIMEOUT 10
    UPDATE_COMMAND ""
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
    LOG_DOWNLOAD ON
   )
ExternalProject_Get_Property(hana_${PROJECT_NAME} source_dir)
set(HANA_INCLUDE_DIR ${source_dir}/include CACHE INTERNAL "Path to include folder for Boost Hana")

add_dependencies(${LASTFM} hana_${PROJECT_NAME})

find_package(Boost REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(JBSON REQUIRED)
find_package(CPPREST REQUIRED)

target_link_libraries(${LASTFM} ${OPENSSL_LIBRARIES} ${LINK_LIBS} ${CPPREST_LIBRARIES})
set_target_properties(${LASTFM} PROPERTIES COMPILE_DEFINITIONS LASTFM_EXPORTS=${LASTFM}_EXPORTS)
include_directories(SYSTEM
    ${Boost_INCLUDE_DIR}
    ${OPENSSL_INCLUDE_DIR}
    ${JBSON_INCLUDE_DIRS}
    ${HANA_INCLUDE_DIR}
    ${CPPREST_INCLUDE_DIR}
)

install(TARGETS lastfmpp
    LIBRARY DESTINATION lib${LASTFMPP_LIBDIR_SUFFIX}
    ARCHIVE DESTINATION lib${LASTFMPP_LIBDIR_SUFFIX})
install(DIRECTORY include/lastfmpp DESTINATION include
    PATTERN "detail" EXCLUDE
)

if(LASTFMPP_BUILD_TESTS)
  if(LASTFMPP_ENABLE_TESTING)
    enable_testing()
  endif(LASTFMPP_ENABLE_TESTING)
  add_subdirectory(test)
endif(LASTFMPP_BUILD_TESTS)
