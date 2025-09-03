//Inclui as bibliotecas
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_CARTAS 81 //Define a quantidade de cartas
#define EPSILON 0.0001 //Corrige a escala

//Extrutura das cartas
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

//Função para calclar os indicadores de densidade populacional e renda per capta
void calcularIndicadores(Carta *c) {
    c->densidadePopulacional = c->populacao / c->area;
    c->pibPerCapita = (c->pib * 1000000000) / c->populacao;
}

//Função para exibir a carta
void exibirCarta(Carta c) {
    printf("\n📍 Cidade: %s (%s)\n", c.nomeCidade, c.estado);
    printf("Código: %s\n", c.codigo);
}
//Função para obter o valor de um atributo
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
//Função para obter o nome do atributo
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

//Função para mostrar o menu de atributos
void mostrarMenuAtributos() {
    printf("\nEscolha 3 atributos para comparação:\n");
    printf("1 - População\n");
    printf("2 - Área\n");
    printf("3 - PIB\n");
    printf("4 - Densidade Populacional\n");
    printf("5 - PIB per capita\n");
    printf("6 - Pontos Turísticos\n");
}

//Função para comparar os atributos
int compararAtributo(float valor1, float valor2, int atributo) {
    if (atributo == 4) {
        if (valor1 + EPSILON < valor2) return 1;
        else if (valor2 + EPSILON < valor1) return 2;
        else return 0;
    } else {
        if (valor1 > valor2 + EPSILON) return 1;
        else if (valor2 > valor1 + EPSILON) return 2;
        else return 0;
    }
}
//Função para exibir o resultado
void exibirResultado(int vencedor, Carta c1, Carta c2, int a1, int a2, int a3) {
    printf("\n=== Resultado da Comparação ===\n");
  
    float v1a1 = obterValorPorAtributo(c1, a1);
    float v2a1 = obterValorPorAtributo(c2, a1);
    float v1a2 = obterValorPorAtributo(c1, a2);
    float v2a2 = obterValorPorAtributo(c2, a2);
    float v1a3 = obterValorPorAtributo(c1, a3);
    float v2a3 = obterValorPorAtributo(c2, a3);
    //Exibe os resultados dos atributos
    printf("\n🔹 %s:\n", nomeAtributo(a1));
    printf("  %s: %.2f\n", c1.nomeCidade, v1a1);
    printf("  %s: %.2f\n", c2.nomeCidade, v2a1);
    //Exibe os resultados dos atributos
    printf("\n🔹 %s:\n", nomeAtributo(a2));
    printf("  %s: %.2f\n", c1.nomeCidade, v1a2);
    printf("  %s: %.2f\n", c2.nomeCidade, v2a2);
    //Exibe os resultados dos atributos
    printf("\n🔹 %s:\n", nomeAtributo(a3));
    printf("  %s: %.2f\n", c1.nomeCidade, v1a3);
    printf("  %s: %.2f\n", c2.nomeCidade, v2a3);
    //Exibe o resultado final
    printf("\n🏆 Resultado Final:\n");
    if (vencedor == 1)
        printf("  Carta 1 (%s) venceu!\n\n", c1.nomeCidade);
    else if (vencedor == 2)
        printf("  Carta 2 (%s) venceu!\n\n", c2.nomeCidade);
    else
        printf("  🤝 Empate entre as cartas!\n\n");
}

