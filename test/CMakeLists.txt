add_executable(gtest_cluster main.cc)
target_link_libraries(gtest_cluster clustering)

add_executable(gtest_topo gtest_topo.cc)
TARGET_LINK_LIBRARIES(gtest_topo libgtest.a libgtest_main.a pthread  topo)
