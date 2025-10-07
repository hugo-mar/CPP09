/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo-mar <hugo-mar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 20:23:05 by hugo-mar          #+#    #+#             */
/*   Updated: 2025/10/07 12:33:55 by hugo-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <stdexcept>		// std::runtime_error
#include <stack>
#include <cctype>			// std::isspace, std::isdigit

RPN::RPN() {}

RPN::RPN(const RPN& other) {
	(void)other;
}

RPN& RPN::operator=(const RPN& other) {
	(void)other;
	return *this;
}

RPN::~RPN() {}

bool	RPN::isOperator(char c){
	return (c == '+' || c == '-' || c== '/' || c == '*');
}

long long	RPN::apply(long long a, long long b, char  op) {
	switch (op)
	{
	case '+':
		return a + b;
	case '-':
		return a - b;
	case '/':
		if (b == 0)
			throw std::runtime_error("division by zero");
		return a / b;
	case '*':
		return a * b;
	default:
		throw std::runtime_error("invalid operator");
	}
}

long long	RPN::evaluate(const std::string& expr) {
	
	std::stack<long long> st;

	for (std::size_t i = 0; i < expr.size(); ++i) {
		
		if (std::isspace(static_cast<unsigned char>(expr[i])))  	// Cast to unsigned char to avoid UB with negative char values
			continue;

		if (std::isdigit(static_cast<unsigned char>(expr[i]))) {
			st.push(expr[i] - '0');
			continue;
		}

		if (isOperator(expr[i])) {
			if (st.size() < 2)
				throw std::runtime_error("not enough operands");
			long long b = st.top(); st.pop();
			long long a = st.top(); st.pop();
			st.push(apply(a, b, expr[i]));
			continue;
		}

		throw std::runtime_error("invalid token");
	}

	if (st.size() != 1)
		throw std::runtime_error("invalid expression");

	return st.top();
}