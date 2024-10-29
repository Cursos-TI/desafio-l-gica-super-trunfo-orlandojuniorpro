#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PAIS 10
#define MAX_ESTADOS 4
#define MAX_CIDADES 8

typedef struct {
    int codigo;
    char nome[50];
    int populacao;
    float area; // em km²
    float pib; // em milhões
    int pontos_turisticos;
} Cidade;

typedef struct {
    char nome[50];
    Cidade cidades[MAX_CIDADES];
} Estado;

typedef struct {
    char nome[50];
    Estado estados[MAX_ESTADOS];
} Pais;

void cadastrarCidades(Estado *estado) {
    for (int j = 0; j < MAX_CIDADES; j++) {
        printf("\n--- Cadastro da Cidade %d ---\n", j + 1);
        printf("Código: ");
        scanf("%d", &estado->cidades[j].codigo);
        printf("Nome: ");
        scanf("%s", estado->cidades[j].nome);
        printf("População: ");
        scanf("%d", &estado->cidades[j].populacao);
        printf("Área (km²): ");
        scanf("%f", &estado->cidades[j].area);
        printf("PIB (milhões): ");
        scanf("%f", &estado->cidades[j].pib);
        printf("Número de pontos turísticos: ");
        scanf("%d", &estado->cidades[j].pontos_turisticos);
        
        // Verifica se a cidade foi cadastrada corretamente
        if (estado->cidades[j].populacao <= 0 || estado->cidades[j].area <= 0) {
            printf("Erro: População e área devem ser maiores que zero.\n");
            j--; // Permite nova entrada
            continue;
        }
    }
}

float calcularDensidadePopulacional(Cidade cidade) {
    return cidade.populacao / cidade.area;
}

float calcularPibPerCapita(Cidade cidade) {
    if (cidade.populacao > 0) {
        return cidade.pib * 1e6 / cidade.populacao; // PIB em milhões dividido pela população
    }
    return 0; // Para evitar divisão por zero
}

float calcularSuperPoder(Cidade cidade) {
    return cidade.populacao + cidade.area + cidade.pib + cidade.pontos_turisticos;
}

void exibirDados(Pais pais) {
    printf("\n--- Dados do País: %s ---\n", pais.nome);
    for (int i = 0; i < MAX_ESTADOS; i++) {
        if (pais.estados[i].nome[0] != '\0') { // Verifica se o estado foi cadastrado
            printf("\nEstado: %s\n", pais.estados[i].nome);
            for (int j = 0; j < MAX_CIDADES; j++) {
                Cidade cidade = pais.estados[i].cidades[j];
                if (cidade.nome[0] != '\0') { // Verifica se a cidade foi cadastrada
                    printf("\nCidade %d:\n", j + 1);
                    printf("Código: %d\n", cidade.codigo);
                    printf("Nome: %s\n", cidade.nome);
                    printf("População: %d\n", cidade.populacao);
                    printf("Área: %.2f km²\n", cidade.area);
                    printf("PIB: %.2f milhões\n", cidade.pib);
                    printf("Pontos turísticos: %d\n", cidade.pontos_turisticos);

                    // Cálculo das novas propriedades
                    float densidade = calcularDensidadePopulacional(cidade);
                    float pibPerCapita = calcularPibPerCapita(cidade);

                    // Exibição das novas propriedades
                    printf("Densidade Populacional: %.2f habitantes/km²\n", densidade);
                    printf("PIB per Capita: R$ %.2f\n", pibPerCapita); // PIB per capita em reais
                    printf("Super Poder: %.2f\n", calcularSuperPoder(cidade));
                }
            }
        }
    }
}

void compararCidades(Cidade c1, Cidade c2) {
    float densidade1 = calcularDensidadePopulacional(c1);
    float densidade2 = calcularDensidadePopulacional(c2);

    float pibPerCapita1 = calcularPibPerCapita(c1);
    float pibPerCapita2 = calcularPibPerCapita(c2);

    float superPoder1 = calcularSuperPoder(c1);
    float superPoder2 = calcularSuperPoder(c2);

    // Comparação de Densidade Populacional (menor é melhor)
    if (densidade1 < densidade2) {
        printf("\nA carta '%s' vence na Densidade Populacional!\n", c1.nome);
    } else if (densidade1 > densidade2) {
        printf("\nA carta '%s' vence na Densidade Populacional!\n", c2.nome);
    } else {
        printf("\nAmbas as cartas têm a mesma Densidade Populacional.\n");
    }

    // Comparação de PIB per Capita (maior é melhor)
    if (pibPerCapita1 > pibPerCapita2) {
        printf("A carta '%s' vence no PIB per Capita!\n", c1.nome);
    } else if (pibPerCapita1 < pibPerCapita2) {
        printf("A carta '%s' vence no PIB per Capita!\n", c2.nome);
    } else {
        printf("Ambas as cartas têm o mesmo PIB per Capita.\n");
    }

    // Comparação de Super Poder (maior é melhor)
    if (superPoder1 > superPoder2) {
        printf("A carta '%s' vence no Super Poder!\n", c1.nome);
    } else if (superPoder1 < superPoder2) {
        printf("A carta '%s' vence no Super Poder!\n", c2.nome);
    } else {
        printf("Ambas as cartas têm o mesmo Super Poder.\n");
    }
}

