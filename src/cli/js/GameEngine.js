/*global THREE*/
/*global VideoContext, GeometryFactory, GameObject, Factory ,gui, Effect, ParticleEngine, Examples*/
/*global SHAPE, LIGHT_SHAPE, MATERIAL, PREFAB_MATERIAL, TEXTURE*/
/*global ImprovedNoise*/
/*jslint browser: true*/
/*global createjs*/
/* EXAMPLE MULTIMATERIAL OBJECT
                this.map[y * this.mapWidth + x].setMultiMaterial(2, [{type: MATERIAL.LAMBERT, color: 0xffffffff, wireframe: false, transparent: false, map: Factory.textures['minecraft_side.png']},
                                                                     {type: MATERIAL.BASIC, color: 0xffff0000, wireframe: true, transparent: true}]);
*/


var x = 0, y = 0, /*COLOURCHANGER = 1, */GROUND = 0, neutralObject = null, projector, mouse = {x: 0, y: 0}, cellList = [], TESTSPRITE, EGG, o, selectorRot = 0.02;
var GameEngine = function (videoContext) {
    'use strict';
    var self = this;

    this.videoContext = videoContext;
    this.mapWidth = null;
    this.mapHeight = null;
    this.map = [];
    this.stones = [];
    this.worldBasics = [];
    this.lights = [];
    this.j = false;
    this.guiReady = false;
    this.gridHelper = null;
    this.decors = null;
    this.targets = [];
    this.selector = null;
    this.mouse = {x: 0, y: 0};
    this.displaySelector = false;
    this.add = function (gameObject) {
        this.videoContext.scene.add(gameObject.mesh);
    };

    this.clearMap = function () {

        for (x = 0; x < this.mapWidth; x += 1) {
            for (y = 0; y < this.mapHeight; y += 1) {
                videoContext.scene.remove(this.map[y * this.mapWidth + x].mesh);
            }
        }
        this.map = [];
    };

    this.generateMap = function (mapWidth, mapHeight) {
        if (self.map.length !== 0) {self.clearMap(); }
        this.mapWidth = (typeof mapWidth === 'number' && mapWidth > 0) ? mapWidth : 0;
        this.mapHeight = (typeof mapHeight === 'number' && mapHeight > 0) ? mapHeight : 0;
        for (x = 0; x < this.mapWidth; x += 1) {
            for (y = 0; y < this.mapHeight; y += 1) {
                self.map[y * this.mapWidth + x] = new GameObject(LIGHT_SHAPE.BOX, PREFAB_MATERIAL.GROUND);
                self.map[y * this.mapWidth + x].mesh.position.set(x, -0.5, y);
                if (x % 2 === 0) {self.map[y * this.mapWidth + x].mesh.rotation.y = Math.PI / 2; }
                this.add(this.map[y * this.mapWidth + x]);
                self.targets.push(self.map[y * this.mapWidth + x].mesh);
            }
        }
    };

    this.addLights = function (nbLight) {
        var i = 0;
        if (self.lights.length !== 0) { for (i = 0; i < self.lights.length; i += 1) {videoContext.scene.remove(self.lights[i]); } }

        for (i = 0; i < 4; i += 1) {
            self.lights[i] = new THREE.DirectionalLight(0xffffffff, 1);
            self.lights[i].position.set(Math.cos((Math.PI / 2) * i) * 200, 200, Math.sin((Math.PI / 2) * i) * 200);
            self.lights[i].intensity = 0.8;
            videoContext.scene.add(self.lights[i]);
        }
    };

    this.setupGrid = function (width, height) {
        self.gridHelper = new THREE.GridHelper((height >= width ? height : width) / 2, 1);
        self.gridHelper.position.set(width / 2 - 0.5, 0.1, height / 2 - 0.5);
        self.gridHelper.setColors(new THREE.Color('gold'), new THREE.Color('gold'));
        this.videoContext.scene.add(self.gridHelper);
    };

    this.changeGridDisplay = function () {
        if (self.gridHelper === null) {
            self.setupGrid(self.mapWidth, self.mapHeight);
            self.videoContext.scene.add(self.gridHelper);
        } else { self.videoContext.scene.remove(self.gridHelper);
                 self.gridHelper = null; }
    };

    this.selectedCell = function () {
        if (self.displaySelector === true) { return {x: self.selector.position.x, y: self.selector.position.z}; }
        return null;
    };

    this.selectCell = function (event) {
        var vector, ray, intersects, camera = self.videoContext.camera;

        self.mouse.x = (event.clientX / self.videoContext.width) * 2 - 1;
        self.mouse.y = -(event.clientY / self.videoContext.height) * 2 + 1;
        vector = new THREE.Vector3(self.mouse.x, self.mouse.y, 1);
        vector.unproject(camera);
        ray = new THREE.Raycaster(camera.position, vector.sub(camera.position).normalize());
        intersects = ray.intersectObjects(self.targets);
        if (intersects.length > 0) {
            self.selector.position.x = intersects[0].object.position.x;
            self.selector.position.z = intersects[0].object.position.z;
            if (self.displaySelector === false) {
                self.videoContext.scene.add(self.selector);
                self.displaySelector = true;
            }
        } else if (self.displaySelector === true) {
            self.videoContext.scene.remove(self.selector);
            self.displaySelector = false;
        }
    };

    this.init = function () {
        self.addLights(3);
        self.selector = new THREE.GridHelper(0.5, 0.10);
        self.selector.setColors(new THREE.Color('gold'), new THREE.Color('gold'));
        self.selector.position.set(15, 0.05, 15);
    };

    this.generateSkyBox = function (skyboxTheme) {
        var faces = ['xpos', 'xneg', 'ypos', 'yneg', 'zpos', 'zneg'],
            skyboxGeometry = new THREE.BoxGeometry(5000, 5000, 5000),
            materialArray = [],
            skyboxMaterial,
            i;

        for (i = 0; i < 6; i += 1) {
            materialArray.push(new THREE.MeshBasicMaterial(
                {
                    map: Factory.textures['skyboxTextures/' + skyboxTheme + '/' + faces[i] + '.png'],
                    side: THREE.BackSide
                }
            ));
            skyboxMaterial = new THREE.MeshFaceMaterial(materialArray);
            this.skybox = new THREE.Mesh(skyboxGeometry, skyboxMaterial);
            this.videoContext.scene.add(this.skybox);
        }
    };

    /*jslint bitwise: true*/
    this.isInArenaRange = function (i, width, height) {
        var x = (i % width), y = (i / width) | 0, hw = width / 2, qw = (self.mapWidth / 2) | 0, hh = height / 2, qh = (self.mapHeight / 2) | 0;
        if (x >= hw - qw && x <= hw + qw && y >= hh - qh && y <= hh + qh) {return true; } else { return false; }
    };
    this.isInBorderRange = function (i, width, height, type) {
        var x = (i % width), y = (i / width) | 0, hw = width / 2, qw = (self.mapWidth / 2) | 0, hh = height / 2, qh = (self.mapHeight / 2) | 0;
        if (type === 0 && x === hw - qw) { return true; }
        if (type === 1 && x === hw + qw) { return true; }
        if (type === 2 && y === hh - qh) { return true; }
        if (type === 3 && y === hh + qh) { return true; }
        if (type === 4 && x === hw - qw && y === hh - qh) { return true; }
        return false;
    };


    this.nxSmoothering = function (data, i, value, width) {
        while (i % width) {
            data[i] += value;
            i -= 1;
        }
        data[i] += value;
    };

    this.pxSmoothering = function (data, i, value, width) {
        while (i % width !== width - 1) {
            data[i] += value;
            i += 1;
        }
        data[i] += value;
    };

    this.pySmoothering = function (data, i, value, width, height) {
        while (i < width * height) {
            data[i] += value;
            i += width;
        }
    };

    this.nySmoothering = function (data, i, value, width, height) {
        while (i > 0) {
            data[i] += value;
            i -= width;
        }
    };

    this.cnSmoothering = function (data, i, value, width, height) {
        var x, y;
        for (x = 0; x <= i % width; x += 1) {
            for (y = 0; y <= (i / width) | 0; y += 1) {
                data[y * width + x] += value;
            }
        }
    };

    this.returnSmootheringDiff = function (a, b) {
        if (a > b) { return Math.abs(a - b); } else { return (a - b); }
    };
    /*jslint bitwise: true */
    /*global manager*/
    this.generateHeightMap = function (width, height) {
        var data = [], perlin = new ImprovedNoise(),
            size = width * height, quality = 2, z = Math.random() * 100,
            j, i, x, y, value = 0;
        self.mapWidth = manager.mapWidth;
        self.mapHeight = manager.mapHeight;
        for (j = 0; j < 4; j += 1) {
            if (j === 0) { for (i = 0; i < size; i += 1) { data[i] = -1; } }

            for (i = 0; i < size; i += 1) {
                x = i % width;
                y = (i / width) | 0;
                if (self.isInArenaRange(i, width, height) === false) { data[i] += perlin.noise(x / quality, y / quality, z) * quality; }
            }
            quality *= 5;
        }
        for (i = 0; i < size; i += 1) {
            if (self.isInBorderRange(i, width, height, 0) && data[i] !== data[i - 1]) { value = self.returnSmootheringDiff(data[i], data[i - 1]); self.nxSmoothering(data, i - 1, value, width); }
            if (self.isInBorderRange(i, width, height, 1) && data[i] !== data[i + 1]) { value = self.returnSmootheringDiff(data[i], data[i + 1]); self.pxSmoothering(data, i + 1, value, width); }
            if (self.isInBorderRange(i, width, height, 2) && data[i] !== data[i - width]) { value = self.returnSmootheringDiff(data[i], data[i - width]); self.nySmoothering(data, i - width, value, width, height); }
            if (self.isInBorderRange(i, width, height, 3) && data[i] !== data[i + width]) { value = self.returnSmootheringDiff(data[i], data[i + width]); self.pySmoothering(data, i + width, value, width, height); }
            if (self.isInBorderRange(i, width, height, 4)) {value = self.returnSmootheringDiff(data[i], data[i - width - 1]); self.cnSmoothering(data, i - width - 1, value, width, height); }
        }
        return data;
    };

    this.getY = function (x, y, width) {
        return (self.heightMap[x + y * width] * 0.2) | 0;
    };

    this.isInGraphicArenaRange = function (worldWidth, worldDepth, x, z) {
        if (
            x - worldWidth / 2 + self.mapWidth / 2 >= 0 &&
                x - worldWidth / 2 + self.mapWidth / 2 <= self.mapWidth - (1 - self.mapWidth % 2) &&
                z - worldDepth / 2 + self.mapHeight / 2 >= 0 &&
                z - worldWidth / 2 + self.mapHeight / 2 <= self.mapHeight - (1 - self.mapHeight % 2)
        ) {return true; }
        return false;

    };

    this.generateTree = function (worldWidth, worldDepth) {
        var matrix = new THREE.Matrix4(),
            leafGeometry = new THREE.Geometry(),
            trunkGeometry = new THREE.Geometry(),
            leaf = new THREE.CylinderGeometry(0, 3, 8, 32, 16),
            trunk = new THREE.CylinderGeometry(1, 1, 3, 32, 16),
            leafMaterial = Factory.prefabMaterials[PREFAB_MATERIAL.GROUND],
            trunkMaterial = Factory.prefabMaterials[PREFAB_MATERIAL.FOOD],
            leavesMesh,
            trunksMesh,
            x = 0,
            y = 0,
            z = 0,
            i,
            position = 0;

        for (i = 0; i < 10; i += 1) {
            x += (worldWidth / 20) | 0;
            z += (worldDepth / 20) | 0;
            if (self.isInGraphicArenaRange(worldWidth, worldDepth, x, z) === false) {
                y = self.getY(x, z, worldWidth);
                matrix.makeTranslation(x - worldWidth / 2 + self.mapWidth / 2 - (self.mapWidth % 2) / 2, y + 6,  z - worldDepth / 2 + self.mapHeight / 2 - (self.mapHeight % 2) / 2);
                leafGeometry.merge(leaf, matrix);
                matrix.makeTranslation(x - worldWidth / 2 + self.mapWidth / 2 - (self.mapWidth % 2) / 2, y + 2,  z - worldDepth / 2 + self.mapHeight / 2 - (self.mapHeight % 2) / 2);
                trunkGeometry.merge(trunk, matrix);
                leavesMesh = new THREE.Mesh(leafGeometry, leafMaterial);
            }
        }
        trunksMesh = new THREE.Mesh(trunkGeometry, trunkMaterial);
        self.videoContext.scene.add(leavesMesh);
        self.videoContext.scene.add(trunksMesh);
        /*
        matrix.makeTranslation(25, 18, 25);
        var tree = new THREE.CylinderGeometry(0, 3, 8, 64, 32);
        test.merge(tree, matrix);
        matrix.makeTranslation(25, 14, 25);
        var trunk = new THREE.CylinderGeometry(1, 1, 3, 64, 32);
        test.merge(trunk, matrix);
        var treemesh = new THREE.Mesh(test, Factory.prefabMaterials[PREFAB_MATERIAL.GROUND]);
        self.videoContext.scene.add(treemesh);
*/

    };

    this.generateRandomMap = function (worldWidth, worldDepth) {
        var matrix = new THREE.Matrix4(), pxGeometry = new THREE.PlaneTypedGeometry(1, 1),
            nxGeometry = new THREE.PlaneTypedGeometry(1, 1), pyGeometry = new THREE.PlaneTypedGeometry(1, 1),
            pzGeometry = new THREE.PlaneTypedGeometry(1, 1), nzGeometry = new THREE.PlaneTypedGeometry(1, 1),
            geometry = new THREE.TypedGeometry(worldWidth * worldDepth * 2 * 5), texture, mesh,
            x, h, z, px, nx, pz, nz;

        pxGeometry.uvs[1] = 0.5;
        pxGeometry.uvs[3] = 0.5;
        pxGeometry.applyMatrix(matrix.makeRotationY(Math.PI / 2));
        pxGeometry.applyMatrix(matrix.makeTranslation(0.5, 0, 0));

        nxGeometry.uvs[1] = 0.5;
        nxGeometry.uvs[3] = 0.5;
        nxGeometry.applyMatrix(matrix.makeRotationY(-Math.PI / 2));
        nxGeometry.applyMatrix(matrix.makeTranslation(-0.5, 0, 0));

        pyGeometry.uvs[5] = 0.5;
        pyGeometry.uvs[7] = 0.5;
        pyGeometry.applyMatrix(matrix.makeRotationX(-Math.PI / 2));
        pyGeometry.applyMatrix(matrix.makeTranslation(0, 0.5, 0));

        pzGeometry.uvs[1] = 0.5;
        pzGeometry.uvs[3] = 0.5;
        pzGeometry.applyMatrix(matrix.makeTranslation(0, 0, 0.5));

        nzGeometry.uvs[1] = 0.5;
        nzGeometry.uvs[3] = 0.5;
        nzGeometry.applyMatrix(matrix.makeRotationY(Math.PI));
        nzGeometry.applyMatrix(matrix.makeTranslation(0, 0, -0.5));

        for (z = 0; z < worldDepth; z += 1) {
            for (x = 0; x < worldWidth; x += 1) {
                if (self.isInGraphicArenaRange(worldWidth, worldDepth, x, z) === false) {
                    h = Math.abs(self.getY(x, z, worldWidth)) + 1;
                    matrix.makeTranslation(x - worldWidth / 2 + self.mapWidth / 2 - (self.mapWidth % 2) / 2, h - 0.5, z - worldDepth / 2 + self.mapHeight / 2 - (self.mapHeight % 2) / 2);
                    px = self.getY(x + 1, z, worldWidth);
                    nx = self.getY(x - 1, z, worldWidth);
                    pz = self.getY(x, z + 1, worldWidth);
                    nz = self.getY(x, z - 1, worldWidth);
                    geometry.merge(pyGeometry, matrix);
                }
                if ((px !== h && px !== h + 1) || (x === 0)) { geometry.merge(pxGeometry, matrix); }
                if ((nx !== h && px !== h + 1) || (x === worldWidth - 1)) { geometry.merge(nxGeometry, matrix); }
                if ((pz !== h && pz !== h + 1) || (z === 0)) { geometry.merge(pzGeometry, matrix); }
                if ((nz !== h && nz !== h + 1) || (z === worldDepth - 1)) { geometry.merge(nzGeometry, matrix); }
            }
        }
        geometry.computeBoundingSphere();
        texture = new THREE.ImageUtils.loadTexture('ressources/images/textures/walldecors.png');
        texture.magFilter = THREE.NearestFilter;
        texture.minFilter = THREE.LinearMipMapLinearFilter;
        texture.wrapS = THREE.ClampToEdgeWrapping;
        texture.wrapT = THREE.ClampToEdgeWrapping;
        self.decors = new THREE.Mesh(geometry, new THREE.MeshLambertMaterial({map: texture, side: THREE.FrontSide}));
        self.videoContext.scene.add(self.decors);
/*
        self.generateTree(worldWidth, worldDepth);
*/
    };

    this.animateStone = function (x, y) {
        var i;
        for (i = 0; i < this.stones[y * this.mapWidth + x].length; i += 1) {
            this.stones[y * this.mapWidth + x][i].mesh.position.y += 0.001 * Math.random();
            this.stones[y * this.mapWidth + x][i].mesh.rotation.x += 0.01 * (i + 1);
            this.stones[y * this.mapWidth + x][i].mesh.rotation.z += 0.01 * (7 - i);
            this.stones[y * this.mapWidth + x][i].orbitAround(x, this.stones[y * this.mapWidth + x][i].mesh.position.y, y);
        }
    };

    this.addAnimatedObjects =  function () {
        o = new Effect(videoContext, this.map[15], {load: 1580, period: 0.5});
    };


    this.update = function () {
        var i, guiX = this.gui.settings.targetX, guiY = this.gui.settings.targetY;
        if (this.gui.settings.applyEffect === false) {
            for (i = 0; i < 6; i += 1) {
                this.stones[guiX * this.mapWidth + guiY][i].retrieveInitialPosition();
            }
        } else {this.animateStone(guiX, guiY); }


        if (this.gridWitness === false && this.gui.settings.grid === true) {
            this.videoContext.scene.add(this.gridHelper);
            this.gridWitness = true;
        } else if (this.gridWitness === true && this.gui.settings.grid === false) {
            this.videoContext.scene.remove(this.gridHelper);
            this.gridWitness = false;
        }
        EGG.rotation.y += 0.01;
        o.update();

    };

    this.render = function () {
        if (this.guiReady === true) {this.update(); }
        if (Math.abs(self.selector.rotation.y) > 0.20) {
            selectorRot *= -1;
        }
        self.selector.rotation.y += selectorRot;
        this.videoContext.render();
        this.videoContext.update();
    };
};