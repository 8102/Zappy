/*
** Require scope
*/
var net = require('net');
var server = require('./http_server.js').Server;
var io = require('socket.io').listen(server);

/*
** variable scope
*/
var client = new net.Socket();
var queue = new Array();
var graphicCmd = ['msz', 'bct', 'tna', 'pnw', 'ppo', 'plv', 'pin', 'pex', 'pbc', 'pic', 'pie',
'pfk', 'pdr', 'pgt', 'pdi', 'enw', 'eht', 'ebo', 'edi', 'sgt', 'seg', 'smg', 'suc', 'sbp', 'tna',
'pnw']

/*
** Init
*/
module.exports = function(addr, port) {
	client.connect(port, addr, function() {
		console.log('Connected');
	});

	client.on('close', function() {
		client.destroy();
		console.log('Connection closed');
	});

	/*
	** Graphical communication to the server
	*/
	io.sockets.on('connection', function(socket) {
		console.log('Graphical interface well connected !');

		socket.on('message', function(message) {
			client.write(message);

		client.on('data', function(data) {
			if (graphicCmd.indexOf(data.slice(0, 3)) > -1) {
				socket.emit('message', data);	
			} else {
				// command from server to IA
			}
			queue.shift();
		});

		});
	});
}

/*
** Action class: do the communication between the server and the AI
*/

var Action  = function () {

};

Action.prototype.forward = function () {
	if (queue.length < 10) {
		client.write('avance\n');
		queue.push('avance');
	}
};

Action.prototype.left = function () {
	if (queue.length < 10) {
		client.write('gauche\n');
		queue.push('gauche');
	}
};

Action.prototype.right = function () {
	if (queue.length < 10) {
		client.write('droite\n');
		queue.push('droite');
	}
};

Action.prototype.see = function () {
	if (queue.length < 10) {
	client.write('voir\n');
	queue.push('voir');
	}
};

Action.prototype.inventory = function () {
	if (queue.length < 10) {
		client.write('inventaire\n');
		queue.push('inventaire');
	}
};

Action.prototype.takeItem = function () {
	if (queue.length < 10) {
		client.write('prendre objet\n');
		queue.push('prendre objet');
	}
};

Action.prototype.dropItem = function () {
	if (queue.length < 10) {
		client.write('pose objet\n');
		queue.push('pose objet');
	}
};

Action.prototype.kickOut = function () {
	if (queue.length < 10) {
		client.write('expulse\n');
		queue.push('expulse');
	}
};

Action.prototype.sayToEveryone = function () {
	if (queue.length < 10) {
		client.write('broadcast texte\n');
		queue.push('broadcast texte');
	}
};

Action.prototype.incantation = function () {
	if (queue.length < 10) {
		client.write('incantation\n');
		queue.push('incantation');
	}
};

Action.prototype.layEgg = function () {
	if (queue.length < 10) {
		client.write('fork\n');
		queue.push('fork');
	}
};

Action.prototype.getFreeSlot = function () {
	if (queue.length < 10) {
		client.write('connect_nbr\n');
		queue.push('connect_nbr');
	}
};