class Black {
	public static getNumberOfBlackPieces(): number {
		let total: number = 0;
		for (let array of Board.pieces)
			for (let piece of array) if (piece !== null) if (piece.value < 0) total++;
		return total;
	}

	public static getPromotion(piece: Piece, newY: number) {
		if (newY === 7 && piece.value === -1) {
			piece.value = 5;
		}
	}

	public static makeMove(): void {
		const blackPieces: number = Black.getNumberOfBlackPieces();
		outer: while (true) {
			const pieceToPick: number = Functions.randomInteger(0, blackPieces - 1);
			let index: number = 0;
			let piecePick: Piece = new Piece(0, 0, 0);
			fast: for (const array of Board.pieces) {
				for (const piece of array) {
					if (index === pieceToPick) {
						piecePick = piece;
						break fast;
					}
					index++;
				}
			}
			let xOffset: number;
			let yOffset: number;
			let counter: number = 0;
			let king: Piece = Piece.getKing(false, Board.pieces);
			while (true) {
				if (
					Check.squareBeingAttackedByWhitePiece(king.x, king.y, Board.pieces)
				) {
					for (const array of Board.pieces) {
						for (const piece of array) {
							if (piece.value < 0) {
								for (let i = 0; i < 8; i++) {
									for (let j = 0; j < 8; j++) {
										if (
											Piece.getValidMove(piece, i, j) &&
											Board.pieces[j][i].value >= 0
										) {
											const pieceCopy: Piece = Functions.deepCopy(piece);
											const newBoard: Piece[][] = Functions.deepCopy(
												Board.pieces
											);
											newBoard[j][i] = pieceCopy;
											newBoard[pieceCopy.y][pieceCopy.x] = new Piece(
												0,
												pieceCopy.x,
												pieceCopy.y
											);
											pieceCopy.y = j;
											pieceCopy.x = i;
											const newKing: Piece = Piece.getKing(false, newBoard);
											if (piece.value === -6) {
												newKing.y = j;
												newKing.x = i;
											}
											if (
												!Check.squareBeingAttackedByWhitePiece(
													newKing.x,
													newKing.y,
													newBoard
												)
											) {
												Board.pieces[j][i] = piece;
												Board.pieces[piece.y][piece.x] = new Piece(
													0,
													piece.x,
													piece.y
												);
												piece.x = i;
												piece.y = j;
												return;
											}
										}
									}
								}
							}
						}
					}
				}
				counter++;
				if (counter == 10) continue outer;
				xOffset = Functions.randomInteger(0, 8) - 4;
				yOffset = Functions.randomInteger(0, 8) - 4;
				if (
					piecePick.x + xOffset < 0 ||
					piecePick.x + xOffset > 7 ||
					piecePick.y + yOffset < 0 ||
					piecePick.y + yOffset > 7
				)
					continue;
				if (
					Board.pieces[piecePick.y + yOffset][piecePick.x + xOffset].value < 0
				)
					continue;
				if (
					Piece.getValidMove(
						piecePick,
						piecePick.x + xOffset,
						piecePick.y + yOffset
					)
				)
					break;
			}
			let newBoard: Piece[][] = Functions.deepCopy(Board.pieces);
			if (piecePick.value === -6) {
				king = Functions.deepCopy(Piece.getKing(false, newBoard));
				king.x += xOffset;
				king.y += yOffset;
				if (Check.squareBeingAttackedByWhitePiece(king.x, king.y, newBoard))
					continue;
			}
			Board.pieces[piecePick.y + yOffset][piecePick.x + xOffset] = piecePick;
			Board.pieces[piecePick.y][piecePick.x] = new Piece(
				0,
				piecePick.x,
				piecePick.y
			);
			piecePick.x += xOffset;
			piecePick.y += yOffset;
			return;
		}
	}
}
