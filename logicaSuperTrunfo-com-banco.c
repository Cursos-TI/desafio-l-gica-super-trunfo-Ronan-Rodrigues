#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_CARTAS 27
#define EPSILON 0.0001

typedef struct {
    char estado[3];
    char codigo[10];
    char nomeCidade[50];
    int populacao;
    float area;
    float pib;
    int pontosTuristicos;
    float densidadePopulacional;
    float pibPerCapita;
} Carta;

void calcularIndicadores(Carta *c) {
    c->densidadePopulacional = c->populacao / c->area;
    c->pibPerCapita = (c->pib * 1000000000) / c->populacao;
}

void exibirCarta(Carta c) {
    printf("\n📍 Cidade: %s (%s)\n", c.nomeCidade, c.estado);
    printf("Código: %s\n", c.codigo);
}

float obterValorPorAtributo(Carta c, int atributo) {
    switch (atributo) {
        case 1: return c.populacao;
        case 2: return c.area;
        case 3: return c.pib;
        case 4: return c.densidadePopulacional;
        case 5: return c.pibPerCapita;
        case 6: return c.pontosTuristicos;
        default: return -1;
    }
}

const char* nomeAtributo(int a) {
    switch (a) {
        case 1: return "População";
        case 2: return "Área";
        case 3: return "PIB";
        case 4: return "Densidade Populacional";
        case 5: return "PIB per capita";
        case 6: return "Pontos Turísticos";
        default: return "Desconhecido";
    }
}

void mostrarMenuAtributos() {
    printf("\nEscolha 3 atributos para comparação:\n");
    printf("1 - População\n");
    printf("2 - Área\n");
    printf("3 - PIB\n");
    printf("4 - Densidade Populacional\n");
    printf("5 - PIB per capita\n");
    printf("6 - Pontos Turísticos\n");
}


int compararAtributo(float valor1, float valor2, int atributo) {
    printf("\n🔍 Comparando atributo %s:\n", nomeAtributo(atributo));
    printf("  Valor da Carta 1: %.2f\n", valor1);
    printf("  Valor da Carta 2: %.2f\n", valor2);

    if (atributo == 4) { // Densidade: menor é melhor
        if (valor1 + EPSILON < valor2) {
            printf("  ✅ Carta 1 venceu neste atributo (menor é melhor).\n");
            return 1;
        } else if (valor2 + EPSILON < valor1) {
            printf("  ✅ Carta 2 venceu neste atributo (menor é melhor).\n");
            return 2;
        } else {
            printf("  🤝 Empate neste atributo.\n");
            return 0;
        }
    } else {
        if (valor1 > valor2 + EPSILON) {
            printf("  ✅ Carta 1 venceu neste atributo (maior é melhor).\n");
            return 1;
        } else if (valor2 > valor1 + EPSILON) {
            printf("  ✅ Carta 2 venceu neste atributo (maior é melhor).\n");
            return 2;
        } else {
            printf("  🤝 Empate neste atributo.\n");
            return 0;
        }
    }
}


void exibirResultado(int vencedor, Carta c1, Carta c2, int a1, int a2, int a3) {
    printf("\n=== Resultado da Comparação ===\n");

    float v1a1 = obterValorPorAtributo(c1, a1);
    float v2a1 = obterValorPorAtributo(c2, a1);
    float v1a2 = obterValorPorAtributo(c1, a2);
    float v2a2 = obterValorPorAtributo(c2, a2);
    float v1a3 = obterValorPorAtributo(c1, a3);
    float v2a3 = obterValorPorAtributo(c2, a3);

    printf("\n🔹 %s:\n", nomeAtributo(a1));
    printf("  %s: %.2f\n", c1.nomeCidade, v1a1);
    printf("  %s: %.2f\n", c2.nomeCidade, v2a1);

    printf("\n🔹 %s:\n", nomeAtributo(a2));
    printf("  %s: %.2f\n", c1.nomeCidade, v1a2);
    printf("  %s: %.2f\n", c2.nomeCidade, v2a2);

    printf("\n🔹 %s:\n", nomeAtributo(a3));
    printf("  %s: %.2f\n", c1.nomeCidade, v1a3);
    printf("  %s: %.2f\n", c2.nomeCidade, v2a3);

    printf("\n🏆 Resultado Final:\n");
    if (vencedor == 1)
        printf("  Carta 1 (%s) venceu!\n\n", c1.nomeCidade);
    else if (vencedor == 2)
        printf("  Carta 2 (%s) venceu!\n\n", c2.nomeCidade);
    else
        printf("  🤝 Empate entre as cartas!\n\n");
}

