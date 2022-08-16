#include "calc.h"

using namespace std;

const int num = 0;
const int X = 1;
const int Y = 2;
const int pluss = 3;
const int minuse = 4;
const int mul = 5;
const int divv = 6;
const int open = 7;
const int close = 8;
const int endd = 9;
const int sinus = 10;
const int cosinus = 11;
const int m_sinus = 12;
const int m_cosinus = 14;
const int function = 15;
const int st_minuse = 16;
const int power = 17;
const int tangent = 18;
const int m_tangent = 19;
const int cotangence = 20;
const int m_cotangence = 21;
const char digits[11] = "0123456789";

int cur_lex, cur_type;
double val, a, x = 0, y = 0, b;
char* str;
std::string s;
bool first_minuse = false;

class tree_node {
public:
	tree_node *left = NULL;
	tree_node *right = NULL;
	double number = 0;
	int type = 0;
	std::queue<int> function_type;
	bool minuse_var = false;
	bool minuse_st = false;
};
class operation {
public:
	double number = 0;
	int type = -1;
	bool minuse_value = false;
	double(*f)(double) = NULL;
};

std::vector<operation> V;
operation *op_null, *op_cur, *op_last;
std::stack<double> st;

bool is_digit(char);
void next_lexem();
tree_node * create_summand(tree_node *);
tree_node * create_expression(tree_node *);
void order(tree_node *);
double m_sin(double);
double m_cos(double);
double m_tan(double);
double ctan(double);
double m_ctan(double);
double get_minuse(double);

