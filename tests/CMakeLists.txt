enable_testing()

add_definitions(-std=c++11)

find_package(Boost COMPONENTS 
    unit_test_framework
    REQUIRED)

set(TESTS
	test_hdl_create
        test_hdl_add
        test_hdl_find
        test_hdl_get
        test_hdl_pop
        test_hdl_remove
        test_hdl_delete
)

set(lib_headers
    test_resources.h
)
include_directories(../src/)


foreach(test ${TESTS})
        add_executable(${test} ${test}.cpp ${lib_headers})
	target_link_libraries(${test} hdllist)
	target_link_libraries(${test} boost_unit_test_framework)
	add_test(${test} ${test})
endforeach(test)

