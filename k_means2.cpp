#include <iostream>
#include <fstream>  //Utilizada apenas para a leitura da database em formato .txt
#include <ctime>    //Utilizada para a geração de numeros aleatorios para a inicializacao dos centros
#include <cmath>

//Quantidade de plantas na database
#define QUANT 30

//Quantas variáveis estão sendo levadas em consideração
#define VAR 2

using namespace std;

/**********************************
 * inicializarCentros: iniciliza os centros de forma aleatória antes de começarem as iteracoes
 * atribuicaoDePontos: atribui todos os pontos ao cluster que esteja mais próximo
 * verificarDistancia: verifica qual cluster está mais perto de um determinado dado
 * reinicializarClusters: reinicializa cada centro de acordo com a media de seu intergrantes
 * imprimeClusters: imprime todos os integrantes de cada cluster
**********************************/
void inicializarCentros(float cluster1[QUANT+1][VAR], float cluster2[QUANT+1][VAR], float cluster3[QUANT+1][VAR]);
void atribuicaoDePontos(float plantas[QUANT][VAR], float cluster1[QUANT+1][VAR], float cluster2[QUANT+1][VAR], float cluster3[QUANT+1][VAR]);
int verificarDistancia(float dist1, float dist2, float dist3);
void reinicializarCentros(float cluster1[QUANT+1][VAR], float cluster2[QUANT+1][VAR], float cluster3[QUANT+1][VAR]);
void imprimeClusters(float cluster1[QUANT+1][VAR], float cluster2[QUANT+1][VAR], float cluster3[QUANT+1][VAR]);

int main(){

    //Abre o arquivo
    fstream file;
    file.open("iris.data");
    
    //Define a seed para a aleatorizacao dos clusters 
    srand(time(NULL));

    //Vetor bidimensional que armazena todos os dados utilizados
    float plantas[QUANT][VAR];

    /*
    Definição dos clusters
    As posições dos clusters serão armazenadas nos vetores clusterN[0], com N sendo 1, 2 ou 3
    */
    float cluster1[QUANT+1][VAR];
    float cluster2[QUANT+1][VAR];
    float cluster3[QUANT+1][VAR];

    //Colocando todos os dados no vetor plantas
    for(int i = 0; i < QUANT; i++){
        file >> plantas[i][0] >> plantas[i][1];
    }

    //Os centros são inicializados e cada ponto e atribuido ao seu respectivo cluster
    inicializarCentros(cluster1, cluster2, cluster3);
    atribuicaoDePontos(plantas, cluster1, cluster2, cluster3);

    //Serao feitas 5 iteracoes do metodo k-means
    int i = 0;
    while(i < 5){
        reinicializarCentros(cluster1, cluster2, cluster3);
        atribuicaoDePontos(plantas, cluster1, cluster2, cluster3);
        i++;
    }

    //imprimeClusters(cluster1, cluster2, cluster3);

    return 0;
}

void inicializarCentros(float cluster1[QUANT+1][VAR], float cluster2[QUANT+1][VAR], float cluster3[QUANT+1][VAR]){

    //Escolha aleatória para a posição dos clusters
    cluster1[0][0] = 4 + (rand() % 10 / 10.0);    cluster1[0][1] = 3 + (rand() % 10 / 10.0);
    cluster2[0][0] = 4 + (rand() % 10 / 10.0);    cluster2[0][1] = 3 + (rand() % 10 / 10.0);
    cluster3[0][0] = 4 + (rand() % 10 / 10.0);    cluster3[0][1] = 3 + (rand() % 10 / 10.0);
    cout << "Posicao inicial dos clusters: " << endl;
    cout << "cluster1: " << "(" << cluster1[0][0]  << ", " << cluster1[0][1]<< ")" << endl;
    cout << "cluster2: " << "(" << cluster2[0][0]  << ", " << cluster2[0][1]<< ")" << endl;
    cout << "cluster3: " << "(" << cluster3[0][0]  << ", " << cluster3[0][1]<< ")" << endl;
    cout << endl;
}

