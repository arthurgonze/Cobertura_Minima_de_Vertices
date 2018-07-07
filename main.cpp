#include <iostream>
#include <random>
#include <fstream>
#include <algorithm>
#include "Adjacente.h"
#include "Grafo.h"

using namespace std;

fstream inputFile, outputFile;
long tamanhoGrafo = 1, kRegular;
Grafo grafo;    //cria grafo não direcionado

void apresentacaoTrabalho();

void criaCabecalho(long _tamanhoGrafo);

int exibeMenu();

void criarGrafo(long _tamanhoGrafo);

void lerAdjcencias(bool isContainPeso);

void verificaGrauVertice();

void verificaNulo();

void verificaTrivial();

void verificaOrdemG();

void verificaGrauGrafo();

void listaAdjacentesVertice();

void verificaKRegularidade();

void verificaGrafoCompleto();

void chamaFuncaoEscolhida(int opMenu);

void verificaBipartido();

void removeAresta();

void removeVertice();

void coberturaDeVerticesGuloso();

void coberturaDeVerticesGulosoRandomizado();

int auxCVGR(double _alfa, bool imprime);

int main(int argc, char **argv)
{
    bool conexo, bipartido;
    long idVertice, idVerticeOrigem, idVerticeDestino;
    int op, opMenu;

    apresentacaoTrabalho();

    if (argc==3)
    {//4 para rodar com o Cmake, 3 quando for rodar no terminal
        inputFile.open(argv[1], ios::in);   //2 para rodar com o Cmake, 1 quando for rodar no terminal
        outputFile.open(argv[2], ios::out); //3 para rodar com o Cmake, 2 quando for rodar no terminal
        //Verificar se arquivo de entrada foi aberto
        if (!inputFile)
        {
            cerr << "ERRO: Arquivo " << argv[1] << " não foi encontrado!" << endl; //voltar para 1 quando executar no terminal
            return -1;
        }
        //Verificar se arquivo de saída foi criado
        if (!outputFile)
        {
            cerr << "ERRO: Arquivo " << argv[2] << " não pode ser criado!" << endl; //voltar para 2 quando executar no terminal
            return -1;
        }
    }
    else
    {
        cerr << "ERRO: Informar os arquivos de entrada ou saída na execução do algoritmo" << endl;
        return 0;
    }

    cout << "Lendo o Tamanho do Grafo...\nOK\n" << endl;
    //Faz leitura do tamanho do Grafo
    char cTamanhoGrafo[15];
    inputFile.getline(cTamanhoGrafo, 80);

    //Converte char para string e depois string para long
    string sTamanhoGrafo = string(cTamanhoGrafo);
    tamanhoGrafo = stol(sTamanhoGrafo); //voltar para sTamanhoGrafo

    cout << "Criando Grafo...\nOK\n" << endl;
    criarGrafo(tamanhoGrafo);

    cout << "Gerando Adjacências do Grafo...\nOK\n" << endl;
    lerAdjcencias(false);   //false = não contém peso

    criaCabecalho(tamanhoGrafo);

    //MENU
    do
    {
        opMenu = exibeMenu();
        if (opMenu!=0)
        {
            chamaFuncaoEscolhida(opMenu);
        }
    }
    while (opMenu!=0);

    cout << "\nOs dados de análise foram salvos no arquivo de saída" << endl;


    //Fecha IO
    outputFile.close();
    inputFile.close();

    return 0;
}

void apresentacaoTrabalho()
{
    char trash;
    cout << "\n\n";
    cout << "#############################################" << endl;
    cout << "\tTrabalho de Teoria dos Grafos 2018.1 - Grupo 2" << endl;
    cout << "#############################################" << endl;
    cout << "\nObs: Os dados serão gerados automaticamente para o arquivo de saída informado por parâmetro.\n" << endl;

    cout << "Digite 1 + <Enter> para iniciar o algoritmo...";
    cin >> trash;
    cout << "\n\n";
}

void criaCabecalho(long _tamanhoGrafo)
{
    outputFile << "Trabalho de Grafos - Cobertura de Vértices" << endl;
    outputFile << "Grupo 2: Nome | Matrícula"<<endl;
    outputFile << "\tArthur Gonze Machado | 201435001" << endl;
    outputFile << "\tLudmilla Yung | " << endl;
    outputFile << "\tLucas | " << endl;
    outputFile << "\tIgor Marchito Zamboni | " << endl;
    outputFile << "\tDavi | " << endl;
    outputFile << "\tAndré Archanjo | " << endl;
    outputFile << endl;
    outputFile << "Análise do Grafo" << endl;
    outputFile << "Número de Vértices: " << _tamanhoGrafo << endl;
}

