//
// Created by Orsan Awwad on 14/01/2019.
//

#include "ThreadPool.h"

Task *TasksQueue::pop() {
    std::lock_guard<std::mutex> g(mut);
    if (tasks.empty()) {
        return nullptr;
    }
    auto task = tasks.front();
    tasks.pop();
    return task;
}

bool TasksQueue::empty() const {
    std::lock_guard<std::mutex> g(mut);
    return tasks.empty();
}

void TasksQueue::push(Task *task) {
    if (task == nullptr) {
        throw std::invalid_argument("Task should not be null");
    }
    std::lock_guard<std::mutex> g(mut);
    tasks.push(task);
    queue_cond_var.notify_one();
}

void TasksQueue::wait() const {
    std::unique_lock<std::mutex> ul(mut);
    if (stop_queue) return;
    queue_cond_var.wait(ul);
}

bool TasksQueue::stop() const {
    return stop_queue;
}

void TasksQueue::exit() {
    std::lock_guard<std::mutex> g(mut);
    stop_queue = true;
    queue_cond_var.notify_all();
}

ThreadPool::ThreadPool() {
    for (int i = 0; i < THREAD_POOL_SIZE; ++i) {
        workers.push(std::thread(&ThreadPool::worker, this));
    }
}

void ThreadPool::worker() {
    while (!tasks_queue.stop()) {
        tasks_queue.wait();

        Task* task = tasks_queue.pop();
        if (task) {
            task->execute();
            delete task;
            task = NULL;
        }
    }
}

void ThreadPool::exit() {
    this->tasks_queue.exit();
    while (!this->workers.empty()) {
        this->workers.front().join();
        this->workers.pop();
    }
}

void ThreadPool::addTask(Task *task) {
    this->tasks_queue.push(task);
}

ClientHandlerTaskAdapter::ClientHandlerTaskAdapter(
        server_side::IClientHandler *clientHandler,
        const posix_sockets::TCPClient &client) : clientHandler(clientHandler), client(client) {}

void ClientHandlerTaskAdapter::execute() {
    this->clientHandler->handleClient(client);
}

ClientHandlerTaskAdapter::~ClientHandlerTaskAdapter() {}