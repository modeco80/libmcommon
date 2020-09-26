
set(MCOMMON_SOURCES 
	Logger.cpp
	IostreamLoggerSink.cpp
	ThreadPool.cpp
)

# All mcommon public includes.
set(MCOMMON_PUBLIC_INCLUDES
	${PROJECT_SOURCE_DIR}/include/modeco/types.h
	${PROJECT_SOURCE_DIR}/include/modeco/span.h
	${PROJECT_SOURCE_DIR}/include/modeco/current_endian.h
	${PROJECT_SOURCE_DIR}/include/modeco/source_location.h
	${PROJECT_SOURCE_DIR}/include/modeco/Logger.h
	${PROJECT_SOURCE_DIR}/include/modeco/ThreadPool.h
)

add_library(mcommon STATIC ${MCOMMON_SOURCES})

set_property(TARGET mcommon PROPERTY CXX_STANDARD 17)
set_property(TARGET mcommon PROPERTY CXX_STANDARD_REQUIRED ON)

target_include_directories(mcommon PUBLIC ${PROJECT_SOURCE_DIR}/include)

if(_MCOMMON_STDLIB STREQUAL "llvm")
	message(STATUS "Linking c++fs library")
	target_link_libraries(mcommon c++fs)
elseif(_MCOMMON_STDLIB STREQUAL "gnu")
	message(STATUS "Linking stdc++fs library")
	target_link_libraries(mcommon stdc++fs)
endif()


target_link_libraries(mcommon ${CMAKE_THREAD_LIBS_INIT})

if(NOT MCOMMON_DO_NOT_INSTALL)
	set(INSTALL_INC_DIR "${CMAKE_INSTALL_PREFIX}/include/modeco")
	set(INSTALL_LIB_DIR "${CMAKE_INSTALL_PREFIX}/lib")

	install(TARGETS mcommon
		ARCHIVE DESTINATION "${INSTALL_LIB_DIR}"
		LIBRARY DESTINATION "${INSTALL_LIB_DIR}")

	install(FILES ${MCOMMON_PUBLIC_INCLUDES} DESTINATION "${INSTALL_INC_DIR}")
endif()