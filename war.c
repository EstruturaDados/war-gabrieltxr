#include "war.h"

// Função callback para fortificar territórios
void fortificar_territorio(Territorio* t) {
    t->exercitos++;
}

// Função de menu principal
void exibir_menu() {
    printf("\n╔════════════════════════════════════════╗\n");
    printf("║         WAR - NOVA EDIÇÃO              ║\n");
    printf("╠════════════════════════════════════════╣\n");
    printf("║ 1. Iniciar Novo Jogo                   ║\n");
    printf("║ 2. Ver Mapa                            ║\n");
    printf("║ 3. Ver Estatísticas                    ║\n");
    printf("║ 4. Simular Ataque                      ║\n");
    printf("║ 5. Verificar Vitória                   ║\n");
    printf("║ 6. Demonstração de Recursos Avançados ║\n");
    printf("║ 0. Sair                                ║\n");
    printf("╚════════════════════════════════════════╝\n");
    printf("Escolha uma opção: ");
}

void demonstrar_recursos_avancados(Jogo* jogo) {
    printf("\n╔═══════════════════════════════════════════════════════════╗\n");
    printf("║  DEMONSTRAÇÃO DE RECURSOS AVANÇADOS                       ║\n");
    printf("╚═══════════════════════════════════════════════════════════╝\n");
    
    // 1. Uso de ponteiros e alocação dinâmica
    printf("\n[1] Demonstração de Alocação Dinâmica:\n");
    printf("    - Jogo alocado dinamicamente com malloc\n");
    printf("    - Endereço da estrutura: %p\n", (void*)jogo);
    printf("    - Tamanho da estrutura: %lu bytes\n", sizeof(Jogo));
    
    // 2. Ponteiros para estruturas
    printf("\n[2] Demonstração de Ponteiros para Estruturas:\n");
    Territorio* primeiro_territorio = &jogo->territorios[0];
    printf("    - Primeiro território: %s\n", primeiro_territorio->nome);
    printf("    - Endereço: %p\n", (void*)primeiro_territorio);
    printf("    - Acessando via ponteiro: jogador_id = %d\n", primeiro_territorio->jogador_id);
    
    // 3. Funções callback
    printf("\n[3] Demonstração de Funções Callback:\n");
    printf("    - Fortificando todos os territórios do Jogador 0...\n");
    printf("    - Antes da fortificação:\n");
    for (int i = 0; i < 4 && i < jogo->num_territorios; i++) {
        if (jogo->territorios[i].jogador_id == 0) {
            printf("      %s: %d exércitos\n", 
                   jogo->territorios[i].nome, 
                   jogo->territorios[i].exercitos);
        }
    }
    
    aplicar_acao_territorios(jogo, 0, fortificar_territorio);
    
    printf("    - Depois da fortificação:\n");
    for (int i = 0; i < 4 && i < jogo->num_territorios; i++) {
        if (jogo->territorios[i].jogador_id == 0) {
            printf("      %s: %d exércitos\n", 
                   jogo->territorios[i].nome, 
                   jogo->territorios[i].exercitos);
        }
    }
    
    // 4. Ponteiros para funções
    printf("\n[4] Demonstração de Ponteiros para Funções:\n");
    printf("    - Ordenando territórios por número de exércitos...\n");
    FuncaoComparacao func_comparar = comparar_exercitos;
    printf("    - Endereço da função de comparação: %p\n", (void*)func_comparar);
    
    // 5. Passagem por referência vs valor
    printf("\n[5] Demonstração de Passagem por Referência:\n");
    int exercitos_antes = jogo->territorios[0].exercitos;
    adicionar_exercitos(jogo, 0, 5);
    printf("    - Território %s:\n", jogo->territorios[0].nome);
    printf("      Antes: %d exércitos\n", exercitos_antes);
    printf("      Depois: %d exércitos (modificado via ponteiro)\n", 
           jogo->territorios[0].exercitos);
    
    // 6. Uso de malloc/calloc/free
    printf("\n[6] Demonstração de Gerenciamento de Memória:\n");
    int* array_teste = (int*)malloc(10 * sizeof(int));
    printf("    - malloc: Alocados 10 inteiros em %p\n", (void*)array_teste);
    
    int* array_teste2 = (int*)calloc(10, sizeof(int));
    printf("    - calloc: Alocados 10 inteiros zerados em %p\n", (void*)array_teste2);
    printf("    - Primeiro elemento (deve ser 0): %d\n", array_teste2[0]);
    
    free(array_teste);
    free(array_teste2);
    printf("    - Memória liberada com free()\n");
    
    // 7. Estruturas aninhadas
    printf("\n[7] Demonstração de Estruturas Aninhadas:\n");
    printf("    - Jogo contém arrays de estruturas:\n");
    printf("      * %d Territórios\n", jogo->num_territorios);
    printf("      * %d Continentes\n", jogo->num_continentes);
    printf("      * %d Jogadores\n", jogo->num_jogadores);
    printf("      * %d Missões\n", jogo->num_missoes);
    
    // 8. Modularização e encapsulamento
    printf("\n[8] Demonstração de Modularização:\n");
    printf("    - Código organizado em módulos (war.h, war.c, main.c)\n");
    printf("    - Funções especializadas por responsabilidade:\n");
    printf("      * Inicialização: criar_jogo(), inicializar_mapa()\n");
    printf("      * Gameplay: atacar_territorio(), mover_exercitos()\n");
    printf("      * Verificações: verificar_vitoria(), verificar_missao()\n");
    printf("      * Utilidades: buscar_territorio(), imprimir_mapa()\n");
    
    printf("\n[Pressione ENTER para continuar]");
    getchar();
    getchar();
}

