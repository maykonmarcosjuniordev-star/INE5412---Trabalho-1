#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "ProcessParams.hpp"

using namespace std;

class File
{
public:
	File()
	{
		myfile.open("entrada.txt");
		if (!myfile.is_open())
		{
			cout << "Erro ao abrir o arquivo!\n";
		}
	}

	void read_file(vector<ProcessParams *> &processes)
	{

		int a, b, c;

		if (!myfile.is_open())
		{
			cout << "Arquivo não está aberto!" << endl;
		}

		while (myfile >> a >> b >> c)
		{
			processes.push_back(&ProcessParams(a, b, c));
		}
	}

private:
	ifstream myfile;
};
