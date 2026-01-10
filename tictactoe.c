#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

char board[9];
char current_player = 'X';
int mode = 1;
int player_x_wins = 0;
int player_o_wins = 0;
int draws = 0;
char player_x_name[50] = "Player X";
char player_o_name[50] = "Player O";

void resetboard() {
    for (int i = 0; i < 9; i++) {
        board[i] = '1' + i;
    }
    current_player = 'X';
}

void asciiart() {
    printf("================================================================================\n");
    printf("████████╗██╗ ██████╗    ████████╗ █████╗  ██████╗    ████████╗ ██████╗ ███████╗\n");
    printf("╚══██╔══╝██║██╔════╝    ╚══██╔══╝██╔══██╗██╔════╝    ╚══██╔══╝██╔═══██╗██╔════╝\n");
    printf("   ██║   ██║██║            ██║   ███████║██║            ██║   ██║   ██║█████╗  \n");
    printf("   ██║   ██║██║            ██║   ██╔══██║██║            ██║   ██║   ██║██╔══╝  \n");
    printf("   ██║   ██║╚██████╗       ██║   ██║  ██║╚██████╗       ██║   ╚██████╔╝███████╗\n");
    printf("   ╚═╝   ╚═╝ ╚═════╝       ╚═╝   ╚═╝  ╚═╝ ╚═════╝       ╚═╝    ╚═════╝ ╚══════╝\n");
    printf("                              TIC TAC TOE GAME                                  \n");
    printf("================================================================================\n\n");
}

void displayboard() {
    printf("\n");
    printf("     │     │     \n");
    printf("  %c  │  %c  │  %c  \n", board[0], board[1], board[2]);
    printf("     │     │     \n");
    printf("─────┼─────┼─────\n");
    printf("     │     │     \n");
    printf("  %c  │  %c  │  %c  \n", board[3], board[4], board[5]);
    printf("     │     │     \n");
    printf("─────┼─────┼─────\n");
    printf("     │     │     \n");
    printf("  %c  │  %c  │  %c  \n", board[6], board[7], board[8]);
    printf("     │     │     \n");
    printf("\n");
}

void display_scoreboard() {
    printf("╔════════════════════════════════════════╗\n");
    printf("║            SCOREBOARD                  ║\n");
    printf("╠════════════════════════════════════════╣\n");
    printf("║ %-20s : %3d wins                       ║\n", player_x_name, player_x_wins);
    printf("║ %-20s : %3d wins                       ║\n", player_o_name, player_o_wins);
    printf("║ Draws : %3d                            ║\n", draws);
    printf("╚════════════════════════════════════════╝\n\n");
}

void switchplayer() {
    current_player = (current_player == 'X') ? 'O' : 'X';
}

int checkwin() {
    int win[8][3] = {
        {0,1,2},{3,4,5},{6,7,8},
        {0,3,6},{1,4,7},{2,5,8},
        {0,4,8},{2,4,6}
    };

    for (int i = 0; i < 8; i++) {
        if (board[win[i][0]] == current_player &&
            board[win[i][1]] == current_player &&
            board[win[i][2]] == current_player)
            return 1;
    }
    return 0;
}

int checkdraw() {
    for (int i = 0; i < 9; i++) {
        if (board[i] != 'X' && board[i] != 'O')
            return 0;
    }
    return 1;
}

void bot_easy_move() {
    int choice;
    while (1) {
        choice = rand() % 9;
        if (board[choice] != 'X' && board[choice] != 'O') {
            board[choice] = 'O';
            break;
        }
    }
}

int minimax(int depth, int is_maximizing) {
    // Check for terminal states
    char original_player = current_player;
    
    // Check if X wins
    current_player = 'X';
    if (checkwin()) {
        current_player = original_player;
        return -10 + depth;
    }
    
    // Check if O wins
    current_player = 'O';
    if (checkwin()) {
        current_player = original_player;
        return 10 - depth;
    }
    
    current_player = original_player;
    
    // Check for draw
    if (checkdraw()) return 0;
    
    if (is_maximizing) {
        int best_score = -1000;
        for (int i = 0; i < 9; i++) {
            if (board[i] != 'X' && board[i] != 'O') {
                char original = board[i];
                board[i] = 'O';
                int score = minimax(depth + 1, 0);
                board[i] = original;
                if (score > best_score) best_score = score;
            }
        }
        return best_score;
    } else {
        int best_score = 1000;
        for (int i = 0; i < 9; i++) {
            if (board[i] != 'X' && board[i] != 'O') {
                char original = board[i];
                board[i] = 'X';
                int score = minimax(depth + 1, 1);
                board[i] = original;
                if (score < best_score) best_score = score;
            }
        }
        return best_score;
    }
}

void bot_hard_move() {
    int best_move = -1;
    int best_score = -1000;
    
    for (int i = 0; i < 9; i++) {
        if (board[i] != 'X' && board[i] != 'O') {
            char original = board[i];
            board[i] = 'O';
            int score = minimax(0, 0);
            board[i] = original;
            
            if (score > best_score) {
                best_score = score;
                best_move = i;
            }
        }
    }
    
    if (best_move != -1) {
        board[best_move] = 'O';
    }
}

