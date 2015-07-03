/*global Factory, Team, Player, GameObject, PREFAB_MATERIAL, LIGHT_SHAPE, GUI, Egg, EFFECT, Effects, Effect, THREE*/
/*jslint browser: true*/
/*global VideoContext*/
/*global GameEngine */
/*global Animation*/
/*global createjs, SoundManager*/

/*
var clickSound = new buzz.sound("ressources/audio/assets/click", { formats: ["mp3"] });
clickSound.setVolume(50);
clickSound.setSpeed(2);
var expulseSound = new buzz.sound("ressources/audio/assets/expulse", { formats: ["mp3"] });
*/

var RessourceName = ['food', 'Linemate', 'Deraumère', 'Sibur', 'Mendiane', 'Phiras', 'Thystame'],
    ActionTImes = {
        move: 7,
        look: 7,
        inventory: 1,
        take: 7,
        put: 7,
        expulse: 7,
        broadcast: 7,
        incantate: 300,
        fork: 42
    },
    convertType = [];
convertType[PREFAB_MATERIAL.FOOD] = 0;
convertType[PREFAB_MATERIAL.LINEMATE] = 1;
convertType[PREFAB_MATERIAL.DERAUMERE] = 2;
convertType[PREFAB_MATERIAL.SIBUR] = 3;
convertType[PREFAB_MATERIAL.MENDIANE] = 4;
convertType[PREFAB_MATERIAL.PHIRAS] = 5;
convertType[PREFAB_MATERIAL.THYSTAME] = 6;