int exibeMenu()
{
    int opMenu;

    cout << " 1- Verificar o Grau de um vértice" << endl;
    cout << " 2- Verificar o Grau de G" << endl;
    cout << " 3- Listar os adjacentes de um vértice" << endl;
    cout << " 4- Verificar se o Grafo é nulo" << endl;
    cout << " 5- Verificar se o Grafo é K-Regular" << endl;
    cout << " 6- Verificar se o Grafo é trivial" << endl;
    cout << " 7- Verificar se o Grafo é Completo" << endl;
    cout << " 8- Verificar se o Grafo é Bipartido" << endl;
    cout << " 9- Verificar a Ordem de G" << endl;
    cout << "10- Remover Vértice" << endl;
    cout << "11- Remover Aresta" << endl;
    cout << "12- Cobertura de Vértices Guloso" << endl;
    cout << "13- Cobertura de Vértices Guloso Randomizado" << endl;
    cout << "14- Cobertura de Vértices Guloso Randomizado Reativo" << endl;
    cout << " 0- Sair" << endl;
    cout << "\nOpção: ";
    cin >> opMenu;
    return opMenu;
}

void chamaFuncaoEscolhida(int opMenu)
{
    switch (opMenu)
    {
        case 0:
        {
            cout << "Algoritmo Encerrado. Os dados foram armazenados em arquivo." << endl;
            break;
        }
        case 1:
        {
            verificaGrauVertice();
            break;
        }
        case 2:
        {
            verificaGrauGrafo();
            break;
        }
        case 3:
        {
            listaAdjacentesVertice();
            break;
        }
        case 4:
        {
            verificaNulo();
            break;
        }
        case 5:
        {
            verificaKRegularidade();
            break;
        }
        case 6:
        {
            verificaTrivial();
            break;
        }
        case 7:
        {
            verificaGrafoCompleto();
            break;
        }
        case 8:
        {
            verificaBipartido();
            break;
        }
        case 9:
        {
            verificaOrdemG();
            break;
        }
        case 10:
        {
            removeVertice();
            break;
        }
        case 11:
        {
            removeAresta();
            break;
        }
        case 12:
        {
            coberturaDeVerticesGuloso();
            break;
        }
        case 13:
        {
            coberturaDeVerticesGulosoRandomizado();
            break;
        }
        case 14://todo algoritmo reativo
        {
            //coberturaDeVerticesGulosoRandomizadoReativo();
            break;
        }
        default:
        {
            cout << "ERRO: Opção Inválida!" << endl;
        }
    }
}

void coberturaDeVerticesGuloso()
{
    bool imprime = false;   //verifica se os vértices da menor cobertura serão impressos
    int op;
    vector<long> verticesUtilizados;
    Grafo grafoAux;
    grafoAux = grafo;
    multiset<pair<double, int>> rankeamentoDeVertices;
    pair<double, int> infoRankeamento; //pesoParaRankeamento, idVertice
    double pesoParaRankeamento;
    bool coberto = false;   //setar para true quando todas as arestas forem cobertas
    long idVerticeMenorCusto;

    while (!coberto)
    {
        for (int i = 0; i < grafoAux.getNumVertices(); i++)
        {
            if (grafoAux.getVertice(i)->getGrau()!=0)
            {
                pesoParaRankeamento = grafoAux.getVertice(i)->getPeso()/(grafoAux.getVertice(i)->getGrau()*1.0);
                infoRankeamento = make_pair(pesoParaRankeamento, grafoAux.getVertice(i)->getIdVertice());
                rankeamentoDeVertices.insert(infoRankeamento);
            }
            else
            {
                //Evita q peso 0 seja escolhido
                pesoParaRankeamento = 999999;
                infoRankeamento = make_pair(pesoParaRankeamento, grafo.getVertice(i)->getIdVertice());
            }
        }
        idVerticeMenorCusto = rankeamentoDeVertices.begin()->second;

        verticesUtilizados.push_back(idVerticeMenorCusto);    //utiliza vértice de menor custo

        //Remove as arestas que o vértice cobre
        for (auto adj : grafoAux.getVertice(idVerticeMenorCusto)->getVerticesAdjacentes())
        {
            long teste = adj.getIdVertice();
            grafoAux.removeAresta(idVerticeMenorCusto, adj.getIdVertice());
        }

        //Verifica se a cobertura está completa
        coberto = true;
        for (int i = 0; i < grafoAux.getNumVertices(); i++)
        {
            if (grafoAux.getVertice(i)->getGrau() > 0)
            {
                coberto = false;
                rankeamentoDeVertices.clear();  //limpa o vetor de rankeamento
                break;
            }
        }
    }

    outputFile << "\nCobertura Mínima Gulosa: " << verticesUtilizados.size() << " vértice(s)" << endl;

    cout << "Deseja que os vértices da melhor cobertura encontrada sejam exibidos no arquivo?" << endl;
    cout << "[1]Sim\t [0]Não" << endl;
    cin >> op;
    if (op==1)
    {
        cout << "op: "<< op << endl;
        for (int i = 0; i < verticesUtilizados.size(); i++)
        {
            cout << "Vertice: "<< verticesUtilizados[i] << endl;
            outputFile << verticesUtilizados[i];
            if (i < verticesUtilizados.size() - 1)
            {
                outputFile << ", ";
            }
        }
    }

}

