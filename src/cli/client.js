/*
** Initialisation
*/

var argc = process.argv[2],
    argv = process.argv.slice(3);

/*
** Arguments checking
*/
var options = new Array();

options['team_name'] = null;
options['port'] = null;
options['hostname'] = "localhost";
options['GUI'] = false;
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
    if (argv[i] == '-g' || argv[i] == '--gui') {
        options.GUI = true;
    }
}

for (var opt in options) {
    if (options[opt] == null) {
        console.log("Missing option: " + opt);
        process.exit(1);
    }
}

if (options.GUI) {
    require('./http_server.js')(1081);
}
require('./tcp_client.js')(options.hostname, options.port, options.team_name);

if (options.GUI) {
    graphicalInterface();
}

function graphicalInterface() {
    var app = require('app');
    var BrowserWindow = require('browser-window');
    var toto = require("websocket");

    var mainWindow = null;

    app.on('window-all-closed', function() {
        if (process.platform != 'darwin') {
        // app.quit();
        }
    });

    app.on('ready', function() {
        mainWindow = new BrowserWindow({width: 1600, height: 960, 'auto-hide-menu-bar': true});

        mainWindow.loadUrl('file://' + __dirname + '/index.html');
        
        mainWindow.on('closed', function() {
        mainWindow = null;
        });
    });    
}
