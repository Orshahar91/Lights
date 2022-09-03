#include "Manager.h"
#include <iostream>
#include <fstream>


int main()
{

	Manager manage;
	try
	{
		manage.Run();
	}
	catch (const std::exception& e)
	{
		std::ofstream file("log.txt");
		file << e.what();
		file.close();
	}

}
