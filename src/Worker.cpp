#include "Worker.h"

Worker::Worker() : _wkr_status(_wStatusIdle)
{
	_wkr_parent = nullptr;
	_wkr_ID = -1;
}

Worker::Worker(Manager* _parent, int _id = -1) : _wkr_status(_wStatusIdle)
{
	_wkr_parent = _parent;
	_wkr_ID = _id;
}

Worker::~Worker()
{
	while (_wkr_status == _wStatusActive) {};

	_wkr_thread->join();

	//_wkr_parent->print(std::stringstream() << "Worker ID " << _wkr_ID << " Terminated.");
}

bool Worker::runTask(struct Task _task)
{
	if (_task.t_status == _tskStatusNoAttachementFnc || &_task.t_fn == nullptr)
	{
		//throw std::exception("Error : a function must be attached to this task.");

		//_wkr_parent->print(std::stringstream() << "Error : no function attached");

		return false;
	}
	else
	{
		bool _t_done = false;

		_task.t_status = _tskStatusRunning; // set the task status as RUNNING

		//_wkr_parent->print(std::stringstream() << "Waiting for task id " << _task.t_id << " to be completed...");

		_task.t_fn(); // run the task

		_wkr_parent->print(std::stringstream() << "Task id " << _task.t_id << " completed.");

		_task.t_status = _tskStatusDone; // set the status
	}
	return true;
}

void Worker::_thread_Routine()
{
	while ((_wkr_status == _wStatusActive || _wkr_status == _wStatusIdle || _wkr_parent->_mngr_status == _mngrStatusPaused) && _wkr_parent->_mngr_status != _mngrStatusInactive)
	{
		_wkr_parent->_mutex.lock();

		if (_wkr_parent->_mngr_status == _mngrStatusActive)
		{
			if (_wkr_parent->getNextTask(_wkr_current_task))
			{
				_wkr_parent->print(std::stringstream() << "Worker id " << _wkr_ID << " executing Task id : " << _wkr_current_task.t_id << ".");

				if (runTask(_wkr_current_task)) {}
				else
				{
					//_wkr_parent->print(std::stringstream() << "Task hasn't been executed, worker " << _wkr_ID << " is shutting down.");

					_wkr_status = _wStatusInactive;
				}
			}
			else
			{
				//_wkr_parent->print(std::stringstream() << "no task found.");

				_wkr_status = _wStatusIdle;

				if (_wkr_parent->isActive() == false)
				{
					//_wkr_parent->print(std::stringstream() << "Manager status is inactive, worker " << _wkr_ID << " is shutting down.");

					_wkr_status = _wStatusInactive;
				}
			}
		}
		else if (_wkr_parent->_mngr_status == _mngrStatusPaused)
		{
			_wkr_parent->print(std::stringstream() << "Manager paused.");
		}

		_wkr_parent->_mutex.unlock();
	}
}

int Worker::getID()
{
	return _wkr_ID;
}

void Worker::setID(int _id)
{
	_wkr_ID = _id;
}

void Worker::run()
{
	if (_wkr_status == _wStatusNoThread)
	{
		_wkr_status = _wStatusActive;
		_wkr_thread = new std::thread(&Worker::_thread_Routine, this);
	}
}

void Worker::setStatus(int _s)
{
	_wkr_status = _s;
}

void Worker::setParent(Manager* _p)
{
	_wkr_parent = _p;
}

int Worker::getStatus()
{
	return _wkr_status;
}