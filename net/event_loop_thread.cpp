#include <iostream>
#include <cassert>
#include "event_loop_thread.h"
#include "base/macro.h"

namespace hyper {
namespace net {
EventLoopThread::EventLoopThread() {
    m_quit.store(false);
    m_eventLoop = nullptr;
}

bool EventLoopThread::start() {
    // HYPER_COMPARE(this->init(), 0, !=, return false, "EventLoopThread start failed");
    m_thread = std::thread(&EventLoopThread::loop, this);
    return true;
}

void EventLoopThread::loop() {
    do {
        m_eventLoop->loop();
    } while (!m_quit);
}

int EventLoopThread::init() {
    m_eventLoop = std::make_shared<EventLoop>();
    HYPER_COMPARE(m_eventLoop, nullptr, ==, return 1, "EventLoopThread make failed");
    HYPER_COMPARE(m_eventLoop->init(), true, !=, return 1, "EventLoopThread init failed");
    return 0;
}

inline void EventLoopThread::addNotification(IChannel* channel) {
    channel->setEventLoop(m_eventLoop);
    m_eventLoop->addNotification(channel);
}

inline void EventLoopThread::quit() {
    m_quit.store(true);
}

void EventLoopThread::waitingQuit() {
    m_thread.join();
}
}
}