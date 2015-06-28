/*global THREE */
/*jsLint browser: true */
var SpriteNames = ['available', 'broadcast', 'expulsion', 'death', 'expulsion-sprite', 'download', 'appear', 'tesla'];

var EFFECT = {
    broadcast: {name: SpriteNames[0], parameters: null},
    eggIsReady: {name: SpriteNames[1], parameters: null},
    expulse: {name: SpriteNames[2], parameters: {nbFrameH: 11, nbFrameV: 1, nbFrame: 11, duration: 100, totalDuration: 75, scale: {x: 2.0, y: 2.0, z: 1.0}, rpos: {x: 0, y: 0, z: 0}}},
    death: {name: SpriteNames[3], parameters: null},
    expulsion: {name: SpriteNames[4]},
    decors: {name: SpriteNames[5], parameters: {nbFrameH: 14, nbFrameV: 1, nbFrame: 14, duration: 0.03, totalDuration: 75, scale: {x: 10.0, y: 10.0, z: 1.0}, rpos: {x: 0, y: 0, z: 0}}},
    appear: {name: SpriteNames[6], parameters: {nbFrameH: 14, nbFrameV: 1, nbFrame: 14, duration: 100, totalDuration: 800, scale: {x: 1.5, y: 2.0, z: 1.0}, rpos: {x: 0, y: 0.25, z: 0}}},
    tesla: {name: SpriteNames[7], parameters: {nbFrameH: 8, nbFrameV: 1, nbFrame: 8, duration: 100, totalDuration: 800, scale: {x: 1.0, y: 1.0, z: 1.0}, rpos: {x: 0, y: 0, z: 0}}}
};


var EffectFactory = function () {
    'use strict';
    var self = this;

    this.textures = [];
    this.materials = [];
    this.toto = 'BONJOUR';

    this.createTexture = function () {

    };
    this.loadTextures = function () {
        var i;

        for (i = 0; i < SpriteNames.length; i += 1) {
            self.textures[SpriteNames[i]] = new THREE.ImageUtils.loadTexture('ressources/images/sprites/' + SpriteNames[i] + '.png');
            self.textures[SpriteNames[i]].minFilter = THREE.NearestFilter;
            self.textures[SpriteNames[i]].wrapS = THREE.ClampToEdgeWrapping;
            self.textures[SpriteNames[i]].wrapT = THREE.ClampToEdgeWrapping;
            self.materials[SpriteNames[i]] = new THREE.SpriteMaterial({map: self.textures[SpriteNames[i]], useScreenCoordinates: false, side: THREE.DoubleSide, transparent: true});
        }
    };

    this.create = function (type) {
        var newSprite;

        if (typeof type.name !== 'string') {return null; }
        self.materials[type.name].rotation = 0;
        newSprite = new THREE.Sprite(self.materials[type.name]);
        newSprite.scale.set(type.parameters.scale.x, type.parameters.scale.y, type.parameters.scale.z);
        return newSprite;
    };

    this.TextureAnimator = function (type) {
        this.texture = self.textures[type.name];
        this.params  = type.parameters;
        this.texture.wrapS = THREE.RepeatWrapping;
        this.texture.wrapT = THREE.RepeatWrapping;
        this.texture.repeat.set(1 / this.params.nbFrameH, 1 / this.params.nbFrameV);
        this.currentFrame = 0;
        this.currentTime = 0;
        this.update = function (time) {
            var currentColumn, currentRow;
            this.currentTime += time;
            while (this.currentTime > this.params.duration) {
                this.currentTime -= this.params.duration;
                this.currentFrame = (this.currentFrame + 1) % this.params.nbFrame;
                currentColumn = this.currentFrame % this.params.nbFrameH;
                this.texture.offset.x = currentColumn / this.params.nbFrameH;
            }
        };
    };
    this.loadTextures();
};

var Effects = new EffectFactory();