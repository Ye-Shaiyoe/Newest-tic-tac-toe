        class TicTacToeBot {
            constructor(difficulty = 'medium') {
                this.difficulty = difficulty;
                this.winPatterns = [
                    [0, 1, 2], [3, 4, 5], [6, 7, 8],
                    [0, 3, 6], [1, 4, 7], [2, 5, 8],
                    [0, 4, 8], [2, 4, 6]
                ];
            }

            getMove(board, player) {
                if (this.difficulty === 'easy') {
                    return this.getRandomMove(board);
                } else if (this.difficulty === 'medium') {
                    return Math.random() < 0.5 
                        ? this.getSmartMove(board, player)
                        : this.getRandomMove(board);
                } else {
                    return this.getSmartMove(board, player);
                }
            }

            getRandomMove(board) {
                const available = board
                    .map((cell, idx) => cell === '' ? idx : null)
                    .filter(idx => idx !== null);
                return available[Math.floor(Math.random() * available.length)];
            }

            getSmartMove(board, player) {
                const opponent = player === 'X' ? 'O' : 'X';
                
                let move = this.findWinningMove(board, player);
                if (move !== -1) return move;
                
                move = this.findWinningMove(board, opponent);
                if (move !== -1) return move;
                
                if (board[4] === '') return 4;
                
                const corners = [0, 2, 6, 8];
                const availableCorners = corners.filter(i => board[i] === '');
                if (availableCorners.length > 0) {
                    return availableCorners[Math.floor(Math.random() * availableCorners.length)];
                }
                
                return this.getRandomMove(board);
            }

            findWinningMove(board, player) {
                for (let pattern of this.winPatterns) {
                    const [a, b, c] = pattern;
                    const cells = [board[a], board[b], board[c]];
                    
                    if (cells.filter(cell => cell === player).length === 2 &&
                        cells.filter(cell => cell === '').length === 1) {
                        if (board[a] === '') return a;
                        if (board[b] === '') return b;
                        if (board[c] === '') return c;
                    }
                }
                return -1;
            }
        }
