/*global dat, createjs*/
/*jslint browser: true*/

//var pageSound = new buzz.sound("ressources/audio/assets/page", { formats: ["mp3"]});
var GUI = function (manager) {
    'use strict';
    var self = this;

    this.manager = manager;
//    manager.GUI = this;
    this.controler = new dat.GUI();
    this.settings = {
        width: manager.mapWidth,
        height: manager.mapHeight,
        targetX: 0,
        targetY: 0,
        nbLights: 3,
        color: "#ffffff",
        lightIntensity: 1,
        effect: 'Incantation - en cours',
        applyEffect: true,
        grid: false,
        theme: 'stormySky',
        command: 'Entrez votre commande',
        commandResult: manager.commandROM.status
    };
    this.describerIconArray = [];

    this.controler.close();
    this.effects = ['Incantation - en cours', 'Incantation - success', 'Incantation - failure'];
    this.skyBoxChoices = ['darkSea', 'dawnMountain', 'oneDayInHell', 'stormySky'];
/*
    this.controler.add(this.settings, 'width').name('Map Width');
    this.controler.add(this.settings, 'height').name('Map Height');
    this.controler.add(this.settings, 'targetX').min(0).max(manager.mapWidth).step(1).name('target : X coordinate');
    this.controler.add(this.settings, 'targetY').min(0).max(manager.mapHeight).step(1).name('target : Y coordinate');
    this.controler.add(this.settings, 'nbLights').min(1).max(10).step(1).name('number of lights').onChange(function (value) {
        var i;
        manager.engine.addLights(value);
        for (i = 0; i < manager.engine.lights.length; i += 1) { manager.engine.lights[i].color.set(self.settings.color); manager.engine.lights[i].intensity = self.settings.lightIntensity; }
    });
    this.controler.addColor(this.settings, 'color').name('Light Color').onChange(function (value) {
        var i;
        for (i = 0; i < manager.engine.lights.length; i += 1) {
            manager.engine.lights[i].color.set(value);
        }
    });
    this.controler.add(this.settings, 'lightIntensity').min(0.1).max(3.0).step(0.1).name('Light Intensity').onChange(function (value) {
        var i;
        for (i = 0; i < manager.engine.lights.length; i += 1) {
            manager.engine.lights[i].intensity = value;
        }
    });
    this.controler.add(this.settings, 'applyEffect').name('apply Effect on Coordinates');
    this.controler.add(this.settings, 'effect', this.effects).name('Effect');
    this.controler.add(this.settings, 'theme', this.skyBoxChoices).name('Theme').onChange(function (value) { manager.engine.generateSkyBox(value); });
    this.controler.add(this.settings, 'grid').name('Show Grid Helper').onChange(function (value) {
        self.manager.engine.changeGridDisplay();
    });
    this.controler.add(this.settings, 'commandResult').name('Last command result :').onChange(function (value) {if (manager.commandROM.status !== value) {self.settings.commandResult = manager.commandROM.status; } });
    this.controler.add(this.settings, 'command').name('Server Order').onFinishChange(function (value) {manager.treatMessage(value + '\n'); });
*/

    this.initDescriberIconArray = function () {
        var i;

        for (i = 0; i < 7; i += 1) {
            self.describerIconArray[i] = document.getElementById("describer-Icon-" + i);
        }
    };

    this.displayInventory = function (event) {
        var players, ressources, position, i, displayer = document.getElementById("GuiDisplayer");

        if (self.describerIconArray.length === 0) { self.initDescriberIconArray(); }

        if ((position = self.manager.engine.selectedCell()) === null) {
            if (displayer.style.display !== 'none') {createjs.Sound.play("page"); displayer.style.display = 'none'; }
            return false;
        }

        if (displayer.style.display !== 'block') { createjs.Sound.play("page"); displayer.style.display = 'block'; }
        document.getElementById("describer-Title").innerHTML = "Cell (" + position.x + ", " + position.y + ")" + "<br>" + "<br>";

        ressources = self.manager.getRessourcesOnCell(position.x, position.y);
        for (i = 0; i < ressources.length; i += 1) {
            self.describerIconArray[i].innerHTML = ressources[i];
        }

        players = self.manager.getPlayersOnCell(position.x, position.y);
        if (players.length === 0) {
            document.getElementById("describer-Players").innerHTML = "No players on this cell";
            return false;
        }
        document.getElementById("describer-Players").innerHTML = "";
        for (i = 0; i < players.length; i += 1) {
            document.getElementById("describer-Players").innerHTML += players[i].getStringInventory() + "<br><br>";
        }
    };

    this.setLogRecordContent = function () {
        var log = document.getElementById("left-page-content"), i, j;

        log.innerHTML = "";
        for (i = 0; i < 10; i += 1) {
            log.innerHTML += "#" + i + "    " + self.manager.commandRecords[i] + "<br><br>";
        }
    };
    this.setRigthPageContent = function () {
        var field = document.getElementById("right-page-size");

        field.innerHTML = "Width : " + manager.mapWidth + "    Height : " + manager.mapHeight;
        document.getElementById("logBook-r-Icon-Food").innerHTML = manager.mapInformations.ressources[0] + "    Food";
        document.getElementById("logBook-r-Icon-Linemate").innerHTML = manager.mapInformations.ressources[1] + "    Linemates";
        document.getElementById("logBook-r-Icon-Deraumere").innerHTML = manager.mapInformations.ressources[2] + "    Deraumeres";
        document.getElementById("logBook-r-Icon-Sibur").innerHTML = manager.mapInformations.ressources[3] + "    Siburs";
        document.getElementById("logBook-r-Icon-Phiras").innerHTML = manager.mapInformations.ressources[4] + "    Phiras";
        document.getElementById("logBook-r-Icon-Mendiane").innerHTML = manager.mapInformations.ressources[5] + "    Mendianes";
        document.getElementById("logBook-r-Icon-Thystame").innerHTML = manager.mapInformations.ressources[6] + "    Thystames";
    };
};

