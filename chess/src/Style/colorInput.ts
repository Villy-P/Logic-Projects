class ColorInput {
	public static colorWell1: any = document.getElementById("colorWell1")!;
	public static colorWell2: any = document.getElementById("colorWell2")!;
	public static colorWell3: any = document.getElementById("colorWell3")!;
	public static colorWell4: any = document.getElementById("colorWell4")!;
	public static colorWell5: any = document.getElementById("colorWell5")!;
	public static colorWell6: any = document.getElementById("colorWell6")!;

	public constructor() {
		ColorInput.colorWell1.addEventListener(
			"change",
			this.watchColorPickerOnePicker
		);
		ColorInput.colorWell2.addEventListener(
			"change",
			this.watchColorPickerTwoPicker
		);
		ColorInput.colorWell3.addEventListener(
			"change",
			this.watchColorPickerThreePicker
		);
		ColorInput.colorWell4.addEventListener(
			"change",
			this.watchColorPickerFourPicker
		);
		ColorInput.colorWell5.addEventListener(
			"change",
			this.watchColorPickerFivePicker
		);
		ColorInput.colorWell6.addEventListener(
			"change",
			this.watchColorPickerSixPicker
		);
	}

	public watchColorPickerOnePicker(event: any) {
		ColorInput.colorWell1.style.color = event.target.value;
		UserSettings.whiteSquareColor = event.target.value;
	}

	public watchColorPickerTwoPicker(event: any) {
		ColorInput.colorWell1.style.color = event.target.value;
		UserSettings.blackSquareColor = event.target.value;
	}

	public watchColorPickerThreePicker(event: any) {
		ColorInput.colorWell3.style.color = event.target.value;
		World.canvas.style.backgroundColor = event.target.value;
	}

	public watchColorPickerFourPicker(event: any) {
		ColorInput.colorWell4.style.color = event.target.value;
		document.body.style.backgroundColor = event.target.value;
	}

	public watchColorPickerFivePicker(event: any) {
		ColorInput.colorWell5.style.color = event.target.value;
		document.getElementById("header")!.style.backgroundColor =
			event.target.value;
	}

	public watchColorPickerSixPicker(event: any) {
		ColorInput.colorWell6.style.color = event.target.value;
		World.history.canvas.style.backgroundColor = event.target.value;
	}
}
