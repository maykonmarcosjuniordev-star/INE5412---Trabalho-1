#include <iostream>

class SJF			//Shortest Job First
{
    int execution_time = 0;
    void exec_STJ(Processo *[p]) {
        //mergeSort(*p, 0, p.length);

        for (int i = 0; i < p.length; i++) {
            if (p[i].executando == 1) {
                p[i].executando = 2;
            }
            execution_time+=p[i].duracao;

            print_status(execution_time, p[i].ID, p[i].executando);
            p[i].executando = 3;
        }
    }
};




// void mergeSort(int *vetor, int posicaoInicio, int posicaoFim) {
//     int i, j, k, metadeTamanho, *vetorTemp;
//     if(posicaoInicio == posicaoFim) return;
//     metadeTamanho = (posicaoInicio + posicaoFim ) / 2;

//     mergeSort(vetor, posicaoInicio, metadeTamanho);
//     mergeSort(vetor, metadeTamanho + 1, posicaoFim);

//     i = posicaoInicio;
//     j = metadeTamanho + 1;
//     k = 0;
//     vetorTemp = (int *) malloc(sizeof(int) * (posicaoFim - posicaoInicio + 1));

//     while(i < metadeTamanho + 1 || j  < posicaoFim + 1) {
//         if (i == metadeTamanho + 1 ) { 
//             vetorTemp[k] = vetor[j];
//             j++;
//             k++;
//         }
//         else {
//             if (j == posicaoFim + 1) {
//                 vetorTemp[k] = vetor[i];
//                 i++;
//                 k++;
//             }
//             else {
//                 if (vetor[i] < vetor[j]) {
//                     vetorTemp[k] = vetor[i];
//                     i++;
//                     k++;
//                 }
//                 else {
//                     vetorTemp[k] = vetor[j];
//                     j++;
//                     k++;
//                 }
//             }
//         }

//     }
//     for(i = posicaoInicio; i <= posicaoFim; i++) {
//         vetor[i] = vetorTemp[i - posicaoInicio];
//     }
//     free(vetorTemp);
// }



