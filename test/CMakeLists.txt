add_executable(gtest_kmeans gtest_kmeans.cc)
target_link_libraries(gtest_kmeans libgtest.a libgtest_main.a pthread)

add_executable(gtest_topo gtest_topo.cc)
TARGET_LINK_LIBRARIES(gtest_topo libgtest.a libgtest_main.a pthread)
