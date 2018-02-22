#include "stdafx.h"

Behaviour::Behaviour(){}

Behaviour::~Behaviour(){}

string Behaviour::Awake() {
	return "S_OK";
}

string Behaviour::Start() {
	return "S_OK";
}

string Behaviour::Update() {
	return "S_OK";
}