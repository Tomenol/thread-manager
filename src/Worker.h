#pragma once

#include "sch.h"

#define _wStatusInactive	0x00
#define _wStatusActive		0x01
#define _wStatusIdle		0x02
#define _wStatusNoThread	0x03

class Manager;

struct Task
{
	std::function<void()> t_fn;

	Manager* t_parent;

	int t_id;
	int t_status;
};

#include "Manager.h"

class Worker
{
private:
	int _wkr_status;
	int _wkr_ID;

	struct Task _wkr_current_task;

	std::thread* _wkr_thread;

	Manager* _wkr_parent;

public:
	Worker();
	Worker(Manager* _parent, int _id);

	~Worker();
	
	void _thread_Routine();
	void run();
	

	bool runTask(struct Task _task);

	int getID();
	int getStatus();

	void setStatus(int _s);
	void setParent(Manager* _p);
	void setID(int _id);
};