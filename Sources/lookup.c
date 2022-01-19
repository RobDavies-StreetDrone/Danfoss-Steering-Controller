#include "PE_types.h"

uint16_t lookup_u16_u16(uint16_t X_value, volatile const uint16_t * p_X_axis, volatile const uint16_t * p_Y_axis, uint16_t breakpoints)
{
	uint16_t breakpoint, breakpoint_next, difference;

	if(0 == breakpoints) return(0);

	breakpoint = breakpoints - 1;

	if(X_value >= p_X_axis[breakpoint])
	{
		return(p_Y_axis[breakpoint]);
	}
	else if(X_value <= p_X_axis[0])
	{
		return(p_Y_axis[0]);
	}
	else
	{
		while(p_X_axis[breakpoint - 1] > X_value)
		{
			breakpoint--;
		}

		breakpoint_next = breakpoint - 1;
		
		difference = (uint16_t)((0xFFFFUL * (uint32_t)(X_value - p_X_axis[breakpoint_next])) / (uint32_t)(p_X_axis[breakpoint] - p_X_axis[breakpoint_next]) + 1);
		
		if(p_Y_axis[breakpoint_next] < p_Y_axis[breakpoint])
		{
			return((uint16_t)((((uint32_t)difference * (uint32_t)(p_Y_axis[breakpoint] - p_Y_axis[breakpoint_next])) / 0xFFFFUL) + p_Y_axis[breakpoint_next]));
		}
		else
		{
			return(p_Y_axis[breakpoint_next] - (uint16_t)(((uint32_t)difference * (uint32_t)(p_Y_axis[breakpoint_next] - p_Y_axis[breakpoint])) / 0xFFFFUL));
		}		
	}
}


int16_t lookup_u16_s16(uint16_t X_value, volatile const uint16_t * p_X_axis, volatile const int16_t * p_Y_axis, uint16_t breakpoints)
{
	uint16_t breakpoint, breakpoint_next, difference;

	if(0 == breakpoints) return(0);	// protection

	breakpoint = breakpoints - 1;	// start at the top, m_Site must be >=1

	if(X_value >= p_X_axis[breakpoint])	// overflow shortcut
	{
		return(p_Y_axis[breakpoint]);
	}
	else if(X_value <= p_X_axis[0])	// underflow shortcut
	{
		return(p_Y_axis[0]);
	}
	else
	{
		while(p_X_axis[breakpoint - 1] > X_value)
		{
			breakpoint--;
		}

		breakpoint_next = breakpoint - 1;

		difference = (int16_t)((0x7FFFL * (uint32_t)(X_value - p_X_axis[breakpoint_next])) / (uint32_t)(p_X_axis[breakpoint] - p_X_axis[breakpoint_next]) + 1);

		return((int16_t)((((int32_t)difference * (int32_t)(p_Y_axis[breakpoint] - p_Y_axis[breakpoint_next])) / 0x7FFFL) + p_Y_axis[breakpoint_next]));
	}
}


int16_t lookup_s16_s16(int16_t X_value, volatile const int16_t * p_X_axis, volatile const int16_t * p_Y_axis, uint16_t breakpoints)
{
	int16_t difference;
	uint16_t breakpoint, breakpoint_next;

	if(0 == breakpoints) return(0);

	breakpoint = breakpoints - 1;

	if(X_value >= p_X_axis[breakpoint])
	{
		return(p_Y_axis[breakpoint]);
	}
	else if(X_value <= p_X_axis[0])
	{
		return(p_Y_axis[0]);
	}
	else
	{
		while(p_X_axis[breakpoint - 1] > X_value)
		{
			breakpoint--;
		}

		breakpoint_next = breakpoint - 1;

		difference = (int16_t)((0x7FFFL * (uint32_t)(X_value - p_X_axis[breakpoint_next])) / (uint32_t)(p_X_axis[breakpoint] - p_X_axis[breakpoint_next]) + 1);

		return((int16_t)((((int32_t)difference * (int32_t)(p_Y_axis[breakpoint] - p_Y_axis[breakpoint_next])) / 0x7FFFL) + p_Y_axis[breakpoint_next]));
	}
}
