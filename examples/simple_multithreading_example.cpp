#include "sch.h"

#include <time.h>

#include "Manager.h"

bool fn(int, int*);

bool fn(int a, int *r)
{
	*r = a;
	
	Sleep(10);

	return true;
}

int main()
{
	int a;

	Manager m(5);

	for (int i = 0; i < 100; i++)
	{
		m.createTask(fn, i, i, &a);
		cout << "New task created." << endl;
	}

	m.start();
	m.waitForTasks();

	Sleep(100);
	
	cout << "Thread manager paused..." << endl;
	m.pause();

	for (int i = 0; i < 10; i++)
	{
		m.createTask(fn, i, i, &a);
		cout << "New task created." << endl;
	}
	
	Sleep(100);
	
	cout << "Thread manager starting..." << endl;
	m.unpause();
	
	// wait for the threamanager to complete all tasks
	m.waitForTasks();
	m.stop();

	cout << "Thread manager stopped..." << endl;

	return 0;
}
