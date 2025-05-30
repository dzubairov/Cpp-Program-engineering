//////////////////////////////////////

#include <cassert>
#include <queue>

//////////////////////////////////////

int main()
{
	std::priority_queue < int > queue;

//  ----------------------------------

	queue.push(1);

	queue.push(3);

	queue.push(2);

//  ----------------------------------

	assert(queue.top() == 3);

//  ----------------------------------

	queue.pop();

//  ----------------------------------

	assert(queue.top() == 2);
}

//////////////////////////////////////