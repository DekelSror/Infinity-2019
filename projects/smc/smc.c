/*==============================================================================
State Machine - Calculator
Module
Dekel Sror
Review - Moti Zamir
RC 1
==============================================================================*/
#include <stdlib.h> /* strtod  */
#include <ctype.h>  /* isdigit */
#include <assert.h> /* assert  */


#include "useful.h" /* UNUSED  			  */
#include "stack.h"  /* stack_t, stack API */
#include "smc.h"


/* offsets in precedence lut, used to differentiate behaviour */
#define OFFSET_EVENTS (10)
#define OFFSET_ARITH_OPS (100)

/* constants */
#define NUM_ASCII_VALS (128)
#define CALC_STACK_SIZE (64)

/* unary and binary operators */
#define DUAL_OP(x) ((x == '+') ||  (x == '-'))

#define NUM_PEEK(sm) (*(double *)StackPeek(sm->out_stack))
#define OP_PEEK(sm) (*(char *)StackPeek(sm->op_stack))

/* types */
typedef enum states_e { NUM_OPEN_STATE, OP_CLOSE_STATE, ERROR_STATE } states_t;
typedef struct machine_s machine_t;
typedef double (*op_func_t)(double, double);

typedef enum event_e
{
	NUM = OFFSET_EVENTS, OPEN, OPERATOR, CLOSE, END
} event_t;

typedef union calc_word_u
{
	double num_word;
	char op_word;
} calc_word_t;

typedef struct token_s
{
	event_t event;
	calc_word_t data;
} token_t;

struct machine_s
{
	stack_t *op_stack;
	stack_t *out_stack;
	op_func_t *op_lut;
	int *precedence_lut;
	int state;
};

typedef int (*handle_t) (machine_t *sm, token_t token);
static machine_t SMCCreate(int initial_state, op_func_t *op_lut, int *precedence_lut);
static void SMCConfig(machine_t *sm);
static token_t Tokenize(const char **word, machine_t *sm);
static void Compute(machine_t *sm);

/* event handlers */
static int HandleClose(machine_t *sm, token_t token);
static int HandleOp(machine_t *sm, token_t token);
static int HandleOpen(machine_t *sm, token_t token);
static int HandleNum(machine_t *sm, token_t token);
static int HandleEnd(machine_t *sm, token_t token);
static int HandleErr(machine_t *sm, token_t token);

/* calculator functions */
static double CalcAdd(double elem_1, double elem_2);
static double CalcSub(double elem_1, double elem_2);
static double CalcMul(double elem_1, double elem_2);
static double CalcDiv(double elem_1, double elem_2);

static const handle_t calc_jump_table[3][5] =
{
	{ HandleNum, HandleOpen, HandleErr, HandleErr, HandleEnd },
	{ HandleErr,  HandleErr, HandleOp,  HandleClose, HandleEnd },
	{ HandleErr,  HandleErr, HandleErr, HandleErr, HandleErr }
};

double Calculate(const char *expression)
{
	static op_func_t calc_op_lut[NUM_ASCII_VALS] = { NULL };
	static int calc_precedence_lut[NUM_ASCII_VALS] = { 0 };
	static int done_config = 0;

	machine_t calc = SMCCreate(0, calc_op_lut, calc_precedence_lut);

	const char *tok_getter = expression;
	token_t token = { 0 };
	double result = 0.0;

	assert(expression);

	if (!done_config)
	{
		SMCConfig(&calc);
		done_config = 1;
	}

	while ((ERROR_STATE != calc.state) && (END != token.event))
	{
		token = Tokenize(&tok_getter, &calc);
		calc.state = calc_jump_table[calc.state]
						[token.event - OFFSET_EVENTS](&calc, token);
	}

	result = *(double *)StackPeek(calc.out_stack);

	StackDestroy(calc.out_stack);
	StackDestroy(calc.op_stack);

	return result;
}

static token_t Tokenize(const char **word, machine_t *sm)
{
	token_t new_token = { 0 };
	const char *op_detect = NULL;
	double num_tok = 0.0;

	assert(sm);
	assert(word);

	op_detect = *word;
	num_tok = strtod(*word, (char **)word);

/* catch '+' or '-' as binary operators */
	if (DUAL_OP(*op_detect) && isdigit(*(op_detect - 1)))
	{
		*word = op_detect;
	}

	if (op_detect == *word)
	{
		new_token.data.op_word = **word;

		if (OFFSET_ARITH_OPS < sm->precedence_lut[(int)**word])
		{
			new_token.event = OPERATOR;
		}
		else
		{
			new_token.event = sm->precedence_lut[(int)**word];
		}

		++*word;
	}
	else
	{
		new_token.data.num_word = num_tok;
		new_token.event = NUM;
	}

	return new_token;
}