var testAnim, targetANim;
var GameManager = function (Context, Engine) {
    'use strict';
    var self = this;

    this.context = null;
    this.engine = null;

    this.teams = [];
    this.teamColors = ['red', 'blue', 'grey', 'gold', 'greenyellow', 'springgreen', 'paleturquoise', 'orange', 'purple', 'fuschia'];
    this.players = [];
    this.eggs = [];
    this.effects = [];
    this.typeArray = [];
    this.ressources = [];
    this.mapWidth = 0;
    this.mapHeight = 0;
    this.regexp = [];
    this.commandArray = [];
    this.time = 100;
    this.commandROM = {lastCommand: "", status: false};
    this.GUI = null;
    this.sound = null;
    this.animations = [];
    this.commandRecords = [];
    this.mapInformations = {size: {x: 0, y: 0}, ressources: [0, 0, 0, 0, 0, 0, 0], witness: true};

    /************************************************************************************/
    /****************************** [Management Basics] *******************************/
    /************************************************************************************/
    this.init = function () {
        self.context = new VideoContext();
        self.context.initVideoContext();
        self.engine = new GameEngine(self.context);
        self.engine.generateSkyBox('stormySky');
        self.engine.init();
        self.sound = new SoundManager();
        self.sound.init();
        self.typeArray = self.initTypeArray();
        self.mapWidth = self.engine.mapWidth;
        self.mapHeight = self.engine.mapHeight;
        self.context.fog = new THREE.Fog(0xffffff, 0.15, 100);
    };
    /************************************************************************************/
    /****************************** [Commands Management] *******************************/
    /************************************************************************************/
    /*msz*/
    this.setMapSize = function (message) {
        var parser = message.split(' ').map(Number);
        self.mapWidth = parser[1];
        self.mapHeight = parser[2];
        self.mapInformations.size.x = self.mapWidth;
        self.mapInformations.size.y = self.mapHeight;
        self.engine.generateMap(self.mapWidth, self.mapHeight);
        self.mapInformations.witness = true;
        if (self.GUI === null) {self.GUI = new GUI(self); }
        document.addEventListener('mousedown', function (event) {
            event.preventDefault();
            if (event.which === 1) {
                self.engine.selectCell(event);
                self.GUI.displayInventory(event);
                createjs.Sound.play("click", {volume: 0.1});
            }
        }, false);
        self.initRessourceArray();
        self.engine.heightMap = self.engine.generateHeightMap(200, 200);
        self.engine.generateRandomMap(200, 200);
        document.addEventListener('keydown', function (event) {
            if (event.keyCode === 32) {
                event.preventDefault();
                self.engine.changeGridDisplay();
            }
            if (event.keyCode === 9) {
                var logBook = document.getElementById("logBook");

                event.preventDefault();
                if (logBook.style.display === 'none') {logBook.style.display = 'block';
                    } else { logBook.style.display = 'none'; }
            }
        }, false);
        return true;
    };

    /*bct*/
    this.addRessourcesToCell = function (message) {
        var i, j, datas = [], parser = message.split(' ').map(Number);

        for (i = 0; i < 9; i += 1) { datas[i] = parser[i + 1]; }
        self.clearRessourceFromCell(datas[0], datas[1]);
        for (i = 2; i < 9; i += 1) {
            if (self.mapInformations.witness === true) {self.mapInformations.ressources[i - 2] += datas[i]; }
            for (j = 0; j < datas[i]; j += 1) {
                self.generateRessource(self.typeArray[i - 2], datas[0], datas[1]);
            }
        }
        return true;
    };
    /*tna*/
    this.createTeam = function (message) {
        var i, teamExist, parser = message.split(' ').map(String);
        if (self.mapInformations.witness === true) {
            self.mapInformations.witness = false;
            self.GUI.setRigthPageContent();
        }
        if ((teamExist = self.getTeamByName(parser[1])) !== null) { return false; }
        self.addNewTeam(parser[1]);
        return true;
    };
    /*pnw*/
    this.createPlayer = function (message) {
        var i, playerExist, parser = message.split(' ').map(String), playerID, playerTeam;
        playerID = parseInt(parser[1], 10);/*.split('#').map(Number)[1];*/
        if ((playerExist = self.getPlayerByID(playerID)) !== null) { return false; }
        if ((playerTeam = self.getTeamByName(parser[6])) === null) { return false; }
        self.addNewPlayer(parser[6],
                          {
                ID: playerID,
                position: [parseInt(parser[2], 10), parseInt(parser[3], 10)],
                orient: parseInt(parser[4], 10),
                level: parseInt(parser[5], 10)
            });
        return true;
    };
    /* ppo */
    this.setPlayerPosition = function (message) {
        var i, playerID, player, parser = message.split(' ').map(String), destination = {x: 0, y: 0};

        playerID = parseInt(parser[1], 10);
        destination.x = parseInt(parser[2], 10);
        destination.y = parseInt(parser[3], 10);
        if ((player = self.getPlayerByID(playerID)) === null) { return false; }
        if (destination.x !== player.position[0] || destination.y !== player.position[1]) {
            player.moveToward(parseInt(parser[2], 10), 0.0, parseInt(parser[3], 10));
        }
//        player.move(parseInt(parser[2], 10), 0.0, parseInt(parser[3], 10));
/*
        player.orientation = parseInt(parser[4], 10);
        player.reorient();
*/
        return true;
    };
    /*plv*/
    this.setPlayerLevel = function (message) {
        var playerID, player, parser = message.split(' ').map(String);

        playerID = parseInt(parser[1], 10);/*.split('#').map(Number)[1];*/
        if ((player = self.getPlayerByID(playerID)) === null) { return false; }
        player.level = parseInt(parser[2], 10);

        /*  /!!\ CHECK VICTORY HERE /!!\ */

        return true;
    };
    /*pin*/
    this.setPlayerInventory = function (message) {
        var i, playerID, player, parser = message.split(' ').map(String);

        playerID = parseInt(parser[1], 10);/*.split('#').map(Number)[1];*/
        if ((player = self.getPlayerByID(playerID)) === null) { return false; }

        for (i = 4; i < 11; i += 1) {
            player.inventory[i - 4] = parseInt(parser[i], 10);
        }
        return true;
    };
    /*pex*/
    /*jslint bitwise: true*/
    this.playerExpulse = function (message) {
        var playerID, player, parser = message.split(' ').map(String),
            playersAround, i;

        playerID = parseInt(parser[1], 10);/*.split('#').map(Number)[1];*/
        if ((player = self.getPlayerByID(playerID)) === null) { return false; }
        playersAround = self.getPlayersOnCell(player.position[0] | 0, player.position[1] | 0);
        for (i = 0; i < playersAround.length; i += 1) {
            if (playersAround[i].ID !== playerID) {playersAround[i].getExpulsed(player.orientation); }
        }
/*
        self.afeffect = new Effect(Effects.create(EFFECT.expulse), self.context, player, {load: 60, blink: false});
        self.anim = new Effects.TextureAnimator(EFFECT.expulse);
*/
        createjs.Sound.play("expulse", {volume: 0.2});
        return true;
    };
    /*pbc*/
    this.playerBroadcast = function (message) {
        var playerID, player, parser = message.split(' ').map(String), parameters, anima;

        playerID = parseInt(parser[1], 10);/*.split('#').map(Number)[1];*/
        if ((player = self.getPlayerByID(playerID)) === null) { return false; }

        /************/
/*
        window.console.log('Player #' + playerID + 'says : \"' + parser[2] + '\" !');
*/
        parameters = {targetP: {x: player.position[0], y: 0.0, z: player.position[1]}, delay: 1, modifyer: {x: 0, y: 0.5, z: 0}, frames: 100, rotate: true, callback: self.move};
        anima = new Animation(player, parameters);
        self.animations.push(anima);

        /************/
        return true;
    };
    /*pic*/
    this.startIncantation = function (message) {
        var i, playerID, player, parser = message.split(' ').map(String);

        playerID = parseInt(parser[4], 10);/*.split('#').map(Number)[1];*/
        if ((player = self.getPlayerByID(playerID)) === null) { return false; }
        window.console.log('Player #' + playerID + ' Has started incantation level {' + parser[3] + '} in (' + parseInt(parser[1], 10) + ', ' + parseInt(parser[2], 10) + ') for next players :');
        for (i = 5; i < parser.length; i += 1) {
            window.console.log(parser[i]);
        }
        return true;
    };
    /*pie*/
    this.endIncantation = function (message) {
        var parser = message.split(' ').map(Number);

        window.console.log('Incantation on cell (' + parser[1] + ', ' + parser[2] + ') is done : ' + (parser[3] === 1 ? 'Success' : 'Failed') + ' !');
    };
    /*pfk*/
    this.playerLaying = function (message) {
        var playerID, player, parser = message.split(' ').map(String);

        playerID = parseInt(parser[1], 10);/*.split('#').map(Number)[1];*/
        if ((player = self.getPlayerByID(playerID)) === null) { return false; }
        window.console.log('Player #' + playerID + ' is laying an egg !');
        return true;
    };
    /*pfk*/
    this.playerLeavingItem = function (message) {
        var playerID, player, parser = message.split(' ').map(String);

        playerID = parseInt(parser[1], 10);/*.split('#').map(Number)[1];*/
        if ((player = self.getPlayerByID(playerID)) === null) { return false; }
        window.console.log('Player #' + playerID + ' is throwing a ' + RessourceName[parseInt(parser[2], 10)] + ' !');
        return true;
    };
    /*pgt*/
    this.playerTakingItem = function (message) {
        var playerID, player, parser = message.split(' ').map(String), item, i, anima;

        playerID = parseInt(parser[1], 10);/*.split('#').map(Number)[1];*/
        if ((player = self.getPlayerByID(playerID)) === null) { return false; }
        window.console.log('Player #' + playerID + ' is taking a ' + RessourceName[parseInt(parser[2], 10)] + ' !');
        if ((item = self.getParticularRessourceOnCell(player.position[0], player.position[1], parseInt(parser[2], 10))) !== null) {
            anima = new Animation(item, {targetP: {x: player.model.position.x, y: 0.5, z: player.model.position.z}, rotate: false, modifyer: {x: 1, y: 1, z: 1}, delay: 1, frames: 50, callback: function () {self.remove(item); }});
            window.alert("Item found");
            self.animations.push(anima);
        }
        return true;
    };
    /*pdi*/
    this.playerDeath = function (message) {
        var playerID, player, parser = message.split(' ').map(String);

        playerID = parseInt(parser[1], 10);/*.split('#').map(Number)[1];*/
        if ((player = self.getPlayerByID(playerID)) === null) { return false; }
        self.removePlayer(playerID);
        self.remove(player);
        window.console.log('Player #' + playerID + ' has died !');
        return true;
    };
    /*enw*/
    this.layEgg = function (message) {
        var playerID, player, eggID, egg, x, y, parser = message.split(' ').map(String);

        playerID = parseInt(parser[2], 10);/*.split('#').map(Number)[1];*/
        eggID = parseInt(parser[1], 10);/*.split('#').map(Number)[1];*/
        x = parseInt(parser[3], 10);
        y = parseInt(parser[4], 10);
        if ((player = self.getPlayerByID(playerID)) === null) { return false; }
        if ((egg = self.getEggByID(eggID)) !== null) { return false; }
        self.addNewEgg(eggID, player, x, y);
        window.console.log('Player #' + playerID + ' has laid an egg in ' + x + ', ' + y + '!');
        return true;
    };
    /*eht*/
    this.eggIsReady = function (message) {
        var eggID, egg, parser = message.split(' ').map(Number);

        eggID = parser[1];
        if ((egg = this.getEggByID(eggID)) === null) { return false; }
        egg.isReady = true;
        return (true);
    };
    /*edi*/
    this.eggIsDead = function (message) {
        var eggID, egg, parser = message.split(' ').map(Number);

        eggID = parser[1];
        if ((egg = self.getEggByID(eggID)) === null) { return false; }
        self.removeEgg(eggID);
        self.remove(egg);
        window.console.log("Egg " + eggID + " has died.");
        return true;
    };
    /*ebo*/
    this.connectToEgg = function (message) {
        var eggID, egg, parser = message.split(' ').map(Number);

        eggID = parser[1];
        if ((egg = self.getEggByID(eggID)) === null) { return false; }
        egg.isReady = true;
        return (true);
    };
    /*sgt*/
    this.setTime = function (message) {
        var parser = message.split(' ').map(Number);

        self.time = parser[1];
        return true;
    };
    /*seg*/
    this.announceVictory = function (message) {
        var team, parser = message.split(' ').map(String);

        if ((team = self.getTeamByName(parser[1])) === null) { return false; }
        window.console.log('Team "' + team + '" has won !');
        return true;
    };
    /*smg*/
    this.receiveMessageFromServer = function (message) {
        var parser = message.split(' ');

        window.console.log("Server has send '" + parser[1] + ".");
        return true;
    };
    /*suc*/
    this.unknownCommand = function (message) {
        window.console.log('Unknown command from server :\'' + message + '\'');
    };
    /*sbp*/
    this.badParameters = function (message) {
        window.console.log('Bad parameters for command \'' + message + '\' .');
    };


    /************************************************************************************/
    /***************************** [Communication Management] ****************************/
    /************************************************************************************/
    this.initRegExpArray = function () {
        var regExpArray = [
            '^[m][s][z]( [0-9]*){2}\n$',
            '^[b][c][t]( [0-9]*){9}\n$',
            '^[t][n][a] [a-zA-Z0-9]*\n$',
            '^[p][n][w] [0-9]*( [0-9]*){2} [1-4] [1-8] [a-zA-Z0-9]+\n$',
            '^[p][p][o] [0-9]*( [0-9]*){2} [1-4]\n$',
            '^[p][l][v] [0-9]* [1-8]\n$',
            '^[p][i][n] [0-9]*( [0-9]*){9}\n$',
            '^[p][e][x] [0-9]*\n$',
            '^[p][b][c] [0-9]*.*\n$',
            '^[p][i][c]( [0-9]*){2} [1-4]( [0-9]*){}\n$',
            '^[p][i][e]( [0-9]*){2} [0-1]\n$',
            '^[p][f][k] [0-9]*\n$',
            '^[p][d][r] [0-9]* [0-6]\n$',
            '^[p][g][t] [0-9]* [0-6]\n$',
            '^[p][d][i] [0-9]*\n$',
            '^[e][n][w] [0-9]* [0-9]( [0-9]*){2}\n$',
            '^[e][h][t] [0-9]*\n$',
            '^[e][b][o] [0-9]*\n$',
            '^[e][d][i] [0-9]*\n$',
            '^[s][g][t] [0-9]*',
            '^[s][e][g] [a-zA-Z0-9]+\n$',
            '^[s][m][g] .*\n$',
            '^[s][u][c]\n$',
            '^[s][b][p]\n$'
        ];
        return regExpArray;
    };

    this.initCommandArray = function () {
        var commandArray = [
            this.setMapSize,
            this.addRessourcesToCell,
            this.createTeam,
            this.createPlayer,
            this.setPlayerPosition,
            this.setPlayerLevel,
            this.setPlayerInventory,
            this.playerExpulse,
            this.playerBroadcast,
            this.startIncantation,
            this.endIncantation,
            this.playerLaying,
            this.playerLeavingItem,
            this.playerTakingItem,
            this.playerDeath,
            this.layEgg,
            this.eggIsReady,
            this.connectToEgg,
            this.eggIsDead,
            this.setTime,
            this.announceVictory,
            this.receiveMessageFromServer,
            this.unknownCommand,
            this.badParameters
        ];
        return commandArray;
    };

    /* Check that [message] is properly formated. */
    this.checkCommand = function (message) {
        var regularExpression, i;
        if (this.regexp.length === 0) {this.regexp = this.initRegExpArray(); }
        if (typeof message !== 'string') { return false; }
        for (i = 0; i < this.regexp.length; i += 1) {
            regularExpression = new RegExp(this.regexp[i]);
            if (regularExpression.exec(message) !== null) { return i; }
        }
        window.console.log("Message from server has not matched : '" + message + "'");
        return null;
    };

    /* Treat [message] according to the correct command; */
    this.treatMessage = function (message) {
        var commandNumber;

        self.commandROM.lastCommand = message;
        self.commandRecords.unshift(message);
        if (self.commandRecords.length > 10) {self.commandRecords.pop(); }
        if (self.GUI && document.getElementById("logBook").style.display !== 'none') {
            self.GUI.setLogRecordContent();
        }
        if (this.regexp.length === 0) {this.regexp = this.initRegExpArray(); }
        if (this.commandArray.length === 0) { this.commandArray = this.initCommandArray(); }
        if ((commandNumber = this.checkCommand(message)) !== null) {
            if ((this.commandArray[commandNumber](message.substring(0, message.length - 1))) === false) { this.badParameters(message); self.commandROM.status = false; self.GUI.settings.commandResult = false;
                } else {self.commandROM.status = true; self.GUI.settings.commandResult = true; }
        } else {this.unknownCommand(message); self.commandROM.status = false; }
    };


    /************************************************************************************/
    /******************************* [General Management] *******************************/
    /************************************************************************************/
    /* add any object to the scene*/
    this.add = function (item) {
        if (item.hasOwnProperty('mesh')) {
            self.context.scene.add(item.mesh);
        } else if (item.hasOwnProperty('model')) {
            self.context.scene.add(item.model);
        } else {self.context.scene.add(item); }
    };

    /* remove any object from the scene*/
    this.remove = function (item) {
        if (item.hasOwnProperty('mesh')) {
            self.context.scene.remove(item.mesh);
        } else if (item.hasOwnProperty('model')) {
            self.context.scene.remove(item.model);
        } else {self.context.scene.remove(item); }
    };


    /************************************************************************************/
    /****************************** [Ressources Management] *****************************/
    /************************************************************************************/
    /* setting up ressource array*/
    this.initRessourceArray = function () {
        var x, y;
        for (x = 0; x < self.mapWidth; x += 1) {
            for (y = 0; y < self.mapHeight; y += 1) {
                self.ressources[y * self.mapWidth + x] = [];
            }
        }
    };

    this.initTypeArray = function () {
        var typeArray = [
            PREFAB_MATERIAL.FOOD, PREFAB_MATERIAL.LINEMATE, PREFAB_MATERIAL.DERAUMERE,
            PREFAB_MATERIAL.SIBUR, PREFAB_MATERIAL.MENDIANE, PREFAB_MATERIAL.PHIRAS,
            PREFAB_MATERIAL.THYSTAME
        ];
        return typeArray;
    };
    this.typeArray = this.initTypeArray();

    /* generates ressource of type [ŧype] in random position [x][y]; */
    this.generateRessource = function (type, x, y) {
        var neutralObject;
        if (self.ressources.length === 0) {self.initRessourceArray(); }
        neutralObject = new GameObject(type === PREFAB_MATERIAL.FOOD ? LIGHT_SHAPE.CYLINDER : LIGHT_SHAPE.TETRAHEDRON, type);
        neutralObject.mesh.position.set(x - 0.5 + Math.random(), 0.05, y - 0.5 + Math.random());
        neutralObject.mesh.scale.set(0.05, 0.05, 0.05);
        neutralObject.setSpecific(x, 0.05, y);
        neutralObject.mesh.castShadow = true;
        self.add(neutralObject);
        self.ressources[y * self.mapWidth + x].push(neutralObject);
        targetANim = neutralObject;
    };

    this.clearRessourceFromCell = function (x, y) {
        var i;
        for (i = 0; i < self.ressources[y * self.mapWidth + x].length; i += 1) {
            self.remove(self.ressources[y * self.mapWidth + x][i]);
        }
        self.ressources[y * self.mapWidth + x] = [];
    };

    this.getRessourcesOnCell = function (x, y) {
        var cell = self.ressources[x + y * self.mapWidth], i, ressources = [0, 0, 0, 0, 0, 0, 0];

        for (i = 0; i < cell.length; i += 1) {
            ressources[convertType[cell[i].type]] += 1;
        }
        return ressources;
    };

    this.getParticularRessourceOnCell = function (x, y, type) {
        var cell = self.ressources[x + y * self.mapWidth], i;

        for (i = 0; i < cell.length; i += 1) {
            if (convertType[cell[i].type] === type) { return cell[i]; }
        }
        return null;
    };
    /************************************************************************************/
    /********************************* [Team Management] ********************************/
    /************************************************************************************/
    /* create and add automatically a new team*/
    this.addNewTeam = function (teamName) {
        var newTeam = new Team(
            {
                name: teamName,
                color: self.teamColors[self.teams.length % self.teamColors.length],
                nbPlayers: 0
            }
        );
        self.teams.push(newTeam);
        return newTeam;
    };

    /*return team correponding to [teamName]*/
    this.getTeamByName = function (teamName) {
        var i;
        for (i = 0; i < self.teams.length; i += 1) {
            if (self.teams[i].name === teamName) { return self.teams[i]; }
        }
        return null;
    };


    /************************************************************************************/
    /******************************** [Player Management] *******************************/
    /************************************************************************************/
    /* create and add to the team a new player. if team doesn't exist, create one.*/
    this.addNewPlayer = function (teamName, parameters) {
        var targetTeam = null, newPlayer, i;
        if ((targetTeam = self.getTeamByName(teamName)) === null) {targetTeam = self.addNewTeam(teamName); }
        newPlayer = new Player(targetTeam, parameters);
        self.players.push(newPlayer);
        targetTeam.addPlayer(parameters.ID);
        return newPlayer;
    };

    /* return the player corresponding to [playerID]; */
    this.getPlayerByID = function (playerID) {
        var i;
        for (i = 0; i < this.players.length; i += 1) {
            if (self.players[i].ID === playerID) { return self.players[i]; }
        }
        return null;
    };

    /* return an array containing players(object) found on cell x, y */
    this.getPlayersOnCell = function (x, y) {
        var playerArray = [], i;

        for (i = 0; i < self.players.length; i += 1) {
            if (self.players[i].position[0] === x && self.players[i].position[1] === y) {
                playerArray.push(self.players[i]);
            }
        }
        return playerArray;
    };

    /* remove player from scene and game*/
    /*NEEDS AN EFFECT*/
    this.removePlayer = function (playerID) {
        var i;
        for (i = 0; i < self.players.length; i += 1) {
            if (self.players[i].ID === playerID) {
                self.players[i].alive = false;
                self.players[i].team.nbDead += 1;
                self.players.splice(i, 1);
            }
        }
    };

    /************************************************************************************/
    /******************************** [Egg Management] *******************************/
    /************************************************************************************/

    /* create an egg and place it to the cell or to the position of the player, while adding it to the player's team*/
    /* FOR NOW ADD AN EFFECT TO THE EGG*/
    this.addNewEgg = function (ID, player, xCoordinate, yCoordinate) {
        var parameters, newEgg;

        parameters = {position: {x: xCoordinate, y: 0.15, z: yCoordinate} };
        if ((self.getEggByID(ID)) !== null) { return false; }
        newEgg = new Egg(ID, player, parameters);
        self.eggs.push(newEgg);
        self.add(newEgg);
/*
        self.afeffect = new Effect(Effects.create(EFFECT.expulse), self.context, newEgg, {load: 150});
        self.anim = new Effects.TextureAnimator(EFFECT.expulse);*/

        return true;
    };

    /*return the egg corresponding to [eggID]*/
    this.getEggByID = function (eggID) {
        var i;
        for (i = 0; i < self.eggs.length; i += 1) {
            if (self.eggs[i].ID === eggID) { return self.eggs[i]; }
        }
        return null;
    };

    this.getTeamNbEggs = function (teamName) {
        var teamEggs = {nb: 0, ready: 0};

    };
    /* return an array containing eggs(object) found on cell x, y */
    this.getEggsOnCell = function (x, y) {
        var eggArray = [], i;

        for (i = 0; i < self.eggs.length; i += 1) {
            if (self.eggs[i].position[0] === x && self.eggs[i].position[1] === y) {
                eggArray.push(self.eggs[i]);
            }
        }
        return eggArray;
    };

    /*remove egg from scene and lists*/
    this.removeEgg = function (eggID) {

        var i;
        for (i = 0; i < self.eggs.length; i += 1) {
            if (self.eggs[i].ID === eggID) {
                self.eggs[i].alive = false;
                self.eggs.splice(i, 1);
            }
        }
    };

    /************************************************************************************/
    /************************************* [Debugger] ***********************************/
    /************************************************************************************/
    this.debugTeam = function () {
        var i;
        window.console.log("{Debug : Teams. }");
        for (i = 0; i < this.teams.length; i += 1) { window.console.log(this.teams[i].name + ' (' + this.teams[i].nbPlayers + ' players)'); }
        window.console.log("End of : {Debug : Teams." + i + " }");
    };

    this.debugPlayer = function () {
        var i, effect2;
        window.console.log("{Debug : Players. }");
        for (i = 0; i < this.players.length; i += 1) { window.console.log(self.players[i].alive + " " + this.players[i].team.name); }
        window.console.log("End of : {Debug : Players. }");
        effect2 = new Effect(Effects.create(EFFECT.decors), self.context, {position: {x: -1, y: 10, z: -1}}, {load: 500});
        self.effects.push(effect2);
        self.test2 = new Effects.TextureAnimator(EFFECT.decors);
        effect2 = new Effect(Effects.create(EFFECT.decors), self.context, {position: {x: self.mapWidth + 1, y: 10, z: -1}}, {load: 500});
        self.effects.push(effect2);
        effect2 = new Effect(Effects.create(EFFECT.decors), self.context, {position: {x: -1, y: 10, z: self.mapHeight + 1}}, {load: 500});
        self.effects.push(effect2);
        effect2 = new Effect(Effects.create(EFFECT.decors), self.context, {position: {x: self.mapWidth + 1, y: 10, z: self.mapHeight + 1}}, {load: 500});
        self.effects.push(effect2);
        self.test2 = new Effects.TextureAnimator(EFFECT.decors);
        document.addEventListener('mousedown', function (event) { self.GUI.displayInventory(); return true; });

    };

    this.testEffect = function (type) {
        self.test = new Effects.TextureAnimator(type);
        targetANim = self.getPlayerByID(1);
        testAnim = new Animation(targetANim, {targetP: {x: 16, y: 0, z: 17}, delay: 0.10, modifyer: {x: 0, y: 3, z: 0}, frames: 150, rotate: true});
    };

    this.update = function () {
        var i, delta = self.context.clock.getDelta() * 1000;
        if (self.afeffect && self.afeffect.exist) {
            if (self.afeffect.update(delta) !== null) {self.anim.update(delta); } else {self.afeffect.mesh.position.y = 50; }
        }
        for (i = 0; i < self.players.length; i += 1) {
            self.players[i].render();
        }
        for (i = 0; i < self.animations.length; i += 1) {
            if (self.animations[i].isDone === false) {self.animations[i].update(delta);
                } else {self.animations.slice(i, 1); }
        }
    };
};
