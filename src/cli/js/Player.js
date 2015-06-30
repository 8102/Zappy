/*global manager, THREE,  Team, Factory, PLAYERCOLOR: true, PLAYER: true*/
/*jslint browser: true*/

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
    this.params = {
        animOffset: 0,
        walking: false,
        duration: 1000,
        keyframes: 20,
        interpolation: 1000 / 20,
        lastKeyframe: 0,
        currentKeyframe: 0
    };
    playerTeam.addPlayer(this.ID);

    this.reorient = function () {
        self.model.rotation.y = (Math.PI / 2) * (self.orientation - 1);
    };

    this.selfLoader = function () {

        var jsonLoader = new THREE.JSONLoader();
        jsonLoader.load('ressources/models/android.js', function (geometry, materials) {
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
        if (self.model) {
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
        }
    };
    for (i = 0; i < 7; i += 1) {this.inventory[i] = 0; }
    this.selfLoader();
};