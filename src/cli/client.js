/*
** Initialisation
*/

var argc = process.argv[2];
var argv = process.argv.slice(3);

/*
** Arguments checking
*/
var options = new Array();
options['team_name'] = null;
options['port'] = null;
options['hostname'] = "localhost";
for (var i = 0; i < argc; i++) {
    if (argv[i] == '-n') {
        options.team_name = argv[i + 1];
    }
    if (argv[i] == '-p') {
        options.port = argv[i + 1];
    }
    if (i < argc - 1 && argv[i] == '-h') {
        options.hostname = argv[i + 1];
    }
}

for (var opt in options) {
    if (options[opt] == null) {
        console.log("Missing option: " + opt);
        process.exit(1);
    }
}

require('./http_server.js')(options.port + 1);
require('./tcp_client.js')(options.hostname, options.port);

var app = require('app');  // Module to control application life.
var BrowserWindow = require('browser-window');  // Module to create native browser window.
var toto = require("websocket");

// Keep a global reference of the window object, if you don't, the window will
// be closed automatically when the javascript object is GCed.
var mainWindow = null;

// Quit when all windows are closed.
app.on('window-all-closed', function() {
    if (process.platform != 'darwin') {
	app.quit();
    }
});

// This method will be called when Electron has done everything
// initialization and ready for creating browser windows.
app.on('ready', function() {
    // Create the browser window.
   mainWindow = new BrowserWindow({width: 800, height: 600, 'auto-hide-menu-bar': true});

    // and load the index.html of the app.
    mainWindow.loadUrl('file://' + __dirname + '/index.html');
    
    // Emitted when the window is closed.
    mainWindow.on('closed', function() {
	// Dereference the window object, usually you would store windows
	// in an array if your app supports multi windows, this is the time
	// when you should delete the corresponding element.
	mainWindow = null;
    });
});
