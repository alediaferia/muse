cmake_minimum_required(VERSION 2.6)

CONFIGURE_FILE(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
  IMMEDIATE @ONLY)

ADD_CUSTOM_TARGET(uninstall
  "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake")

######################### The Project ##################################
project (Muse)

find_package(Qt4 REQUIRED)
find_package(KDE4)

include(${QT_USE_FILE})
if (KDE4_FOUND)
    include(KDE4Defaults)
    include_directories(${PHONON_INCLUDE_DIR})
    message(STATUS "Found Phonon includes: ${PHONON_INCLUDE_DIR}")
    set (PHONON_LINK ${PHONON_LIBRARY})
elseif (KDE4_FOUND)
    set (PHONON_LINK ${QT_PHONON_LIBRARY})
endif(KDE4_FOUND)

set (Muse_SRCS
main.cpp
mainwindow.cpp
museview.cpp
musemediabutton.cpp
musescene.cpp
musemediacontrols.cpp
musevideowidget.cpp
musemediaengine.cpp
)

set (muse_UIS
    mainwindow.ui
)

set (muse_RCS
    resource.qrc
)

include_directories(${CMAKE_CURRENT_BINARY_DIR}
                    ${CMAKE_CURRENT_SOURCE_DIR}
)

qt4_wrap_ui(Muse_SRCS ${muse_UIS})
qt4_add_resources( Muse_SRCS ${muse_RCS})
qt4_automoc(${Muse_SRCS})

add_executable(muse ${Muse_SRCS})
target_link_libraries(muse ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} ${QT_QTSVG_LIBRARY} ${PHONON_LINK})

install( TARGETS muse RUNTIME DESTINATION bin)
