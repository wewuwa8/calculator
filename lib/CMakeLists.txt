add_library(tokenizer tokenizer.cpp ${CMAKE_SOURCE_DIR}/include/tokenizer.h)
target_include_directories(tokenizer PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_library(parser parser.cpp ${CMAKE_SOURCE_DIR}/include/parser.h)
target_include_directories(parser PUBLIC ${CMAKE_SOURCE_DIR}/include)
