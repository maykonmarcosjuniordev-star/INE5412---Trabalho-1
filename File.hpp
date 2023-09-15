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
	~File()
	{
		if (myfile.is_open())
		{
			myfile.close();
		}
	}
	// recebe os parâmetros dos processos a serem escalonados
	void read_file(std::vector<ProcessParams> &not_ready_queue)
	{

		int crea_t, dura_t, prior;

		if (!myfile.is_open())
		{
			std::cout << "Arquivo não está aberto!\n";
		}
		int id = 0;
		while (myfile >> crea_t >> dura_t >> prior)
		{
			id++;
			int i = 0;
			// ordena os processos pelo tempo de criação
			while (i < not_ready_queue.size() && not_ready_queue[i].get_creation_time() <= crea_t)
			{
				i++;
			}
			not_ready_queue.insert(not_ready_queue.begin() + i, ProcessParams(crea_t, dura_t, prior, id));
		}
	}
};
