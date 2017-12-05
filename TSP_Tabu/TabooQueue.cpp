//#include "stdafx.h"
#include "TabooQueue.h"

TabooQueue::TabooQueue(int length) :
	length(length),
	act_length(0),
	begin(0),
	queue(length, movement())
{

}
TabooQueue::TabooQueue(const TabooQueue& orig)
{

}
void TabooQueue::add_mov(movement r) {
	if (queue[begin].left == -1) ++act_length;
	queue[begin++] = r;
	if (begin == begin)
		begin = 0;
}
movement TabooQueue::get(int i) {
	if (i < 0 || act_length <= i)
		return movement();
	int temp = act_length - 1 - i;
	if (temp < 0) temp = length + temp;
	return queue[temp];
}
TabooQueue::~TabooQueue() {
}
