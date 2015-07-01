/*global THREE*/
/*global Stats*/
/*jslint browser: true*/


/*
** VideoContext {} : Link WebGL and html as well as
** controls input.
*/
var VideoContext = function (width, height) {
    'use strict';

    this.width  = typeof width  !== 'undefined' ? width  : window.innerWidth;
    this.height = typeof height !== 'undefined' ? height : window.innerHeight;

                        /* VideoContext fields*/

    this.renderer = null;
    this.controls = null;
    this.stats = null;
    this.scene = null;
    this.camera = null;
    this.clock = null;
    this.statDisplayer = true; /*wether or not displaying Stats */

                        /* Frame Functions */

    this.render = function () {
        this.renderer.render(this.scene, this.camera);
    };

    this.update = function () {
        this.controls.update();
        this.stats.update();
    };

    this.changeStatDisplay = function () {
        this.statDisplayer = !this.statDisplayer;
    };
                    /* Initialisation Functions */
    this.initClock = function () {
        this.clock = new THREE.Clock();
    };

    this.initRenderer = function () {
        this.renderer = new THREE.WebGLRenderer();
        this.renderer.setSize(this.width, this.height);
        this.renderer.setClearColor(0xDEDEDEDE, 1);
        document.body.appendChild(this.renderer.domElement);
    };

    this.initScene = function () {
        this.scene = new THREE.Scene();
    };

    this.initCamera = function () {
        this.camera = new THREE.PerspectiveCamera(65, this.width / this.height, 0.1, 10000);
        this.camera.position.set(70, 30, 60);
        this.camera.lookAt(this.scene.position);
    };

    this.initControls = function () {
        this.controls = new THREE.OrbitControls(this.camera, this.renderer.domElement);
    };

    this.initStats = function () {
        this.stats = new Stats();
        this.stats.domElement.style.position = 'absolute';
        this.stats.domElement.style.bottom = '0px';
        this.stats.domElement.style.zIndex = 100;
        if (this.statDisplayer === true) { document.body.appendChild(this.stats.domElement); }
    };

    this.initVideoContext = function () {
        this.initClock();
        this.initRenderer();
        this.initScene();
        this.initCamera();
        this.initControls();
        this.initStats();
    };
};