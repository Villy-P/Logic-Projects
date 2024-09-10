class Board {
	public static pieces: Piece[][] = [];
	public static previousBoard: Piece[][];

	public constructor() {
		FenHandling.fillBoardFromFEN(FenHandling.startWhiteFenString);
	}

	public static createEmptyBoard(): void {
		for (let i = 0; i < 8; i++) {
			Board.pieces.push([]);
			for (let j = 0; j < 8; j++) Board.pieces[i].push(new Piece(0, i, j));
		}
	}

	public drawNumbers(i: number, sideNumber: number): void {
		Functions.drawText(
			sideNumber.toString(),
			DevSettings.numberLetterDimensions / 2,
			DevSettings.numberLetterDimensions * (i + 2) -
				DevSettings.numberLetterDimensions / 2,
			"black",
			"Arial",
			20,
			"middle",
			"center",
			World.context
		);
	}

	public drawLetters(j: number) {
		Functions.drawText(
			String.fromCharCode(j + "A".charCodeAt(0)).toLowerCase(),
			DevSettings.numberLetterDimensions * (j + 2) -
				DevSettings.numberLetterDimensions / 2,
			DevSettings.numberLetterDimensions / 2,
			"black",
			"Arial",
			20,
			"middle",
			"center",
			World.context
		);
	}

	public drawBoard(): void {
		let sideNumber: number = 8;
		for (let file = 0; file < 8; file++) {
			this.drawNumbers(file, sideNumber);
			for (let rank = 0; rank < 8; rank++) {
				this.drawLetters(rank);
				const isLightSquare: boolean = (file + rank) % 2 != 0;
				const squareColor: string = isLightSquare
					? UserSettings.whiteSquareColor
					: UserSettings.blackSquareColor;
				const xOffset: number =
					DevSettings.numberLetterDimensions + file * DevSettings.boxDimensions;
				const yOffset: number =
					DevSettings.numberLetterDimensions + rank * DevSettings.boxDimensions;
				Functions.drawRect(
					squareColor,
					xOffset,
					yOffset,
					DevSettings.boxDimensions,
					DevSettings.boxDimensions
				);
			}
			sideNumber--;
		}
		const xyPosition = DevSettings.numberLetterDimensions;
		const widthHeight = DevSettings.boxDimensions * 8;
		Functions.drawStrokeRect(
			"black",
			xyPosition,
			xyPosition,
			widthHeight,
			widthHeight
		);
	}

	public drawPieces(): void {
		for (let file = 0; file < 8; file++) {
			for (let rank = 0; rank < 8; rank++) {
				const piece: Piece = Board.pieces[rank][file];
				if (piece.value !== 0)
					Functions.drawImage(
						Piece.getImageUrlFromFEN(piece.value),
						piece.x * (DevSettings.numberLetterDimensions + 1) +
							DevSettings.numberLetterDimensions +
							piece.dx,
						piece.y * (DevSettings.numberLetterDimensions + 1) +
							DevSettings.numberLetterDimensions +
							piece.dy,
						DevSettings.pieceDimensions,
						DevSettings.pieceDimensions
					);
			}
		}
	}
}
