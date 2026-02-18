add_library(core
    FamilyTree.h
    FamilyTree.cpp

    entities/PersonNode.h
    entities/PersonNode.cpp

    rules/FamilyRules.h
    rules/FamilyRules.cpp

    services/BranchAnalyzer.h
    services/BranchAnalyzer.cpp
)


target_include_directories(core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(core
    Qt6::Core
)