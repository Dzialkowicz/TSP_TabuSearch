#pragma once
#ifndef TABOOQUEUE_H
#define	TABOOQUEUE_H

#include <vector>

using namespace std;
struct movement {
	int left;
	int right;
	movement()
	{
		left = -1;
		right = -1;
	}
	movement(int left, int right)
	{
		this->left = left;
		this->right = right;
	}
};

class TabooQueue {
public:

	TabooQueue(int queueLength);
	int getLength() { return length; };
	void add_mov(movement r);
	movement get(int i);
	TabooQueue(const TabooQueue& orig);
	virtual ~TabooQueue();

private:
	int length;
	int act_length;
	int begin;
	vector <movement> queue;
};

#endif	/* KOLEJKATABU_H */
