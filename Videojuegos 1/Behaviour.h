#pragma once
#ifndef _Behaviour_H_
#define _Behaviour_H_

class Behaviour
{
public:
	Behaviour();
	~Behaviour();

	virtual string Awake();
	virtual string Start();
	virtual string Update();
};

#endif