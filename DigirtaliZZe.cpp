/*
 * ==================================================
 * Programa: GAC109 Projeto Prático - Enunciado 4
 * Autores: Marcelo Rodrigues Júnior e Matheus Marciano
 * Instituição: Universidade Federal de Lavras
 *
 * Descrição: Um sistema para uma plataforma de conteúdo digital que fornece transmissão on-line de uma ampla variedade de conteúdo digital
 * ==================================================
 */

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

struct conteudo {
    int anoLancamento;
    double precoUnitario;
    char titulo[50], genero[20], elenco[100], classificacao[10], situacao[20];
};

void exibeConteudo(conteudo *vetor, int posicao) {
    cout << endl;
    cout << "Titulo do conteudo: " << vetor[posicao].titulo << endl;
    cout << "Genero: " << vetor[posicao].genero << endl;
    cout << "Elenco: " << vetor[posicao].elenco << endl;
    cout << "Classificacao: " << vetor[posicao].classificacao << endl;
    cout << "Ano: " << vetor[posicao].anoLancamento << endl;
    cout << "Preco: " << vetor[posicao].precoUnitario << endl;
    cout << "Situacao: " << vetor[posicao].situacao << endl;
    cout << endl;
}

void exportar(string arquivo, conteudo *vetor, int quantidade) {
    ofstream gravacao(arquivo);
    if (gravacao) {
        for (int i = 0; i < quantidade; ++i) {
            if (strcmp("Excluido", vetor[i].situacao) != 0) {
                gravacao.write((const char *) (&vetor[i]), sizeof(conteudo));
            }
        }
        cout << "Conteudos exportados com sucesso." << endl << endl;
        gravacao.close();
    } else {
        cout << "Erro ao criar o arquivo." << endl << endl;
    }
}

void listar(conteudo *vetor, int quantidade) {
    for (int i = 0; i < quantidade; ++i) {
        if (strcmp("Excluido", vetor[i].situacao) != 0) {
            cout << "Titulo do conteudo: " << vetor[i].titulo << endl;
            cout << "Genero: " << vetor[i].genero << endl;
            cout << "Elenco: " << vetor[i].elenco << endl;
            cout << "Classificacao: " << vetor[i].classificacao << endl;
            cout << "Ano: " << vetor[i].anoLancamento << endl;
            cout << "Preco: " << vetor[i].precoUnitario << endl;
            cout << "Situacao: " << vetor[i].situacao << endl;
            cout << endl;
        }
    }
}

void listarComprado(conteudo *vetor, int quantidade) {
    cout << endl;
    for (int i = 0; i < quantidade; ++i) {
        if (strcmp("Comprado", vetor[i].situacao) == 0) {
            cout << "Titulo do conteudo: " << vetor[i].titulo << endl;
            cout << "Genero: " << vetor[i].genero << endl;
            cout << "Elenco: " << vetor[i].elenco << endl;
            cout << "Classificacao: " << vetor[i].classificacao << endl;
            cout << "Ano: " << vetor[i].anoLancamento << endl;
            cout << "Preco: " << vetor[i].precoUnitario << endl;
            cout << "Situacao: " << vetor[i].situacao << endl;
            cout << endl;
        }
    }
}

void menu() {
    cout << "[1] Cadastrar novo conteudo" << endl
         << "[2] Consultar conteudo" << endl
         << "[3] Listar conteudos" << endl
         << "[4] Excluir conteudo" << endl
         << "[5] Efetuar compra" << endl
         << "[6] Listar conteudos comprados" << endl
         << "[7] Exportar dados" << endl
         << "[8] Sair" << endl;
}

void preencheVetor(conteudo *vetor, int posicao) {
    cin.ignore();
    cout << "Informe o genero do conteudo:";
    cin.get(vetor[posicao].genero, 20);
    cin.ignore();
    cout << "Informe o elenco do conteudo:";
    cin.get(vetor[posicao].elenco, 100);
    cin.ignore();
    cout << "Informe a classificacao do conteudo:";
    cin >> vetor[posicao].classificacao;
    cin.ignore();
    cout << "Informe o ano de lancamento do conteudo:";
    cin >> vetor[posicao].anoLancamento;
    cin.ignore();
    cout << "Informe o preco do conteudo:";
    cin >> vetor[posicao].precoUnitario;
    cin.ignore();
    cout << "Informe a situacao de venda do conteudo:";
    cin.get(vetor[posicao].situacao, 20);
    cin.ignore();
    cout << endl;
}