void simular_ataque_completo(Jogo* jogo) {
    printf("\n╔═══════════════════════════════════════════╗\n");
    printf("║      SIMULAÇÃO DE ATAQUE COMPLETO         ║\n");
    printf("╚═══════════════════════════════════════════╝\n");
    
    // Encontrar dois territórios vizinhos de jogadores diferentes
    int origem_id = -1, destino_id = -1;
    
    for (int i = 0; i < jogo->num_territorios && origem_id == -1; i++) {
        if (jogo->territorios[i].exercitos > 1) {
            for (int j = 0; j < jogo->territorios[i].num_vizinhos; j++) {
                int vizinho_id = jogo->territorios[i].vizinhos[j];
                Territorio* vizinho = buscar_territorio(jogo, vizinho_id);
                if (vizinho && vizinho->jogador_id != jogo->territorios[i].jogador_id) {
                    origem_id = i;
                    destino_id = vizinho_id;
                    break;
                }
            }
        }
    }
    
    if (origem_id == -1) {
        printf("Nenhum ataque possível no momento.\n");
        return;
    }
    
    Territorio* origem = &jogo->territorios[origem_id];
    Territorio* destino = buscar_territorio(jogo, destino_id);
    
    printf("\n┌─────────────────────────────────────┐\n");
    printf("│ CONFIGURAÇÃO DO ATAQUE              │\n");
    printf("├─────────────────────────────────────┤\n");
    printf("│ Atacante: %-25s │\n", origem->nome);
    printf("│   Jogador: %-24d │\n", origem->jogador_id);
    printf("│   Exércitos: %-22d │\n", origem->exercitos);
    printf("├─────────────────────────────────────┤\n");
    printf("│ Defensor: %-25s │\n", destino->nome);
    printf("│   Jogador: %-24d │\n", destino->jogador_id);
    printf("│   Exércitos: %-22d │\n", destino->exercitos);
    printf("└─────────────────────────────────────┘\n");
    
    int exercitos_antes_ataque = origem->exercitos;
    int exercitos_antes_defesa = destino->exercitos;
    
    printf("\n🎲 Iniciando ataque...\n");
    int resultado = atacar_territorio(jogo, origem_id, destino_id, 3);
    
    printf("\n┌─────────────────────────────────────┐\n");
    printf("│ RESULTADO DO COMBATE                │\n");
    printf("├─────────────────────────────────────┤\n");
    
    if (resultado == 1) {
        printf("│ ✓ TERRITÓRIO CONQUISTADO!           │\n");
        printf("├─────────────────────────────────────┤\n");
        printf("│ %s agora pertence        │\n", destino->nome);
        printf("│ ao Jogador %d                        │\n", origem->jogador_id);
    } else {
        printf("│ ✗ ATAQUE REPELIDO                   │\n");
        printf("├─────────────────────────────────────┤\n");
        printf("│ Perdas do Atacante: %-15d │\n", 
               exercitos_antes_ataque - origem->exercitos);
        printf("│ Perdas do Defensor: %-15d │\n", 
               exercitos_antes_defesa - destino->exercitos);
    }
    
    printf("└─────────────────────────────────────┘\n");
    
    printf("\n[Pressione ENTER para continuar]");
    getchar();
    getchar();
}

