/*
 * SlothDecoder.cpp
 *
 *  Created on: Jul 7, 2018
 *      Author: gabriel
 */

#include "SlothDecoder.hpp"
#include <string.h>


SlothDecoder::SlothDecoder(/*mbed::Serial& serial*/)// : log(serial)
{
	_callback = NULL;
	_currentSize = 0;
	_buffCounter = 0;
}

bool SlothDecoder::pushByte(uint8_t byte)
{
	if(_currentSize == 0)
	{
		_currentSize = byte;

		if((_currentSize > (SLOTH_PROTOCOL_CMD_MAX_SIZE)))
		{
			reset();
			return false;
		}
		_buffCounter = 0;
//		log.printf(" new cmd | setting size to %d  \n" , byte);
	}
	else
	{
		if(_buffCounter < _currentSize)
		{
			_cmdBuffer[_buffCounter] = byte;
//			log.printf(" size = %d | buff: %d | Storing byte 0x%02X\n", _currentSize, _buffCounter, byte);
			_buffCounter++;

			if(_buffCounter == _currentSize)
			{
//				log.printf("!! cmd ack. Calling callback !! \n");
				memcpy(&_rxCommand, _cmdBuffer, _currentSize);

				if(_callback != NULL)
				{
					_callback(&_rxCommand);
				}
				reset();
			}
		}
	}
	return true;
}

uint8_t * SlothDecoder::getCmdBuff()
{
	return _cmdBuffer;
}

uint8_t SlothDecoder::getBuffSize()
{
	return _buffCounter;
}

void SlothDecoder::cmdRxEventSubscribe(void (*callback)(sloth_cmd_t *))
{
	_callback = callback;
}

void SlothDecoder::reset()
{
	_currentSize = 0;
	_buffCounter = 0;
}
