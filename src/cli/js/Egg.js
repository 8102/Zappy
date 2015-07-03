/* global THREE*/
/*global Factory*/

var Egg = function (ID, player, parameters) {
    'use strict';
    var self = this;

    this.ID = ID;
    this.player = player;
    this.team = player.team;
    this.isReady = false;
    this.model = null;
    this.alive = true;
    this.timer = 600; /* time to get ready */
    this.position = [0, 0];

    /*jslint bitwise: true*/
    this.selfLoader = function () {
        self.model = Factory.createEgg(self.team.color);
        if (parameters.position === undefined) {
            self.model.position.set(player.model.position.x, 0.25, player.model.position.z);
        } else {self.model.position.set(parameters.position.x, parameters.position.y, parameters.position.z); }
        self.position[0] = self.model.position.x | 0;
        self.position[1] = self.model.position.z | 0;
        self.team.eggs.push(self);
        self.team.updateNbPlayersOnBanner();
    };
    /*jslint bitwise: false*/

    this.hatch = function () {
        self.isReady = true;
        /* Add EFfect Here */
    };

    this.selfLoader();
};