int main() {
    Jogo* jogo = NULL;
    int opcao;
    int jogo_iniciado = 0;
    
    printf("\n");
    printf("╔════════════════════════════════════════════════════════════╗\n");
    printf("║                                                            ║\n");
    printf("║          🎮  WAR - NOVA EDIÇÃO - TECHNOVA  🎮             ║\n");
    printf("║                                                            ║\n");
    printf("║      Sistema de Gerenciamento de Territórios              ║\n");
    printf("║      Desenvolvido com Estruturas de Dados em C            ║\n");
    printf("║                                                            ║\n");
    printf("╚════════════════════════════════════════════════════════════╝\n");
    
    do {
        exibir_menu();
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 1: {
                if (jogo) {
                    destruir_jogo(jogo);
                }
                
                printf("\n🎲 Inicializando novo jogo...\n");
                jogo = criar_jogo();
                
                if (!jogo) {
                    printf("❌ Erro ao criar o jogo!\n");
                    break;
                }
                
                printf("📍 Inicializando mapa...\n");
                inicializar_mapa(jogo);
                
                printf("🎯 Inicializando missões...\n");
                inicializar_missoes(jogo);
                
                printf("👥 Quantos jogadores? (2-6): ");
                int num_jogadores;
                scanf("%d", &num_jogadores);
                
                if (num_jogadores < 2) num_jogadores = 2;
                if (num_jogadores > 6) num_jogadores = 6;
                
                for (int i = 0; i < num_jogadores; i++) {
                    char nome[MAX_NOME];
                    printf("Nome do Jogador %d: ", i + 1);
                    scanf("%s", nome);
                    adicionar_jogador(jogo, nome, i);
                }
                
                printf("🗺️  Distribuindo territórios...\n");
                distribuir_territorios(jogo);
                
                printf("⚔️  Distribuindo exércitos...\n");
                distribuir_exercitos_iniciais(jogo);
                
                printf("📜 Atribuindo missões...\n");
                atribuir_missoes(jogo);
                
                jogo_iniciado = 1;
                printf("\n✅ Jogo inicializado com sucesso!\n");
                break;
            }
            
            case 2:
                if (!jogo_iniciado) {
                    printf("\n❌ Inicie um jogo primeiro!\n");
                } else {
                    imprimir_mapa(jogo);
                }
                break;
            
            case 3:
                if (!jogo_iniciado) {
                    printf("\n❌ Inicie um jogo primeiro!\n");
                } else {
                    imprimir_estatisticas(jogo);
                }
                break;
            
            case 4:
                if (!jogo_iniciado) {
                    printf("\n❌ Inicie um jogo primeiro!\n");
                } else {
                    simular_ataque_completo(jogo);
                }
                break;
            
            case 5:
                if (!jogo_iniciado) {
                    printf("\n❌ Inicie um jogo primeiro!\n");
                } else {
                    printf("\n🏆 Verificando condições de vitória...\n");
                    int vencedor = -1;
                    for (int i = 0; i < jogo->num_jogadores; i++) {
                        if (verificar_vitoria(jogo, i)) {
                            vencedor = i;
                            break;
                        }
                    }
                    
                    if (vencedor >= 0) {
                        printf("\n🎉 VITÓRIA! %s venceu o jogo!\n", 
                               jogo->jogadores[vencedor].nome);
                    } else {
                        printf("\n⏳ Nenhum jogador venceu ainda.\n");
                    }
                }
                break;
            
            case 6:
                if (!jogo_iniciado) {
                    printf("\n❌ Inicie um jogo primeiro!\n");
                } else {
                    demonstrar_recursos_avancados(jogo);
                }
                break;
            
            case 0:
                printf("\n👋 Encerrando War - Nova Edição...\n");
                if (jogo) {
                    destruir_jogo(jogo);
                }
                printf("Até a próxima batalha! 🎮\n\n");
                break;
            
            default:
                printf("\n❌ Opção inválida!\n");
        }
        
    } while (opcao != 0);
    
    return 0;
}