void coberturaDeVerticesGulosoRandomizado()
{
    int op;
    bool imprime = false;   //verifica se os vértices da menor cobertura serão impressos
    double alfa1 = 0.1;
    double alfa2 = 0.2;
    double alfa3 = 0.3;
    double melhorAlfa;
    int semente;
    //define a primeira semente como melhor
    int melhorSementeAlfa1 = 1;
    int melhorSementeAlfa2 = 1;
    int melhorSementeAlfa3 = 1;

    srand(1);   //obtem a cobertura pra semente 1
    int minCobertura1 = auxCVGR(alfa1, false);
    int minCobertura2 = auxCVGR(alfa2, false);
    int minCobertura3 = auxCVGR(alfa3, false);
    int auxMinCobertura;

    for (semente = 2; semente <= 30; semente++)
    {
        // inicializa o gerador de números randômicos
        srand(semente); //semente varia de 1 a 30

        auxMinCobertura = auxCVGR(alfa1, false);
        if (auxMinCobertura < minCobertura1)
        {
            minCobertura1 = auxMinCobertura;
            melhorSementeAlfa1 = semente;
        }

        auxMinCobertura = auxCVGR(alfa2, false);
        if (auxMinCobertura < minCobertura2)
        {
            minCobertura2 = auxMinCobertura;
            melhorSementeAlfa2 = semente;
        }

        auxMinCobertura = auxCVGR(alfa3, false);
        if (auxMinCobertura < minCobertura3)
        {
            minCobertura3 = auxMinCobertura;
            melhorSementeAlfa3 = semente;
        }
    }

    cout << "Deseja que os vértices da melhor cobertura sejam exibidos?" << endl;
    cout << "[1]Sim\t [0]Não" << endl;
    cin >> op;
    if (op==1)
    {
        imprime = true;
    }
    outputFile << endl;
    outputFile << endl;
    outputFile << "--- Descrição da Cobertura Mínima de Cértices ---" << endl;
    outputFile << "Alfa: " << alfa1 << endl;
    outputFile << "Menor Cobertura: " << minCobertura1 << endl;
    outputFile << "Melhor Semente: " << melhorSementeAlfa1 << endl << endl;
    if (imprime)
    {
        srand(melhorSementeAlfa1);
        auxCVGR(alfa1, false);
        outputFile << endl;
    }

    outputFile << "Alfa: " << alfa2 << endl;
    outputFile << "Menor Cobertura: " << minCobertura2 << endl;
    outputFile << "Melhor Semente: " << melhorSementeAlfa2 << endl << endl;
    if (imprime)
    {
        srand(melhorSementeAlfa2);
        auxCVGR(alfa2, false);
        outputFile << endl;
    }

    outputFile << "Alfa: " << alfa3 << endl;
    outputFile << "Menor Cobertura: " << minCobertura3 << endl;
    outputFile << "Melhor Semente: " << melhorSementeAlfa3 << endl << endl;
    if (imprime)
    {
        srand(melhorSementeAlfa3);
        auxCVGR(alfa3, false);
        outputFile << endl;
    }

}

