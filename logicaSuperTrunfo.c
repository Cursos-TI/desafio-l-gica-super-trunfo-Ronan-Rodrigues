#include <stdio.h>
#include <string.h>

// Estrutura para armazenar os dados de uma cidade
typedef struct {
    char codigo[10];
    char nome[50];
    int populacao;
    float area;
    float pib;
} Cidade;

int main() {
    Cidade cidade1, cidade2;

    // Cadastro da primeira cidade
    printf("Cadastro da Cidade 1:\n");
    printf("Digite o código: ");
    scanf("%s", cidade1.codigo);
    printf("Digite o nome: ");
    scanf(" %[^\n]", cidade1.nome);
    printf("Digite a população: ");
    scanf("%d", &cidade1.populacao);
    printf("Digite a área (km²): ");
    scanf("%f", &cidade1.area);
    printf("Digite o PIB (em bilhões): ");
    scanf("%f", &cidade1.pib);

    // Cadastro da segunda cidade
    printf("\nCadastro da Cidade 2:\n");
    printf("Digite o código: ");
    scanf("%s", cidade2.codigo);
    printf("Digite o nome: ");
    scanf(" %[^\n]", cidade2.nome);
    printf("Digite a população: ");
    scanf("%d", &cidade2.populacao);
    printf("Digite a área (km²): ");
    scanf("%f", &cidade2.area);
    printf("Digite o PIB (em bilhões): ");
    scanf("%f", &cidade2.pib);

    // Comparação de atributos
    printf("\n=== Comparação de Cartas ===\n");

    // População
    if (cidade1.populacao > cidade2.populacao)
        printf("✅ %s tem maior população.\n", cidade1.nome);
    else if (cidade2.populacao > cidade1.populacao)
        printf("✅ %s tem maior população.\n", cidade2.nome);
    else
        printf("🤝 Ambas têm a mesma população.\n");

    // Área
    if (cidade1.area > cidade2.area)
        printf("✅ %s tem maior área.\n", cidade1.nome);
    else if (cidade2.area > cidade1.area)
        printf("✅ %s tem maior área.\n", cidade2.nome);
    else
        printf("🤝 Ambas têm a mesma área.\n");

    // PIB
    if (cidade1.pib > cidade2.pib)
        printf("✅ %s tem maior PIB.\n", cidade1.nome);
    else if (cidade2.pib > cidade1.pib)
        printf("✅ %s tem maior PIB.\n", cidade2.nome);
    else
        printf("🤝 Ambas têm o mesmo PIB.\n");

    // Resultado final (pontuação simples)
    int pontos1 = 0, pontos2 = 0;
    if (cidade1.populacao > cidade2.populacao) pontos1++;
    else if (cidade2.populacao > cidade1.populacao) pontos2++;

    if (cidade1.area > cidade2.area) pontos1++;
    else if (cidade2.area > cidade1.area) pontos2++;

    if (cidade1.pib > cidade2.pib) pontos1++;
    else if (cidade2.pib > cidade1.pib) pontos2++;

    printf("\n🏆 Resultado Final:\n");
    if (pontos1 > pontos2)
        printf("A cidade vencedora é: %s\n", cidade1.nome);
    else if (pontos2 > pontos1)
        printf("A cidade vencedora é: %s\n", cidade2.nome);
    else
        printf("Empate entre as cidades!\n");

    return 0;
}

