add_library(data
    Repository.h
    Repository.cpp
    JsonMapper.h
    JsonMapper.cpp
    CSVMapper.h
    CSVMapper.cpp
)

target_include_directories(data PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(data core)
