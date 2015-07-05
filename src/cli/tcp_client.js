/*
** Require scope
*/
var net = require('net');
var server = require('./http_server.js').Server;
var io = require('socket.io').listen(server);
var EventEmitter = require('events').EventEmitter;

/*
** debug
*/
var debug = false;

/*
** variable scope
*/
var IA = new EventEmitter();
var client = new net.Socket();
var cmdQueue = [];
var graphicCmd = ['msz', 'bct', 'tna', 'pnw', 'ppo', 'plv', 'pin', 'pex', 'pbc', 'pic', 'pie',
'pfk', 'pdr', 'pgt', 'pdi', 'enw', 'eht', 'ebo', 'edi', 'sgt', 'seg', 'smg', 'suc', 'sbp', 'tna',
'pnw', 'BIE'];
var mapSize = {
		x: 0,
		y: 0
	};
var availPlaces = 0;
var isAuth = false;
var graphicSocket = undefined;

require('./ia.js')(Action, IA, cmdQueue);

/*
** Utils functions
*/
function isNumber(n) {
  return !isNaN(parseFloat(n)) && isFinite(n);
}

function updateQueue(cmd) {
	for (var i = 0; i < cmdQueue.length; i++) {
		if (cmdQueue[i].state == undefined) {
			cmdQueue[i].state = cmd;
			break;
		}
	}
}

function dumpQueue() {
	console.log("*** DUMP ***");
	for (var i = 0; i < cmdQueue.length; i++) {
		console.log(cmdQueue[i].command + ' --> ' + cmdQueue[i].state);
	}
	console.log("*** END ***");
}

function treatQueue() {
	var full = false;
	if (cmdQueue.length == 10) {
		full = true;
	}
	if (cmdQueue[0] && (cmdQueue[0].state == 'ok' || cmdQueue[0].state == 'ko')) {
		if (cmdQueue[0].state == 'ko') {
			IA.emit('update');
		}
		cmdQueue.shift();
	} else if (cmdQueue[0] && cmdQueue[0].command == 'voir' && cmdQueue[0].state) {
		IA.emit('saw', cmdQueue[0].state);
		cmdQueue.shift();
	} else if (cmdQueue[0] && cmdQueue[0].command == 'inventaire' && cmdQueue[0].state) {
		IA.emit('inventory', cmdQueue[0].state);
		cmdQueue.shift();
	} else {
		if (cmdQueue[0]) {
			console.log('Command not taken into account: ' + cmdQueue[0].command);
			cmdQueue.shift();
		}
	}
	if (full) {
		IA.emit('wakeUp');
	}
}

/*
** Init
*/
module.exports = function(addr, port, team_name, gui) {
	console.log('connecting to ' + addr + ':' + port + '...')
	client.connect(port, addr, function() {
		console.log('Connected');
	});

	client.on('close', function() {
		client.destroy();
		console.log('Connection closed');
		process.exit(1);
	});
	client.on('data', function(data) {
		if (debug) {
			console.log(data.toString(undefined, 0, data.length - 1));
		}

		var res = data.toString().split('\n');
		for (var i = 0; i < res.length; i++) {
			if (res[i].length == 0) {
				res.splice(i, 1);
				i = 0;
			}
		}
		for (var i = 0; i < res.length; i++) {
			if (!isAuth) {
				if (res[i] == 'BIENVENUE') {
					if (gui == 'only') {
						isAuth = true;
					} else {
						client.write(team_name + '\n');
					}
				} else if (isNumber(res[i]) > 0) {
					availPlaces = res[i];
				} else if (res[i].split(' ').length == 2) {
					var tmp = res[i].split(' ');
					if (isNumber(tmp[0]) && isNumber(tmp[1])) {
						isAuth = true;
						mapSize.x = tmp[0];
						mapSize.y = tmp[1];
						console.log('Authentification succeed !');
						IA.emit('launch');
					} else {
						console.error('Bad map size !');
					}
				}
			} else if (graphicCmd.indexOf(res[i].slice(0, 3)) > -1) {
				if (res[i].length > 0) {
				    graphicSocket.emit('message', res[i] + '\n');
				}
			} else {
				// command from server to IA
				if (res[i].search('deplacement') != -1) {
					IA.emit('bump');
				} else if (res[i].search('message') != -1) {
					console.log('notif --> \\' + res[i] + '/');
					IA.emit('notification', res[i].split(',')[1], res[i].substring(res[i].indexOf('message') + 8, res[i].indexOf(',')));
				} else if (res[i].split(' ')[0] == 'niveau') {
					IA.emit('levelUp');
				} else {
					updateQueue(res[i]);
					if (debug) dumpQueue();
					treatQueue();
				}
			}
		}
	});

/*
                    var regexp = new RegExp("^[G][:]([a-zA-Z0-9 ])*[:]([0-9])*\n$$"), parser = message.split(':').map(String), ip;
                console.log("[[ - " + parser[0] + " - " + parser[1] + " - " + parser[2] + " - " + message);
                if (regexp.exec(message) === null) { gui = 'ia'; console.log("Laucnhing in spectator mode"); return true; }
                team_name = parser[1];
                port = parseInt(parser[2], 10);
*/

	/*
	** Graphical communication to the server
	*/
	io.sockets.on('connection', function(socket) {
		console.log('Graphical interface well connected !');
		graphicSocket = socket;

		socket.on('answer', function(message) {
			client.write(message);
		});
	});
}

