include(ExternalProject)

ExternalProject_Add(
    catch_${PROJECT_NAME}
    GIT_REPOSITORY https://github.com/philsquared/Catch.git
#    GIT_TAG origin/master
    TIMEOUT 10
    UPDATE_COMMAND ""
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
    LOG_DOWNLOAD ON
   )
ExternalProject_Get_Property(catch_${PROJECT_NAME} source_dir)
set(CATCH_INCLUDE_DIR ${source_dir}/single_include CACHE INTERNAL "Path to include folder for Catch")

add_library(${PROJECT_NAME}_test_main OBJECT test_main.cpp)
set_property(TARGET ${PROJECT_NAME}_test_main APPEND PROPERTY INCLUDE_DIRECTORIES ${CATCH_INCLUDE_DIR})

find_package(Boost REQUIRED COMPONENTS system filesystem locale)

set(LINK_LIBS ${LINK_LIBS} ${Boost_FILESYSTEM_LIBRARY_RELEASE} ${Boost_SYSTEM_LIBRARY_RELEASE} ${Boost_LOCALE_LIBRARY_RELEASE})

function(lastfm_cxx_test test_name)
  add_executable(${test_name} ${test_name}.cpp $<TARGET_OBJECTS:${PROJECT_NAME}_test_main>)
  add_dependencies(${test_name} catch_${PROJECT_NAME})
  target_link_libraries(${test_name} ${LINK_LIBS} ${CPPREST_LIBRARIES} ${LASTFM})
  set_property(TARGET ${test_name} APPEND PROPERTY INCLUDE_DIRECTORIES ${CATCH_INCLUDE_DIR} ${CMAKE_SOURCE_DIR}/test)
  add_test(${test_name} ${EXECUTABLE_OUTPUT_PATH}/${test_name})
  set_property(TARGET ${test_name} APPEND PROPERTY COMPILE_DEFINITIONS
    LASTFMPP_TEST_DATA_DIR="${PROJECT_SOURCE_DIR}/test")
endfunction()

function(lastfm_cxx_header_test test_name)
  add_executable(${test_name} ${test_name}.cpp $<TARGET_OBJECTS:${PROJECT_NAME}_test_main>)
  add_dependencies(${test_name} catch_${PROJECT_NAME})
  target_link_libraries(${test_name} ${LINK_LIBS} ${CPPREST_LIBRARIES})
  set_property(TARGET ${test_name} APPEND PROPERTY INCLUDE_DIRECTORIES ${CATCH_INCLUDE_DIR} ${CMAKE_SOURCE_DIR}/test)
  add_test(${test_name} ${EXECUTABLE_OUTPUT_PATH}/${test_name})
  set_property(TARGET ${test_name} APPEND PROPERTY COMPILE_DEFINITIONS
    LASTFMPP_TEST_DATA_DIR="${PROJECT_SOURCE_DIR}/test")
endfunction()

add_executable(service_test service_test.cpp $<TARGET_OBJECTS:${PROJECT_NAME}_test_main>)
add_dependencies(service_test catch_${PROJECT_NAME} ${LASTFM})
target_link_libraries(service_test ${LINK_LIBS} ${OPENSSL_LIBRARIES} ${CPPREST_LIBRARIES} ${LASTFM})
set_property(TARGET service_test APPEND PROPERTY INCLUDE_DIRECTORIES ${CATCH_INCLUDE_DIR})

lastfm_cxx_test(lastfm_track_test)
lastfm_cxx_test(lastfm_album_test)
lastfm_cxx_test(lastfm_artist_test)
lastfm_cxx_test(lastfm_event_test)
lastfm_cxx_test(lastfm_venue_test)
lastfm_cxx_header_test(params_test)
