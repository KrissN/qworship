set(QWORSHIP_SOURCES
  main.cpp
  Lyrics.cpp
  LyricsSection.cpp)

file(GLOB QWORSHIP_TRANSLATIONS ${CMAKE_CURRENT_SOURCE_DIR}/lang/*.ts)

qt5_create_translation(QWORSHIP_QMFILES ${CMAKE_CURRENT_SOURCE_DIR} ${QWORSHIP_TRANSLATIONS})

set(LANG_QRC "<RCC><qresource prefix=\"/lang\">")
foreach(QMF ${QWORSHIP_QMFILES})
  get_filename_component(QMF_FNAME "${QMF}" NAME)
  set(LANG_QRC "${LANG_QRC}<file alias=\"qworship_${QMF_FNAME}\">${QMF}</file>")
endforeach(QMF ${QWORSHIP_QMFILES})
set(LANG_QRC "${LANG_QRC}</qresource></RCC>")

file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/translations.qrc "${LANG_QRC}")

qt5_add_resources(QWORSHIP_RESOURCES qworship.qrc ${CMAKE_CURRENT_BINARY_DIR}/translations.qrc OPTIONS --compress 9 --threshold 0)

include_directories(Qt5::Quick)

add_executable(qworship WIN32 ${QWORSHIP_SOURCES} ${QWORSHIP_RESOURCES})

target_link_libraries(qworship Qt5::Quick)
