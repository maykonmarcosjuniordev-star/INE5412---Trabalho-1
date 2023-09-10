#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "ProcessParams.hpp"

using namespace std;

class File {
	public:
		File() {
			myfile.open("entrada.txt");
			if (!myfile.is_open()) {
				cout << "Erro ao abrir o arquivo!\n";
			}
		}
		
		void read_file(vector<ProcessParams *> &processes) {
		
			int a, b, c;
			
			if (!myfile.is_open()) {
				cout << "Arquivo não está aberto!" << endl;
			}
			
			while (myfile >> a >> b >> c) {
				ProcessParams *p = new ProcessParams(a, b, c);
				processes.push_back(p);
			}

			cout << "Quantidade de processos lidos do arquivo: " << processes.size() << endl;
		}

		void print_processes_params(vector<ProcessParams *> &processes) {
			vector<ProcessParams *>::iterator iter = processes.begin();

			for(; iter < processes.end(); iter++) {
				ProcessParams *p = *iter;
				cout << *p;
			}
		}

	private:
		ifstream myfile;
};
