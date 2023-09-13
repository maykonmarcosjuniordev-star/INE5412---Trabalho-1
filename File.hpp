#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "ProcessParams.hpp"

class File
{
private:
	std::ifstream myfile;

public:
	File()
	{
		myfile.open("entrada.txt");
		if (!myfile.is_open())
		{
			std::cout << "Erro ao abrir o arquivo!\n";
		}
	}

	void read_file(std::vector<ProcessParams *> &processes)
	{

		int a, b, c;

		if (!myfile.is_open())
		{
			std::cout << "Arquivo não está aberto!\n";
		}
		int id = 0;
		while (myfile >> a >> b >> c)
		{
			id++;
			processes.push_back(&ProcessParams(a, b, c, id));
		}
	}
};
