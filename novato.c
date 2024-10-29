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
        
        // Exibir confirmação de cadastro
        printf("\nCidade cadastrada com sucesso!\n");
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
                }
            }
        }
    }
}

void compararCidades(Cidade c1, Cidade c2, char* propriedade) {
    float valor1, valor2;

    if (strcmp(propriedade, "populacao") == 0) {
        valor1 = c1.populacao;
        valor2 = c2.populacao;
    } else if (strcmp(propriedade, "area") == 0) {
        valor1 = c1.area;
        valor2 = c2.area;
    } else if (strcmp(propriedade, "pib") == 0) {
        valor1 = c1.pib;
        valor2 = c2.pib;
    } else if (strcmp(propriedade, "densidade") == 0) {
        valor1 = calcularDensidadePopulacional(c1);
        valor2 = calcularDensidadePopulacional(c2);
        
        // Comparação de Densidade Populacional (menor é melhor)
        if (valor1 < valor2) {
            printf("\nA carta '%s' vence na Densidade Populacional!\n", c1.nome);
            return;
        } else if (valor1 > valor2) {
            printf("\nA carta '%s' vence na Densidade Populacional!\n", c2.nome);
            return;
        } else {
            printf("\nAmbas as cartas têm a mesma Densidade Populacional.\n");
            return;
        }
    } else if (strcmp(propriedade, "pib_per_capita") == 0) {
        valor1 = calcularPibPerCapita(c1);
        valor2 = calcularPibPerCapita(c2);
    } else {
        printf("Propriedade inválida para comparação.\n");
        return;
    }

    // Comparação padrão (maior é melhor)
    if (valor1 > valor2) {
        printf("\nA carta '%s' vence na propriedade escolhida!\n", c1.nome);
    } else if (valor1 < valor2) {
        printf("\nA carta '%s' vence na propriedade escolhida!\n", c2.nome);
    } else {
        printf("\nAmbas as cartas têm o mesmo valor na propriedade escolhida.\n");
    }
}

void menu() {
    printf("\n=== Jogo Super Trunfo - Cadastro de Países ===\n");
    printf("1. Cadastrar Países e Cidades\n");
    printf("2. Exibir Dados Cadastrados\n");
    printf("3. Comparar Cartas\n");
    printf("4. Sair\n");
}

void limparBuffer() {
    while(getchar() != '\n'); // Limpa o buffer de entrada
}

int main() {
    Pais paises[MAX_PAIS];
    int numPaises = 0;
    int opcao;

    while (1) {
        menu();
        printf("Escolha uma opção: ");
        
        while(scanf("%d", &opcao) != 1) { // Verifica se a entrada é válida
            limparBuffer(); // Limpa o buffer se não for um número
            printf("Entrada inválida! Tente novamente: ");
        }

        switch (opcao) {
            case 1:
                if (numPaises < MAX_PAIS) {
                    printf("\n--- Cadastro do País ---\n");
                    printf("Nome do país: ");
                    limparBuffer(); // Limpa o buffer antes de ler uma string
                    scanf("%[^\n]", paises[numPaises].nome); // Lê uma linha inteira

                    for (int j = 0; j < MAX_ESTADOS; j++) {
                        printf("\nCadastro do Estado %d:\n", j + 1);
                        printf("Nome do estado: ");
                        limparBuffer(); 
                        scanf("%[^\n]", paises[numPaises].estados[j].nome); 
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
                    
                    while(scanf("%d", &paisEscolhido) != 1 || paisEscolhido < 1 || paisEscolhido > numPaises){
                        limparBuffer();
                        printf("País inválido! Tente novamente: ");
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

                    while(1){
                        printf("Escolha a primeira cidade para comparação: ");
                        while(scanf("%d", &cidadeIndex1) != 1 || cidadeIndex1 < 1 || cidadeIndex1 > MAX_CIDADES){
                            limparBuffer();
                            printf("Cidade inválida! Tente novamente: ");
                        }

                        printf("Escolha a segunda cidade para comparação: ");
                        while(scanf("%d", &cidadeIndex2) != 1 || cidadeIndex2 < 1 || cidadeIndex2 > MAX_CIDADES){
                            limparBuffer();
                            printf("Cidade inválida! Tente novamente: ");
                        }

                        // Verifica se os índices estão dentro do limite
                        if(cidadeIndex1 <= MAX_CIDADES && cidadeIndex2 <= MAX_CIDADES){
                            break; // Saia do loop se as cidades forem válidas
                        }
                        else{
                            printf("Cidades inválidas! Tente novamente.\n");
                        }
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

                    char propriedade[20];
                    
                    // Escolha da propriedade para comparação
                    while(1){
                        printf("Escolha a propriedade para comparação (populacao/area/pib/densidade/pib_per_capita): ");
                        limparBuffer();
                        scanf("%[^\n]", propriedade);

                        if(strcmp(propriedade, "populacao") == 0 || 
                           strcmp(propriedade, "area") == 0 ||
                           strcmp(propriedade, "pib") == 0 ||
                           strcmp(propriedade, "densidade") == 0 ||
                           strcmp(propriedade, "pib_per_capita") == 0){
                            break; // Saia do loop se a propriedade for válida
                        }else{
                            printf("Propriedade inválida! Tente novamente.\n");
                        }
                    }

                    compararCidades(cidade1, cidade2, propriedade);

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