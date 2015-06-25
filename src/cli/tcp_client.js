/*
** Require scope
*/
var net = require('net');
var server = require('./http_server.js').Server;
var io = require('socket.io').listen(server);

/*
** debug
*/
var debug = true;

/*
** variable scope
*/
var client = new net.Socket();
var queue = [];
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

function isNumber(n) {
  return !isNaN(parseFloat(n)) && isFinite(n);
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
					} else {
						console.error('Bad map size !');
					}
				}
			}
		} else if (graphicCmd.indexOf(data.slice(0, 3)) > -1) {
			socket.emit('message', data);
		} else {
			// command from server to IA
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

var Action  = function() {

};

Action.prototype.forward = function() {
	if (queue.length < 10) {
		client.write('avance\n');
		queue.push({command: 'avance', state: undefined});
	}
};

Action.prototype.left = function() {
	if (queue.length < 10) {
		client.write('gauche\n');
		queue.push({command: 'gauche', state: undefined});
	}
};

Action.prototype.right = function() {
	if (queue.length < 10) {
		client.write('droite\n');
		queue.push({command: 'droite', state: undefined});
	}
};

Action.prototype.see = function() {
	if (queue.length < 10) {
		client.write('voir\n');
		queue.push({command: 'voir', state: undefined});
		return (true);
	}
	return (false);
};

Action.prototype.inventory = function() {
	if (queue.length < 10) {
		client.write('inventaire\n');
		queue.push({command: 'inventaire', state: undefined});
		return (true);
	}
	return (false);
};

Action.prototype.takeItem = function(obj) {
	if (queue.length < 10) {
		client.write('prendre ' + obj + '\n');
		queue.push({command: 'prendre objet', state: undefined});
	}
};

Action.prototype.dropItem = function(obj) {
	if (queue.length < 10) {
		client.write('pose ' + obj +'\n');
		queue.push({command: 'pose objet', state: undefined});
	}
};

Action.prototype.kickOut = function() {
	if (queue.length < 10) {
		client.write('expulse\n');
		queue.push({command: 'expulse', state: undefined});
	}
};

Action.prototype.sayToEveryone = function(message) {
	if (queue.length < 10) {
		client.write('broadcast texte\n');
		queue.push({command: 'broadcast texte', state: undefined});
	}
};

Action.prototype.incantation = function() {
	if (queue.length < 10) {
		client.write('incantation\n');
		queue.push({command: 'incantation', state: undefined});
	}
};

Action.prototype.layEgg = function() {
	if (queue.length < 10) {
		client.write('fork\n');
		queue.push({command: 'fork', state: undefined});
	}
};

Action.prototype.getFreeSlot = function() {
	if (queue.length < 10) {
		client.write('connect_nbr\n');
		queue.push({command: 'connect_nbr', state: undefined});
	}
};

module.exports.actions = Action;