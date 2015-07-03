module.exports = function (Actions, Ia, Queue) {
var sleep = require('sleep');
var spellbook = require('./spellbook.json');

/*
** debug
*/
var debug = false;

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
	EAT: 8,
	JOIN: 9
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
	prevObjective: goal.NONE,
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

function dumpFOV() {
	console.log('======== DUMP FOV ========');
	console.log(brain.fov);
	console.log('======== END ========');
}

function findResource(resource) {
	if (brain.direction == 4) {
		for (var i = 0; i < Math.floor((Math.random() * 15) + 1); i++) {
			if (i % (brain.visualCapacity + 1) == 0) {
				updateFov();
			}
			for (var i = 0; i < brain.fov.length; i++) {
				if (brain.fov[i].indexOf(resource) > -1) {
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
			if (brain.fov[i].indexOf(resource) > -1) {
				calcCoord(i, brain.to);
				brain.objective = goal.TAKE;
				brain.obj = resource;
				IA.emit('move');
				return (true);
			}
		}
		action.right();
		updateFov();
		brain.direction += 1;
	}
	return (false);
}

/*
** This function returns the quantity of the element passed in parameter
*/
function inInventory(stoneName) {
	var quantity = 0;
	for (var i = 0; i < brain.inventory.length; i++) {
		if (brain.inventory[i][0] == stoneName) {
			quantity += brain.inventory[i][1];
		}
	}
	return (quantity);
}

function findGoal() {
	var idx = brain.level + 1;
	var compos = spellbook[idx.toString()];

	for (var compo in compos) {
		if (compo == 'nbPlayer') {
			continue;
		}
		if (compos[compo] > 0 && inInventory(compo) < compos[compo]) {
			brain.objective = goal.SEARCH;
			brain.obj = compo;
			return (false);
		}
	}
	console.log(compos);
	if (compos.nbPlayer > 1) {
		brain.objective = goal.CALL;
		IA.emit('callTeam', compos.nbPlayer);
	} else {
		prepareIncantation();
		action.incantation();
	}
	return (true);
}

function updateInventory() {
	action.inventory();
}

function updateFov() {
	brain.fov.length = 0;
	action.see();
}

function prepareIncantation() {
	var idx = brain.level + 1;
	var compos = spellbook[idx.toString()];

	for (var compo in compos) {
		if (compo == 'nbPlayer') {
			continue;
		}
		if (compos[compo] > 0) {
			var quantity = compos[compo];
			while (quantity > 0) {
				action.dropItem(compo);
				quantity -= 1;
			}
		}		
	}
}

IA.on('levelUp', function() {
	console.log('I level ' + (brain.level + 1) + ' now madafaka !');
	brain.level += 1;
	brain.visualCapacity += 1;
	brain.objective = goal.NONE;
});

IA.on('callTeam', function(playersRequired) {
	var currentCase = brain.fov[0];
	var nbPlayer = 0;

	if (currentCase == undefined) {
		return (false);
	}
	for (var i = 0; i < currentCase.length; i++) {
		if (currentCase[i] == 'joueur') {
			nbPlayer += 1;
		}
	}
	if (nbPlayer >= playersRequired) {
		brain.objective = goal.CALL;
		prepareIncantation();
		action.incantation();
	} else {
		action.sayToEveryone('incantation-' + brain.level);
	}
	return (true);
});

IA.on('notification', function(msg, direction) {
	if (brain.objective != goal.WAIT && brain.objective != goal.EAT && msg.split('-')[0] == 'incantation' && msg.split('-')[1] == brain.level) {
		brain.pos.x = brain.pos.y = 0;
		if (direction == 1 || direction == 2 || direction == 8) {
			brain.pos.y = 1;
		} else if (direction >= 4 && direction <= 6) {
			brain.pos.y = -1;
		}
		if (direction >= 3 && direction <= 4) {
			brain.pos.x = 1;
		} else if (direction >= 6 && direction <= 8) {
			brain.pos.x = -1;
		}
		if (brain.pos.y < 0) {
			action.right();
			action.right();
		}
		brain.objective = goal.JOIN;
	}
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

IA.on('updateInventory', function(action, compoName, quantity) {
	if (action == 'prend') {
		var added = false;
		for (var i = 0; i < brain.inventory.length; i++) {
			if (brain.inventory[i][0] == compoName) {
				brain.inventory[i][1] += quantity;
				added = true;
			}
		}
		if (!added) {
			brain.inventory.push([compoName, quantity]);
		}
		brain.objective = goal.NONE;
		if (compoName == 'nourriture') {
			brain.hp += quantity;
		}
	} else {
		for (var i = 0; i < brain.inventory.length; i++) {
			if (brain.inventory[i][0] == compoName) {
				brain.inventory[i][1] -= 1;
			}
			if (brain.inventory[i][1] == 0) {
				brain.inventory.splice(i, 1);
			}
		}
		brain.objective = goal.NONE;
	}
	updateFov();
});

IA.on('inventory', function(cmd) {
	brain.inventory.length = 0;
	cmd = cmd.replace('{', '');
	cmd = cmd.replace('}', '');
	tmp = cmd.split(',');
	for (var j = 0; j < tmp.length; j++) {
		brain.inventory.push(tmp[j].split(' '));
	}
});

IA.on('bump', function() {
	updateFov();
	updateInventory();
});

IA.on('update', function(part) {
	if (part == 'prend' || part == 'pose') {
		updateFov();
	} else {
		updateInventory();
	}
});

IA.on('move', function() {
	if (brain.pos.y != brain.to.y) {
		action.forward();
		brain.pos.y += 1;
		return (true);
	}
	if (brain.to.x < 0) {
		action.left();
	} else if (brain.to.x > 0 ){
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
	action.takeItem(brain.obj);
	brain.objective = goal.NONE;
	brain.obj = undefined;
	brain.pos.x = brain.pos.y = 0;
});

IA.on('starving', function() {
	findResource(entity.FOOD);		
});

IA.on('launch', function() {
	run();
});

IA.on('wait', function() {
	if (brain.objective != goal.WAIT) {
		brain.prevObjective = brain.objective;
		brain.objective = goal.WAIT;
	}
});

IA.on('wakeUp', function() {
	if (brain.objective == goal.WAIT) {
		brain.objective = brain.prevObjective;
		brain.prevObjective = goal.NONE;
	}
});

function brainManagement() {
	if (brain.objective == goal.NONE) {
		updateFov();
	}
	if (brain.objective == goal.NONE && brain.hp < 5) {
		brain.objective = goal.EAT;
	}
	if (brain.objective == goal.EAT && brain.hp > 5) {
		brain.objective = goal.NONE;
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
		case goal.JOIN:
			// IA.emit('notification');
			break;
		case goal.SEARCH:
			findResource(brain.obj);
			break;
		case goal.WAIT:
			//IA.emit('');
			break;
		case goal.CALL:
			IA.emit('callTeam');
			break;
		case goal.NONE:
			findGoal();
			break;
		default:
			console.log('im waiting');
	}
}

function run() {
	if (debug) console.log('Here we gooo !');
	var intervall = setInterval(brainManagement, 1000);
}

};

/*
**		 Todo:
**			- modifier l'update de l'inventaire
**			- update brain.hp
**			- enlever les commandes qui ont échoué de la queue (ex: avance --> level actuel : 2)
*/