void menu() {
    printf("\n=== Jogo Super Trunfo - Cadastro de Países ===\n");
    printf("1. Cadastrar Países e Cidades\n");
    printf("2. Exibir Dados Cadastrados\n");
    printf("3. Comparar Cartas\n");
    printf("4. Sair\n");
}

int main() {
    Pais paises[MAX_PAIS] = {0}; // Inicializa o array para evitar lixo de memória
    int numPaises = 0;
    
    while (1) {
        menu();
        int opcao;
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                if (numPaises < MAX_PAIS) {
                    printf("\n--- Cadastro do País ---\n");
                    printf("Nome do país: ");
                    scanf("%s", paises[numPaises].nome);

                    for (int j = 0; j < MAX_ESTADOS; j++) {
                        printf("\nCadastro do Estado %d:\n", j + 1);
                        printf("Nome do estado: ");
                        scanf("%s", paises[numPaises].estados[j].nome);
                        cadastrarCidades(&paises[numPaises].estados[j]);
                    }

                    numPaises++;
                } else {
                    printf("Limite de países atingido!\n");
                }
                break;

            case 2:
                for (int i = 0; i < numPaises; i++) {
                    exibirDados(paises[i]);
                }
                break;

            case 3:
                if (numPaises > 0) {
                    int estadoIndex, cidadeIndex1, cidadeIndex2;
                    
                    // Escolha do país para comparação
                    for (int i = 0; i < numPaises; i++) {
                        printf("%d. %s\n", i + 1, paises[i].nome);
                    }
                    
                    int paisEscolhido;
                    printf("Escolha o país para comparação: ");
                    scanf("%d", &paisEscolhido);
                    
                    if(paisEscolhido < 1 || paisEscolhido > numPaises){
                        printf("País inválido!\n");
                        break;
                    }

                    Pais paisSelecionado = paises[paisEscolhido - 1];

                    // Escolha das cidades para comparação
                    for (int i = 0; i < MAX_ESTADOS; i++) {
                        if(paisSelecionado.estados[i].nome[0] != '\0'){
                            for(int j = 0; j < MAX_CIDADES; j++){
                                if(paisSelecionado.estados[i].cidades[j].nome[0] != '\0'){
                                    printf("%d. %s - Cidade %d\n",
                                           j + 1,
                                           paisSelecionado.estados[i].cidades[j].nome,
                                           paisSelecionado.estados[i].cidades[j].codigo);
                                }
                            }
                        }
                    }

                    printf("Escolha a primeira cidade para comparação: ");
                    scanf("%d", &cidadeIndex1);

                    printf("Escolha a segunda cidade para comparação: ");
                    scanf("%d", &cidadeIndex2);

                    // Verifica se os índices estão dentro do limite
                    if(cidadeIndex1 < 1 || cidadeIndex2 < 1 || 
                       cidadeIndex1 > MAX_CIDADES || 
                       cidadeIndex2 > MAX_CIDADES){
                        printf("Cidades inválidas!\n");
                        break;
                    }

                    Cidade cidade1, cidade2;
                    
                    // Busca as cidades escolhidas
                    for(int i = 0; i < MAX_ESTADOS; i++){
                        for(int j = 0; j < MAX_CIDADES; j++){
                            if(paisSelecionado.estados[i].cidades[j].codigo == cidadeIndex1){
                                cidade1 = paisSelecionado.estados[i].cidades[j];
                            }
                            if(paisSelecionado.estados[i].cidades[j].codigo == cidadeIndex2){
                                cidade2 = paisSelecionado.estados[i].cidades[j];
                            }
                        }
                    }

                    compararCidades(cidade1, cidade2);

                } else {
                    printf("Nenhum país cadastrado para comparação.\n");
                }
                break;

            case 4:
                printf("Saindo do programa. Até logo!\n");
                exit(0);

            default:
                printf("Opção inválida! Tente novamente.\n");
                break;
        }
    }

    return 0;
}