int buscarPorEstado(Carta cartas[], int total, const char sigla[]) {
    for (int i = 0; i < total; i++) {
        if (strcmp(cartas[i].estado, sigla) == 0) {
            return i;
        }
    }
    return -1;
}

void inicializarBanco(Carta cartas[]) {
    Carta base[MAX_CARTAS] = {
        {"SP", "SP001", "São Paulo", 11895578, 1521, 85, 80},
        {"RJ", "RJ001", "Rio de Janeiro", 6729894, 1200, 55, 100},
        {"DF", "DF001", "Brasília", 2982818, 5802, 47.8, 40},
        {"CE", "CE001", "Fortaleza", 2574412, 313, 25, 50},
        {"BA", "BA001", "Salvador", 2568928, 693, 30, 70},
        {"MG", "MG001", "Belo Horizonte", 2416339, 331, 40, 45},
        {"AM", "AM001", "Manaus", 2279686, 11401, 35, 35},
        {"PR", "PR001", "Curitiba", 1829225, 434, 45, 50},
        {"PE", "PE001", "Recife", 1587707, 218, 38, 60},
        {"GO", "GO001", "Goiânia", 1494599, 739, 42, 25},
        {"PA", "PA001", "Belém", 1398531, 1059, 30, 40},
        {"RS", "RS001", "Porto Alegre", 1389322, 496, 48, 45},
        {"MA", "MA001", "São Luís", 1088057, 831, 28, 35},
        {"AL", "AL001", "Maceió", 994464, 511, 32, 40},
        {"MS", "MS001", "Campo Grande", 954537, 8096, 40, 20},
        {"PI", "PI001", "Teresina", 902644, 1392, 27, 18},
        {"PB", "PB001", "João Pessoa", 888679, 211, 35, 35},
        {"RN", "RN001", "Natal", 785368, 170, 33, 40},
        {"MT", "MT001", "Cuiabá", 682932, 3538, 38, 25},
        {"SE", "SE001", "Aracaju", 628849, 182, 30, 30},
        {"SC", "SC001", "Florianópolis", 576361, 675, 50, 60},
        {"RO", "RO001", "Porto Velho", 514873, 34082, 32, 15},
        {"AP", "AP001", "Macapá", 487200, 6563, 28, 20},
        {"RR", "RR001", "Boa Vista", 470169, 5686, 30, 18},
        {"AC", "AC001", "Rio Branco", 387852, 8835, 29, 18},
        {"ES", "ES001", "Vitória", 342800, 93, 55, 35},
        {"TO", "TO001", "Palmas", 323625, 2218, 35, 25}
    };


    for (int i = 0; i < MAX_CARTAS; i++) {
        cartas[i] = base[i];
        calcularIndicadores(&cartas[i]);
    }
}




 int determinarVencedorPorAtributos(Carta c1, Carta c2, int atributos[], int totalAtributos) {
    int pontos1 = 0;
    int pontos2 = 0;

    printf("\n=== Comparação Detalhada dos Atributos ===\n");

    for (int i = 0; i < totalAtributos; i++) {
        int atributo = atributos[i];
        float valor1 = obterValorPorAtributo(c1, atributo);
        float valor2 = obterValorPorAtributo(c2, atributo);
        int resultado = compararAtributo(valor1, valor2, atributo);

        printf("\n🔹 %s:\n", nomeAtributo(atributo));
        printf("  %s: %.2f\n", c1.nomeCidade, valor1);
        printf("  %s: %.2f\n", c2.nomeCidade, valor2);

        if (resultado == 1) {
            printf("  ✅ %s venceu neste atributo.\n", c1.nomeCidade);
            pontos1++;
        } else if (resultado == 2) {
            printf("  ✅ %s venceu neste atributo.\n", c2.nomeCidade);
            pontos2++;
        } else {
            printf("  🤝 Empate neste atributo.\n");
        }
    }

    printf("\n📊 Pontuação Final:\n");
    printf("  %s: %d ponto(s)\n", c1.nomeCidade, pontos1);
    printf("  %s: %d ponto(s)\n", c2.nomeCidade, pontos2);

    if (pontos1 > pontos2) return 1;
    else if (pontos2 > pontos1) return 2;
    else return 0;
}





