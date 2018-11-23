/*
 * SlothInterpreter.hpp
 *
 *  Created on: Jul 7, 2018
 *      Author: gabriel
 */

#ifndef LIB_SLOTHPROTOCOL_SLOTHINTERPRETER_HPP_
#define LIB_SLOTHPROTOCOL_SLOTHINTERPRETER_HPP_

#include "../../Communication/sloth_protocol.h"


class SlothInterpreter
{
public:
	SlothInterpreter();

	void command(sloth_cmd_t* cmd);
	void setKpPointer(float* kp);
	void setKiPointer(float* ki);
	void setKdPointer(float* kd);

	float getKp();
	float getKi();
	float getKd();

	void setStartCallback(void (*save)());
	void setSaveCallback(void (*start)());
	void setStopCallback(void (*stop)());

private:
	void increment(sloth_ctrl_var_t var) {
		switch (var) {
		case SLOTH_VAR_KP:
			if (_kp != NULL)
				*_kp += 0.001;
			break;
		case SLOTH_VAR_KI:
			if (_ki != NULL)
				*_ki += 0.000;
			break;
		case SLOT_VAR_KD:
			if (_kd != NULL)
				*_kd += 0.0001;
			break;

		default:
			break;
		}
	}
	void decrement(sloth_ctrl_var_t var) {
		switch (var) {
		case SLOTH_VAR_KP:
			if (_kp != NULL)
				*_kp -= 0.001;
			break;
		case SLOTH_VAR_KI:
			if (_ki != NULL)
				*_ki -= 0.000;
			break;
		case SLOT_VAR_KD:
			if (_kd != NULL)
				*_kd -= 0.0001;
			break;

		default:
			break;
		}
	}
	void set(sloth_ctrl_var_t var, float value);

	float* _kp;
	float* _ki;
	float* _kd;
	void (*_stop)();
	void (*_start)();
	void (*_save)();
};



#endif /* LIB_SLOTHPROTOCOL_SLOTHINTERPRETER_HPP_ */