bool is_digit(char d) {
	for (int i = 0; i < 10; i++) {
		if (d == digits[i]) {
			return true;
		}
	}
	return false;
}
//переход к следующему символу выражения
void next_lexem() {
	if ((str == &s[0] && *str == '-') || (cur_lex == open && *str == '-')) {
		str++;
		if (*str == 's') {
			str++;
			if (*str == 'i') {
				str++;
				if (*str == 'n') {
					cur_lex = m_sinus;
				}
				else {
					str--; str--;
				}
			}
			else {
				str--;
			}
		}
		if (*str == 'c') {
			str++;
			if (*str == 'o') {
				str++;
				if (*str == 's') {
					cur_lex = m_cosinus;
				}
				else {
					str--; str--;
				}
			}
			else {
				str--;
			}
		}
		if (*str == 't') {
			str++;
			if (*str == 'g') {
				cur_lex = m_tangent;
			}
			else {
				str--;
			}
		}
		if (*str == 'c') {
			str++;
			if (*str == 't') {
				str++;
				if (*str == 'g') {
					cur_lex = m_cotangence;
				}
				else {
					str--; str--;
				}
			}
			else {
				str--;
			}
		}
		if (*str == '(') {
			cur_lex = st_minuse;
		}
		if (is_digit(*str)) {
			cur_lex = num;
			std::string number = "";
			while (is_digit(*str) || *str == '.') {
				number += *str;
				str++;
			}
			str--;
			val = -std::stod(number);
		}
		else if (*str == 'x') {
			cur_lex = X;
			first_minuse = true;
		}
		else if (*str == 'y') {
			cur_lex = Y;
			first_minuse = true;
		}
	}
	else if (*str == '(') {
		cur_lex = open;
	}
	else if (*str == 'x') {
		cur_lex = X;
	}
	else if (*str == 'y') {
		cur_lex = Y;
	}
	else if (*str == ')') {
		cur_lex = close;
	}
	else if (*str == '+') {
		cur_lex = pluss;
	}
	else if (*str == '-') {
		cur_lex = minuse;
	}
	else if (*str == '*') {
		cur_lex = mul;
	}
	else if (*str == '^') {
		cur_lex = power;
	}
	else if (*str == '/') {
		cur_lex = divv;
	}
	else if (*str == '\0') {
		cur_lex = endd;
	}
	else if (is_digit(*str)) {
		cur_lex = num;
		std::string number = "";
		while (is_digit(*str) || *str == '.') {
			number += *str;
			str++;
		}
		str--;
		val = std::stod(number);
	}
	if (*str == 's') {
		str++;
		if (*str == 'i') {
			str++;
			if (*str == 'n') {
				cur_lex = sinus;
			}
			else {
				str--; str--;
			}
		}
		else {
			str--;
		}
	}
	if (*str == 'c') {
		str++;
		if (*str == 'o') {
			str++;
			if (*str == 's') {
				cur_lex = cosinus;
			}
			else {
				str--; str--;
			}
		}
		else {
			str--;
		}
	}
	if (*str == 't') {
		str++;
		if (*str == 'g') {
			cur_lex = tangent;
		}
		else {
			str--;
		}
	}
	if (*str == 'c') {
		str++;
		if (*str == 't') {
			str++;
			if (*str == 'g') {
				cur_lex = cotangence;
			}
			else {
				str--; str--;
			}
		}
		else {
			str--;
		}
	}
	str++;
}
//создать слагаемое
tree_node * create_summand(tree_node *left_mul) {
	tree_node *node = new tree_node;
	node->type = cur_lex;

	//==============================
	if (cur_lex == sinus) {
		next_lexem();
		next_lexem();
		tree_node *null_node = new tree_node;
		node = create_expression(null_node);
		node->function_type.push(sinus);
	}
	else if (cur_lex == cosinus) {
		next_lexem();
		next_lexem();
		tree_node *null_node = new tree_node;
		node = create_expression(null_node);
		node->function_type.push(cosinus);
	}
	else if (cur_lex == tangent) {
		next_lexem();
		next_lexem();
		tree_node *null_node = new tree_node;
		node = create_expression(null_node);
		node->function_type.push(tangent);
	}
	else if (cur_lex == cotangence) {
		next_lexem();
		next_lexem();
		tree_node *null_node = new tree_node;
		node = create_expression(null_node);
		node->function_type.push(cotangence);
	}
	else if (cur_lex == m_sinus) {
		next_lexem();
		next_lexem();
		tree_node *null_node = new tree_node;
		node = create_expression(null_node);
		node->function_type.push(m_sinus);
	}
	else if (cur_lex == m_cosinus) {
		next_lexem();
		next_lexem();
		tree_node *null_node = new tree_node;
		node = create_expression(null_node);
		node->function_type.push(m_cosinus);
	}
	else if (cur_lex == m_tangent) {
		next_lexem();
		next_lexem();
		tree_node *null_node = new tree_node;
		node = create_expression(null_node);
		node->function_type.push(m_tangent);
	}
	else if (cur_lex == m_cotangence) {
		next_lexem();
		next_lexem();
		tree_node *null_node = new tree_node;
		node = create_expression(null_node);
		node->function_type.push(m_cotangence);
	}
	else if (cur_lex == st_minuse) {
		next_lexem();
		tree_node *null_node = new tree_node;
		node = create_expression(null_node);
		node->function_type.push(st_minuse);
	}
	//==============================

	if (cur_lex == open) {
		next_lexem();
		tree_node *null_node = new tree_node;
		node = create_expression(null_node);
	}
	else if (cur_lex == num) {
		node->number = val;
	}
	else if (first_minuse) {
		node->minuse_var = first_minuse;
		first_minuse = false;
	}
	else if (cur_lex == mul || cur_lex == divv || cur_lex == power) {
		node->left = left_mul;
		next_lexem();
		tree_node *right_node = new tree_node;
		node->right = right_node;
		node->right->type = cur_lex;

		//==============================
		if (cur_lex == sinus) {
			next_lexem();
			next_lexem();
			tree_node *null_node = new tree_node;
			node->right = create_expression(null_node);
			node->right->function_type.push(sinus);
		}
		else if (cur_lex == cosinus) {
			next_lexem();
			next_lexem();
			tree_node *null_node = new tree_node;
			node->right = create_expression(null_node);
			node->right->function_type.push(cosinus);
		}
		else if (cur_lex == tangent) {
			next_lexem();
			next_lexem();
			tree_node *null_node = new tree_node;
			node->right = create_expression(null_node);
			node->right->function_type.push(tangent);
		}
		else if (cur_lex == cotangence) {
			next_lexem();
			next_lexem();
			tree_node *null_node = new tree_node;
			node->right = create_expression(null_node);
			node->right->function_type.push(cotangence);
		}
		//==============================

		if (cur_lex == open) {
			next_lexem();
			tree_node *null_node = new tree_node;
			node->right = create_expression(null_node);
		}
		else {
			node->right->number = val;
		}
	}
	next_lexem();
	if (cur_lex != pluss && cur_lex != minuse && cur_lex != close && cur_lex != endd) {
		tree_node *left = node;
		node = create_summand(left);
	}

	return node;
}

