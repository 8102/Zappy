module.exports = function (Actions, Ia, Queue) {
	var sleep = require('sleep');
	var spellbook = require('./spellbook.json');

	var debug = true;

	var actions = Actions;
	var IA = Ia;
	var cmdQueue = Queue;

	var action = new actions();


	var goal = {
		NONE: 0,
		EAT: 1,
		COLLECT: 2,
		MOVE: 3,
		CAST: 4,
		INCANT: 5,
		JOIN: 6,
		WAIT: 7
	}

	var syncFov = false,
		syncInv = false;

	var step = 0;

	var lock = false;

	var brain = {
		inventory: [],
		fov: [],
		pos: {
			x: 0,
			y: 0
		},
		to: {
			x: 0,
			y: 0
		},
		objective: goal.NONE,
		resource: undefined,
		level: 1,
		direction: 0,
		state: undefined,
		message: {
			content: undefined,
			direction: 0
		}
	}

	function calcCoord(pos, to) {
		var tmpRight = 0, tmpLeft = 0;
		for (var y = 0; y < 10; y++) {
			if (y * y <= pos && y * y * (y + 2) >= pos) {
				to.y = y;
				tmpRight = y * y * (y + 2);
				tmpLeft = y * y;
				break;
			}
		}
		var middle = (tmpRight + tmpLeft) / 2;
		to.x = pos - middle;
	}

	function inQueue(action) {
		for (var i = 0; i < cmdQueue.length; i++) {
			if (action == cmdQueue[i].command) {
				return (true);
			}
		}
		return (false);
	}

	function updateInventory() {
		if (!inQueue('inventaire') && cmdQueue.length < 10) {
			action.inventory();
			syncInv = false;
		}
	}

	function updateFov() {
		if (!inQueue('voir') && cmdQueue.length < 10) {
			action.see();
			syncFov = false;
		}
	}

	function inInventory(stoneName) {
		var quantity = 0;
		for (var i = 0; i < brain.inventory.length; i++) {
			if (brain.inventory[i][0] == stoneName) {
				quantity += brain.inventory[i][1];
			}
		}
		return (quantity);
	}

	function findRessource(resource) {
		if (!syncFov) {
			return (false);
		}
		// console.log(brain.fov);
		for (var i = 0; i < brain.fov.length; i++) {
			if (brain.fov[i].indexOf(resource) > -1) {
				brain.pos.x = brain.pos.y = 0;
				calcCoord(i, brain.to);
				brain.resource = resource;
				brain.objective = goal.MOVE;
				brain.state = 'take';
				return (true);
			}
		}
		return (false);
	}

	function move() {
		if (cmdQueue.length > 0) {
			return (false);
		}
		console.log('je suis en ' + brain.pos.x + ' ' + brain.pos.y);
		console.log('je dois aller en ' + brain.to.x + ' ' + brain.to.y);
		if (brain.pos.y != brain.to.y) {
			action.forward();
			brain.pos.y += 1;				
			return (true);
		}
		if (brain.to.x < 0) {
			action.left();
		} else if (brain.to.x > 0 ) {
			action.right();
		}
		if (brain.pos.x != brain.to.x) {
			action.forward();
			if (brain.to.x < 0) {
				brain.pos.x -= 1;
			} else {
				brain.pos.x += 1;
			}
			return (true);
		}
		if (brain.state == 'take') {
			action.takeItem(brain.resource);
			brain.pos.x = brain.pos.y = brain.to.x = brain.to.y = 0;
			brain.state = 'took';
			brain.objective = goal.NONE;
			brain.resource = undefined;
			syncInv = false;
			syncFov = false;
		} else if (brain.state == 'join') {
			brain.objective = goal.NONE;
			console.log('jy suis ! ' + brain.pos.x + ' ' + brain.pos.y);
			brain.pos.x = brain.pos.y = brain.to.x = brain.to.y = 0;
			brain.state = 'joined';
		}
	}

	function collect(resource) {
		if (!syncFov) {
			return (false);
		}
		brain.resource = resource;
		var dir = Math.floor((Math.random() * 4) + 1);
		if (brain.direction == dir) {
			var steps = Math.floor((Math.random() * 6) + 1);
			for (var i = 0; i < steps; i++) {
				action.forward();
			}
			brain.direction = 0;
		}
		if (findRessource(resource)) {
			// object trouvé plus qu'à aller le chercher
			move();
		} else {
			brain.direction = (brain.direction + 1) % 4;
			action.right();
			syncFov = false;
		}
	}

	function findGoal() {
		var idx = brain.level + 1;
		var compos = spellbook[idx.toString()];

		if (!syncFov || !syncInv) {
			return (false);
		}
		for (var compo in compos) {
			if (compo == 'nbPlayer') {
				continue;
			}
			if (compos[compo] > 0 && inInventory(compo) < compos[compo]) {
				brain.objective = goal.COLLECT;
				brain.resource = compo;
				return (false);
			}
		}
		if (compos.nbPlayer > 1) {
			brain.objective = goal.CALL;
		} else {
			brain.objective = goal.CAST;
		}
		return (true);
	}

	function onCase(compo) {
		if (!syncFov) {
			return (0);
		}
		var quantity = 0;	
		var currentCase = brain.fov[0];

		if (currentCase.length == 0) {
			return (false);
		}
		for (var i = 0; i < currentCase.length; i++) {
			if (currentCase[i] == compo) {
				quantity += 1;
			}
		}
		return (quantity);
	}

	function prepareIncantation() {
		var idx = brain.level + 1;
		var compos = spellbook[idx.toString()];
		var drop = false;

		if (!syncFov || !syncInv) {
			return (false);
		}
		if (onCase('joueur') > compos.nbPlayer) {
			console.log('----> ' + onCase('joueur') + ' ' + compos.nbPlayer);
			if (cmdQueue.length == 10) {
				return (false);
			}
			action.forward();
			syncFov = false;
			return (false);
		}
		if (brain.hp <= 8) {
			brain.objective = goal.EAT;
			return (false);
		}
		for (var compo in compos) {
			if (compo == 'nbPlayer') {
				continue;
			}
			if (compos[compo] < onCase(compo) && brain.fov[0].indexOf(compo) > -1) {
				if (cmdQueue.length < 10) {
					action.takeItem(compo);
					syncFov = syncInv = false;
				}
				drop = true;
			} else if (compos[compo] > 0 && inInventory(compo) > 0 && compos[compo] > onCase(compo) ) {
				var quantity = compos[compo];
				while (quantity > 0) {
					action.dropItem(compo);
					syncFov = syncInv = false;
					quantity -= 1;
				}
				drop = true;
			}
		}
		if (!drop) {
			brain.objective = goal.INCANT;
		}
		return (!drop);
	}

	function incant() {
		if (!inQueue('incantation')) {
			action.incantation();
		}
	}

	function callTeam() {
		var currentCase = brain.fov[0];
		var nbPlayer = 0;
		var idx = brain.level + 1;
		var playersRequired = spellbook[idx.toString()].nbPlayer;

		if (!syncFov || currentCase == undefined) {
			return (false);
		}
		for (var i = 0; i < currentCase.length; i++) {
			if (currentCase[i] == 'joueur') {
				nbPlayer += 1;
			}
		}
		if (nbPlayer == 0) {
			return (false);
		}
		console.log(nbPlayer + '/' + playersRequired + ' players');
		if (nbPlayer >= playersRequired) {
			brain.objective = goal.CAST;
		} else {
			action.sayToEveryone('incantation-' + brain.level);
			syncFov = false;
		}
		return (true);	
	}

	function joinCoop() {
		if (brain.state != 'joined') {
			move();
		}
	}

	function brainManagement() {
		if (!syncFov) {
			updateFov();
		}
		if (!syncInv) {
			updateInventory();
		}
		if (brain.objective == goal.NONE && brain.hp < 10) {
			brain.objective = goal.EAT;
		}
		switch (brain.objective) {
			case goal.EAT:
				collect('nourriture');
				break;
			case goal.COLLECT:
				collect(brain.resource);
				break;
			case goal.MOVE:
				move();
				break;
			case goal.NONE:
				findGoal();
				break;
			case goal.CALL:
				callTeam();
				break;
			case goal.CAST:
				prepareIncantation();
				break;
			case goal.INCANT:
				incant();
				break;
			case goal.JOIN:
				joinCoop();
				break;
			case goal.WAIT:
				break;
			default:
				console.log('pas d\'objectif... ' + brain.objective);
		}
	}

	IA.on('forward', function() {
		step += 1;
		if (step % (brain.level + 1) == 0) {
			step = 0;
			updateFov();
		}
	});

	IA.on('saw', function(cmd) {
		syncFov = true;
		cmd = cmd.replace('{', '');
		cmd = cmd.replace('}', '');
		brain.fov.length = 0;
		tmp = cmd.split(',');
		for (var j = 0; j < tmp.length; j++) {
			brain.fov.push(tmp[j].split(' '));
		}
		if (brain.objective == goal.COLLECT || brain.objective == goal.EAT) {
			if (findRessource(brain.resource)) {
				// objet trouvé plus qu'à aller le chercher !
				move();
			}
		}
	});

	IA.on('inventory', function(cmd) {
		brain.inventory.length = 0;
		cmd = cmd.replace('{', '');
		cmd = cmd.replace('}', '');
		tmp = cmd.split(',');
		for (var j = 0; j < tmp.length; j++) {
			brain.inventory.push(tmp[j].split(' '));
		}
		brain.hp = brain.inventory[0][1];
		syncInv = true;
	});

	IA.on('notification', function(msg, direction) {
		if (!lock) {
			lock = true;
			brain.objective = goal.WAIT;
		}
		if (brain.state == 'join' || (brain.objective == goal.WAIT && cmdQueue.length > 0)) {
			return (false);
		}
		if (brain.objective != goal.EAT && msg.split('-')[0] == 'incantation' && msg.split('-')[1] == brain.level) {
			brain.pos.x = brain.pos.y = brain.to.x = brain.to.y = 0;
			if (direction == 1 || direction == 2 || direction == 8) {
				brain.to.y = 1;
			} else if (direction >= 4 && direction <= 6) {
				brain.to.y = -1;
			}
			if (direction >= 2 && direction <= 4) {
				brain.to.x = -1;
			} else if (direction >= 6 && direction <= 8) {
				brain.to.x = 1;
			}
			if (brain.to.y < 0) {
				if (cmdQueue.length > 8) {
					console.log('je quitte la biatch !!');
					return (false);
				}
				action.right();
				action.right();
				brain.to.x *= -1;
				brain.to.y *= -1;
			}
			console.log('le son vient de ' + direction + ' je dois donc me rendre en ' + brain.to.x + ' ' + brain.to.y);
			brain.message.content = msg;
			brain.message.direction = direction;
			brain.objective = goal.MOVE;
			brain.state = 'join';
		}
	});

	IA.on('levelUp', function() {
		console.log('I level ' + (brain.level + 1) + ' now madafaka !');
		brain.level += 1;
		brain.objective = goal.NONE;
	});

	IA.on('update', function() {
		syncFov = syncInv = false;
	});

	IA.on('launch', function() {
		run();
	});

	function run() {
		if (debug) console.log('Here we gooo !');
		var intervall = setInterval(brainManagement, 50)
	}

}