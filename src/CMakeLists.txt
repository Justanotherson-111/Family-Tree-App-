add_subdirectory(core)
add_subdirectory(data)
add_subdirectory(ui)
add_subdirectory(app)

add_executable(CayGiaPha main.cpp)

target_link_libraries(CayGiaPha
    Qt6::Core
    Qt6::Widgets
    app
)

