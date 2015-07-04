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
options['GUI'] = '';
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
    if (argv[i].slice(0, 2) == '-g' || argv[i].slice(0, 2) == '--gui') {
        options.GUI = 'ia';
        if (argv[i].split('=')[1] == 'only') {
            options.GUI = 'only';
        }
    }
}

for (var opt in options) {
    if (options[opt] == null) {
        console.log("Missing option: " + opt);
        process.exit(1);
    }
}

if (options.GUI.length > 0) {
    console.log('launch http server');
    require('./http_server.js')(1081);
}
require('./tcp_client.js')(options.hostname, options.port, options.team_name, options.GUI);

if (options.GUI.length > 0) {
    console.log('launch interface');
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
/*	mainWindow.openDevTools(); */
        
        mainWindow.on('closed', function() {
        mainWindow = null;
        });
    });    
}
