/*global createjs*/
var getTargetPosition = function (target) {
    'use strict';
    var position = {x: 0, y: 0, z: 0},
        targetPosition = null;

    if (target.hasOwnProperty('mesh')) {
        targetPosition = target.mesh.position;
    } else if (target.hasOwnProperty('model')) {
        targetPosition = target.model.position;
    } else if (target.hasOwnProperty('position')) {
        targetPosition = target.position;
    }
    if (targetPosition === null) { return null; }
    if (targetPosition.hasOwnProperty('isArray')) {
        position.x = targetPosition[0];
        position.y = targetPosition.length > 2 ? targetPosition[1] : 0;
        position.y = targetPosition.length > 2 ? targetPosition[2] : targetPosition[1];
    } else {
        position.x = targetPosition.x;
        position.y = targetPosition.y;
        position.z = targetPosition.z;
    }

    return position;
};

var applyVector = function (target, vector, modif) {
    'use strict';
    var m = modif !== undefined ? modif : {x: 0, y: 0, z: 0};

    if (target.hasOwnProperty('mesh')) {
        target.mesh.position.x += vector.x + m.x;
        target.mesh.position.y += vector.y + m.y;
        target.mesh.position.z += vector.z + m.z;
/*    } else if (target.hasOwnProperty('move')) {
        target.move(vector.x + m.x, vector.z + m.z);*/
    } else if (target.hasOwnProperty('model')) {
        target.model.position.x += vector.x + m.x;
        target.model.position.y += vector.y + m.y;
        target.model.position.z += vector.z + m.z;
    } else if (target.hasOwnProperty('position')) {
        target.position.x += vector.x + m.x;
        target.position.y += vector.y + m.y;
        target.position.z += vector.z + m.z;
    }
};

var applyRotation = function (target, rotationVector, angle) {
    'use strict';
    if (target.hasOwnProperty('mesh')) {
        target.mesh.rotation.x += rotationVector.x * angle;
        target.mesh.rotation.y += rotationVector.y * angle;
        target.mesh.rotation.z += rotationVector.z * angle;
/*    } else if (target.hasOwnProperty('move')) {
        target.move(vector.x* angle, vector.z + m.z);*/
    } else if (target.hasOwnProperty('model')) {
        target.model.rotation.x += rotationVector.x * angle;
        target.model.rotation.y += rotationVector.y * angle;
        target.model.rotation.z += rotationVector.z * angle;
    } else if (target.hasOwnProperty('rotation')) {
        target.rotation.x += rotationVector.x * angle;
        target.rotation.y += rotationVector.y * angle;
        target.rotation.z += rotationVector.z * angle;
    }
};
/*
parameters : {targetP: {x: 0, y: 0, z: 0}, delay: 0.10, modifyer: {x: 0, y: 0, z: 0}, frames: 5};
*/
var Animation = function (target, parameters) {
    'use strict';
    var self = this;

    this.startPosition = null;
    this.targetPosition = null;
    this.vector = {x: 0, y: 0, z: 0};
    this.isInit = false;
    this.isDone = false;
    this.sandClock = 0;
    this.counter = parameters.frames;
    this.modify = {x: 0, y: 0, z: 0};
    this.alter = {x: 0, y: 0, z: 0};
    this.trend = {x: 0.98, y: 0.98, z: 0.98};

    this.computeVector = function (sp, tp, params) {
        self.modify.x = params.modifyer.x / params.frames;
        self.modify.y = params.modifyer.y / params.frames;
        self.modify.z = params.modifyer.z / params.frames;
        self.vector.x = (tp.x - sp.x) / params.frames;
        self.vector.y = (tp.y - sp.y) / params.frames;
        self.vector.z = (tp.z - sp.z) / params.frames;
        self.alter.x = -1 * self.modify.x / (params.frames / 2);
        self.alter.y = -1 * self.modify.y / (params.frames / 2);
        self.alter.z = -1 * self.modify.z / (params.frames / 2);
        return self.vector;
    };

    this.initAnimation = function () {
        self.startPosition = getTargetPosition(target);
        self.targetPosition = parameters.targetP;
        self.vector = self.computeVector(self.startPosition, self.targetPosition, parameters);
        self.sandClock = parameters.delay;
        self.isInit = true;
        if (typeof parameters.sound === 'string' && parameters.soundParams === 'atStart') { createjs.Sound.play(parameters.sound); }
    };
    /*jslint bitwise: true*/
    this.update = function (deltaTime) {
        if (self.isInit === false) {
            self.initAnimation();
        } else {
            self.sandClock -= deltaTime;
            if (self.sandClock <= 0) {
                self.counter -= 1;
                self.sandClock = parameters.delay;
                self.modify.x *= self.trend.x;
                self.modify.y *= self.trend.y;
                self.modify.z *= self.trend.z;
                self.alter.x *= self.modify.x;
                self.alter.y *= self.modify.y;
                self.alter.z *= self.modify.z;
                self.vector.x += self.alter.x;
                self.vector.y += self.alter.y;
                self.vector.z += self.alter.z;
                applyVector(target, self.vector, self.modify);
                if (parameters.rotate === true) {
                    applyRotation(target, {x: 0, y: 1, z: 0}, (2 * Math.PI) / parameters.frames);
                }
                if (self.counter <= 0) {
                    self.isDone = true;
                    if (typeof parameters.sound === 'string' && parameters.soundParams === 'atEnd') { createjs.Sound.play(parameters.sound); }
                    if (parameters.callback !== undefined) {parameters.callback(parameters.targetP.x, parameters.targetP.y, parameters.targetP.z); }
/*
                    if (target.hasOwnProperty('move')) {
                        target.move(parameters.targetP.x, parameters.targetP.y, parameters.targetP.z);
*/
                }
                if (self.counter === (parameters.frames / 2) | 0) {self.modify.x *= -1;
                                                                   self.modify.y *= -1;
                                                                   self.modify.z *= -1;
                                                                   self.alter.x *= -1;
                                                                   self.alter.y *= -1;
                                                                   self.alter.z *= -1;
                                                                   self.trend.x = 1.02;
                                                                   self.trend.y = 1.02;
                                                                   self.trend.z = 1.02;
                                                                  }
            }
        }
    };
};