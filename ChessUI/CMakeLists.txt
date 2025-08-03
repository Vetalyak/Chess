project(ChessUI)

file(GLOB_RECURSE CHESSUI_SRC CONFIGURE_DEPENDS
    *.cpp
    *.h
)

find_package(SFML 3 REQUIRED COMPONENTS Graphics System Window)
add_executable(ChessUI ${CHESSUI_SRC})
target_link_libraries(ChessUI PRIVATE ChessLogic)

target_link_libraries(ChessUI PRIVATE SFML::Graphics SFML::System SFML::Window)
target_include_directories(ChessUI PRIVATE ${CMAKE_SOURCE_DIR}/ChessLogic/src)

add_custom_command(
    TARGET ChessUI POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:ChessLogic>
        $<TARGET_FILE_DIR:ChessUI>

    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:ChessUI>/assets
)