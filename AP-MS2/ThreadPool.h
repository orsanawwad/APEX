//
// Created by Orsan Awwad on 14/01/2019.
//

#ifndef AP_MS2_THREADPOOL_H
#define AP_MS2_THREADPOOL_H

//#define THREAD_POOL_SIZE std::thread::hardware_concurrency()
#define THREAD_POOL_SIZE 50

#include <thread>
#include <queue>
#include <atomic>
#include <mutex>
#include <string>
#include <iostream>
#include <condition_variable>
#include "IClientHandler.h"

class Task {
public:
    virtual void execute() = 0;
    virtual ~Task() {};
};

class ClientHandlerTaskAdapter : public Task {
    server_side::IClientHandler *clientHandler;
    posix_sockets::TCPClient client;
public:
    ClientHandlerTaskAdapter(server_side::IClientHandler *clientHandler, const posix_sockets::TCPClient &client);
    virtual void execute();

    virtual ~ClientHandlerTaskAdapter();
};

class TasksQueue {
    std::atomic<bool> stop_queue;
    std::queue<Task*> tasks;
    mutable std::condition_variable queue_cond_var;
    mutable std::mutex mut;
public:
    TasksQueue() : stop_queue(false) {}

    Task* pop();

    bool empty() const;

    void push(Task* task);

    void wait() const;

    bool stop() const;

    void exit();
};

class ThreadPool {
    std::queue<std::thread> workers;
    TasksQueue tasks_queue;
    void worker();
public:
    ThreadPool();
    void exit();
    void addTask(Task* task);
};


#endif //AP_MS2_THREADPOOL_H
