/*
 * SlothInterpreter.cpp
 *
 *  Created on: Jul 7, 2018
 *      Author: gabriel
 */
#include <stddef.h>
#include <stdint.h>
#include "SlothInterpreter.hpp"



SlothInterpreter::SlothInterpreter()
{
	_kd = NULL;
	_ki = NULL;
	_kp = NULL;
	_start = NULL;
	_stop = NULL;
	_save = NULL;
}

void SlothInterpreter::command(sloth_cmd_t* cmd)
{
	switch(cmd->cmd)
	{
	case SLOTH_OPCODE_INC:
		increment(cmd->variable.var);
		break;
	case SLOTH_OPCODE_DEC:
		decrement(cmd->variable.var);
		break;
	case SLOTH_OPCODE_SET:
		set(cmd->variable.var, (cmd->variable.value/10000.0));
		break;
	case SLOTH_OPCODE_CONFIG:
		break;

	case SLOTH_OPCODE_SAVE:
		if(_save != NULL) _save();
		break;

	case SLOTH_OPCODE_START:
		if(_start != NULL)
		{
			_start();
		}
		break;

	case SLOTH_OPCODE_STOP:
		if(_stop != NULL)
		{
			_stop();
		}
		break;
	default:
		break;
	}
}

void SlothInterpreter::setKpPointer(float* kp)
{
	_kp = kp; //0.001
}

void SlothInterpreter::setKiPointer(float* ki)
{
	_ki = ki;
}

void SlothInterpreter::setKdPointer(float* kd)
{
	_kd = kd; // 0.0001
}

void SlothInterpreter::setStartCallback(void (*start)())
{
	_start = start;
}

void SlothInterpreter::setStopCallback(void (*stop)())
{
	_stop = stop;
}

void SlothInterpreter::setSaveCallback(void (*save)())
{
	_save = save;
}

float SlothInterpreter::getKp()
{
	if(_kp != NULL) return *_kp;
	else return 0;
}
float SlothInterpreter::getKi()
{
	if(_ki != NULL) return *_ki;
	else return 0;
}
float SlothInterpreter::getKd()
{
	if(_kd != NULL) return *_kd;
	else return 0;
}

void SlothInterpreter::set(sloth_ctrl_var_t var, float value)
{
	switch(var)
	{
		case SLOTH_VAR_KP:
			if(_kp != NULL) *_kp = value;
			break;
		case SLOTH_VAR_KI:
			if(_ki != NULL) *_ki = value;
			break;
		case SLOT_VAR_KD:
			if(_kd != NULL) *_kd = value;
			break;

		default:
			break;
	}
}




