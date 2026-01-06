use std::io::{self, Write};
use rand::Rng; // Pastikan tambahkan `rand = "0.8"` di Cargo.toml

fn ascii_art() {
    println!("================================================================================");
    println!("████████╗██╗ ██████╗    ████████╗ █████╗  ██████╗    ████████╗ ██████╗ ███████╗");
    println!("╚══██╔══╝██║██╔════╝    ╚══██╔══╝██╔══██╗██╔════╝    ╚══██╔══╝██╔═══██╗██╔════╝");
    println!("   ██║   ██║██║            ██║   ███████║██║            ██║   ██║   ██║█████╗  ");
    println!("   ██║   ██║██║            ██║   ██╔══██║██║            ██║   ██║   ██║██╔══╝  ");
    println!("   ██║   ██║╚██████╗       ██║   ██║  ██║╚██████╗       ██║   ╚██████╔╝███████╗");
    println!("   ╚═╝   ╚═╝ ╚═════╝       ╚═╝   ╚═╝  ╚═╝ ╚═════╝       ╚═╝    ╚═════╝ ╚══════╝");
    println!("                                TIC TAC TOE GAME                                ");
    println!("===============================================================================\n");
}

fn display_board(board: &[char]) {
    println!("\n");
    println!(" {} | {} | {} ", board[0], board[1], board[2]);
    println!("---+---+---");
    println!(" {} | {} | {} ", board[3], board[4], board[5]);
    println!("---+---+---");
    println!(" {} | {} | {} ", board[6], board[7], board[8]);
    println!("\n");
}

fn check_win(board: &[char], player: char) -> bool {
    let win_patterns = [
        [0, 1, 2], [3, 4, 5], [6, 7, 8], // Baris
        [0, 3, 6], [1, 4, 7], [2, 5, 8], // Kolom
        [0, 4, 8], [2, 4, 6],             // Diagonal
    ];

    win_patterns.iter().any(|&p| {
        board[p[0]] == player && board[p[1]] == player && board[p[2]] == player
    })
}

fn check_draw(board: &[char]) -> bool {
    board.iter().all(|&c| c == 'X' || c == 'O')
}

fn clear_screen() {
    print!("{esc}[2J{esc}[1;1H", esc = 27 as char);
}

fn main() {
    let mut stdout = io::stdout();

    loop {
        let mut board = ['1', '2', '3', '4', '5', '6', '7', '8', '9'];
        let mut current_player = 'X';
        
        clear_screen();
        ascii_art();

        println!("Pilih Mode:");
        println!("1. Player vs Player");
        println!("2. Player vs Bot (Easy)");
        print!("Pilihan: ");
        stdout.flush().unwrap();

        let mut mode_input = String::new();
        io::stdin().read_line(&mut mode_input).unwrap();
        let mode: i32 = mode_input.trim().parse().unwrap_or(1);

        loop {
            clear_screen();
            ascii_art();
            display_board(&board);

            let choice: usize;

            if mode == 2 && current_player == 'O' {
                println!("Bot sedang berpikir...");
                let mut rng = rand::thread_rng();
                loop {
                    let random_idx = rng.gen_range(0..9);
                    if board[random_idx] != 'X' && board[random_idx] != 'O' {
                        choice = random_idx;
                        break;
                    }
                }
                std::thread::sleep(std::time::Duration::from_millis(800)); // Biar bot ga terlalu cepat
            } else {
                print!("Player {}, pilih angka (1-9): ", current_player);
                stdout.flush().unwrap();

                let mut input = String::new();
                io::stdin().read_line(&mut input).unwrap();
                
                match input.trim().parse::<usize>() {
                    Ok(n) if n >= 1 && n <= 9 && board[n-1] != 'X' && board[n-1] != 'O' => {
                        choice = n - 1;
                    }
                    _ => {
                        println!("Pilihan tidak valid! Tekan Enter...");
                        io::stdin().read_line(&mut String::new()).unwrap();
                        continue;
                    }
                }
            }

            board[choice] = current_player;

            if check_win(&board, current_player) {
                clear_screen();
                ascii_art();
                display_board(&board);
                println!("Player {} MENANG! 🎉", current_player);
                break;
            }

            if check_draw(&board) {
                clear_screen();
                ascii_art();
                display_board(&board);
                println!("Permainan SERI 🤝");
                break;
            }

            current_player = if current_player == 'X' { 'O' } else { 'X' };
        }

        print!("\nMain lagi? (y/n): ");
        stdout.flush().unwrap();
        let mut play_again = String::new();
        io::stdin().read_line(&mut play_again).unwrap();
        if play_again.trim().to_lowercase() != "y" {
            break;
        }
    }

    println!("\nTerima kasih sudah bermain 💙");
}