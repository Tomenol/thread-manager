#pragma once

#define _tskStatusRunning				0x00
#define _tskStatusIdle					0x01
#define _tskStatusNoAttachementFnc		0x02
#define _tskStatusDone					0x03

#define _mngrStatusActive				0x04
#define	_mngrStatusInactive				0x05
#define _mngrStatusPaused				0x06


#include "sch.h"

#include "Worker.h"

struct Task;

class Worker;

class Manager
{
private:
	Worker* _workers;

	deque<struct Task> _tsk_queue;

	std::mutex _cout_mutex;
	std::mutex _mutex;

	int _wkr_cnt;
	int _mngr_status;

	friend Worker;

public:
	Manager();
	Manager(int _cnt);

	void start();
	void stop();
	void printStatus();
	void printTaskQueue();
	void waitForTasks();
	void createWorkers(int _n, int _s);

	void pause();
	void unpause();

	void print(const std::basic_ostream<char>& _ss)
	{
		_cout_mutex.lock();

		cout << "Manager : " << static_cast<const std::stringstream&>(_ss).str() << endl;

		_cout_mutex.unlock();
	}

	bool getNextTask(struct Task &_t);

	template<typename _Fn, typename ..._Args>
	void createTask(_Fn&& _fnc, int _id = -1, _Args&&... _params)
	{
		struct Task _tsk;

		_tsk.t_parent = this;
		_tsk.t_id = _id;
		_tsk.t_status = _tskStatusIdle;
		_tsk.t_fn = bind(_fnc, _params...);

		_mutex.lock();

		_tsk_queue.push_back(_tsk);

		_mutex.unlock();
	}

	template<typename _Fn>
	void createTask(_Fn&& _fnc)
	{
		struct Task _tsk;

		_tsk.t_parent = this;
		_tsk.t_id = -1;
		_tsk.t_status = _tskStatusIdle;
		_tsk.t_fn = bind(_fnc);

		_mutex.lock();
		_tsk_queue.push_back(_tsk);
		_mutex.unlock();
	}

	bool isActive();
};

