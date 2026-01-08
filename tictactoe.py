
import os 
import random 
import time

board = []
current_player = 'X'
mode = 1  # 1 = PVP, 2 = vs Bot

def reset_board():
    global board, current_player
    board = [str(i) for i in range(1, 10)]
    current_player = 'X'

def ascii_art():
    print("=" * 80)
    print("████████╗██╗ ██████╗    ████████╗ █████╗  ██████╗    ████████╗ ██████╗ ███████╗")
    print("╚══██╔══╝██║██╔════╝    ╚══██╔══╝██╔══██╗██╔════╝    ╚══██╔══╝██╔═══██╗██╔════╝")
    print("   ██║   ██║██║            ██║   ███████║██║            ██║   ██║   ██║█████╗  ")
    print("   ██║   ██║██║            ██║   ██╔══██║██║            ██║   ██║   ██║██╔══╝  ")
    print("   ██║   ██║╚██████╗       ██║   ██║  ██║╚██████╗       ██║   ╚██████╔╝███████╗")
    print("   ╚═╝   ╚═╝ ╚═════╝       ╚═╝   ╚═╝  ╚═╝ ╚═════╝       ╚═╝    ╚═════╝ ╚══════╝")
    print("                              TIC TAC TOE GAME         ")
    print("=" * 80)
    print()

def display_board():
    print()
    print(f" {board[0]} | {board[1]} | {board[2]} ")
    print("---+---+---")
    print(f" {board[3]} | {board[4]} | {board[5]} ")
    print("---+---+---")
    print(f" {board[6]} | {board[7]} | {board[8]} ")
    print()

def switch_player():
    global current_player
    current_player = 'O' if current_player == 'X' else 'X'

def check_win():
    win_patterns = [
        [0, 1, 2], [3, 4, 5], [6, 7, 8],  # horizontal
        [0, 3, 6], [1, 4, 7], [2, 5, 8],  # vertical
        [0, 4, 8], [2, 4, 6]              # diagonal
    ]
    
    for pattern in win_patterns:
        if (board[pattern[0]] == current_player and
            board[pattern[1]] == current_player and
            board[pattern[2]] == current_player):
            return True
    return False

def check_draw():
    for cell in board:
        if cell != 'X' and cell != 'O':
            return False
    return True

def bot_easy_move():
    while True:
        choice = random.randint(0, 8)
        if board[choice] != 'X' and board[choice] != 'O':
            board[choice] = 'O'
            break

def clear_screen():
    os.system('clear' if os.name != 'nt' else 'cls')

def main():
    global mode
    
    random.seed(time.time())
    reset_board()
    
    clear_screen()
    ascii_art()
    
    print("Pilih Mode:")
    print("1. Player vs Player")
    print("2. Player vs Bot (Easy)")
    
    while True:
        try:
            mode = int(input("Pilihan: "))
            if mode in [1, 2]:
                break
            print("Pilihan harus 1 atau 2!")
        except ValueError:
            print("Masukkan angka yang valid!")
    
    play_again = 'y'
    
    while play_again.lower() == 'y':
        reset_board()
        
        while True:
            clear_screen()
            ascii_art()
            display_board()
            
            if mode == 2 and current_player == 'O':
                print("Bot sedang berpikir...")
                time.sleep(0.5)
                bot_easy_move()
            else:
                while True:
                    try:
                        choice = int(input(f"Player {current_player}, pilih angka (1-9): "))
                        
                        if choice < 1 or choice > 9:
                            print("Pilihan harus antara 1-9!")
                            input("Tekan Enter untuk melanjutkan...")
                            clear_screen()
                            ascii_art()
                            display_board()
                            continue
                        
                        if board[choice - 1] == 'X' or board[choice - 1] == 'O':
                            print("Pilihan tidak valid! Kotak sudah terisi!")
                            input("Tekan Enter untuk melanjutkan...")
                            clear_screen()
                            ascii_art()
                            display_board()
                            continue
                        
                        board[choice - 1] = current_player
                        break
                    except ValueError:
                        print("Masukkan angka yang valid!")
                        input("Tekan Enter untuk melanjutkan...")
                        clear_screen()
                        ascii_art()
                        display_board()
            
            if check_win():
                clear_screen()
                ascii_art()
                display_board()
                print(f"Player {current_player} MENANG! 🎉")
                break
            
            if check_draw():
                clear_screen()
                ascii_art()
                display_board()
                print("Permainan SERI 🤝")
                break
            
            switch_player()
        
        play_again = input("\nMain lagi? (y/n): ")
    
    print("\nTerima kasih sudah bermain 💙")

if __name__ == "__main__":
    main()
