#include "State.h"
int CurrentState = 0;
int State::currentState()
{
	return state;
}

void State::NextState(int s)
{
	state = s;
}