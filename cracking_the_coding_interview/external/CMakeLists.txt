add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/googletest)

foreach(target ${TARGETS})
    target_include_directories(${target} PRIVATE ${gtest_SOURCE_DIR}/include)
    target_link_libraries(${target} gtest gtest_main)
endforeach()
