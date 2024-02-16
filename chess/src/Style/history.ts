class HistoryCanvas {
    public readonly canvas: HTMLCanvasElement = <HTMLCanvasElement> document.getElementById("historyCanvas");
    public readonly context: CanvasRenderingContext2D = this.canvas.getContext("2d")!;

    public components: HistoryComponent[] = [];

    public constructor() {
        this.canvas.width = 200;
        this.canvas.height = 0;
    }

    public addComponent(component: HistoryComponent): void {
        this.canvas.height += 20;
        this.components.push(component);
    }

    public print(): void {
        Functions.drawLine(20, 0, 20, this.canvas.height, undefined, this.context);
        Functions.drawLine(110, 0, 110, this.canvas.height, undefined, this.context);
        for (let i = 1; i <= this.components.length; i++) {
            Functions.drawText(i + ":", 2, ((i) * 20 - 5), "black", "Arial", 10, undefined, undefined, this.context);
            Functions.drawText(this.components[i - 1].move1, 22, ((i) * 20 - 5), "black", "Arial", 10, undefined, undefined, this.context);
            Functions.drawLine(0, (i * 20), this.canvas.width, (i * 20), undefined, this.context);
        }
    }
}