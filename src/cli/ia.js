module.exports = function (Actions, Ia, Queue) {
var sleep = require('sleep');
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

function dumpFOV() {
	console.log('======== DUMP FOV ========');
	console.log(brain.fov);
	console.log('======== END ========');
}

function findResource(resource) {
	dumpFOV();
	if (brain.direction == 4) {
		for (var i = 0; i < Math.floor((Math.random() * 15) + 1); i++) {
			if (i % (brain.visualCapacity + 1) == 0) {
				updateFov();
			}
			for (var i = 0; i < brain.fov.length; i++) {
				if (brain.fov[i].indexOf(resource) > -1) {
					console.log('oOoOoOoOoO ' + i);
					calcCoord(i, brain.to);
					console.log('pos = (' + brain.pos.x + ',' + brain.pos.y + ') to = (' + brain.to.x + ',' + brain.to.y + ')');
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
				console.log('oOoOoOoOoO ' + i);
				calcCoord(i, brain.to);
				console.log('pos = (' + brain.pos.x + ',' + brain.pos.y + ') to = (' + brain.to.x + ',' + brain.to.y + ')');
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
	}
	return (true);
}

function updateInventory() {
	action.inventory();
}

function updateFov() {
	action.see();
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

IA.on('updateInventory', function(action, compoName, quantity) {
	if (action == 'prendre') {
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
		console.log("c'est bon j'ai remplis ma mission bitach !");
		brain.inventory.push([compoName, quantity]);
		brain.objective = goal.NONE;

	} else {
		for (var i = 0; i < brain.inventory.length; i++) {
			if (brain.inventory[i][0] == compoName) {
				brain.inventory[i][1] -= 1;
			}
			if (brain.inventory[i][1] == 0) {
				brain.inventory.splice(i, 1);
			}
		}
	}
	updateFov();
});

IA.on('inventory', function() {
	brain.inventory.length = 0;
	cmd.state = cmd.replace('{', '');
	cmd.state = cmd.replace('}', '');
	tmp = cmd.state.split(',');
	for (var j = 0; j < tmp.length; j++) {
		brain.inventory.push(tmp[j].split(' '));
	}
});

IA.on('bump', function() {
	updateFov();
	updateInventory();
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
	} else if (brain.to.x > 0 ){
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
	brain.pos.x = brain.pos.y = 0;
});

IA.on('starving', function() {
	findResource(entity.FOOD);		
});

IA.on('launch', function() {
	run();
});

IA.on('wait', function() {
	brain.prevObjective = brain.objective;
	brain.objective = goal.wait;
});

IA.on('wakeUp', function() {
	brain.objective = brain.prevObjective;
	brain.prevObjective = goal.NONE;
});

function brainManagement() {
	if (brain.objective == goal.NONE && brain.hp < 20) {
		brain.objective = goal.EAT;
	}
	if (brain.objective == goal.EAT && brain.hp > 20) {
		brain.objective = goal.NONE;
	}
	console.log(brain.objective);
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
	updateFov();
	var intervall = setInterval(brainManagement, 50);
}

};

/*
**		 Todo:
**			- modifier l'update de l'inventaire
**			- update brain.hp
*/