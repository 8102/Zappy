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

    this.selfLoader = function () {
        self.model = Factory.createEgg(self.team.color);
        if (parameters.position === undefined) {
            self.model.position.set(player.model.position.x, 0.25, player.model.position.z);
        } else {self.model.position.set(parameters.position.x, parameters.position.y, parameters.position.z); }
    };

    this.hatch = function () {
        self.isReady = true;
        /* Add EFfect Here */
    };

    this.selfLoader();
};