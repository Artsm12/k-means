#include <iostream>
#include <fstream>
#include <cmath>
#include <ctime>

//QUANT: quantidade de objetos a serem avaliados
//CAR: quantidade de caracteristcas de cada objeto a serem levadas em consideracao
#define QUANT 150
#define CAR 4

using namespace std;

//Estrutura que define o cluster, composta pelo seu centroide e pelos seus membros
struct Cluster{
    float centroide[CAR];
    float membros[QUANT][CAR];
};

/*******************************
* inicializarCluster(): recebe um cluster como parametro e devolve o cluster com o centroide inicializado e com seus membros zerados
* k_means(): realiza n iteracoes do algoritmo k-means
* verificaDistancias(): recebe as distancias entre um ponto especifico e os centroides de cada cluster e devolve o index da menor distancia
*******************************/
Cluster inicializarCluster(float dados[QUANT][CAR], Cluster cluster);
void k_means(float dados[QUANT][CAR], Cluster cluster1, Cluster cluster2, Cluster cluster3, int n);
int verificaDistancias(float dist1, float dist2, float dist3);

int main(){

    //Abre o arquivo de texto
    fstream arq;
    arq.open("iris.data");

    srand(time(NULL));

    //Define e inicializa uma matriz QUANT X VAR que contem todos os dados da database
    float dados[QUANT][CAR];
    for(int i = 0; i < QUANT; i++){
        for(int j = 0; j < CAR; j++){
            arq >> dados[i][j];
        }
    }

    //Fecha o arquivo de texto
    arq.close();

    //Inicializa os clusters e imprime a posicao incial dos centroides
    cout << "Posicao inicial do centroide 1:\n";
    Cluster cluster1 = inicializarCluster(dados, cluster1);
    cout << "Posicao inicial do centroide 2:\n";
    Cluster cluster2 = inicializarCluster(dados, cluster2);
    cout << "Posicao inicial do centroide 3:\n";
    Cluster cluster3 = inicializarCluster(dados, cluster3);

    //Quantidade de vezes que será realizado o metodo k-means (input do usuario)
    int n;
    cin >> n;
    //Inicio do k-means
    k_means(dados, cluster1, cluster2, cluster3, n);

    return 0;
}

Cluster inicializarCluster(float dados[QUANT][CAR], Cluster cluster){
    int k = rand() % 150;  
    for(int i = 0; i < CAR; i++){
        cluster.centroide[i] = dados[k][i];
    }
    for(int i = 0; i < QUANT; i++){
        for(int j = 0; j < CAR; j++){
            cluster.membros[i][j] = 0;
        }
    }  
    for(int i = 0; i < CAR; i++){
        cout << cluster.centroide[i] << " ";
    }
    cout << '\n';
    return cluster;
}

void k_means(float dados[QUANT][CAR], Cluster cluster1, Cluster cluster2, Cluster cluster3, int n){

    int cont = 0;
    while(cont < n){

        //Variaveis de controle utilizadas para a associacao de pontos para cada cluster
        int i1 = 0, i2 = 0, i3 = 0;

        for(int i = 0; i < QUANT; i++){
            float dist1 = 0, dist2 = 0, dist3 = 0;

            //Calculo da distancia euclidiana entre o ponto em questao e os clusters
            for(int j = 0; j < CAR; j++){
                dist1 += pow(dados[i][j] - cluster1.centroide[j], 2);
                dist2 += pow(dados[i][j] - cluster2.centroide[j], 2);
                dist3 += pow(dados[i][j] - cluster3.centroide[j], 2);
            }

            dist1 = sqrt(dist1);
            dist2 = sqrt(dist2);
            dist3 = sqrt(dist3);

            //Verifica as distancias e confere qual delas é a menor, associando o ponto ao cluster correto
            switch (verificaDistancias(dist1, dist2, dist3)){

            case 1:
                for(int k = 0; k < CAR; k++){
                    cluster1.membros[i1][k] = dados[i][k];
                }
                i1++;
                break;

            case 2:
                for(int k = 0; k < CAR; k++){
                    cluster2.membros[i2][k] = dados[i][k];
                }
                i2++;
                break;

            case 3:
                for(int k = 0; k < CAR; k++){
                    cluster3.membros[i3][k] = dados[i][k];
                }
                i3++;
                break;
            
            default:
                break;
            }
        }

        //Variaveis que armazenam as somas dos membros de cada cluster, para a reinizializacao dos centroides
        float soma1, soma2, soma3;

        for(int i = 0; i < CAR; i++){
            soma1 = 0;
            int j;
            for(j = 0; cluster1.membros[j][0] != 0; j++){
                soma1 += cluster1.membros[j][i];
            }
            cluster1.centroide[i] = soma1 / float(j);
        }

        for(int i = 0; i < CAR; i++){
            soma2 = 0;
            int j;
            for(j = 0; cluster2.membros[j][0] != 0; j++){
                soma2 += cluster2.membros[j][i];
            }
            cluster2.centroide[i] = soma2 / float(j);
        }

        for(int i = 0; i < CAR; i++){
            soma3 = 0;
            int j;
            for(j = 0; cluster3.membros[j][0] != 0; j++){
                soma3 += cluster3.membros[j][i];
            }
            cluster3.centroide[i] = soma3 / float(j);
        }

        //Os clusters sao zerados entre uma iteracao e outra, para que a associacao de pontos ocorra novamente (exceto na ultima iteracao)
        if(cont < n-1){
            for(int j = 0; j < QUANT; j++){
                for(int k = 0; k < CAR; k++){
                    cluster1.membros[j][k] = 0;
                    cluster2.membros[j][k] = 0;
                    cluster3.membros[j][k] = 0;
                }
            }
        }
        cont++;
    }
    
    //Impressao dos membros de cada um dos clusters
    cout << "Cluster 1:\n";
    for(int i = 0; cluster1.membros[i][0] != 0; i++){
        for(int j = 0; j < CAR; j++){
                cout << cluster1.membros[i][j] << " ";
                
        }
        cout << '\n';
    }

    cout << "\nCluster 2:\n";
    for(int i = 0; cluster2.membros[i][0] != 0; i++){
        for(int j = 0; j < CAR; j++){
            cout << cluster2.membros[i][j] << " ";
        }
        cout << '\n';
    }

    cout << "\nCluster 3:\n";
    for(int i = 0; cluster3.membros[i][0] != 0; i++){
        for(int j = 0; j < CAR; j++){
            cout << cluster3.membros[i][j] << " ";
        }
        cout << '\n';
    }
}

int verificaDistancias(float dist1, float dist2, float dist3){
    if(dist1 < dist2 && dist1 < dist3){
        return 1;
    }
    else if(dist2 < dist1 && dist2 < dist3){
        return 2;
    }
    else if(dist3 < dist1 && dist3 < dist2){
        return 3;
    }
    else{
        return 0;
    }
}