/*
** Action class: do the communication between the server and the AI
*/

function Action() {
if (typeof Action.initialized == 'undefined') {
	Action.prototype.forward = function() {
		if (cmdQueue.length < 10) {
			client.write('avance\n');
			cmdQueue.push({command: 'avance', state: undefined});
		} else {
			IA.emit('wait');
		}
	};

	Action.prototype.left = function() {
		if (cmdQueue.length < 10) {
			client.write('gauche\n');
			cmdQueue.push({command: 'gauche', state: undefined});
		} else {
			IA.emit('wait');
		}
	};

	Action.prototype.right = function() {
		if (cmdQueue.length < 10) {
			client.write('droite\n');
			cmdQueue.push({command: 'droite', state: undefined});
		} else {
			IA.emit('wait');
		}
	};

	Action.prototype.see = function() {
		if (cmdQueue.length < 10) {
			client.write('voir\n');
			cmdQueue.push({command: 'voir', state: undefined});
			return (true);
		} else {
			IA.emit('wait');
		}
		return (false);
	};

	Action.prototype.inventory = function() {
		if (cmdQueue.length < 10) {
			client.write('inventaire\n');
			cmdQueue.push({command: 'inventaire', state: undefined});
			return (true);
		} else {
			IA.emit('wait');
		}
		return (false);
	};

	Action.prototype.takeItem = function(obj) {
		if (cmdQueue.length < 10) {
			client.write('prend ' + obj + '\n');
			cmdQueue.push({command: 'prend ' + obj, state: undefined});
		} else {
			IA.emit('wait');
		}
	};

	Action.prototype.dropItem = function(obj) {
		if (cmdQueue.length < 10) {
			client.write('pose ' + obj +'\n');
			cmdQueue.push({command: 'pose ' + obj, state: undefined});
		} else {
			IA.emit('wait');
		}
	};

	Action.prototype.kickOut = function() {
		if (cmdQueue.length < 10) {
			client.write('expulse\n');
			cmdQueue.push({command: 'expulse', state: undefined});
		} else {
			IA.emit('wait');
		}
	};

	Action.prototype.sayToEveryone = function(message) {
		if (cmdQueue.length < 10) {
			client.write('broadcast ' + message + '\n');
			cmdQueue.push({command: 'broadcast ' + message, state: undefined});
		} else {
			IA.emit('wait');
		}
	};

	Action.prototype.incantation = function() {
		if (cmdQueue.length < 10) {
			client.write('incantation\n');
			cmdQueue.push({command: 'incantation', state: undefined});
		} else {
			IA.emit('wait');
		}
	};

	Action.prototype.layEgg = function() {
		if (cmdQueue.length < 10) {
			client.write('fork\n');
			cmdQueue.push({command: 'fork', state: undefined});
		} else {
			IA.emit('wait');
		}
	};

	Action.prototype.getFreeSlot = function() {
		if (cmdQueue.length < 10) {
			client.write('connect_nbr\n');
			cmdQueue.push({command: 'connect_nbr', state: undefined});
		} else {
			IA.emit('wait');
		}
	};
	Action.initialized = true;
}
}
