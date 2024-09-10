class Piece {
	public value: number;
	public x: number;
	public y: number;
	public dx: number = 0;
	public dy: number = 0;
	public hasMoved: boolean = false;
	public selected: boolean = false;

	public static pieceIdentifiers: Map<string, number> = new Map([
		["x", 0],
		["p", -1],
		["n", -2],
		["b", -3],
		["r", -4],
		["q", -5],
		["k", -6],
		["P", 1],
		["N", 2],
		["B", 3],
		["R", 4],
		["Q", 5],
		["K", 6],
	]);

	public static pieceNumberIdentifiers: Map<number, string> = new Map([
		[0, "x"],
		[-1, "p"],
		[-2, "n"],
		[-3, "b"],
		[-4, "r"],
		[-5, "q"],
		[-6, "k"],
		[1, "P"],
		[2, "N"],
		[3, "B"],
		[4, "R"],
		[5, "Q"],
		[6, "K"],
	]);

	public constructor(value: number, x: number, y: number) {
		this.value = value;
		this.x = x;
		this.y = y;
	}

	public static getImageUrlFromFEN(fenUnit: number): string {
		let url: string = UserSettings.fileBeginning;
		switch (fenUnit) {
			case 1:
				url += "WhitePawn";
				break;
			case -1:
				url += "BlackPawn";
				break;
			case 4:
				url += "WhiteRook";
				break;
			case -4:
				url += "BlackRook";
				break;
			case 2:
				url += "WhiteKnight";
				break;
			case -2:
				url += "BlackKnight";
				break;
			case 3:
				url += "WhiteBishop";
				break;
			case -3:
				url += "BlackBishop";
				break;
			case 5:
				url += "WhiteQueen";
				break;
			case -5:
				url += "BlackQueen";
				break;
			case 6:
				url += "WhiteKing";
				break;
			case -6:
				url += "BlackKing";
				break;
		}
		return url + ".png";
	}

	public getPromotion(newY: number) {
		if (newY === 0 && this.value === 1) {
			let input: string | null = prompt(
				"Enter promotion value: (q)ueen, (r)ook, (k)night, (b)ishop (Default is Queen)"
			);
			if (input === null) this.value = 5;
			else {
				let trueInput: string = input.toLowerCase();
				if (trueInput === "r") this.value = 4;
				else if (trueInput === "b") this.value = 3;
				else if (trueInput === "k") this.value = 2;
				else this.value = 5;
			}
		}
	}

	public static getValidMove(
		piece: Piece,
		newX: number,
		newY: number
	): boolean {
		switch (piece.value) {
			case 0:
				return false;
			case -1:
				return Move.validBlackPawnMove(piece, newX, newY);
			case 1:
				return Move.validWhitePawnMove(piece, newX, newY);
			case 2:
			case -2:
				return Move.validKnightMove(piece, newX, newY);
			case 3:
			case -3:
				return Move.validBishopMove(piece, newX, newY);
			case 4:
			case -4:
				return Move.validRookMove(piece, newX, newY);
			case 5:
			case -5:
				return Move.validQueenMove(piece, newX, newY);
			case 6:
				return Move.validWhiteKingMove(piece, newX, newY);
			case -6:
				return Move.validBlackKingMove(piece, newX, newY);
		}
		throw new Error("Pieces value is undefined");
	}

	public static invertNumber(number: number): number {
		switch (number) {
			case 0:
				return 8;
			case 1:
				return 7;
			case 2:
				return 6;
			case 3:
				return 5;
			case 4:
				return 4;
			case 5:
				return 3;
			case 6:
				return 2;
			case 7:
				return 1;
		}
		return 0;
	}

	public move(e: MouseEvent): void {
		this.selected = false;

		let newX: number =
			Math.floor(Functions.getMousePos(e).x / DevSettings.boxDimensions) - 1;
		let newY: number =
			Math.floor(Functions.getMousePos(e).y / DevSettings.boxDimensions) - 1;
		this.dx = 0;
		this.dy = 0;

		if (newX < 0 || newX >= 8 || newY < 0 || newY >= 8) return;
		if (Board.pieces[newY][newX].value > 0) return;
		let check: boolean = Piece.getValidMove(this, newX, newY);
		if (check) {
			let historyComponent: string = "";
			let blackKing: Piece = Piece.getKing(false, Board.pieces);
			if (this.value === 6 && Board.pieces[newY][newX - 1].value === 4)
				historyComponent = "O-O";
			else if (Board.pieces[newY][newX].value === 0)
				historyComponent =
					Piece.pieceNumberIdentifiers.get(this.value) +
					"-" +
					String.fromCharCode(97 + newX) +
					Piece.invertNumber(newY);
			else
				historyComponent =
					Piece.pieceNumberIdentifiers.get(this.value)! +
					Piece.pieceNumberIdentifiers.get(Board.pieces[newY][newX].value) +
					"x" +
					String.fromCharCode(97 + newX) +
					Piece.invertNumber(newY);
			if (this.value === 1) World.drawCounter = 0;
			if (
				Check.squareBeingAttackedByBlackPiece(newX, newY, Board.pieces) &&
				this.value === 6
			)
				return;
			this.getPromotion(newY);
			Board.previousBoard = Functions.deepCopy(Board.pieces);
			this.hasMoved = true;
			Board.pieces[newY][newX] = this;
			Board.pieces[this.y][this.x] = new Piece(0, this.x, this.y);
			this.x = newX;
			this.y = newY;
			if (
				Check.squareBeingAttackedByWhitePiece(
					blackKing.x,
					blackKing.y,
					Board.pieces
				)
			)
				historyComponent += "+";
			if (Check.blackKingInCheckMate()) {
				alert("Black King is in checkmate. White has won the game!");
				return;
			}
			Black.makeMove();
			World.drawCounter += 2;
			if (World.drawCounter === 100) {
				alert("Game has ended in a draw");
				return;
			}
			if (Check.whiteKingInCheckMate()) {
				alert("White King is in checkmate. Black has won the game!");
				return;
			}
			World.history.addComponent(new HistoryComponent(historyComponent, ""));
		}
	}

	public static getKing(isWhite: boolean, board: Piece[][]): Piece {
		let kingColor: number = isWhite ? 6 : -6;
		for (let array of board)
			for (let piece of array) if (piece.value === kingColor) return piece;
		throw new Error("King not found");
	}
}
