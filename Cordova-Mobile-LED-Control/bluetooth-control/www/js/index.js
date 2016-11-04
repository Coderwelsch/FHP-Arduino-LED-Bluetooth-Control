var app = {
	initialize: function () {
		this.bindEvents();
	},

	bindEvents: function () {
		document.addEventListener( "deviceready", this.onDeviceReady, false );
	},

	onDeviceReady: function () {
		window.bluetoothSerial.isEnabled( app.bluetoothIsEnabled, app.bluetoothIsNotEnabled );
	},

	bluetoothIsEnabled: function () {
		alert( "BLUETOOTH ENABLED!" );

		window.bluetoothSerial.list( app.bluetoothDevicesDiscovered, app.bluetoothDevicesCouldntBeDiscovered );
	},

	bluetoothDevicesDiscovered: function ( devices ) {
		if ( devices === null || !devices ) {
			devices = [];
		}

		alert( JSON.stringify( devices, null, 4 ) );

		window.bluetoothSerial.list( app.bluetoothDevicesDiscovered, app.bluetoothDevicesCouldntBeDiscovered );
	},

	bluetoothDevicesCouldntBeDiscovered: function () {
		alert( "ERROR: DEVICES COULDNT BEE DISCOVERED!" );
	},

	bluetoothIsNotEnabled: function () {
		alert( "NO BLUETOOTH ENABLED!" );
	}
};

app.initialize();
