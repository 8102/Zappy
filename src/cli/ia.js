module.exports = function (Actions, Ia, Queue) {
// var sleep = require('sleep');
var spellbook = require('./spellbook.json');

/*
** debug
*/
var debug = true;

var actions = Actions;
var IA = Ia;
var cmdQueue = Queue;

var action = new actions();

var goal = {
	NONE: 0,
	TAKE: 1,
	MOVE: 2,
	FIGHT: 3,
	CAST: 4,
	SEARCH: 5,
	WAIT: 6,
	CALL: 7,
	EAT: 8
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
	objective: goal.NONE,
	obj: undefined,
	visualCapacity: 1,
	level: 1,
	direction: 0
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
	if (brain.direction == 4) {
		for (var i = 0; i < Math.floor((Math.random() * 15) + 1); i++) {
			if (i % (brain.visualCapacity + 1) == 0) {
				IA.emit('updateFov');
			}
			for (var i = 0; i < brain.fov.length; i++) {
				if (fov[i].indexOf(resource) > -1) {
					calcCoord(i, brain.to);
					brain.objective = goal.TAKE;
					brain.obj = resource;
					IA.emit('move');
					return (true);
				}
			}
			action.forward();
		}
		brain.direction = 0;
	} else {
		for (var i = 0; i < brain.fov.length; i++) {
			if (fov[i].indexOf(resource) > -1) {
				calcCoord(i, brain.to);
				brain.objective = goal.TAKE;
				brain.obj = resource;
				IA.emit('move');
				return (true);
			}
		}
		action.right();
		IA.emit('updateFov');
		brain.direction += 1;
	}
	return (false);
}

/*
** This function returns the quantity of the element passed in parameter
*/
function inInventory(stoneName) {
	var quantity = 0;
	for (var i = 0; i < inventory.length; i++) {
		if (inventory[i][0] == stoneName) {
			quantity += inventory[i][1];
		}
	}
	return (quantity);
}

function findGoal() {
	var compos = spellbook[level.toString()];

	for (var compo in compos) {
		if (compo == 'nbPlayer') {
			continue;
		}
		if (compos[compo] > 0 && inventory(compo) < compos[compo]) {
			brain.objective = goal.SEARCH;
			brain.obj = compo;
			return (false);
		}
	}
	if (compos.nbPlayer > 1) {
		brain.objective = goal.CALL;
		IA.emit('callTeam', compos.nbPlayer);
	}
	return (true);
}

IA.on('levelUp', function() {
	if (debug) console.log('I level ' + (brain.level + 1) + 'now madafaka !');
	brain.level += 1;
	brain.visualCapacity += 1;
	brain.objective = goal.NONE;
});

IA.on('callTeam', function(playersRequired) {
	var levelUp = false;
	var currentCase = brain.fov[0];
	var nbPlayer = 0;

	for (var i = 0; i < currentCase.length; i++) {
		if (currentCase[i] == 'player') {
			nbPlayer += 1;
		}
	}
	if (nbPlayer >= playersRequired) {
		brain.objective = goal.CALL;
		action.incantation();
	} else {
		action.sayToEveryone('incantation-' + brain.level);
	}
});

IA.on('notification', function(msg) {
	console.log('I\'m earing a sound: [' + msg + ']');
});

IA.on('saw', function(cmd) {
	cmd = cmd.replace('{', '');
	cmd = cmd.replace('}', '');
	brain.fov.length = 0;
	tmp = cmd.split(',');
	for (var j = 0; j < tmp.length; j++) {
		brain.fov.push(tmp[j].split(' '));
	}
});

IA.on('updateFov', function() {
	action.see();
});

IA.on('inventory', function() {
	brain.inventory.length = 0;
	cmd.state = cmd.replace('{', '');
	cmd.state = cmd.replace('}', '');
	tmp = cmd.state.split(',');
	for (var j = 0; j < tmp.length; j++) {
		brain.inventory.push(tmp[j].split(' '));
	}
	brain.hp = brain.inventory[0][1];
});

IA.on('updateInventory', function() {
	action.inventory();
});

IA.on('bump', function() {
	IA.emit('updateFov');
	IA.emit('updateInventory');
});

IA.on('move', function() {
	if (brain.pos.y != brain.to.y) {
		action.forward();
		brain.pos.y += 1;
		return (true);
	}
	if (brain.to.x < 0) {
		action.left;
		return (true);
	} else {
		action.right;
		return (true);
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
	action.takeItem(brain.obj);
	brain.objective = goal.NONE;
	brain.obj = undefined;
});

IA.on('starving', function() {
	findResource(entity.FOOD);		
});

IA.on('launch', function() {
	run();
});

function brainManagement() {
	if (brain.objective == goal.NONE && brain.hp < 20) {
		brain.objective = goal.EAT;
	}
	if (brain.objective == goal.EAT && brain.hp > 20) {
		brain.objective = goal.SEARCH;
	}
	switch (brain.objective) {
		case goal.TAKE:
			IA.emit('move');
			break;
		case goal.EAT:
			IA.emit('starving');
			break;
		case goal.MOVE:
			IA.emit('move');
			break;
		case goal.FIGHT:
			//IA.emit('');
			break;
		case goal.SEARCH:
			findGoal();
			break;
		case goal.WAIT:
			//IA.emit('');
			break;
		case goal.CALL:
			IA.emit('callTeam');
			break;
		default:
			console.log('im waiting');
	}
}

function run() {
	if (debug) console.log('Here we gooo !');
	IA.emit('updateFov');
	var intervall = setInterval(brainManagement, 50);
}

};

/*
**		 Todo:
**			- error management (if a command fail)
**			- improve IA (chief, take resources more efficiently)
*/