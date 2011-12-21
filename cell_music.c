#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>


void fill_functions(int (*default_function)(int , int) , int num_functions , int (**functions)(int , int))
{
	int i;
	for(i = 0; i < num_functions; i++)
	{
		functions[i] = default_function;
	}
}

uint8_t perform_evolution(uint8_t curr_state , int radius , int (**functions)(int , int))
{
	int size = sizeof(curr_state) * 8;

	uint8_t new_state = 0;

	int i;
	for(i = 0; i < size; i ++)
	{
		int bits = 0; 

		int j;
		for(j = radius * -1; j <= radius; j ++)
		{
			int curr_index = i + j;

			if(curr_index < 0)
			{
				curr_index = size + curr_index;
			}
			else if(curr_index > size)
			{
				curr_index = curr_index - size;
			}

			int power = j + radius;

			bits = ((curr_state >> curr_index) & 1) << power;
		
		}

		printf("%d" , bits);

		int new_bit = functions[bits](bits , radius);
		
		new_state |= new_bit << i;
	}

	printf("\n");
}

int rule_150(int state_bits , int bits_size)
{
	int ret = 0;

	int i;
	for(i = 0; i < bits_size; i ++)
	{
		ret += state_bits >> i;
	}

	ret %= 2;

	return ret;
}

int main(int argc , char * argv[])
{
	int generations = 44000 * 30;

	int radius = 1;

	int num_states = 1 << (2 * radius + 1);

	int (**functions)(int , int)  = malloc(sizeof(int(*)(int , int)) * num_states);
	int (*default_function)(int , int) = rule_150;

	fill_functions(default_function , num_states , functions);

	uint8_t initial_state = 0x01;
	uint8_t curr_state = initial_state;

	int i;
	for(i = 0; i < generations; i++)
	{
		curr_state = perform_evolution(curr_state , radius , functions);
		printf("\n%d\n" , curr_state);
	}
}
