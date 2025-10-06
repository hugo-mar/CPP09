/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo-mar <hugo-mar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 00:01:21 by hugo-mar          #+#    #+#             */
/*   Updated: 2025/10/07 00:16:00 by hugo-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <iostream>
#include <exception>

int main(int argc, char** argv) {

	if (argc != 2) {
		std::cerr << "Error\n";
		return 1;
	}

	try {
		RPN rpn;
		std::cout<< rpn.evaluate(argv[1]) << '\n';
	}
	catch (...) {
		std::cerr << "Error\n";
		return 1;
	}

	return 0;
}