include_directories(${Boost_INCLUDE_DIRS})

file(GLOB GZZZTSERVER_SRC "*.cc")

add_executable(gzzzt-server ${GZZZTSERVER_SRC})

target_link_libraries(gzzzt-server
  gzzzt-server0
  gzzzt-shared0
  ${Boost_LIBRARIES}
)

install(
  TARGETS gzzzt-server
  RUNTIME DESTINATION games
)
