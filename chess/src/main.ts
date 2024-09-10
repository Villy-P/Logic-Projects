class World {
	public static readonly canvas: HTMLCanvasElement = <HTMLCanvasElement>(
		document.getElementById("mainCanvas")
	);
	public static readonly context: CanvasRenderingContext2D =
		World.canvas.getContext("2d")!;
	public static readonly boundingClient: DOMRect =
		World.canvas.getBoundingClientRect();
	public static readonly offsetX: number = World.boundingClient.left;
	public static readonly offsetY: number = World.boundingClient.top;
	public static readonly colorPickers: ColorInput = new ColorInput();
	public static readonly history: HistoryCanvas = new HistoryCanvas();
	public static drawCounter: number = 0;
	public static dragging: boolean = false;
	public static isWhiteTurn: boolean = true;

	public readonly board: Board = new Board();

	public constructor() {
		World.canvas.width =
			DevSettings.boxDimensions * 8 + DevSettings.numberLetterDimensions;
		World.canvas.height =
			DevSettings.boxDimensions * 8 + DevSettings.numberLetterDimensions;
		World.canvas.onmousedown = KeyEvents.mouseDown;
		World.canvas.onmouseup = KeyEvents.mouseUp;
		World.canvas.onmousemove = KeyEvents.mouseMove;
	}
}
