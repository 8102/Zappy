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
var debug = true;

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
		}
	}
}

function treatQueue() {
	var full = false;
	if (cmdQueue.length == 10) {
		full = true;
	}
	if (cmdQueue[0] && (cmdQueue[0].state == 'ok' || cmdQueue[0].state == 'ko')) {
		cmdQueue.shift();
	} else if (cmdQueue[0] && cmdQueue[0].command == 'voir' && cmdQueue[0].state) {
		IA.emit('saw', cmdQueue[0].state);
		cmdQueue.shift();
	} else if (cmdQueue[0] && cmdQueue[0].command == 'inventaire' && cmdQueue[0].state) {
		IA.emit('inventory');
		cmdQueue.shift();
	} else {
		console.log('Command not taken into account: ' + cmdQueue[0].command);
		cmdQueue.shift();
	}
	if (full) {
		IA.emit('wakeUp');
	}
}

/*
** Init
*/
module.exports = function(addr, port, team_name) {
	console.log('connecting to ' + addr + ':' + port + '...')
	client.connect(port, addr, function() {
		console.log('Connected');
	});

	client.on('close', function() {
		client.destroy();
		console.log('Connection closed');
	});
	client.on('data', function(data) {
		if (debug) {
			console.log(data.toString(undefined, 0, data.length - 1));
		}
		console.log('>>> ' + graphicCmd.indexOf(data.toString().slice(0, 3)));

		var res = data.toString().split('\n');
		if (!isAuth) {
			for (var i = 0; i < res.length; i++) {
				if (res[i] == 'BIENVENUE') {
					client.write(team_name + '\n');
				} else if (isNumber(res[i])) {
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
			}
		} else if (graphicCmd.indexOf(data.toString().slice(0, 3)) > -1) {
			for (var i = 0; i < res.length; i++) {
				graphicSocket.emit('message', res[i] + '\n');
			}
		} else {
			// command from server to IA
			for (var i = 0; i < res.length; i++) {
				if (res[i].search('deplacement') != -1) {
					IA.emit('bump');
				} else if (res[i].search('message') != -1) {
					IA.emit('notification', res[i].substring(res[i].indexOf('message'), res[i].length));
				} else {
					updateQueue(res[i]);
				}
			}
		}
	});

	/*
	** Graphical communication to the server
	*/
	io.sockets.on('connection', function(socket) {
		console.log('Graphical interface well connected !');
		graphicSocket = socket;

		socket.on('message', function(message) {
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
			client.write('prendre ' + obj + '\n');
			cmdQueue.push({command: 'prendre objet', state: undefined});
		} else {
			IA.emit('wait');
		}
	};

	Action.prototype.dropItem = function(obj) {
		if (cmdQueue.length < 10) {
			client.write('pose ' + obj +'\n');
			cmdQueue.push({command: 'pose objet', state: undefined});
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
			client.write('broadcast texte\n');
			cmdQueue.push({command: 'broadcast texte', state: undefined});
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
