/*global manager, THREE,  Team, Factory, PLAYERCOLOR: true, PLAYER: true*/
/*jslint browser: true*/
/*global Animation*/

var Player = function (playerTeam, parameters) {
    'use strict';
    var self = this, i;

    this.team = playerTeam;
    this.ID = parameters.ID;
    this.position = parameters.position === undefined ? [0, 0] : parameters.position;
    this.level = parameters.level === undefined ? 1 : parameters.level;
    this.color = playerTeam.color;
    this.orientation = parameters.orient;
    this.model = null;
    this.alive = true;
    this.inventory = [];
    this.moving = false;
    this.params = {
        animOffset: 0,
        walking: false,
        duration: 500,
        keyframes: 20,
        interpolation: 500 / 20,
        lastKeyframe: 0,
        currentKeyframe: 0
    };

    this.reorient = function () {
        if (self.model !== null) {
            self.model.rotation.y = (Math.PI / 2) * (self.orientation - 1);
        }
    };

    this.getStringInventory = function () {
        var invent = "P " + self.ID, i;

        invent += " lvl : " + self.level + " O : " + self.orientation + " - ";
        for (i = 0; i < 7; i += 1) {
            invent += " " + self.inventory[i];
        }
        return invent;
    };

    /*jslint bitwise: true*/
    this.move = function (x, y, z) {
        self.position[0] = x | 0;
        self.position[1] = z | 0;
        if (self.model !== null) {
            self.model.position.set(self.position[0], y, self.position[1]);
            self.reorient();
        }
        self.moving = false;
    };
    /*jslint bitwise: false*/

    this.moveToward = function (x, y, z, o) {
        if (self.model === null) { return false; }
        var targetPosition = {x: x, y: y, z: z},
            parameters,
            anima;
        self.moving = true;
        if (targetPosition.x > self.position[0]) {self.orientation = 2;
            } else if (targetPosition.x < self.position[0]) {self.orientation = 4;
            } else if (targetPosition.y < self.position[1]) {self.orientation = 3;
            } else if (targetPosition.y > self.position[1]) {self.orientation = 1;
            }
        self.reorient();
        parameters = {targetP: targetPosition, delay: 0.0001, modifyer: {x: 0, y: 0, z: 0}, frames: 100, rotate: false, callback: function () {self.move(x, y, z); self.orientation = o; self.reorient(); }};
        anima = new Animation(self, parameters);
        manager.animations.push(anima);
        return true;
    };

    this.getExpulsed = function (orientation) {
        if (self.model === null) {return false; }
        var targetPosition = {x: self.model.position.x,
                              y: self.model.position.y,
                              z: self.model.position.z
                             },
            parameters,
            anima,
            angle = (orientation - 1) * (Math.PI / 2);

        targetPosition.x += Math.sin(angle);
        targetPosition.z += Math.cos(angle);
        parameters = {targetP: targetPosition, delay: 1, modifyer: {x: 0, y: 4, z: 0}, frames: 100, rotate: true, callback: self.move};
        anima = new Animation(self, parameters);
        manager.animations.push(anima);
        return true;
    };

    this.selfLoader = function () {

        var jsonLoader = new THREE.JSONLoader();
        jsonLoader.load('ressources/models/android.json', function (geometry, materials) {
            for (i = 0; i < materials.length; i += 1) {
                if (i !== 2 && i !== 3) {
                    materials[i].color.set(self.color);
                }
                materials[i].morphTargets = true;
            }
            var material = new THREE.MeshFaceMaterial(materials);
            self.model = new THREE.Mesh(geometry, material);

            self.model.scale.set(0.05, 0.05, 0.05);
            self.model.position.set(self.position[0], 0.0, self.position[1]);
            self.model.rotation.y = (Math.PI / 2) * (self.orientation - 1);
            manager.context.scene.add(self.model);
        });
    };

    this.update = function () {
        if (this.model !== null) { this.model.rotation.y += 0.1; this.model.position.y += 0.1; }
    };

    this.render = function () {
        if (self.moving === true && self.model) {
            var time = new Date().getTime() % self.params.duration,
                keyframe = Math.floor(time / self.params.interpolation) + self.params.animOffset;
            if (keyframe !== self.params.currenKeyframe) {
                self.model.morphTargetInfluences[self.params.lastKeyframe] = 0;
                self.model.morphTargetInfluences[self.params.currentKeyframe] = 1;
                self.model.morphTargetInfluences[keyframe] = 0;
                self.params.lastKeyframe = self.params.currentKeyframe;
                self.params.currentKeyframe = keyframe;
            }
            self.model.morphTargetInfluences[keyframe] = (time / self.params.interpolation) / self.params.interpolation;
            self.model.morphTargetInfluences[self.params.lastKeyframe] = 1 - self.model.morphTargetInfluences[keyframe];
        } else if (self.moving === false && self.model) {
            self.params.lastKeyframe = 0;
            self.params.currentKeyframe = 0;

        }
    };

    this.inventory[0] = 10;
    for (i = 1; i < 7; i += 1) {this.inventory[i] = 0; }
    this.selfLoader();
};
