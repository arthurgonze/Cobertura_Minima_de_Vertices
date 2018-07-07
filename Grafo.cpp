//
// Created by helder on 27/04/16.
//

#include "Grafo.h"

using namespace std;

Grafo::Grafo()
{
    Vertice vertice;
    vertices.push_back(vertice);
    isGrafoDirecionado = false;
}

Grafo::~Grafo()
{

}

void Grafo::setIsGrafoDirecionado(bool _isDirecionado)
{
    isGrafoDirecionado = _isDirecionado;
}

void Grafo::imprimeVertices()
{
    for (unsigned int i = 0; i < vertices.size(); i++)
    {
        cout << vertices[i].getIdVertice() << endl;
    }
}

Vertice *Grafo::getVertice(int idVertice)
{
    return &vertices[idVertice];
}

void Grafo::addVertice(long _idVertice)
{
    Vertice vertice;
    vertice.setIdVertice(_idVertice);
    vertices.push_back(vertice);
}

void Grafo::addVerticeAdjacente(int _verticeOrigem, int _verticeDestino, float _pesoAresta)
{
    //verifica existência dos vértices
    if (_verticeOrigem < 0 || _verticeOrigem >= vertices.size())
    {
        cout << "Vértice de Origem " << _verticeOrigem << " é inválido!" << endl;
    }
    else if (_verticeDestino < 0 || _verticeDestino >= vertices.size())
    {
        cout << "Vértice de Destino " << _verticeDestino << " é inválido!" << endl;
    }
    else
    {
        vertices[_verticeOrigem].addVerticeAdjacente(_verticeDestino, _pesoAresta);

        if (!isGrafoDirecionado)
        {
            vertices[_verticeDestino].addVerticeAdjacente(_verticeOrigem, _pesoAresta);
        }
    }
}

bool Grafo::isVerticesVisitados()
{

    for (int i = 0; i < vertices.size(); i++)
    {
        if (vertices[i].getVisitado()==Coloracao::SEMCOR)
        {
            return false;
        }
    }
    return true;
}

//Auxiliar para verificar se grafo é bipartido
bool Grafo::auxIsBipartido(long _vertice, long _numPasso)
{
    bool coloriuCorretamente = false;
    Coloracao corDePreenchimento = Coloracao::SEMCOR;
    _numPasso%2==0 ? corDePreenchimento = Coloracao::AZUL : corDePreenchimento = Coloracao::VERDE;

    if (vertices[_vertice].getVisitado()==Coloracao::SEMCOR)
    {
        vertices[_vertice].setCorVisita(corDePreenchimento);

        //Adjacente auxAdj(0);
        //percorre a lista dos adjacentes do vértice atual
        //for(auxAdj : vertices[_vertice].getVerticesAdjacentes()){
        //Cria Arestas
        for (Adjacente adj : vertices[_vertice].getVerticesAdjacentes())
        {
            coloriuCorretamente = auxIsBipartido(adj.getIdVertice(), _numPasso + 1);
            if (!coloriuCorretamente)
            {
                break;
            }
        }
    }
    else
    {
        if (vertices[_vertice].getVisitado()!=corDePreenchimento)
        {
            return false;
        }
    }
    return true;
}

bool Grafo::isGrafoBipartido()
{
    int passo = 0;
    int j = 0;
    isBipartido = true; //seta o grafo como bipartido, caso provado que não seja, a variável é setada com false

    //determina que todos vértices não foram visitados.
    for (int i = 0; i < vertices.size(); i++)
    {
        vertices[i].setCorVisita(Coloracao::SEMCOR);    //marca vértice como não visitado
    }

    isBipartido = auxIsBipartido(0, passo);

}

long Grafo::verificaGrauVertice(long _idVertice)
{
    //return getVertice(_idVertice)->getVerticesAdjacentes().size();
    return getVertice(_idVertice)->getGrau();
}

long Grafo::verificaGrauGrafo()
{
    long grauMax = verificaGrauVertice(0);
    long grauVerticeAtual;
    for (int i = 1; i < vertices.size(); i++)
    {
        grauVerticeAtual = verificaGrauVertice(i);
        if (grauVerticeAtual > grauMax)
            grauMax = grauVerticeAtual;
    }
    return grauMax;
}

bool Grafo::verificaKRegular(long *kRegular)
{
    *kRegular = getVertice(0)->getVerticesAdjacentes().size();

    for (int i = 1; i < vertices.size(); i++)
    {
        if (getVertice(i)->getVerticesAdjacentes().size()!=*kRegular)
            return false;
    }
    return true;
}