int auxCVGR(double _alfa, bool imprime)
{
    long posicaoEscolhida;
    vector<long> verticesUtilizados;
    Grafo grafoAux;
    grafoAux = grafo;
    multiset<pair<double, int>> rankeamentoDeVertices;
    multiset<pair<double, int>>::iterator itRakeamento;
    pair<double, int> infoRankeamento; //pesoParaRankeamento, idVertice
    double pesoParaRankeamento;
    bool coberto = false;   //setar para true quando todas as arestas forem cobertas
    long idVerticeMenorCusto;
    long rangeMax;  //Vértice escolhido deve ser aleatório no intervalo de 0 a RageMax
    int valRandomico;
    int numVerticesGrauZero;

    while (!coberto)
    {

        numVerticesGrauZero = 0;
        for (int i = 0; i < grafoAux.getNumVertices(); i++)
        {
            //Se o vértice não possui mais aresta, descartar ele
            if (grafoAux.getVertice(i)->getGrau()==0)
            {
                numVerticesGrauZero++;
            }
        }
        //Encontrar qual vai ser o vértice escolhido
        rangeMax = (grafoAux.getNumVertices() - numVerticesGrauZero)*_alfa;
        if (rangeMax > 0)
        { //evitar divisão por zero
            valRandomico = rand();
            posicaoEscolhida = valRandomico%rangeMax;
        }
        else
        {
            posicaoEscolhida = 0;
        }

        for (int i = 0; i < grafoAux.getNumVertices(); i++)
        {

            if (grafoAux.getVertice(i)->getGrau()!=0)
            {
                pesoParaRankeamento = grafoAux.getVertice(i)->getPeso()/(grafoAux.getVertice(i)->getGrau()*1.0);
                infoRankeamento = make_pair(pesoParaRankeamento, grafoAux.getVertice(i)->getIdVertice());
                rankeamentoDeVertices.insert(infoRankeamento);
            }
            else
            {
                //Evita q peso 0 seja escolhido
                pesoParaRankeamento = 999999;
                infoRankeamento = make_pair(pesoParaRankeamento, grafo.getVertice(i)->getIdVertice());
                rankeamentoDeVertices.insert(infoRankeamento);
            }
        }

        //Posiciona o iterador na posição do elemento escolhido
        itRakeamento = rankeamentoDeVertices.begin();
        for (int i = 1; i <= posicaoEscolhida; i++)
        {
            itRakeamento++;
        }

        //idVerticeMenorCusto = rankeamentoDeVertices.begin()->second;
        idVerticeMenorCusto = itRakeamento->second;
        verticesUtilizados.push_back(idVerticeMenorCusto);    //utiliza vértice de menor custo

        //Remove as arestas que o vértice cobre
        for (auto adj : grafoAux.getVertice(idVerticeMenorCusto)->getVerticesAdjacentes())
        {
            long teste = adj.getIdVertice();
            grafoAux.removeAresta(idVerticeMenorCusto, adj.getIdVertice());
        }

        //Verifica se a cobertura está completa
        coberto = true;
        for (int i = 0; i < grafoAux.getNumVertices(); i++)
        {
            if (grafoAux.getVertice(i)->getGrau() > 0)
            {
                coberto = false;
                rankeamentoDeVertices.clear();  //limpa o vetor de rankeamento
                break;
            }
        }
    }

    if (imprime)
    {
        for (int i = 0; i < verticesUtilizados.size(); i++)
        {
            outputFile << verticesUtilizados[i];
            if (i < verticesUtilizados.size() - 1)
            {
                outputFile << ", ";
            }
        }
        outputFile << "\n" << endl;
    }

    return verticesUtilizados.size();
}

void removeVertice()
{
    long idVertice;
    cout << "Qual vértice remover? ";
    cin >> idVertice;
    grafo.removeVertice(idVertice);
}

void removeAresta()
{
    long idOrigem, idDestino;
    cout << "Informe o Vértice de Origem: ";
    cin >> idOrigem;
    cout << "\nInforme o Vértice de Destino: ";
    cin >> idDestino;
    grafo.removeAresta(idOrigem, idDestino);
}

void criarGrafo(long _tamanhoGrafo)
{
    long i = 1;
    int op;

    //O primeiro vértice é criado automaticamente
    grafo.getVertice(0)->setIdVertice(0);

    while (i < _tamanhoGrafo)
    {
        grafo.addVertice(i);
        i++;
    }

    //Verifica se o grafo é direcionado
    do
    {
        cout << "O Grafo é direcionado? " << endl;
        cout << "0-Não\t 1-Sim" << endl;
        cin >> op;
        if (op < 0 || op > 1)
        {
            cout << "ERRO: Opção Inválida!" << endl;
        }
        else
        {
            op==0 ? grafo.setIsGrafoDirecionado(false) : grafo.setIsGrafoDirecionado(true);
        }

    }
    while (op < 0 || op > 1);
}

