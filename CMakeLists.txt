cmake_minimum_required(VERSION 3.2)


set(PATCH_VERSION 0)
if($ENV{TRAVIS_BUILD_NUMBER})
  set(PATCH_VERSION $ENV{TRAVIS_BUILD_NUMBER})
endif()


project(matrix VERSION 0.0.${PATCH_VERSION})

find_package(Boost COMPONENTS unit_test_framework REQUIRED)
find_package(Boost COMPONENTS log REQUIRED)
find_package(Boost COMPONENTS program_options REQUIRED)
find_package(Threads)

add_executable(matrix main.cpp)

add_executable(test_matrix test_matrix.cpp)


set_target_properties(matrix test_matrix PROPERTIES
  CXX_STANDARD 14
  CXX_STANDARD_REQUIRED ON
  COMPILE_DEFINITIONS BOOST_LOG_DYN_LINK
  COMPILE_OPTIONS -Wpedantic -Wall -Wextra
  INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)

target_link_libraries(matrix
  ${Boost_LIBRARIES}
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_LOG_LIBRARY}
  ${Boost_LOG_SETUP_LIBRARY}
  ${Boost_THREAD_LIBRARY}
  ${CMAKE_THREAD_LIBS_INIT}
)

#set_target_properties(test_matrix PROPERTIES
#  COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
#  INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
#)


target_link_libraries(test_matrix
  ${Boost_UNIT_TEST_LIBRARIES}
  ${Boost_LIBRARIES}
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_LOG_LIBRARY}
  ${Boost_LOG_SETUP_LIBRARY}
  ${Boost_THREAD_LIBRARY}
  ${CMAKE_THREAD_LIBS_INIT}
)

install(TARGETS matrix RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT kolobrod2002@yandex.ru)

include (CPack)

enable_testing()

add_test(test_matrix test_matrix)


configure_file("${PROJECT_SOURCE_DIR}/version.h.in" "${PROJECT_BINARY_DIR}/version.h" @ONLY)
target_include_directories(matrix PUBLIC "${PROJECT_BINARY_DIR}")

configure_file("${PROJECT_SOURCE_DIR}/bintray.json.in" "${PROJECT_BINARY_DIR}/bintray.json")