void undo_move(int *history, int *move_count) {
    if (*move_count > 0) {
        (*move_count)--;
        int pos = history[*move_count];
        board[pos] = '1' + pos;
        switchplayer();
    }
}

void show_hint() {
    printf("\n💡 Hint: ");
    
    // Check for winning move
    for (int i = 0; i < 9; i++) {
        if (board[i] != 'X' && board[i] != 'O') {
            char original = board[i];
            board[i] = current_player;
            if (checkwin()) {
                board[i] = original;
                printf("Langkah terbaik adalah posisi %d (Menang!)\n", i + 1);
                return;
            }
            board[i] = original;
        }
    }
    
    // Check for blocking move
    char opponent = (current_player == 'X') ? 'O' : 'X';
    for (int i = 0; i < 9; i++) {
        if (board[i] != 'X' && board[i] != 'O') {
            char original = board[i];
            board[i] = opponent;
            char temp = current_player;
            current_player = opponent;
            if (checkwin()) {
                current_player = temp;
                board[i] = original;
                printf("Blokir lawan di posisi %d!\n", i + 1);
                return;
            }
            current_player = temp;
            board[i] = original;
        }
    }
    
    // Suggest center or corner
    if (board[4] != 'X' && board[4] != 'O') {
        printf("Ambil tengah (posisi 5) untuk kontrol lebih baik!\n");
    } else {
        int corners[] = {0, 2, 6, 8};
        for (int i = 0; i < 4; i++) {
            if (board[corners[i]] != 'X' && board[corners[i]] != 'O') {
                printf("Ambil sudut di posisi %d!\n", corners[i] + 1);
                return;
            }
        }
        printf("Coba posisi yang masih tersedia!\n");
    }
}

int main() {
    int choice;
    char playagain;
    int move_history[9];
    int move_count = 0;
    char input[10];

    srand(time(NULL));

    system("clear");
    asciiart();

    printf("Masukkan nama Player X: ");
    fgets(player_x_name, 50, stdin);
    player_x_name[strcspn(player_x_name, "\n")] = 0;
    
    printf("Pilih Mode:\n");
    printf("1. Player vs Player\n");
    printf("2. Player vs Bot (Easy)\n");
    printf("3. Player vs Bot (Hard)\n");
    printf("Pilihan: ");
    scanf("%d", &mode);
    
    if (mode == 2 || mode == 3) {
        strcpy(player_o_name, (mode == 2) ? "Bot (Easy)" : "Bot (Hard)");
    } else {
        printf("Masukkan nama Player O: ");
        getchar();
        fgets(player_o_name, 50, stdin);
        player_o_name[strcspn(player_o_name, "\n")] = 0;
    }

    do {
        resetboard();
        move_count = 0;

        while (1) {
            system("clear");
            asciiart();
            display_scoreboard();
            displayboard();

            if ((mode == 2 || mode == 3) && current_player == 'O') {
                printf("🤖 Bot sedang berpikir...\n");
                getchar();
                if (mode == 2) {
                    bot_easy_move();
                } else {
                    bot_hard_move();
                }
                move_history[move_count++] = -1; 
            } else {
                printf("\n%s (%c), giliran Anda!\n", 
                       (current_player == 'X') ? player_x_name : player_o_name, 
                       current_player);
                printf("Pilih (1-9), 'h' untuk hint, 'u' untuk undo: ");
                scanf("%s", input);

                if (input[0] == 'h' || input[0] == 'H') {
                    show_hint();
                    printf("\nTekan Enter untuk lanjut kawan...");
                    getchar(); getchar();
                    continue;
                }
                
                if (input[0] == 'u' || input[0] == 'U') {
                    if (move_count > 0) {
                        undo_move(move_history, &move_count);
                        if (mode != 1 && move_count > 0) {
                            undo_move(move_history, &move_count);
                        }
                    } else {
                        printf("Tidak ada langkah untuk di-undo!\n");
                        getchar(); getchar();
                    }
                    continue;
                }

                choice = atoi(input);

                if (choice < 1 || choice > 9 ||
                    board[choice - 1] == 'X' || board[choice - 1] == 'O') {
                    printf("❌ Pilihan tidak valid!\n");
                    getchar(); getchar();
                    continue;
                }

                board[choice - 1] = current_player;
                move_history[move_count++] = choice - 1;
            }

            if (checkwin()) {
                system("clear");
                asciiart();
                displayboard();
                
                if (current_player == 'X') {
                    player_x_wins++;
                    printf("🎉 %s MENANG! 🎉\n", player_x_name);
                } else {
                    player_o_wins++;
                    printf("🎉 %s MENANG! 🎉\n", player_o_name);
                }
                break;
            }

            if (checkdraw()) {
                system("clear");
                asciiart();
                displayboard();
                draws++;
                printf("🤝 Permainan SERI! 🤝\n");
                break;
            }

            switchplayer();
        }

        printf("\n");
        display_scoreboard();
        printf("\nMain lagi? (y/n): ");
        scanf(" %c", &playagain);

    } while (playagain == 'y' || playagain == 'Y');

    printf("\n╔════════════════════════════════════════╗\n");
    printf("  ║      TERIMA KASIH SUDAH BERMAIN! 💙    ║\n");
    printf("  ╚════════════════════════════════════════╝\n");
    printf("\nFinal Score:\n");
    display_scoreboard();
    
    return 0;
}
