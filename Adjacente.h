//
// Created by caveira on 7/7/18.
//

#ifndef GRAFOS_CV_2018_1_ADJACENTE_H
#define GRAFOS_CV_2018_1_ADJACENTE_H

#include "Vertice.h"

using namespace std;

class Vertice;

class Adjacente
{

private:
    long idVertice;
    float pesoAresta;

public:
    Adjacente();
    Adjacente(long _idVerticeAdjacente);
    Adjacente(long _idVerticeAdjacente, float _pesoAresta);
    long getIdVertice();
    float getPesoDaAresta();
    void setPesoDaAresta(float _pesoAresta);
    void updateIdVertice(); //usado quando um vértice é removido
    virtual ~Adjacente();
};

#endif //GRAFOS_CV_2018_1_ADJACENTE_H
