/*global dat*/

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
    this.effects = ['Incantation - en cours', 'Incantation - success', 'Incantation - failure'];
    this.skyBoxChoices = ['darkSea', 'dawnMountain', 'oneDayInHell', 'stormySky'];
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
        if (manager.engine.gridHelper === null) {
            manager.engine.setupGrid(manager.mapWidth, manager.mapHeight);
            manager.context.scene.add(manager.engine.gridHelper);
        } else { manager.context.scene.remove(manager.engine.gridHelper);
                 manager.engine.gridHelper = null; }
    });
    this.controler.add(this.settings, 'commandResult').name('Last command result :').onChange(function (value) {if (manager.commandROM.status !== value) {self.settings.commandResult = manager.commandROM.status; } });
    this.controler.add(this.settings, 'command').name('Server Order').onFinishChange(function (value) {manager.treatMessage(value + '\n'); });
    this.controler.open();
};