bool Grafo::isCompleto()
{
    for (int i = 0; i < vertices.size(); i++)
    {
        if (getVertice(i)->getVerticesAdjacentes().size()!=vertices.size() - 1);
        return false;
    }
    return true;
}

void Grafo::atualizaNumeracaoAdjacentes(int _idVertice, int _idVerticeRemovido)
{
    //Percorre adjacentes do vértice
    for (list<Adjacente>::iterator it = vertices[_idVertice].getVerticesAdjacentes().begin(); it!=vertices[_idVertice].getVerticesAdjacentes().end(); it++)
    {
        //verifica se id de algum adjacente está acima do valor do vértice removido
        if (it->getIdVertice() >= _idVerticeRemovido)
            it->updateIdVertice();
    }
}

bool Grafo::removeVertice(int _idVertice)
{
    _idVertice;
    int idVerticeRemovido = _idVertice;
    if (_idVertice < 0 || _idVertice >= vertices.size())
    {
        cout << "Vértice inválido!" << endl;
        return false;
    }
    if (!isGrafoDirecionado)
    {
        for (int i = 0; i < vertices[_idVertice].getVerticesAdjacentes().size(); i++)
        {

            //Percorre adjacentes do vértice
            for (list<Adjacente>::iterator it = vertices[_idVertice].getVerticesAdjacentes().begin();
                 it!=vertices[_idVertice].getVerticesAdjacentes().end(); it++)
            {
                auxRemoveAresta(it->getIdVertice(), _idVertice);
            }

            //Remove o vértice desejado
            vertices.erase(vertices.begin() + _idVertice);

            //Chama função para atualizar os IDs maiores do que o removido
            atualizaIDs(_idVertice);

        }
    }
    else
    {
        //Remove o vértice desejado
        vertices.erase(vertices.begin() + _idVertice);

        for (int i = 0; i < vertices.size(); i++)
        {
            for (Adjacente adj : vertices[i].getVerticesAdjacentes())
            {
                //verifica se é um adjacente do vértice removido
                if (adj.getIdVertice()==_idVertice)
                {
                    removeAresta(i, adj.getIdVertice());
                }
            }
        }
        atualizaIDs(_idVertice);
    }
    return true;
}

void Grafo::atualizaIDs(int _idVerticeRemovido)
{//Atualiza ids dos demais vértices
    for (int i = 0; i < vertices.size(); i++)
    {
        atualizaNumeracaoAdjacentes(i, _idVerticeRemovido);

        //caso o vértice atual tenha id acima do vértice removido atualiza a numeração dele.
        if (i > _idVerticeRemovido)
        {
            vertices[i].setIdVertice(i - 1);
        }
    }
}

bool Grafo::auxRemoveAresta(int _idVerticeOrigem, int _idVerticeDestino)
{
    if (isGrafoDirecionado)
    {
        getVertice(_idVerticeOrigem)->removeVerticeAdjacente(_idVerticeDestino);
    }
    else
    {
        getVertice(_idVerticeOrigem)->removeVerticeAdjacente(_idVerticeDestino);
        getVertice(_idVerticeDestino)->removeVerticeAdjacente(_idVerticeOrigem);
    }
    return true;
}

bool Grafo::removeAresta(int _idVerticeOrigem, int _idVerticeDestino)
{

    //verifica se os vértices são válidos
    if (_idVerticeOrigem < 0 || _idVerticeDestino < 0 || _idVerticeOrigem >= vertices.size() || _idVerticeDestino >= vertices.size())
    {
        cout << "Erro: Pelo menos um dos IDs informados é inválido!\n" << endl;
        return false;
    }

    bool isRemovido;

    if (isGrafoDirecionado)
    {
        //Verifica se existe a aresta
        if (getVertice(_idVerticeOrigem)->removeVerticeAdjacente(_idVerticeDestino))
        {
            cout << "Aresta Removida!\n" << endl;
        }
        else
        {
            cout << "ERRO: Aresta Não Existente!\n" << endl;
        }
    }
    else
    {
        //Verifica se existe a aresta
        if (getVertice(_idVerticeOrigem)->removeVerticeAdjacente(_idVerticeDestino))
        {
            getVertice(_idVerticeDestino)->removeVerticeAdjacente(_idVerticeOrigem);
            //cout << "Aresta Removida!\n" << endl;
        }
        else
        {
            cout << "ERRO: Aresta Não Existente!\n" << endl;
        }
    }
    return true;
}

long Grafo::getNumVertices()
{
    return vertices.size();
}




