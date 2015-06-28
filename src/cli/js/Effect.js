/*global THREE, VideoContext, Factory, Effects */
/*jslint browser: true*/

var Effect = function (mesh, videoContext, target, params) {
    'use strict';
    var self = this;

    this.videoContext = videoContext;

    if (params !== undefined) {
        this.load = params.load !== undefined ? params.load : 20;
        this.period = params.period !== undefined ? params.period : 0.25;
    } else {this.load = 20; this.period = 0.25; }
    this.perioder = this.period;
    this.show = true;
    this.witness = true;
    this.exist = true;
    this.mesh = mesh;
/*
     To be replaced with a call to EffectFactory 
    this.texture = new THREE.ImageUtils.loadTexture('ressources/images/textures/expulsion.png');
    this.material = new THREE.SpriteMaterial({ map: this.texture, useScreenCoordinates: false, side: THREE.DoubleSide, transparent: true });
    this.mesh = new THREE.Sprite(this.material);
*/
    if (target.hasOwnProperty('mesh')) {
        self.mesh.position.set(target.mesh.position.x, target.mesh.position.y, target.mesh.position.z);
    } else if (target.hasOwnProperty('model')) {
        self.mesh.position.set(target.model.position.x, target.model.position.y, target.model.position.z);
    } else { self.mesh.position.set(target.position.x, target.position.y, target.position.z); }

//    this.mesh.position.x += 0.5;
    /*this.mesh.position.y += 0.5;
    *///this.mesh.scale.set(0.5, 0.5, 1.0);
    videoContext.scene.add(this.mesh);


    /* To make it blink */
    this.update = function () {
        if (target.alive !== true) {self.exist = false; videoContext.scene.remove(self.mesh); }
        if (self.exist === true) {
            self.perioder -= videoContext.clock.getDelta();
            if (self.load <= 0) { self.exist = false;
                if (self.witness === true) {videoContext.scene.remove(self.mesh); }
                } else if (self.perioder <= 0.0) { self.show = !self.show; self.perioder = self.period; self.load -= 1; }
            if (self.show === true && self.witness === false) {videoContext.scene.add(self.mesh); self.witness = true;
                } else if (self.show === false && self.witness === true) { videoContext.scene.remove(self.mesh); self.witness = false; }
            return true;
        } else { return false; }
    };
};