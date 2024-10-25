#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "projeto2.h"


void jogar() {
    
    FILE *arquivo_perguntas;
    Pergunta perguntas[MAX_PERGUNTAS];
    int i, qtd_perguntas = 0;
    char nome_jogador[MAX_NOME];
    int pontuacao = 0;
    int pergunta_atual = 0;
    Pergunta perguntas_selecionadas[MAX_PERGUNTAS];
    Pergunta perguntas_arrays[5][20];

    // Abrir arquivo de perguntas
    arquivo_perguntas = fopen("perguntas_jogo.bin", "rb");
    if (arquivo_perguntas == NULL) {
        printf("Erro ao abrir o arquivo perguntas_jogo.bin.\n");
        return;
    }

    // Ler perguntas do arquivo
    while (fread(&perguntas[qtd_perguntas], sizeof(Pergunta), 1, arquivo_perguntas) == 1) {
        qtd_perguntas++;
    }

    fclose(arquivo_perguntas);

    // Dividir perguntas em 5 arrays de 20 perguntas cada
    for (i = 0; i < qtd_perguntas; i++) {
        int indice_array = i / 20;
        int indice_pergunta = i % 20;
        perguntas_arrays[indice_array][indice_pergunta] = perguntas[i];
    }

    // Selecionar um dos arrays para exibir ao usuário
    srand(time(NULL));
    int indice_array_selecionado = rand() % 5;
    for (i = 0; i < 20; i++) {
        perguntas_selecionadas[i] = perguntas_arrays[indice_array_selecionado][i];
    }

    // Solicitar nome do jogador
    printf("Digite seu nome (sem espacos): ");
    scanf("%s", nome_jogador);

    // Jogar
    while (pergunta_atual < 20) {
        printf("\nPergunta %d:\n", pergunta_atual + 1);
        printf("%s\n", perguntas_selecionadas[pergunta_atual].pergunta);
        for (int j = 0; j < MAX_RESPOSTAS; j++) {
            printf("%d. %s\n", j + 1, perguntas_selecionadas[pergunta_atual].alternativas[j]);
        }
        printf("Digite a alternativa correta: ");
        int resposta;
        scanf("%d", &resposta);

        if (resposta == perguntas_selecionadas[pergunta_atual].resposta) {
            printf("Resposta correta!\n");
            pontuacao++;
        } else {
            printf("Resposta incorreta. A resposta correta e %d. %s\n", perguntas_selecionadas[pergunta_atual].resposta, perguntas_selecionadas[pergunta_atual].alternativas[perguntas_selecionadas[pergunta_atual].resposta - 1]);
            break;
        }

        pergunta_atual++;
    }

    // Salvar pontuação do jogador
    FILE *arquivo_placar;
    arquivo_placar = fopen("placar_jogadores.txt", "a");
    if (arquivo_placar == NULL) {
        printf("Erro ao abrir o arquivo placar_jogadores.txt.\n");
        return;
    }

    fprintf(arquivo_placar, "%s %d\n", nome_jogador, pontuacao);
    fclose(arquivo_placar);

    printf("Pontuacao final: %d\n", pontuacao);
}


void exibir_tutorial() {
    FILE *arquivo_tutorial;
    char linha[1024];

    arquivo_tutorial = fopen("tutorial.txt", "r");
    if (arquivo_tutorial == NULL) {
        printf("Erro ao abrir o arquivo tutorial.txt.\n");
        return;
    }

    while (fgets(linha, sizeof(linha), arquivo_tutorial)) {
        printf("%s", linha);
    }

    fclose(arquivo_tutorial);
}