int particiona(conteudo *vetor, int inicio, int fim) {
    conteudo pivo;
    pivo = vetor[inicio];
    int i = inicio + 1, j = fim;
    while (i <= j) {
        if (vetor[i].titulo[0] <= pivo.titulo[0]) {
            i++;
        } else if (pivo.titulo[0] <= vetor[j].titulo[0]) {
            j--;
        } else {
            swap(vetor[i], vetor[j]);
            i++;
            j--;
        }
    }
    vetor[inicio] = vetor[j];
    vetor[j] = pivo;
    return j;
}

void quickSort(conteudo *vetor, int posPivo, int fim) {
    int posNovoPivo;
    if (posPivo < fim) {
        posNovoPivo = particiona(vetor, posPivo, fim);
        quickSort(vetor, posPivo, posNovoPivo - 1);
        quickSort(vetor, posNovoPivo + 1, fim);
    }
}

int busca(conteudo *vetor, char titulo[], int quantidade) {
    int inicio = 0;
    while (inicio <= quantidade) {
        int i = (inicio + quantidade) / 2;
        if (strcmp(titulo, vetor[i].titulo) == 0) {
            return i;
        }
        if (vetor[i].titulo[0] < titulo[0]) {
            inicio = i + 1;
        } else {
            quantidade = i;
        }
    }
    return -1;
}

int verificaExistencia(conteudo *vetor, char titulo[], int quantidade) {
    for (int i = 0; i < quantidade; ++i) {
        if (strcmp(titulo, vetor[i].titulo) == 0) {
            return 0;
        }
    }
    return 1;
}

double somaPrecoTotal(conteudo *vetor, int quantidade) {
    double soma = 0;
    for (int i = 0; i < quantidade; ++i) {
        if (strcmp("Comprado", vetor[i].situacao) == 0) {
            soma += vetor[i].precoUnitario;
        }
    }
    return soma;
}

conteudo *redimensionaVetor(conteudo *vetor, int &tamanho) {
    conteudo *vetorAux = new conteudo[tamanho];
    for (int i = 0; i < tamanho; ++i) {
        vetorAux[i] = vetor[i];
    }
    tamanho += 3;
    vetor = new conteudo[tamanho];
    for (int i = 0; i < tamanho; ++i) {
        vetor[i] = vetorAux[i];
    }
    delete[] vetorAux;
    return vetor;
}

