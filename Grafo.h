#ifndef GRAFOS_CV_2018_1_GRAFO_H
#define GRAFOS_CV_2018_1_GRAFO_H


#include <vector>
#include <string>
#include <list>
#include <set>

#include "Adjacente.h"

using namespace std;

class Vertice;

class Grafo
{

private:
    vector<Vertice> vertices;
    bool isGrafoDirecionado;
    bool isBipartido;
    void atualizaNumeracaoAdjacentes(int _idVertice, int _idVerticeRemovido);
    bool isVerticesVisitados();
    bool auxRemoveAresta(int _idVerticeOrigem, int _idVerticeDestino);
    void atualizaIDs(int _idVerticeRemovido);
    bool auxIsBipartido(long _vertice, long _numPasso);

public:
    Grafo();
    virtual ~Grafo();
    Vertice *getVertice(int _idVertice);
    void addVertice(long _idVertice);
    void addVerticeAdjacente(int _verticeOrigem, int _verticeDestino, float _pesoAresta);
    void imprimeVertices();
    void setIsGrafoDirecionado(bool _isDirecionado);
    bool isGrafoBipartido();
    long verificaGrauGrafo();
    long verificaGrauVertice(long _idVertice);
    bool verificaKRegular(long *kRegular);
    bool isCompleto();
    bool removeVertice(int _idVertice);
    bool removeAresta(int _idVerticeOrigem, int _idVerticeDestino);
    long getNumVertices();
    list<Vertice> getVertices();
};

#endif //GRAFOS_CV_2018_1_GRAFO_H