//Função que determina o vencedor por atributos
int determinarVencedorPorAtributos(Carta c1, Carta c2, int atributos[], int totalAtributos) {
    int pontos1 = 0;
    int pontos2 = 0;
    printf("\n=== Comparação Detalhada dos Atributos ===\n");
    for (int i = 0; i < totalAtributos; i++) {
        int atributo = atributos[i];
        float valor1 = obterValorPorAtributo(c1, atributo);
        float valor2 = obterValorPorAtributo(c2, atributo);
        int resultado = compararAtributo(valor1, valor2, atributo);

        if (resultado == 1) pontos1++;
        else if (resultado == 2) pontos2++;
    }

    if (pontos1 > pontos2) return 1;
    else if (pontos2 > pontos1) return 2;
    else return 0;
}
//Lista de cidades por estados
void inicializarBanco(Carta cartas[]) {
    Carta base[] = {
       {"SP", "SP001", "São Paulo", 11895578, 1521, 85, 80},
    {"SP", "SP002", "Campinas", 1213792, 795, 82, 75},
    {"SP", "SP003", "Santos", 433656, 280, 80, 70},

    {"RJ", "RJ001", "Rio de Janeiro", 6729894, 1200, 55, 100},
    {"RJ", "RJ002", "Niterói", 515317, 133, 54, 85},
    {"RJ", "RJ003", "Petrópolis", 306678, 795, 50, 80},

    {"DF", "DF001", "Brasília", 2982818, 5802, 47.8, 40},
    {"DF", "DF002", "Taguatinga", 221909, 121, 48, 35},
    {"DF", "DF003", "Ceilândia", 398374, 230, 47, 30},

    {"CE", "CE001", "Fortaleza", 2574412, 313, 25, 50},
    {"CE", "CE002", "Juazeiro do Norte", 274207, 248, 26, 45},
    {"CE", "CE003", "Sobral", 211000, 212, 27, 40},

    {"BA", "BA001", "Salvador", 2568928, 693, 30, 70},
    {"BA", "BA002", "Feira de Santana", 619609, 1337, 31, 60},
    {"BA", "BA003", "Vitória da Conquista", 341000, 3200, 22, 55},

    {"MG", "MG001", "Belo Horizonte", 2416339, 331, 40, 45},
    {"MG", "MG002", "Uberlândia", 706597, 4116, 38, 50},
    {"MG", "MG003", "Juiz de Fora", 577532, 1436, 36, 48},

    {"AM", "AM001", "Manaus", 2279686, 11401, 35, 35},
    {"AM", "AM002", "Parintins", 114273, 5954, 34, 30},
    {"AM", "AM003", "Itacoatiara", 104046, 8676, 33, 28},

    {"PR", "PR001", "Curitiba", 1829225, 434, 45, 50},
    {"PR", "PR002", "Londrina", 575377, 1650, 44, 45},
    {"PR", "PR003", "Maringá", 439340, 487, 43, 48},

    {"PE", "PE001", "Recife", 1587707, 218, 38, 60},
    {"PE", "PE002", "Olinda", 393115, 41, 37, 55},
    {"PE", "PE003", "Caruaru", 365278, 920, 35, 50},

    {"GO", "GO001", "Goiânia", 1494599, 739, 42, 25},
    {"GO", "GO002", "Anápolis", 391772, 918, 41, 30},
    {"GO", "GO003", "Aparecida de Goiânia", 590146, 289, 42, 28},

    {"PA", "PA001", "Belém", 1398531, 1059, 30, 40},
    {"PA", "PA002", "Santarém", 306480, 22960, 31, 35},
    {"PA", "PA003", "Marabá", 283542, 15300, 32, 33},

    {"RS", "RS001", "Porto Alegre", 1389322, 496, 48, 45},
    {"RS", "RS002", "Caxias do Sul", 517451, 1644, 46, 42},
    {"RS", "RS003", "Pelotas", 343132, 1610, 45, 40},

    {"MA", "MA001", "São Luís", 1088057, 831, 28, 35},
    {"MA", "MA002", "Imperatriz", 259353, 1367, 29, 30},
    {"MA", "MA003", "Caxias", 164880, 518, 28, 28},

    {"AL", "AL001", "Maceió", 994464, 511, 32, 40},
    {"AL", "AL002", "Arapiraca", 234696, 351, 33, 35},
    {"AL", "AL003", "Palmeira dos Índios", 73000, 460, 32, 30},

    {"MS", "MS001", "Campo Grande", 954537, 8096, 40, 20},
    {"MS", "MS002", "Dourados", 225495, 4063, 39, 18},
    {"MS", "MS003", "Três Lagoas", 123281, 1020, 38, 17},

    {"PI", "PI001", "Teresina", 902644, 1392, 27, 18},
    {"PI", "PI002", "Parnaíba", 153863, 436, 28, 15},
    {"PI", "PI003", "Picos", 78300, 577, 27, 14},

    {"PB", "PB001", "João Pessoa", 888679, 211, 35, 35},
    {"PB", "PB002", "Campina Grande", 413830, 620, 34, 30},
    {"PB", "PB003", "Patos", 106000, 513, 33, 28},

    {"RN", "RN001", "Natal", 785368, 170, 33, 40},
    {"RN", "RN002", "Mossoró", 300618, 2110, 34, 35},
    {"RN", "RN003", "Parnamirim", 261469, 123, 33, 32},

    {"MT", "MT001", "Cuiabá", 682932, 3538, 38, 25},
    {"MT", "MT002", "Várzea Grande", 287526, 1166, 37, 22},
    {"MT", "MT003", "Rondonópolis", 236042, 4115, 36, 20},

    {"SE", "SE001", "Aracaju", 628849, 182, 30, 30},
    {"SE", "SE002", "Nossa Senhora do Socorro", 185706, 155, 30, 28},
    {"SE", "SE003", "Lagarto", 106000, 969, 29, 25},

    {"SC", "SC001", "Florianópolis", 576361, 675, 50, 60},
    {"SC", "SC002", "Joinville", 616323, 1120, 49, 55},
    {"SC", "SC003", "Blumenau", 361855, 519, 48, 50},

    {"RO", "RO001", "Porto Velho", 514873, 34082, 32, 15},
    {"RO", "RO002", "Ji-Paraná", 126316, 6897, 31, 13},
    {"RO", "RO003", "Ariquemes", 109523, 4420, 30, 12},

    {"AP", "AP001", "Macapá", 487200, 6563, 28, 20},
    {"AP", "AP002", "Santana", 123000, 112, 28, 18},
    {"AP", "AP003", "Laranjal do Jari", 45000, 3039, 27, 15},

    {"RR", "RR001", "Boa Vista", 470169, 5686, 30, 18},
    {"RR", "RR002", "Rorainópolis", 30000, 33000, 29, 15},
    {"RR", "RR003", "Caracaraí", 20000, 11800, 28, 14},

    {"AC", "AC001", "Rio Branco", 387852, 8835, 29, 18},
    {"AC", "AC002", "Cruzeiro do Sul", 89492, 7900, 28, 16},
    {"AC", "AC003", "Sena Madureira", 45800, 6400, 27, 15},

    {"ES", "ES001", "Vitória", 342800, 93, 55, 35},
    {"ES", "ES002", "Vila Velha", 501325, 210, 54, 38},
    {"ES", "ES003", "Serra", 527240, 553, 53, 36},

    {"TO", "TO001", "Palmas", 323625, 2218, 35, 25},
    {"TO", "TO002", "Araguaína", 183381, 4000, 34, 22},
    {"TO", "TO003", "Gurupi", 87000, 1835, 33, 20}

    };
    
    int total = sizeof(base) / sizeof(base[0]);
    for (int i = 0; i < total; i++) {
        cartas[i] = base[i];
        calcularIndicadores(&cartas[i]);
    }
}
//funcao para colocar as palavras em caixa alta
void lerUpper(char *destino, int tamanho) {
    scanf(" %s", destino);
    for (int i = 0; i < strlen(destino) && i < tamanho; i++) {
        destino[i] = toupper(destino[i]);
    }
}

