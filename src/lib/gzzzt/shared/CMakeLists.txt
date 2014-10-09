include_directories(${Boost_INCLUDE_DIRS})

file(GLOB LIBGZZZTSHARED0_SRC "*.cc")

add_library(gzzzt-shared0 SHARED
  ${LIBGZZZTSHARED0_SRC}
)

target_link_libraries(gzzzt-shared0
  ${Boost_LIBRARIES}
)

set_target_properties(gzzzt-shared0
  PROPERTIES
  VERSION ${CPACK_PACKAGE_VERSION}
  SOVERSION ${CPACK_PACKAGE_VERSION_MAJOR}
)

install(
  TARGETS gzzzt-shared0
  LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
  ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
)
