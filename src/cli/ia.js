var EventEmitter = require('events').EventEmitter;
var sleep = require('sleep');
var spellbook = require('./spellbook.json');
var actions = require('./tcp_client.js').actions;

var IA = new EventEmitter();

var goal = {
	NONE: 0,
	TAKE: 1,
	MOVE: 2,
	FIGHT: 3,
	CAST: 4
};

var brain = {
	job: 'collector',
	inventory: [],
	hp: 10,
	teamName: '',
	teamSize: 1,
	fov: [],
	to: {
		x: 0,
		y: 0
	},
	pos: {
		x: 0,
		y: 0
	},
	objectif: goal.NONE,
	obj: undefined,
	visualCapacity: 1,
	level: 1
};

var entity = {
	FOOD: 'nourriture',
	LINEMATE: 'linemate',
	DERAUMERE: 'deraumere',
	SIBUR: 'sibur',
	MENDIANE: 'mendiane',
	PHIRAS: 'phiras',
	THYSTAME: 'thystame'
};

function calcCoord(pos, to) {
	var tmpRight = 0, tmpLeft = 0;
	for (var y = 0; y < 10; y++) {
		if (y * y <= pos && y * y * (y + 2)) {
			to.y = y;
			tmpRight = y * y * (y + 2);
			tmpLeft = y *y;
			break;
		}
	}
	var middle = (tmpRight - tmpLeft) / 2;
	to.x = pos - middle;
}

function findResource(resource) {
	for (var turn = 0; turn < 3; turn++) {
		for (var i = 0; i < brain.fov.length; i++) {
			if (fov[i].indexOf(resource) > -1) {
				calcCoord(i, brain.to);
				brain.objectif = goal.TAKE;
				brain.obj = resource;
				IA.emit('move');
				return;
			}
		}
		action.right();
		IA.emit('updateFov');
	}
	for (var i = 0; i < Math.floor((Math.random() * 15) + 1); i++) {
		if (i % (visualCapacity + 1) == 0) {
			IA.emit('updateFov');
		}
		for (var i = 0; i < brain.fov.length; i++) {
			if (fov[i].indexOf(resource) > -1) {
				calcCoord(i, brain.to);
				brain.objectif = goal.TAKE;
				brain.obj = resource;
				IA.emit('move');
				return;
			}
		}
		action.forward();
	}
}

function findGoal() {
	var compos = spellbook[level.toString()];

	for (var compo in compos) {
		if (compo == 'nbPlayer') {
			continue;
		}
		if (compos[compo] > 0) {
			for (var i = 0; i < compos[compo]; i++) {
				findResource(compo);
			}
		}
	}
	if (compos.nbPlayer > 1) {
		IA.emit('CallTeam', compos.nbPlayer);
	}
}

function run() {
	while (brain.level != 8) {
		if (hp < 20) {
			IA.emit('starving');
		}
		findGoal();
	}
}

IA.on('CallTeam', function(playersRequired) {
	var levelUp = false;
	var currentCase = brain.fov[0];
	var nbPlayer = 0;

	while (!levelUp) {
		for (var i = 0; i < currentCase.length; i++) {
			if (currentCase[i] == 'player') {
				nbPlayer += 1;
			}
		}
		if (nbPlayer >= playersRequired) {
			action.incantation();
			brain.level += 1;
			brain.visualCapacity += 1;
		} else {
			action.sayToEveryone('incantation-' + brain.level);
		}		
	}
});

IA.on('updateFov', function() {
	var updated = false;
	while (action.see() == false) {
		sleep.usleep(50000);
	}
	while (!updated) {
		for (var i = 0; i < queue.length; i++) {
			if (queue[i].command == 'voir' && queue[i].state) {
				queue[i].state = queue[i].replace('{', '');
				queue[i].state = queue[i].replace('}', '');
				brain.fov.length = 0;
				tmp = queue[i].state.split(',');
				for (var j = 0; j < tmp.length; j++) {
					brain.fov.push(tmp[j].split(' '));
				}
				queue.splice(i, 1);
				updated = true;
				break;
			}
		}
		sleep.usleep(50000);
	}
});

IA.on('updateInventory', function() {
	var updated = false;
	while (action.inventory() == false) {
		sleep.usleep(50000);
	}
	while (!updated) {
		for (var i = 0; i < queue.length; i++) {
			if (queue[i].command == 'inventaire' && queue[i].state) {
				brain.fov.length = 0;
				queue[i].state = queue[i].replace('{', '');
				queue[i].state = queue[i].replace('}', '');
				tmp = queue[i].state.split(',');
				for (var j = 0; j < tmp.length; j++) {
					brain.inventory.push(tmp[j].split(' '));
				}
				queue.splice(i, 1);
				updated = true;
				break;
			}
		}
		sleep.usleep(50000);
	}
	brain.hp = brain.inventory[0][1];
});

IA.on('move', function() {
	while (brain.pos.y != brain.to.y) {
		action.forward();
		brain.pos.y += 1;
	}
	if (brain.to.x < 0) {
		action.left;
	} else {
		action.right;
	}
	while (brain.pos.x != brain.to.x) {
		action.forward();
		if (brain.to.x < 0) {
			brain.pos.x -= 1;
		} else {
			brain.pos.x += 1;
		}
	}
	action.takeItem(brain.obj);
	brain.objectif = goal.NONE;
	brain.obj = undefined;
});

IA.on('starving', function() {
	while (brain.hp < 20) {
		findResource(entity.FOOD);		
	}
});

/*
**		 Todo: 
**			- rethink the communication between client and IA
**			- error management (if a command fail)
**			- improve IA (chief, take resources more efficiently)
*/