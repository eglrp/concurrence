#include <iostream>
#include <thread> //¢Ù
void hello() //¢Ú
{
	std::cout << "Hello Concurrent World\n";
}
int main()
{
	std::thread t(hello); //¢Û
	t.join(); //¢Ü

	return 0;
}