int main() {
    system("chcp 65001");

    Carta cartas[MAX_CARTAS];
    inicializarBanco(cartas);

    char sigla1[3], sigla2[3];
    int i1, i2;

printf("\nDigite a sigla do primeiro estado (ex: SP): ");
scanf(" %2s", sigla1);
for (int i = 0; i < strlen(sigla1); i++) {
    sigla1[i] = toupper(sigla1[i]);
}
i1 = buscarPorEstado(cartas, MAX_CARTAS, sigla1);

printf("Digite a sigla do segundo estado (ex: RJ): ");
scanf(" %2s", sigla2);
for (int i = 0; i < strlen(sigla2); i++) {
    sigla2[i] = toupper(sigla2[i]);
}
i2 = buscarPorEstado(cartas, MAX_CARTAS, sigla2);


    if (i1 == -1 || i2 == -1) {
        printf("\n❌ Estado não encontrado. Verifique as siglas digitadas.\n");
        return 1;
    }

    printf("\n=== Cartas Selecionadas ===\n");
    exibirCarta(cartas[i1]);
    exibirCarta(cartas[i2]);

    printf("\n=== Comparação de Atributos ===\n");
    mostrarMenuAtributos();

    int atributo1, atributo2, atributo3;
    printf("Escolha o primeiro atributo (1-6): ");
    scanf("%d", &atributo1);
    printf("Escolha o segundo atributo (1-6): ");
    scanf("%d", &atributo2);
    printf("Escolha o terceiro atributo (1-6): ");
    scanf("%d", &atributo3);

    printf("\nVocê escolheu:\n");
    printf("1. %s\n", nomeAtributo(atributo1));
    printf("2. %s\n", nomeAtributo(atributo2));
    printf("3. %s\n", nomeAtributo(atributo3));
    printf("\n🔍 Iniciando a comparação...\n");
    printf("\n=== Resultados da Comparação ===\n");
    printf("Comparando %s, %s e %s entre as cartas selecionadas...\n", 
           nomeAtributo(atributo1), nomeAtributo(atributo2), nomeAtributo(atributo3));

    // Validação dos atributos

    if (atributo1 < 1 || atributo1 > 6 ||
        atributo2 < 1 || atributo2 > 6 ||
        atributo3 < 1 || atributo3 > 6 ||
        atributo1 == atributo2 || atributo1 == atributo3 || atributo2 == atributo3) {
        printf("\n❌ Atributos inválidos ou repetidos. Tente novamente.\n");
        return 1;
    }


int atributos[3] = {atributo1, atributo2, atributo3};
int vencedor = determinarVencedorPorAtributos(cartas[i1], cartas[i2], atributos, 3);

    exibirResultado(vencedor, cartas[i1], cartas[i2], atributo1, atributo2, atributo3);
   
    return 0;
}
