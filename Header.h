#include<stdio.h>
#include<stdlib.h>
#include<string.h>
char opcodes[17][10] = { "MOV", "MOV", "ADD", "SUB", "MUL", "JUMP", "IF", "EQ", "LT", "GT", "LTEQ", "GTEQ", "PRINT", "READ", "ENDIF", "ELSE","LABEL" };
void * memory = malloc(800);
FILE *f,*sf,*m,*metadata;
struct intermediatelang
{
	int inno;
	int opcode;
	int parameters[6];
	int len;
};
struct label
{
	char *name;
	int add;
};
struct label lbl[10];
int lblind = 0;
int stack[10];
int top = -1;
int inno = 0,nsym=0;
void push(int n)
{
	stack[++top] = n;
}
int pop()
{
	int t = stack[top];
	top--;
	return t;
}
int add = 0, ind = 0;
struct symboltable
{
	char sym;
	int add;
	int size;
};
struct symboltable st[10];
int getopcode(char *key)
{
	for (int i = 0; i < 16; i++)
	{
		if (strcmp(key, opcodes[i]) == 0)
			return i + 1;
	}
	if (key[strlen(key) - 1] == ':')
		return 17;
	return -1;
}
int findsymsize(char *sym)
{
	int val = 0, i = 0;
	if (strlen(sym) != 1)
	{
		sym += 2;
		while (sym[i] != ']')
		{
			val = val * 10 + (sym[i] - '0');
			i++;
		}
		return val;
	}
	return 1;
}
int getparamno(char *param)
{
	
	if (strcmp(param, "AX") == 0)
		return 0;
	if (strcmp(param, "BX") == 0)
		return 1;
	if (strcmp(param, "CX") == 0)
		return 2;
	if (strcmp(param, "DX") == 0)
		return 3;
	if (strcmp(param, "EX") == 0)
		return 4;
	if (strcmp(param, "FX") == 0)
		return 5;
	if (strcmp(param, "GX") == 0)
		return 6;
	if (strcmp(param, "HX") == 0)
		return 7;
	for (int i = 0; i < ind; i++)
	{
		if (param[0] == st[i].sym && strlen(param)==1)
			return st[i].add;
	}
	if (param[strlen(param) - 1] == ']')
	{
		for (int i = 0; i < ind; i++)
		{
			if (param[0] == st[i].sym)
			{
				int offset=0,j=0;
				param += 2;
				while (param[j] != ']')
					offset = offset * 10 + param[j++] - '0';
				return st[i].add + offset;
			}
		}
	}
	return -1;
}
void display(intermediatelang il[])
{
	fprintf(metadata, "%d ", inno);
	for (int i = 0; i < inno; i++)
	{
		printf("%d    %d    ", il[i].inno, il[i].opcode);
		fprintf(f, "%d %d ", il[i].inno, il[i].opcode);
		for (int j = 0; j < il[i].len; j++)
		{
			printf("%d ", il[i].parameters[j]);
			fprintf(f, "%d ", il[i].parameters[j]);
		}
		fprintf(metadata, "%d ", il[i].len);
		
		printf("\n");
		fprintf(f, "\n");
	}
	fprintf(metadata, "%d ", nsym);
	fprintf(metadata, "%d ", lblind);
	for (int i = 0; i < lblind; i++)
		fprintf(metadata, "%d %s ", (lbl[i].add)-1, lbl[i].name);
	fclose(metadata);
	fclose(f);
}
void displaysymboltable()
{
	for (int i = 0; i < ind; i++)
	{
		printf("%c    %d    %d\n", st[i].sym, st[i].add, st[i].size);
		fprintf(sf,"%c %d %d\n", st[i].sym, st[i].add, st[i].size);
	}
	fclose(sf);
}
int lab_add(char *lab)
{
	//lab[strlen(lab) - 1] = '\0';
	for (int i = 0; i < lblind; i++)
	{
		
		if (strcmp(lbl[i].name, lab) == 0)
			return lbl[i].add;
	}
	return -1;
}