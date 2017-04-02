#include <iostream>
#include <thread>
void thread_func(int &sum)
{
	for (int i = 1; i <= 100; ++i) {
		sum += i;
	}
}
int main(void)
{
	int sum = 0;
	std::thread thd(thread_func, std::ref(sum));
	thd.join();
	std::cout << "sum is " << sum << std::endl;
	std::cout << std::thread::hardware_concurrency() << std::endl;
	return 0;
}