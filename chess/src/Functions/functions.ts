class Functions {
	public static images: Map<string, HTMLImageElement> = new Map<
		string,
		HTMLImageElement
	>();

	public static drawRect(
		color: string,
		x: number,
		y: number,
		width: number,
		height: number
	) {
		World.context.fillStyle = color;
		World.context.fillRect(x, y, width, height);
	}

	public static drawStrokeRect(
		color: string,
		x: number,
		y: number,
		width: number,
		height: number
	) {
		World.context.strokeStyle = color;
		World.context.strokeRect(x, y, width, height);
	}

	public static drawLine(
		x1: number,
		y1: number,
		x2: number,
		y2: number,
		width: number = 0.5,
		context: CanvasRenderingContext2D
	): void {
		context.beginPath();
		context.lineWidth = width;
		context.moveTo(x1, y1);
		context.lineTo(x2, y2);
		context.stroke();
	}

	public static drawText(
		text: string,
		x: number,
		y: number,
		color: string = "black",
		font: string = "Arial",
		fontSize: number = 10,
		textBaseline: string = "left",
		textAlign: string = "left",
		context: CanvasRenderingContext2D
	) {
		context.fillStyle = color;
		context.font = `${fontSize}px ${font}`;
		context.textBaseline = <CanvasTextBaseline>textBaseline;
		context.textAlign = <CanvasTextAlign>textAlign;

		context.fillText(text, x, y);
	}

	public static drawImage(
		src: string,
		x: number,
		y: number,
		width: number = 50,
		height: number = 50
	) {
		const image: HTMLImageElement = Functions.images.get(src)!;
		World.context.drawImage(image, x, y, width, height);
	}

	public static getMousePos(evt: MouseEvent) {
		const rect = World.canvas.getBoundingClientRect();
		return {
			x:
				((evt.clientX - rect.left) / (rect.right - rect.left)) *
				World.canvas.width,
			y:
				((evt.clientY - rect.top) / (rect.bottom - rect.top)) *
				World.canvas.height,
		};
	}

	public static extractKeyValue(
		obj: Map<string, number>,
		value: number
	): string {
		return Object.keys(obj)[Object.values(obj).indexOf(value)];
	}

	public static deepCopy(object: any): any {
		return JSON.parse(JSON.stringify(object));
	}

	// Special thanks to Lior Elrom from https://stackoverflow.com/questions/4959975/generate-random-number-between-two-numbers-in-javascript
	public static randomInteger(min: number, max: number): number {
		return Math.floor(Math.random() * (max - min + 1)) + min;
	}

	public static async loadImages(): Promise<void> {
		const imageLinks: string[] = [
			"images/Basic/BlackBishop.png",
			"images/Basic/BlackKing.png",
			"images/Basic/BlackKnight.png",
			"images/Basic/BlackPawn.png",
			"images/Basic/BlackQueen.png",
			"images/Basic/BlackRook.png",
			"images/Basic/WhiteBishop.png",
			"images/Basic/WhiteKing.png",
			"images/Basic/WhiteKnight.png",
			"images/Basic/WhitePawn.png",
			"images/Basic/WhiteQueen.png",
			"images/Basic/WhiteRook.png",
		];

		let loadImage = async (link: string) => {
			const image: HTMLImageElement = new Image();
			image.src = link;

			return new Promise((resolve) => {
				image.onload = async () => {
					Functions.images.set(link, image);
					resolve(true);
				};
			});
		};

		for (let i = 0; i < imageLinks.length; i++) {
			await loadImage(imageLinks[i]);
		}
	}
}