//создать выражение
tree_node * create_expression(tree_node *left_summand) {
	tree_node *node = new tree_node;
	tree_node *null_node = new tree_node;
	if (cur_lex == pluss || cur_lex == minuse) {
		node->type = cur_lex;
		node->left = left_summand;
		next_lexem();
		tree_node *right_node = new tree_node;
		right_node = create_summand(null_node);
		node->right = right_node;
	}
	else if (cur_lex != close && cur_lex != endd) {
		node = create_summand(null_node);
	}
	if (cur_lex == pluss || cur_lex == minuse) {
		tree_node *left = node;
		node = create_expression(left);
	}
	return node;
}
//перевод из дерева в обратную польскую запись
void order(tree_node *node) {
	if (node->left) {
		order(node->left);
	}
	else {
		operation oper;
		oper.number = node->number;
		oper.type = node->type;
		oper.minuse_value = node->minuse_var;
		V.push_back(oper);
		//===================
		while (node->function_type.size()) {
			int t = node->function_type.front();
			if (t == sinus) {
				operation oper;
				oper.type = function;
				oper.f = sin;
				V.push_back(oper);
			}
			else if (t == cosinus) {
				operation oper;
				oper.type = function;
				oper.f = cos;
				V.push_back(oper);
			}
			else if (t == tangent) {
				operation oper;
				oper.type = function;
				oper.f = tan;
				V.push_back(oper);
			}
			else if (t == cotangence) {
				operation oper;
				oper.type = function;
				oper.f = ctan;
				V.push_back(oper);
			}
			else if (t == m_sinus) {
				operation oper;
				oper.type = function;
				oper.f = m_sin;
				V.push_back(oper);
			}
			else if (t == m_cosinus) {
				operation oper;
				oper.type = function;
				oper.f = m_cos;
				V.push_back(oper);
			}
			else if (t == m_tangent) {
				operation oper;
				oper.type = function;
				oper.f = m_tan;
				V.push_back(oper);
			}
			else if (t == m_cotangence) {
				operation oper;
				oper.type = function;
				oper.f = m_ctan;
				V.push_back(oper);
			}
			else if (t == st_minuse) {
				operation oper;
				oper.type = function;
				oper.f = get_minuse;
				V.push_back(oper);
			}
			node->function_type.pop();
		}
		//===================
		return;
	}
	order(node->right);
	operation oper;
	oper.number = node->number;
	oper.type = node->type;
	oper.minuse_value = node->minuse_var;
	V.push_back(oper);
	//===================
	while (node->function_type.size()) {
		int t = node->function_type.front();
		if (t == sinus) {
			operation oper;
			oper.type = function;
			oper.f = sin;
			V.push_back(oper);
		}
		else if (t == cosinus) {
			operation oper;
			oper.type = function;
			oper.f = cos;
			V.push_back(oper);
		}
		else if (t == tangent) {
			operation oper;
			oper.type = function;
			oper.f = tan;
			V.push_back(oper);
		}
		else if (t == cotangence) {
			operation oper;
			oper.type = function;
			oper.f = ctan;
			V.push_back(oper);
		}
		else if (t == m_sinus) {
			operation oper;
			oper.type = function;
			oper.f = m_sin;
			V.push_back(oper);
		}
		else if (t == m_cosinus) {
			operation oper;
			oper.type = function;
			oper.f = m_cos;
			V.push_back(oper);
		}
		else if (t == m_tangent) {
			operation oper;
			oper.type = function;
			oper.f = m_tan;
			V.push_back(oper);
		}
		else if (t == m_cotangence) {
			operation oper;
			oper.type = function;
			oper.f = m_ctan;
			V.push_back(oper);
		}
		else if (t == st_minuse) {
			operation oper;
			oper.type = function;
			oper.f = get_minuse;
			V.push_back(oper);
		}
		node->function_type.pop();
	}
	//===================
}
//алгоритм стекового калькулятора
double calculate() {
	op_cur = op_null;
	while (op_cur != op_last) {
		cur_type = op_cur->type;
		if (cur_type == num) {
			a = op_cur->number;
			
			st.push(a);
		}
		else if (cur_type == X) {
			a = op_cur->minuse_value ? -x : x;
			
			st.push(a);
		}
		else if (cur_type == Y) {
			a = op_cur->minuse_value ? -y : y;
			
			st.push(a);
		}
		else if (cur_type == pluss) {
			
			b = st.top();
			st.pop();

			a = st.top();
			st.pop();

			a = a + b;

			st.push(a);
		}
		else if (cur_type == minuse) {
			b = st.top();
			st.pop();

			a = st.top();
			st.pop();

			a = a - b;

			st.push(a);
		}
		else if (cur_type == mul) {
			b = st.top();
			st.pop();

			a = st.top();
			st.pop();

			a = a * b;

			st.push(a);
		}
		else if (cur_type == divv) {
			b = st.top();
			st.pop();

			a = st.top();
			st.pop();

			a = a / b;

			st.push(a);
		}
		else if (cur_type == function) {
			a = st.top();
			st.pop();

			a = (*op_cur->f)(a);

			st.push(a);
		}
		else if (cur_type == power) {
			b = st.top();
			st.pop();

			a = st.top();
			st.pop();

			a = pow(a, b);

			st.push(a);
		}
		op_cur++;
	}

	a = st.top();
	st.pop();

	return a;
}
double m_sin(double a) {
	return -sin(a);
}
double m_cos(double a) {
	return -cos(a);
}
double m_tan(double a) {
	return -tan(a);
}
double ctan(double a) {
	return cos(a) / sin(a);
}
double m_ctan(double a) {
	return -(cos(a) / sin(a));
}
double get_minuse(double a) {
	return -a;
}
void processing_expr(std::string ex){
	s = ex;
	str = &s[0];
	next_lexem();
	tree_node *null_node = new tree_node;
	tree_node *node = create_expression(null_node);
	order(node);
	op_null = &V[0];
	op_last = &V[V.size() - 1];
	op_last++;
}
void set_x(double&var) {
	x = var;
}
void set_y(double&var) {
	y = var;
}
