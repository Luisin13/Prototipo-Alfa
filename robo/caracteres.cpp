#include "caracteres.hpp"
#include <Arduino.h>

byte setaEsquerda[8] = {
    0b00010,
    0b00110,
    0b01110,
    0b11111,
    0b11111,
    0b01110,
    0b00110,
    0b00010};

byte setaDireita[8] = {
    0b01000,
    0b01100,
    0b01110,
    0b11111,
    0b11111,
    0b01110,
    0b01100,
    0b01000};

byte setaFrente[8] = {
    0b00100,
    0b01110,
    0b11111,
    0b00100,
    0b00100,
    0b00100,
    0b00100,
    0b00000};

byte caudaEsquerda[8] = {
    0b00000,
    0b00000,
    0b00000,
    0b11110,
    0b11110,
    0b00000,
    0b00000,
    0b00000};

byte caudaDireita[8] = {
    0b00000,
    0b00000,
    0b00000,
    0b01111,
    0b01111,
    0b00000,
    0b00000,
    0b00000};

byte grausSimbolo[8] = {
    0b11100,
    0b10100,
    0b11100,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000};