int main() {
    cout << "Bem-vindo ao Digitalizze!" << endl << endl;

    int opcaoMenu, controladorMenu = -1;
    int tamanhoVetorCadastro = 3, quantidadeConteudoCadastrado = 0, posicao = 0;
    conteudo *vetorCadastro = new conteudo[tamanhoVetorCadastro];

    do {
        menu();
        cout << "Digite uma opcao: ";
        cin >> opcaoMenu;
        cout << endl;
        switch (opcaoMenu) {
            case 1:
                if (quantidadeConteudoCadastrado < tamanhoVetorCadastro) {
                    char *tituloAux = new char[50];
                    cout << "Informe o titulo do conteudo:";
                    cin.ignore();
                    cin.get(tituloAux, 50);
                    if (verificaExistencia(vetorCadastro, tituloAux, quantidadeConteudoCadastrado) == 1) { //Cuidado com os espaços vazios.
                        strcpy(vetorCadastro[posicao].titulo, tituloAux);
                        preencheVetor(vetorCadastro, posicao);
                        cout << "Conteudo cadastrado com sucesso." << endl << endl;
                        ++quantidadeConteudoCadastrado;
                        ++posicao;
                    } else {
                        cout << "Conteudo ja cadastrado no sistema." << endl << endl;
                    }
                    delete[] tituloAux;
                } else {
                    vetorCadastro = redimensionaVetor(vetorCadastro, tamanhoVetorCadastro);
                    char *tituloAux = new char[50];
                    cin.ignore();
                    cin.get(tituloAux, 50);
                    if (verificaExistencia(vetorCadastro, tituloAux, quantidadeConteudoCadastrado) == 1) { //Cuidado com os espaços vazios.
                        strcpy(vetorCadastro[posicao].titulo, tituloAux);
                        preencheVetor(vetorCadastro, posicao);
                        ++quantidadeConteudoCadastrado;
                        ++posicao;
                    } else {
                        cout << "Conteúdo já cadastrado no sistema." << endl << endl;
                    }
                    delete[] tituloAux;
                }
                break;

            case 2: {
                quickSort(vetorCadastro, 0, quantidadeConteudoCadastrado - 1);
                char *tituloBusca = new char[50];
                cout << "Informe o titulo do conteudo desejado para a consulta:";
                cin.ignore();
                cin.get(tituloBusca, 50);
                if (verificaExistencia(vetorCadastro, tituloBusca, quantidadeConteudoCadastrado) == 0) {
                    int posBusca;
                    posBusca = busca(vetorCadastro, tituloBusca, quantidadeConteudoCadastrado);
                    if (strcmp("Excluido", vetorCadastro[posBusca].situacao) != 0) {
                        exibeConteudo(vetorCadastro, posBusca);
                    } else {
                        cout << "O conteudo encontra-se excluido do sistema." << endl << endl;
                    }
                } else {
                    cout << "O conteudo nao existe no sistema." << endl << endl;
                }
                delete[] tituloBusca;
            }
                break;

            case 3:
                quickSort(vetorCadastro, 0, quantidadeConteudoCadastrado - 1);
                listar(vetorCadastro, quantidadeConteudoCadastrado);
                break;

            case 4: {
                quickSort(vetorCadastro, 0, quantidadeConteudoCadastrado - 1);
                char *tituloExclusao = new char[50];
                cout << "Informe o titulo do conteudo desejado para a exclusao:";
                cin.ignore();
                cin.get(tituloExclusao, 50);
                if (verificaExistencia(vetorCadastro, tituloExclusao, quantidadeConteudoCadastrado) == 0) {
                    int posBusca, escolha;
                    posBusca = busca(vetorCadastro, tituloExclusao, quantidadeConteudoCadastrado);
                    if (strcmp("Excluido", vetorCadastro[posBusca].situacao) != 0) {
                        exibeConteudo(vetorCadastro, posBusca);
                        cout << "Confirmar exclusao? 1 - Sim | 2 - Nao" << endl;
                        cin >> escolha;
                        if (escolha == 1) {
                            strcpy(vetorCadastro[posBusca].situacao, "Excluido");
                            cout << "Conteudo excluido com sucesso." << endl << endl;
                        } else {
                            cout << "Ato de exclusao cancelado." << endl << endl;
                        }
                    } else {
                        cout << "O conteudo encontra-se excluido do sistema." << endl << endl;
                    }
                } else {
                    cout << "O conteudo nao existe no sistema." << endl << endl;
                }
                delete[] tituloExclusao;
            }
                break;

            case 5: {
                quickSort(vetorCadastro, 0, quantidadeConteudoCadastrado - 1);
                char *tituloCompra;
                tituloCompra = new char[50];
                cout << "Informe o titulo do conteudo desejado para a compra:";
                cin.ignore();
                cin.get(tituloCompra, 50);
                if (verificaExistencia(vetorCadastro, tituloCompra, quantidadeConteudoCadastrado) == 0) {
                    int posBusca, escolha;
                    posBusca = busca(vetorCadastro, tituloCompra, quantidadeConteudoCadastrado);
                    if (strcmp("Para comprar", vetorCadastro[posBusca].situacao) == 0) {
                        exibeConteudo(vetorCadastro, posBusca);
                        cout << "Confirmar compra do conteudo? 1 - Sim | 2 - Nao" << endl;
                        cin >> escolha;
                        if (escolha == 1) {
                            strcpy(vetorCadastro[posBusca].situacao, "Comprado");
                            cout << "Compra efetuada com sucesso." << endl << endl;
                        } else {
                            cout << "Ato de compra cancelado." << endl << endl;
                        }
                    } else {
                        cout << "O conteudo nao esta disponivel para compra." << endl << endl;
                    }
                } else {
                    cout << "O conteudo nao existe no sistema." << endl << endl;
                }
                delete[] tituloCompra;
            }
                break;

            case 6:
                quickSort(vetorCadastro, 0, quantidadeConteudoCadastrado - 1);
                listarComprado(vetorCadastro, quantidadeConteudoCadastrado);
                cout << "Valor total pago: " << somaPrecoTotal(vetorCadastro, quantidadeConteudoCadastrado) << endl << endl;
                break;

            case 7: {
                quickSort(vetorCadastro, 0, quantidadeConteudoCadastrado - 1);
                string nomeArquivo;
                cout << "Informe o nome para o seu arquivo a ser criado:";
                cin >> nomeArquivo;
                exportar(nomeArquivo, vetorCadastro, quantidadeConteudoCadastrado);
            }
                break;

            case 8:
                delete[] vetorCadastro;
                ++controladorMenu;
                cout << "Encerrando sistema...";
                break;

            default:
                cout << "Opcao invalida!" << endl << endl;
        }
    } while (controladorMenu < 0);
    return 0;
}
