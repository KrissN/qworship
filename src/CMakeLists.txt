set(QWORSHIP_SOURCES
  main.cpp)

qt5_add_resources(QWORSHIP_RESOURCES qworship.qrc OPTIONS --compress 9 --threshold 0)

include_directories(Qt5::Quick)

add_executable(qworship WIN32 ${QWORSHIP_SOURCES} ${QWORSHIP_RESOURCES})

target_link_libraries(qworship Qt5::Quick)
