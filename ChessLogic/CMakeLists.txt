project(ChessLogic)

file(GLOB_RECURSE CHESSLOGIC_SRC CONFIG_DEPENDS
    *.cpp
    *.h
)

add_library(ChessLogic SHARED ${CHESSLOGIC_SRC})
target_include_directories(ChessLogic PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_compile_definitions(ChessLogic PRIVATE CHESSLOGIC_EXPORTS)
