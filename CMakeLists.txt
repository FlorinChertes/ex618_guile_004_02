# set minimum cmake version
cmake_minimum_required(VERSION 3.18 FATAL_ERROR)

# project name and language
project (ex618_guile_004_02_prj  LANGUAGES CXX)

set(INCLUDE_LOCAL_DIRS "test/inc" "lib/inc" "inc")

SET(INCLUDE_DIRS "C:/Qt6_9/6.9.0/mingw_64/include/QtWidgets")
SET(QT_LIB_DIR "C:/Qt6_9/6.9.0/mingw_64/lib")

include_directories(${INCLUDE_DIRS})
link_directories(${QT_LIB_DIR})

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Qml)

# Enable the AUTOMOC feature
set(CMAKE_AUTOMOC ON)

#------------------------------------------------------------------------------
# add app
#------------------------------------------------------------------------------
SET(GUILE_APP_NAME "guile_app_04_02_01")
add_executable(${GUILE_APP_NAME}

	inc/widget_factory.h
	src/widget_factory.cpp

	inc/dialog_dynamic.h
	src/dialog_dynamic.cpp
	
	main/main_01.cpp
)
target_link_libraries(${GUILE_APP_NAME} PRIVATE Qt6::Core Qt6::Widgets Qt6::Qml)
target_include_directories(${GUILE_APP_NAME} PUBLIC ${INCLUDE_DIRS} ${INCLUDE_LOCAL_DIRS})


#------------------------------------------------------------------------------
# add app 2
#------------------------------------------------------------------------------
SET(GUILE_APP_NAME_02 "guile_app_04_02_02")
add_executable(${GUILE_APP_NAME_02}

	inc/widget_factory_02.h
	src/widget_factory_02.cpp

	inc/dialog_dynamic_02.h
	src/dialog_dynamic_02.cpp
	
	main/main_02.cpp
)
target_link_libraries(${GUILE_APP_NAME_02} PRIVATE Qt6::Core Qt6::Widgets Qt6::Qml)
target_include_directories(${GUILE_APP_NAME_02} PUBLIC ${INCLUDE_DIRS} ${INCLUDE_LOCAL_DIRS})

#------------------------------------------------------------------------------
# add app 4
#------------------------------------------------------------------------------
SET(GUILE_APP_NAME_04 "guile_app_04_02_04")
add_executable(${GUILE_APP_NAME_04}

	inc/evaluater.h
	inc/caller.h
	inc/console_logger.h

	inc/constructable.h

	inc/date_time.h
	src/date_time.cpp

	inc/widget_factory_04.h
	src/widget_factory_04.cpp

	inc/dialog_dynamic_04.h
	src/dialog_dynamic_04.cpp

	main/main_04.cpp
)
target_link_libraries(${GUILE_APP_NAME_04} PRIVATE Qt6::Core Qt6::Widgets Qt6::Qml)
target_include_directories(${GUILE_APP_NAME_04} PUBLIC ${INCLUDE_DIRS} ${INCLUDE_LOCAL_DIRS})