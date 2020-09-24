project(test_calculator)

set(SOURCE_FILES tokenizer_test.cpp parser_test.cpp)

add_executable(test_calculator ${SOURCE_FILES})

target_link_libraries(test_calculator catch2)

add_test(NAME ctests COMMAND test_calculator)