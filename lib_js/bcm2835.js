'use strict';

let native = require('native');

exports.LOW = 0;
exports.HIGH  = 1;
exports.INPUT = 0;
exports.OUTPUT = 1;
exports.PIN3 = 0;
exports.PIN5 = 1;
exports.PIN7 = 4;
exports.PIN8 = 14;
exports.PIN10 = 15;
exports.PIN11 = 17;
exports.PIN12 = 18;
exports.PIN13 = 21;
exports.PIN15 = 22;
exports.PIN16 = 23;
exports.PIN18 = 24;
exports.PIN19 = 10;
exports.PIN21 = 9;
exports.PIN22 = 25;
exports.PIN23 = 11;
exports.PIN24 = 8;
exports.PIN26 = 7;

exports.DIGITAL = 0;
exports.ANALOG = 1;

exports.INPUT_PULLUP = 1;
exports.INPUT_PULLDOWN = 2;

exports.init = native.bcm2835Init;
exports.close = native.bcm2835Close;
exports.setDebug = native.bcm2835SetDebug;
exports.gpioFsel = native.bcm2835GpioFsel;
exports.gpioSet = native.bcm2835GpioSet;
exports.gpioClr = native.bcm2835GpioClr;
exports.gpioLev = native.bcm2835GpioLev;
exports.delay = native.bcm2835GpioDelay;


