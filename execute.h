#include"Header.h"
int registers[8];
void execute(struct intermediatelang interlang[])
{
	int i = 0,ifflag=0;
	while (i<inno)
	{
		switch (interlang[i].opcode)
		{
		case 2:
			memcpy(&memory + interlang[i].parameters[0], &registers[interlang[i].parameters[1]],sizeof(int));
			i++;
			break;
		case 1:
			memcpy(&memory + interlang[i].parameters[1], &registers[interlang[i].parameters[0]], sizeof(int));
			i++;
			break;
		case 3:
			registers[interlang[i].parameters[0]] = registers[interlang[i].parameters[1]] + registers[interlang[i].parameters[2]];
			i++;
			break;
		case 4:
			registers[interlang[i].parameters[0]] = registers[interlang[i].parameters[1]] - registers[interlang[i].parameters[2]];
			i++;
			break;
		case 5:
			registers[interlang[i].parameters[0]] = registers[interlang[i].parameters[1]] * registers[interlang[i].parameters[2]];
			i++;
			break;
		case 6:
			i = interlang[i].parameters[0]-1;
			break;
		case 7:
			if (interlang[i].parameters[2] == 8)
			{
				if (registers[interlang[i].parameters[0]] == registers[interlang[i].parameters[1]])
				{
					ifflag = 1;
					i++;
				}
			else
				i = interlang[i].parameters[3]-1;
			}
			else if (interlang[i].parameters[2] == 9)
			{
				if (registers[interlang[i].parameters[0]] < registers[interlang[i].parameters[1]])
				{
					ifflag = 1;
					i++;
				}
				else
					i = interlang[i].parameters[3]-1;
			}
			else if (interlang[i].parameters[2] == 10)
			{
				if (registers[interlang[i].parameters[0]] > registers[interlang[i].parameters[1]])
				{
					ifflag = 1;
					i++;
				}
				else
					i = interlang[i].parameters[3]-1;
			}
			else if (interlang[i].parameters[2] == 11)
			{
				if (registers[interlang[i].parameters[0]] <= registers[interlang[i].parameters[1]])
				{
					ifflag = 1;
					i++;
				}
				else
					i = interlang[i].parameters[3]-1;
			}
			else if (interlang[i].parameters[2] == 12)
			{
				if (registers[interlang[i].parameters[0]] >= registers[interlang[i].parameters[1]])
				{
					ifflag = 1;
					i++;
				}
				else
					i = interlang[i].parameters[3]-1;
			}
			break;
		case 13:printf("%d ", registers[interlang[i].parameters[0]]);
			i++;
			break;
		case 14:scanf("%d", &registers[interlang[i].parameters[0]]);
			i++;
			break;
		case 16:
			if (ifflag == 1)
			{
				i = interlang[i].parameters[0] - 1;
			}
			else
			{
				ifflag = 0;
				i++;
			}
			break;
		default:i++;
		}
	}
}