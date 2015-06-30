/*global THREE*/
/*global VideoContext, GeometryFactory*/
/*global SHAPE, LIGHT_SHAPE, MATERIAL, PREFAB_MATERIAL, TEXTURE, cubeGeom*/
/*jslint browser: true*/

var Factory = new GeometryFactory(),
    checkerTexture = new THREE.ImageUtils.loadTexture('ressources/images/textures/checkerboard.jpg'),
    CubeMaterial = new THREE.MeshLambertMaterial({map: Factory.textures['checkerboard.jpg'], side: THREE.DoubleSide});

var GameObject = function (shape, material, texture, shapeParameters) {
    'use strict';
    var self = this;

    this.texture = null;
    this.type = material;
    this.material = null;
    this.geometry = null;
    this.mesh = null;
    this.tango = 0.25;


    /* In case of construction of a new shape : /!\ Pretty heavy if done numerous time : send for any of the objects a new set of vertices*/
    if (shape < 12) {
    /* Handle numerous cases of arguments for the geometry */
        if (typeof shapeParameters !== 'object') { this.geometry = new Factory.shapes[shape](1, 1, 1);
            } else if (shapeParameters[0] === 2) { this.geometry = new Factory.shapes[shape](shapeParameters[1],
            shapeParameters[2]);
            } else if (shapeParameters[0] === 3) { this.geometry = new Factory.shapes[shape](shapeParameters[1],
            shapeParameters[2], shapeParameters[3]);
            } else if (shapeParameters[0] === 4) { this.geometry = new Factory.shapes[shape](shapeParameters[1],
            shapeParameters[2], shapeParameters[3], shapeParameters[4]);
            } else if (shapeParameters[0] === 5) { this.geometry = new Factory.shapes[shape](shapeParameters[1],
            shapeParameters[2], shapeParameters[3], shapeParameters[4], shapeParameters[5]);
            } else if (shapeParameters[0] === 6) { this.geometry = new Factory.shapes[shape](shapeParameters[1],
            shapeParameters[2], shapeParameters[3], shapeParameters[4], shapeParameters[5], shapeParameters[6]);
            } else if (shapeParameters[0] === 7) { this.geometry = new Factory.shapes[shape](shapeParameters[1],
            shapeParameters[2], shapeParameters[3], shapeParameters[4], shapeParameters[5], shapeParameters[6],
            shapeParameters[7]);
            } else if (shapeParameters[0] === 8) { this.geometry = new Factory.shapes[shape](shapeParameters[1],
            shapeParameters[2], shapeParameters[3], shapeParameters[4], shapeParameters[5], shapeParameters[6],
            shapeParameters[7], shapeParameters[8]);
            }
        /* In case of use of pre-defined shapes : much lighter than build a new one */
    } else {this.geometry = Factory.preparedShapes[shape]; }

    /* Wether or not a texture is to be set */
    this.material = Factory.prefabMaterials[material];
    this.mesh = new THREE.Mesh(this.geometry, this.material);

    /* To be called in order to add a material to an object */
    this.setMultiMaterial = function (nbMaterials, materials) {
        var i, multiMaterial = [], currentMaterial;
        for (i = 0; i < nbMaterials; i += 1) {
            currentMaterial = new Factory.materials[materials[i].type](
                {
                    color: materials[i].color,
                    wireframe: materials[i].wireframe,
                    transparent: materials[i].transparent
                }
            );
            multiMaterial[i] = currentMaterial;
        }
        this.mesh = new THREE.SceneUtils.createMultiMaterialObject(this.geometry, multiMaterial);
    };


    this.setInitialPosition = function (x, y, z) {
        this.initialPosition = new THREE.Vector3();
        this.initialPosition.x = this.mesh.position.x;
        this.initialPosition.y = this.mesh.position.y;
        this.initialPosition.z = this.mesh.position.z;
    };

    this.setRadius = function (x, y, z) {
        this.radius = new THREE.Vector3();
        this.radius.x = this.mesh.position.x - x;
        this.radius.y = this.mesh.position.y - y;
        this.radius.z = this.mesh.position.z - z;
    };

    this.setSpecific = function (x, y, z) {
        this.setInitialPosition(x, y, z);
        this.setRadius(x, y, z);
    };

    this.orbitAround = function (x, y, z) {
        this.mesh.position.x = x + this.radius.x * Math.sin(this.mesh.rotation.x) * Math.cos(this.mesh.rotation.z);
        this.mesh.position.z = z + this.radius.z * Math.sin(this.mesh.rotation.z) * Math.sin(this.mesh.rotation.x);
    };

    this.retrieveInitialPosition = function () {
        var check = [false, false, false];
        if (Math.round(this.mesh.position.x * 100) / 100 === Math.round(this.initialPosition.x * 100) / 100) { check[0] = true;
            } else { this.mesh.position.x += (this.initialPosition.x - this.mesh.position.x) / 100; }
        if (Math.round(this.mesh.position.y * 100) / 100 === Math.round(this.initialPosition.y * 100) / 100) { check[1] = true;
            } else { this.mesh.position.y += (this.initialPosition.y - this.mesh.position.y) / 100; }
        if (Math.round(this.mesh.position.z * 100) / 100 === Math.round(this.initialPosition.z * 100) / 100) { check[2] = true;
            } else { this.mesh.position.z += (this.initialPosition.z - this.mesh.position.z) / 100; }
        if (check[0] === true && check[1] === true && check[2] === true) { return true; } else { return false; }
    };

};