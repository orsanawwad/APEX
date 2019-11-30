cmake_minimum_required(VERSION 3.12)
project(AP-MS2)

set(CMAKE_CXX_STANDARD 14)

add_executable(AP-MS2 main.cpp IServer.h IClientHandler.h ISolver.h ICacheManager.h MySerialServer.cpp MySerialServer.h MyTestClientHandler.cpp MyTestClientHandler.h FileCacheManager.cpp FileCacheManager.h Base64Codec.h Base64Codec.cpp StringReverser.cpp StringReverser.h ISearchable.h ISearcher.h State.h MazeDomain.cpp MazeDomain.h BestFirstSearch.cpp BestFirstSearch.h MyPriorityQueue.h Searcher.h Solution.h SearcherSolution.h Searchable.h DFS.cpp DFS.h BFS.cpp BFS.h AstarAlgo.cpp AstarAlgo.h MyParallelServer.cpp MyParallelServer.h POSIXSockets.h POSIXSockets.cpp ThreadPool.cpp ThreadPool.h MyClientHandler.cpp MyClientHandler.h SearchableSolverAdapter.cpp SearchableSolverAdapter.h)

find_package(Threads REQUIRED)
if(THREADS_HAVE_PTHREAD_ARG)
 target_compile_options(AP-MS2 PUBLIC "-pthread")
endif()
if(CMAKE_THREAD_LIBS_INIT)
 target_link_libraries(AP-MS2 "${CMAKE_THREAD_LIBS_INIT}")
endif()
