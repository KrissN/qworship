
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../src/)

add_executable(tu_lyricssection tu_LyricsSection.cpp ../src/LyricsSection.cpp)
target_link_libraries(tu_lyricssection Qt5::Test)

add_executable(tu_lyrics tu_Lyrics.cpp ../src/Lyrics.cpp ../src/LyricsSection.cpp)
target_link_libraries(tu_lyrics Qt5::Test)

add_test(tu_lyricssection ${CMAKE_CURRENT_BINARY_DIR}/tu_lyricssection)
add_test(tu_lyrics ${CMAKE_CURRENT_BINARY_DIR}/tu_lyrics)
