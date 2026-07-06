cmake_minimum_required(VERSION 3.16)

project(projetograficos LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Adicione "Widgets" no primeiro find_package
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Widgets)

# 2. Adicione "Widgets" no segundo find_package também
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets)

add_executable(projetograficos
  main.cpp
  janelaprincipal.h
  graficolinha.h    graficobarras.h graficobarras.cpp
  graficolinha.cpp
  janelaprincipal.cpp
  graficobarras.h
  graficosetores.h
  graficosetores.cpp
  imagens.qrc
)

# CORREÇÃO AQUI: Linkar também o Widgets
target_link_libraries(projetograficos PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Widgets
)

include(GNUInstallDirs)
install(TARGETS projetograficos
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