void lerAdjcencias(bool isContainPeso)
{
    char cVerticeOrigem[15], cVerticeDestino[15];
    string sVerticeOrigem, sVerticeDestino;
    long verticeOrigem, verticeDestino;

    if (!isContainPeso)
    {
        while (inputFile >> cVerticeOrigem >> cVerticeDestino)
        {

            //Faz conversões
            sVerticeOrigem = string(cVerticeOrigem);
            sVerticeDestino = string(cVerticeDestino);
            verticeOrigem = stol(sVerticeOrigem);
            verticeDestino = stol(sVerticeDestino);

            //Faz conversão para inputs iniciando por 1
            grafo.addVerticeAdjacente(verticeOrigem - 1, verticeDestino - 1, 0.0);
        }
    }
    else
    {
        char cPesoAresta[15];
        string sPesoAresta;
        float pesoAresta;
        while (inputFile >> cVerticeOrigem >> cVerticeDestino >> cPesoAresta)
        {
            //Faz conversões
            sVerticeOrigem = string(cVerticeOrigem);
            sVerticeDestino = string(cVerticeDestino);
            sPesoAresta = string(cPesoAresta);
            verticeOrigem = stol(sVerticeOrigem);
            verticeDestino = stol(sVerticeDestino);
            pesoAresta = stof(sPesoAresta);

            grafo.addVerticeAdjacente(verticeOrigem, verticeDestino, pesoAresta);
        }
    }
}

void verificaGrauVertice()
{
    int idVertice, op;
    do
    {
        cout << "Digite o id do Vértice que deseja consultar seu Grau: ";
        cin >> idVertice;
        if (idVertice < 0 || idVertice >= tamanhoGrafo)
        {
            cout << "Erro: Vértice Inválido!\n" << endl;
        }
        else
        {
            cout << "Verificando Grau do Vértice " << idVertice << "...\nOK\n" << endl;
            outputFile << "gr(" << idVertice << "): " << grafo.verificaGrauVertice(idVertice) << endl;
        }
        cout << "0- Encerrar Função    1-Escolher Outro Vértice" << endl;
        cin >> op;
    }
    while (op!=0);
}

void verificaGrauGrafo()
{
    outputFile << "Grau(G): " << grafo.verificaGrauGrafo() << endl;
    cout << "Verificando Grau do Grafo...\nOK\n" << endl;
}

void listaAdjacentesVertice()
{//4- Lista os Adjacentes de um Vértice
    int idVertice, op;
    do
    {
        cout << "Digite o id do Vértice que deseja consultar seus adjacentes: ";
        cin >> idVertice;
        if (idVertice < 0 || idVertice >= tamanhoGrafo)
        {
            cout << "Erro: Vértice Inválido!\n" << endl;
        }
        else
        {
            cout << "Verificando Vértices Adjacentes ao Vértice " << idVertice << "...\nOK\n" << endl;
            outputFile << "Vizinhança aberta do vértice " << idVertice << ":\n";
            outputFile << "< " << grafo.getVertice(idVertice)->listarAdjacentes() << " >" << endl;
            outputFile << "\nVizinhança fechada do vértice " << idVertice << ":\n";
            outputFile << "< "<< idVertice << " " << grafo.getVertice(idVertice)->listarAdjacentes() << " >" << endl;
        }
        cout << "\n0- Encerrar Função    1-Escolher Outro Vértice" << endl;
        cin >> op;
    }
    while (op!=0);
}

void verificaKRegularidade()
{//6- Verifica se Grafo é K-Regular
    if (grafo.verificaKRegular(&kRegular))
    {
        outputFile << "K-Regular: SIM - Grafo " << kRegular << "-Regular" << endl;
    }
    else
    {
        outputFile << "K-Regular: NÃO" << endl;
    }
}

void verificaGrafoCompleto()
{//8- Verifica se G é completo
    cout << "Verificando se Grafo é Completo...\nOK\n" << endl;
    outputFile << (grafo.isCompleto() ? "Grafo Completo: SIM" : "Grafo Completo: NÃO") << endl;
}

void verificaBipartido()
{

    cout << "Verificando se Grafo é Bipartido...";
    outputFile << (grafo.isGrafoBipartido() ? "Grafo Bipartido: SIM" : "Grafo Bipartido: NÃO") << endl;

    cout << "\nOK\n\n" << endl;
}

void verificaNulo()
{
    if(grafo.getNumVertices()==0)
    {
        outputFile << "Grafo Nulo: SIM" << endl;
    }else
    {
        outputFile << "Grafo Nulo: NÃO" << endl;
    }
}

void verificaTrivial()
{
    if(grafo.getNumVertices()==1)
    {
        outputFile << "Grafo Trivial: SIM" << endl;
    }else
    {
        outputFile << "Grafo Trivial: NÃO" << endl;
    }
}

void verificaOrdemG()
{
    outputFile << "Ordem do Grafo: "<< grafo.getNumVertices() << endl;
}
