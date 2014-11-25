include_directories(${Boost_INCLUDE_DIRS})

file(GLOB GZZZT_SRC "*.cc")

add_executable(gzzzt ${GZZZT_SRC})

target_link_libraries(gzzzt
  gzzzt0
  gzzzt-shared0
  ${Boost_LIBRARIES}
  ${CMAKE_THREAD_LIBS_INIT}
)

install(
  TARGETS gzzzt
  RUNTIME DESTINATION games
)
