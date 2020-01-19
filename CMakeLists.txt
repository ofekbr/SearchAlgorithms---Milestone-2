cmake_minimum_required(VERSION 3.15)
project(ex4)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread)

add_executable(ex4 main.cpp Server.h SerialServer.h SerialServer.cpp ClientHandler.h
        MyTestClientHandler.cpp CacheManager.h Solver.h FileCacheManager.h Matrix.h State.h Searchable.h Searcher.h ObjectAdapter.h BestFS.h MyPriorityQueue.h)
