#include<iostream>
#include<mutex>
#include<condition_variable>
#include<queue>
#include<thread>
#include<Windows.h>//VS2013�����õ�

std::mutex mut;
std::queue<int> q;
std::condition_variable cond;

void data_preparation_thread()
{
	while (true)
	{
		//����һ��
		Sleep(3000);//1s
		int data = rand() % 20;
		std::lock_guard<std::mutex> lk(mut);
		q.push(data);
		std::cout << "Preparation Data:" << data << std::endl;
		cond.notify_one();//����һ����notify_any()��������
	}
}

void data_processing_thread()
{
	while (true)
	{
		//Sleep(2000);//2s
		std::unique_lock<std::mutex> lk(mut);
		/*
		wait�ȼ��lambda���ʽ��������������򷵻ء�����͵ȴ�����ʱunlock mutȻ���߳�������
		���̱߳����ѣ�������lock mut�������lambda���ʽ�����lambda�����㣬��ôunlock mut�����ȴ���
		��������Ҫ��unique_lock
		*/
		cond.wait(lk, []{return !q.empty(); });//lambda function���ȴ�������[]{return !q.empty(); }
		int data = q.front();
		q.pop();
		lk.unlock();
		std::cout << "Processing Data:" << data << std::endl;
	}
}
int main()
{
	std::thread t1(data_preparation_thread);
	std::thread t2(data_processing_thread);
	t1.join();
	t2.join();
	return 0;
}