//Função para listar as cidades
int listarCidadesNumeradas(Carta cartas[], int total, const char sigla[], int indices[]) {
    int count = 0;
    printf("\n📍 Cidades disponíveis no estado %s:\n", sigla);
    for (int i = 0; i < total; i++) {
        if (strcmp(cartas[i].estado, sigla) == 0) {
            printf("  %d - %s (Código: %s)\n", count + 1, cartas[i].nomeCidade, cartas[i].codigo);
            indices[count] = i;
            count++;
        }
    }
    return count;
}


int main() {
    system("chcp 65001"); // Corrige as acentuações 

    Carta cartas[MAX_CARTAS];
    inicializarBanco(cartas);

    //Menu principal
    int opcao;
    do {
        printf("\n=== Menu Principal ===\n");
        printf("1 - Listar cidades por estado\n");
        printf("2 - Comparar duas cidades\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        // Verifica a opção escolhida
        switch (opcao) {
            case 1: {
                char sigla[3];
                printf("\nDigite a sigla do estado (ex: SP): ");
                lerUpper(sigla, 2);
                int dummy[MAX_CARTAS];
                listarCidadesNumeradas(cartas, MAX_CARTAS, sigla, dummy);
                break;
            }

            case 2: {
                char sigla1[3], sigla2[3];
                int indices1[MAX_CARTAS], indices2[MAX_CARTAS];
                int total1, total2, escolha1, escolha2;
                int i1, i2;

                printf("\nDigite a sigla do primeiro estado (ex: SP): ");
                lerUpper(sigla1, 2);
                total1 = listarCidadesNumeradas(cartas, MAX_CARTAS, sigla1, indices1);
                if (total1 == 0) {
                    printf("\n❌ Nenhuma cidade encontrada para o estado %s.\n", sigla1);
                    break;
                }
                printf("Escolha o número da cidade desejada (1 a %d): ", total1);
                scanf("%d", &escolha1);
                if (escolha1 < 1 || escolha1 > total1) {
                    printf("\n❌ Escolha inválida.\n");
                    break;
                }
                i1 = indices1[escolha1 - 1];

                printf("\nDigite a sigla do segundo estado (ex: RJ): ");
                lerUpper(sigla2, 2);
                total2 = listarCidadesNumeradas(cartas, MAX_CARTAS, sigla2, indices2);
                if (total2 == 0) {
                    printf("\n❌ Nenhuma cidade encontrada para o estado %s.\n", sigla2);
                    break;
                }
                printf("Escolha o número da cidade desejada (1 a %d): ", total2);
                scanf("%d", &escolha2);
                if (escolha2 < 1 || escolha2 > total2) {
                    printf("\n❌ Escolha inválida.\n");
                    break;
                }
                i2 = indices2[escolha2 - 1];

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

                if (atributo1 < 1 || atributo1 > 6 ||
                    atributo2 < 1 || atributo2 > 6 ||
                    atributo3 < 1 || atributo3 > 6 ||
                    atributo1 == atributo2 || atributo1 == atributo3 || atributo2 == atributo3) {
                    printf("\n❌ Atributos inválidos ou repetidos. Tente novamente.\n");
                    break;
                }

                int atributos[3] = {atributo1, atributo2, atributo3};
                int vencedor = determinarVencedorPorAtributos(cartas[i1], cartas[i2], atributos, 3);
                exibirResultado(vencedor, cartas[i1], cartas[i2], atributo1, atributo2, atributo3);
                break;
            }
            //Opção para sair do programa
            case 0:
                printf("\n👋 Encerrando o programa. Até mais!\n");
                break;
            //Opção inválida
            default:
                printf("\n❌ Opção inválida. Tente novamente.\n");
        }
        // Verifica se o usuário deseja continuar
        printf("\nDeseja continuar? (1 - Sim, 0 - Não): ");
    } while (opcao != 0);

    return 0;
}
