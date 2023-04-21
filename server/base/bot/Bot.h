#pragma once

#include "../order/OrderAbstract.h"

#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>

using namespace std;

class Bot {
protected:
	queue<OrderAbstract *> m_queue;
	thread m_thread;
	mutex m_mutex;
	condition_variable m_sync;

public:
	Bot() {
		m_queue = queue<OrderAbstract *>();
		m_thread = thread(&Bot::processOrders, this);
	};

	~Bot() {
		m_thread.join();
	}

	void processOrder(OrderAbstract *order) {
		unique_lock lock(m_mutex);
		m_queue.push(order);
		m_sync.notify_all();
	}

protected:
	void processOrders() {
		while(true) {
			unique_lock lock(m_mutex);
			m_sync.wait(lock);
			OrderAbstract *order = m_queue.front();
		}
	}
};
