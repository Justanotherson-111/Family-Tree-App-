add_library(ui
    FamilyTreeView.h
    FamilyTreeView.cpp
    PersonItem.h
    PersonItem.cpp
    FamilyController.h
    FamilyController.cpp
    MenuView.h
    MenuView.cpp
    MenuController.h
    MenuController.cpp
    PersonInspector.h
    PersonInspector.cpp
)

target_include_directories(ui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(ui
    Qt6::Widgets
    Qt6::Core
    Qt6::PrintSupport
    core
    data
)

