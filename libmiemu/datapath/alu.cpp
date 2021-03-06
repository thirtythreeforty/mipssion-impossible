#include "alu.h"

void ALU::signals_in(ALUOp op, uint16_t data1, uint16_t data2)
{
	//Copies
	_op = op;
	_data1 = data1;
	_data2 = data2;
}

void ALU::tick()
{
	//Everything
	switch (_op)
	{
	case ALUOp::Add:
		_output = _data1 + _data2;
		break;
	case ALUOp::Subtract:
		_output = _data1 - _data2;
		if (_data1 < _data2)
		{
			_cflag = 1;
		}
		else
		{
			_cflag = 0;
		}
		if (_output == 0)
		{
			_zflag = 1;
		}
		else 
		{
			_zflag = 0;
		}
		break;
	case ALUOp::ShiftLeft:
		_output = _data1 << _data2;
		break;
	case ALUOp::ShiftRight:
		_output = _data1 >> _data2;
		break;
	case ALUOp::And:
		_output = _data1 & _data2;
		break;
	case ALUOp::Or:
		_output = _data1 | _data2;
		break;
	case ALUOp::Xor:
		_output = _data1 ^ _data2;
		break;

	}
}

void ALU::tock()
{
}

uint16_t ALU::data_out()
{
	return _output;
}

bool ALU::z_out()
{
	return _zflag;
}

bool ALU::c_out()
{
	return _cflag;
}