/* initializers */
static machine_t SMCCreate(int initial_state, op_func_t *op_lut, int *precedence_lut)
{
	machine_t new_machine = { 0 };

	assert(op_lut);
	assert(precedence_lut);

	new_machine.out_stack = StackCreate(sizeof(double), CALC_STACK_SIZE);

	if (NULL == new_machine.out_stack)
	{
		return new_machine;
	}

	new_machine.op_stack = StackCreate(sizeof(char), CALC_STACK_SIZE);

	if (NULL == new_machine.op_stack)
	{
		return new_machine;
	}

	new_machine.op_lut = op_lut;
	new_machine.precedence_lut = precedence_lut;
	new_machine.state = initial_state;

	return new_machine;
}

static void SMCConfig(machine_t *sm)
{
	assert(sm);

	sm->op_lut['+'] = CalcAdd;
	sm->op_lut['-'] = CalcSub;
	sm->op_lut['*'] = CalcMul;
	sm->op_lut['/'] = CalcDiv;

	sm->precedence_lut['\0'] = END;
	sm->precedence_lut['('] = OPEN;
	sm->precedence_lut[')'] = CLOSE;
	sm->precedence_lut['+'] = 101;
	sm->precedence_lut['-'] = 101;
	sm->precedence_lut['*'] = 102;
	sm->precedence_lut['/'] = 102;
}

/* handlers */
static int HandleErr(machine_t *sm, token_t token)
{
	UNUSED(sm);
	UNUSED(token);

	return ERROR_STATE;
}

static void Compute(machine_t *sm)
{
	double elem_2 = 0.0;
	double elem_1 = 0.0;
	char operator = 0;

	assert(sm);

	operator = OP_PEEK(sm);
	StackPop(sm->op_stack);

	/* get elem_2 first to maintain commutativity */
	elem_2 = NUM_PEEK(sm);
	StackPop(sm->out_stack);
	elem_1 = NUM_PEEK(sm);
	StackPop(sm->out_stack);


	elem_1 = sm->op_lut[(int)operator](elem_1, elem_2);

	StackPush(sm->out_stack, &elem_1);
}

static int HandleEnd(machine_t *sm, token_t token)
{
	UNUSED(token);
	assert(sm);

	while (0 < StackSize(sm->op_stack) && 1 < StackSize(sm->out_stack))
	{
		Compute(sm);
	}

	return OP_CLOSE_STATE;
}

static int HandleNum(machine_t *sm, token_t token)
{
	assert(sm);

	StackPush(sm->out_stack, &token.data.num_word);

	return OP_CLOSE_STATE;
}

static int HandleOpen(machine_t *sm, token_t token)
{
	assert(sm);

	StackPush(sm->op_stack, &token.data.op_word);

	return NUM_OPEN_STATE;
}


static int HandleOp(machine_t *sm, token_t token)
{
	int tok_prec = 0;
	int peek_prec = 0;

	assert(sm);

	tok_prec = sm->precedence_lut[(int)token.data.op_word];

	if (StackSize(sm->op_stack) > 0)
	{
		peek_prec = sm->precedence_lut[(int)OP_PEEK(sm)];
	}

	/* maintain order of precedence */
	if (tok_prec <= peek_prec)
	{
		/* as long as op_stack has an arithmetic op, do */
		while
		(
			(0 < StackSize(sm->op_stack)) &&
			(sm->precedence_lut[(int)OP_PEEK(sm)] > OFFSET_ARITH_OPS)
		)
		{
			Compute(sm);
		}
	}

	StackPush(sm->op_stack, &token.data.op_word);

	return NUM_OPEN_STATE;
}

static int HandleClose(machine_t *sm, token_t token)
{
	UNUSED(token);
	assert(sm);

	while (0 < StackSize(sm->op_stack) && OP_PEEK(sm) != '(')
	{
		Compute(sm);
	}

	StackPop(sm->op_stack);

	return OP_CLOSE_STATE;
}

/* operator functions */
static double CalcAdd(double elem_1, double elem_2)
{
	return elem_1 + elem_2;
}
static double CalcSub(double elem_1, double elem_2)
{
	return elem_1 - elem_2;
}
static double CalcMul(double elem_1, double elem_2)
{
	return elem_1 * elem_2;
}
double CalcDiv(double elem_1, double elem_2)
{
	return elem_1 / elem_2;
}