void atribuicaoDePontos(float plantas[QUANT][VAR], float cluster1[QUANT+1][VAR], float cluster2[QUANT+1][VAR], float cluster3[QUANT+1][VAR]){

    //Distâncias de entre cada ponto e os clusters
    float dist1, dist2, dist3;
    int i1 = 1, i2 = 1, i3 = 1;

    for(int i = 0; i < QUANT; i++){
        //Calculo das distancias entre o dado em questao e os centros
        dist1 = sqrt(pow(plantas[i][0] - cluster1[0][0], 2) + pow(plantas[i][1] - cluster1[0][1], 2));
        dist2 = sqrt(pow(plantas[i][0] - cluster2[0][0], 2) + pow(plantas[i][1] - cluster2[0][1], 2));
        dist3 = sqrt(pow(plantas[i][0] - cluster3[0][0], 2) + pow(plantas[i][1] - cluster3[0][1], 2));

        switch(verificarDistancia(dist1, dist2, dist3)){
            //Caso a distancia entre o ponto e centro 1 seja a menor, entao aquele dado fara parte do primeiro cluster
            case 1:
                cluster1[i1][0] = plantas[i][0];
                cluster1[i1][1] = plantas[i][1];
                i1++;
                break;
            //Caso a distancia entre o ponto e centro 1 seja a menor, entao aquele dado fara parte do primeiro cluster
            case 2:
                cluster2[i2][0] = plantas[i][0];
                cluster2[i2][1] = plantas[i][1];
                i2++;
                break;
            //Caso a distancia entre o ponto e centro 1 seja a menor, entao aquele dado fara parte do primeiro cluster
            case 3:
                cluster3[i3][0] = plantas[i][0];
                cluster3[i3][1] = plantas[i][1];
                i3++;
                break;
            default: 
                break;
        }
    }
    cout << "Cluster 1: " << endl;
        for(int i = 1; i < i1; i++){
            cout << cluster1[i][0] << " " <<  cluster1[i][1] << endl;
        }
        cout << "Cluster 2: " << endl;
        for(int i = 1; i < i2; i++){
            cout << cluster2[i][0] << " " <<  cluster2[i][1] << endl;
        }
        cout << "Cluster 3: " << endl;
        for(int i = 1; i < i3; i++){
            cout << cluster3[i][0] << " " <<  cluster3[i][1] << endl;
        }
        cout << endl;
}


int verificarDistancia(float dist1, float dist2, float dist3){
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
        if(dist1 == dist2 && dist1 < dist3){
            return 1;
        }
        else if(dist1 == dist3 && dist1 < dist2){
            return 1;
        }
        else if(dist2 == dist3 && dist2 < dist1){
            return 2;
        }
        else{
            return 0;
        }
    }
}

void reinicializarCentros(float cluster1[QUANT+1][VAR], float cluster2[QUANT+1][VAR], float cluster3[QUANT+1][VAR]){

    //Variaveis usadas no calculo da media entre os dados integrantes de um cluster
    float soma0 = 0, soma1= 0;
    float media0, media1;

    //Variaveis de controle, representando os indexes durante a iteracao dos clusters
    int i1, i2, i3;

    if(cluster1[1][0] != 0){
        for(i1 = 1; cluster1[i1][0] != 0; i1++){
            soma0+=cluster1[i1][0];
            soma1+=cluster1[i1][1];
        }
        media0 = soma0 / float(i1);
        media1 = soma1 / float(i1);
    

    cluster1[0][0] = media0;
    cluster1[0][1] = media1;
    }

    soma0 = 0; soma1 = 0;

    if(cluster2[1][0] != 0){
        for(i2 = 1; cluster2[i2][0] != 0; i2++){
            soma0+=cluster2[i2][0];
            soma1+=cluster2[i2][1];
        }
        media0 = soma0 / float(i2);
        media1 = soma1 / float(i2);

        cluster1[0][0] = media0;
        cluster1[0][1] = media1;
    }

    soma0 = 0; soma1 = 0;

    if(cluster1[1][0] != 0){
        for(i3 = 1; cluster3[i3][0] != 0; i3++){
            soma0+=cluster3[i3][0];
            soma1+=cluster3[i2][1];
        }
        media0 = soma0 / float(i3);
        media1 = soma1 / float(i3);
    }

    soma0 = 0; soma1 = 0;

    //Imprime a nova posicao dos centros (determinada nas posicoes clusterN[0][0] e clusterN[0][1]
    cout << "Nova posicao dos centros: " << endl;
    cout << cluster1[0][0] << " " << cluster1[0][1] << endl;
    cout << cluster2[0][0] << " " << cluster2[0][1] << endl;
    cout << cluster3[0][0] << " " << cluster3[0][1] << endl;
    cout << endl;
}

void imprimeClusters(float cluster1[QUANT+1][VAR], float cluster2[QUANT+1][VAR], float cluster3[QUANT+1][VAR]){
    cout << "Cluster 1: " << "(" << cluster1[0][0] << ", " << cluster1[0][1] << ")" << endl;
    for(int i = 1; cluster1[i][0] != 0; i++){
        cout << cluster1[i][0] << " " << cluster1[i][1] << endl;
    }

    cout << "Cluster 2: " << "(" << cluster2[0][0] << ", " << cluster2[0][1] << ")" << endl;
    for(int i = 1; cluster2[i][0] != 0; i++){
        cout << cluster2[i][0] << " " << cluster2[i][1] << endl;
    }

    cout << "Cluster 3: " << "(" << cluster3[0][0] << ", " << cluster3[0][1] << ")" << endl;
    for(int i = 1; cluster3[i][0] != 0; i++){
        cout << cluster3[i][0] << " " << cluster3[i][1] << endl;
    }
}