cmake_minimum_required(VERSION 3.21)

file( GLOB APP_SOURCES *.cpp)
foreach( testsourcefile ${APP_SOURCES} )
    get_filename_component(testname ${testsourcefile} NAME_WE)
    #string( REPLACE ".cpp" "" testname ${testsourcefile} )
    add_executable( ${testname} ${testsourcefile} )
    target_link_libraries( ${testname} PUBLIC
    gtest_main 
    )
    add_test(
    NAME ${testname}
    COMMAND ${testname}
    )
endforeach( testsourcefile ${APP_SOURCES} )