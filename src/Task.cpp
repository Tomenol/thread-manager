#include "Task.h"
/*
#include "Manager.h"

Task::Task()
{
	_tsk_status = _tskStatusNoAttachementFnc;
	_tsk_id = -1;
}

Task::Task(std::function<void()> _t_fn)
	:
	_tsk_fnc(_t_fn), _tsk_id(-1)
{
	_tsk_status = _tskStatusIdle;
}

Task::Task(std::function<void()> _t_fn, int _id) :
	_tsk_fnc(_t_fn), _tsk_id(_id)
{
	_tsk_status = _tskStatusIdle;
}

void Task::deleteTask()
{
	if (_tsk_fnc != nullptr)
	{

	}

	_tsk_status = _tskStatusDone; // set the status as Done
}

bool Task::runTask()
{
	if (_tsk_status == _tskStatusNoAttachementFnc || &_tsk_fnc == nullptr)
	{
		//throw std::exception("Error : a function must be attached to this task.");

		//_tsk_parent->//print(std::stringstream() << "Error : no function attached");

		return false;
	}
	else
	{
		bool _t_done = false;

		_tsk_status = _tskStatusRunning; // set the task status as RUNNING

		//_tsk_parent->//print(std::stringstream() << "Waiting for task id " << _tsk_id << " to be completed...");

		_tsk_fnc(); // run the task

		//_tsk_parent->//print(std::stringstream() << "Task id " << _tsk_id << " completed.");

		_tsk_status = _tskStatusDone; // set the status
	}
	return true;
}

*/