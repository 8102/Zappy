/*global createjs*/

var soundArray = ["broadcast", "click", "expulse", "chain", "page", "crunch", "reward"];

var SoundManager = function () {
    'use strict';
    var self = this;

    this.init = function () {
        var i, ID;
        for (i = 0; i < soundArray.length; i += 1) {
            createjs.Sound.registerSound("ressources/audio/assets/" + soundArray[i] + ".mp3", soundArray[i]);
        }
    };

};