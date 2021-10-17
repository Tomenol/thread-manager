#include "Manager.h"

Manager::Manager() : Manager(5)
{

}

Manager::Manager(int _cnt) : _wkr_cnt(_cnt)
{
	createWorkers(_cnt, _wStatusNoThread);
}

void Manager::createWorkers(int _n, int _status)
{
	_wkr_cnt = _n;

	_workers = new Worker[_n];

	for (int i = 0; i < _wkr_cnt; i++)
	{
		_workers[i].setStatus(_status);
		_workers[i].setParent(this);
		_workers[i].setID(i);
	}
}

bool Manager::isActive()
{
	if (_mngr_status == _mngrStatusActive) return true;
	else return false;
}

void Manager::stop()
{
	_mngr_status = _mngrStatusInactive;

	waitForTasks();

	delete[] _workers;

	if (_tsk_queue.empty() == false)
	{
		_mutex.lock();
		_tsk_queue.clear();
		_mutex.unlock();
	}
}

void Manager::printTaskQueue()
{
	_mutex.lock();
	for (int i = 0; i < _tsk_queue.size(); i++)
	{
		print(std::stringstream() << "Task ID " << i << " : " << &_tsk_queue[i]);
	}
	_mutex.unlock();
}

void Manager::printStatus()
{
	print(std::stringstream() << "Thread Manager Status :\n");
	
	for (int i = 0; i < _wkr_cnt; i++)
		print(std::stringstream() << "	Worker " << i << " is " << (_workers[i].getStatus() == 1 ? "Active" : "Inactive"));
}

bool Manager::getNextTask(struct Task &_tsk)
{
	bool _iflag = false;

	if (_tsk_queue.empty() == false)
	{
		_tsk = _tsk_queue.front();
		_tsk_queue.pop_front();

		_iflag = true;
	}

	return _iflag;
}

void Manager::waitForTasks()
{
	int _wkr_done, _cnt = 0;
	bool _empt = false;

	print(std::stringstream() << "Waiting for tasks to be completed...");

	do
	{
		_cnt = 0;

		for (int n = 0; n < _wkr_cnt; n++)
		{
			if (_workers[n].getStatus() == _wStatusInactive || _workers[n].getStatus() == _wStatusIdle)
			{
				_cnt++;
			}	
		}	

		_mutex.lock();
		_empt = _tsk_queue.empty();
		_mutex.unlock();

	} while (_empt == false || _cnt < _wkr_cnt);

	print(std::stringstream() << "All tasks are completed.");
}

void Manager::start()
{
	if (_mngr_status != _mngrStatusActive)
	{
		_mngr_status = _mngrStatusActive;

		for (int i = 0; i < _wkr_cnt; i++)
		{
			_workers[i].run();
		}
	}
}

void Manager::pause()
{
	_mutex.lock();
	_mngr_status = _mngrStatusPaused;
	_mutex.unlock();
}

void Manager::unpause()
{
	_mutex.lock();
	_mngr_status = _mngrStatusActive;
	_mutex.unlock();
}
