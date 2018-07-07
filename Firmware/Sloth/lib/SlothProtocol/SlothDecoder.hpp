/*
 * SlothDecoder.cpp
 *
 *  Created on: Jul 7, 2018
 *      Author: gabriel
 */

#ifndef LIB_SLOTHPROTOCOL_SLOTHDECODER_CPP_
#define LIB_SLOTHPROTOCOL_SLOTHDECODER_CPP_

#include <stdint.h>
#include "../../Communication/sloth_protocol.h"

#include <Serial.h>

class SlothDecoder
{
public:
	SlothDecoder();

	bool pushByte(uint8_t byte);
	void cmdRxEventSubscribe(void (*callback)(sloth_cmd_t *));

	uint8_t* getCmdBuff();
	uint8_t getBuffSize();

private:
	void reset();
	uint8_t _currentSize;
	uint8_t _cmdBuffer[sizeof(sloth_cmd_t)];
	uint8_t _buffCounter;
	sloth_cmd_t _rxCommand;

	void (*_callback)(sloth_cmd_t*);

};



#endif /* LIB_SLOTHPROTOCOL_SLOTHDECODER_CPP_ */
