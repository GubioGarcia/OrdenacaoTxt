#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <chrono>
#include <string>
#include <time.h>
#include <list>

class ElementoArquivo {
    private:
        int indice;
        std::string texto;

    public:
        // Construtor com parâmetros
        ElementoArquivo(int indice, std::string texto):
            indice(indice), texto(texto) {}

        // Métodos de configuração (set)
        void setIndice(const int &newIndice) {
            indice = newIndice;
        }

        void setTexto(const std::string &newTexto) {
            texto = newTexto;
        }

        // Métodos de obtenção (get)
        int getIndice() const {
            return indice;
        }

        std::string getTexto() const {
            return texto;
        }
};

// Função de troca de elementos
template <typename T>
void troca(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

// QuickSort para ordenação numérica
void QuickSortNumerico(std::list<ElementoArquivo>& lista) {
    if (lista.size() <= 1) {
        return; // A lista já está ordenada ou está vazia
    }

    ElementoArquivo pivot = lista.front();
    std::list<ElementoArquivo> menores, iguais, maiores;

    for (const ElementoArquivo& elemento : lista) {
        if (elemento.getIndice() < pivot.getIndice()) {
            menores.push_back(elemento);
        } else if (elemento.getIndice() == pivot.getIndice()) {
            iguais.push_back(elemento);
        } else {
            maiores.push_back(elemento);
        }
    }

    QuickSortNumerico(menores);
    QuickSortNumerico(maiores);

    lista.clear();
    lista.insert(lista.end(), menores.begin(), menores.end());
    lista.insert(lista.end(), iguais.begin(), iguais.end());
    lista.insert(lista.end(), maiores.begin(), maiores.end());
}

// QuickSort para ordenação alfabética
void QuickSortAlfabetico(std::list<ElementoArquivo>& lista) {
    if (lista.size() <= 1) {
        return; // A lista já está ordenada ou está vazia
    }

    ElementoArquivo pivot = lista.front();
    std::list<ElementoArquivo> menores, iguais, maiores;

    for (const ElementoArquivo& elemento : lista) {
        if (elemento.getTexto() < pivot.getTexto()) {
            menores.push_back(elemento);
        } else if (elemento.getTexto() == pivot.getTexto()) {
            iguais.push_back(elemento);
        } else {
            maiores.push_back(elemento);
        }
    }

    QuickSortAlfabetico(menores);
    QuickSortAlfabetico(maiores);

    lista.clear();
    lista.insert(lista.end(), menores.begin(), menores.end());
    lista.insert(lista.end(), iguais.begin(), iguais.end());
    lista.insert(lista.end(), maiores.begin(), maiores.end());
}

// SelectionSort para ordenação numérica
void SelectionSortNumerico(std::list<ElementoArquivo>& lista) {
    for (auto it = lista.begin(); it != lista.end(); ++it) {
        auto min = it;
        for (auto it2 = std::next(it); it2 != lista.end(); ++it2) {
            if (it2->getIndice() < min->getIndice()) {
                min = it2;
            }
        }
        if (min != it) {
            troca(*it, *min);
        }
    }
}

// SelectionSort para ordenação alfabética
void SelectionSortAlfabetico(std::list<ElementoArquivo>& lista) {
    for (auto it = lista.begin(); it != lista.end(); ++it) {
        auto min = it;
        for (auto it2 = std::next(it); it2 != lista.end(); ++it2) {
            if (it2->getTexto() < min->getTexto()) {
                min = it2;
            }
        }
        if (min != it) {
            troca(*it, *min);
        }
    }
}

int main () {
    // Abertura dos arquivos a serem manipulados
    std::ifstream arquivoLeitura("arq.txt");
    std::ofstream arquivoOrdenado("arqOrdenado.txt", std::ios::out);

    // Tratamento para erro na abertura
    if (!arquivoLeitura.is_open()) {
        std::cout << "Nao foi possivel abrir o arquivo de Leitura.\n";
        return 1;
    }
    if (!arquivoOrdenado.is_open()) {
        std::cout << "Nao foi possivel abrir o arquivo de Ordenacao.\n";
        return 1;
    }

    // Manipulacao dos Arquivos
    std::string linha;
    std::list<ElementoArquivo> listaElementos;

    while (std::getline(arquivoLeitura, linha)) {
        // Encontre a posição do separador '.'
        size_t pos = linha.find('.');

        // Verifique se o ponto foi encontrado
        if (pos != std::string::npos) {
            // Separe a linha em indice e texto
            int indice = stoi(linha.substr(0, pos));
            std::string texto = linha.substr(pos + 1);

            // Cria um objeto ElementoArquivo e adiciona à lista
            listaElementos.push_back(ElementoArquivo(indice, texto));
        }
    }

    std::list<ElementoArquivo> listaElementosCopia = listaElementos;

    // Ordenacao
    std::chrono::high_resolution_clock::time_point inicioQS, inicioSS, fimQS, fimSS;
    double tempoDecorridoQS, tempoDecorridoSS;

    int tipoOrdenacao = 0;
    while (tipoOrdenacao != 1 && tipoOrdenacao != 2)
    {
        std::cout << "Indique o tipo de ordenacao desejado! Digite:\n";
        std::cout << "'1' para ordenacao NUMERICA.\n";
        std::cout << "'2' para ordenacao ALFABETICA.\n";
        std::cin >> tipoOrdenacao;
    }

    if (tipoOrdenacao == 1) {
        // Inicio contador
        inicioQS = std::chrono::high_resolution_clock::now();
        QuickSortNumerico(listaElementos);
        // Fim contador
        fimQS = std::chrono::high_resolution_clock::now();

        // Inicio contador
        inicioSS = std::chrono::high_resolution_clock::now();
        SelectionSortNumerico(listaElementosCopia);
        // Fim contador
        fimSS = std::chrono::high_resolution_clock::now();
    } else {
        // Inicio contador
        inicioQS = std::chrono::high_resolution_clock::now();
        QuickSortAlfabetico(listaElementos);
        // Fim contador
        fimQS = std::chrono::high_resolution_clock::now();

        // Inicio contador
        inicioSS = std::chrono::high_resolution_clock::now();
        SelectionSortAlfabetico(listaElementosCopia);
        // Fim contador
        fimSS = std::chrono::high_resolution_clock::now();
    }

    tempoDecorridoQS = std::chrono::duration<double>(fimQS - inicioQS).count();
    tempoDecorridoSS = std::chrono::duration<double>(fimSS - inicioSS).count();

    // Impressao dados no terminal
    std::cout << "\nTempo de Ordenacao QuickSort: " << std::fixed << std::setprecision(6) << tempoDecorridoQS << "\n";
    std::cout << "Tempo de Ordenacao SelectionSort: " << std::fixed << std::setprecision(6) << tempoDecorridoSS << "\n\n";
    while (!listaElementosCopia.empty()) {
        const ElementoArquivo &elemento = listaElementosCopia.front();
        std::cout << elemento.getIndice() << "." << elemento.getTexto() << "\n";
        listaElementosCopia.pop_front(); // Remove o elemento da frente da lista
    }

    // Manipuilacao arquivo Ordenado
    while (!listaElementos.empty()) {
        const ElementoArquivo &elemento = listaElementos.front();
        arquivoOrdenado << elemento.getIndice() << "." << elemento.getTexto() << "\n";
        listaElementos.pop_front(); // Remove o elemento da frente da lista
    }

    arquivoLeitura.close();
    arquivoOrdenado.close();
}