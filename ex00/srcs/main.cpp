/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo-mar <hugo-mar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 23:52:47 by hugo-mar          #+#    #+#             */
/*   Updated: 2025/10/05 21:48:38 by hugo-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>
#include <exception>

int main (int argc, char** argv) {

	if (argc != 2) {
		std::cerr << "Error: could not open file.\n";
		return 1;	
	}

	try {
		BitcoinExchange btc;
		
		btc.loadDatabase("data.csv");
		
		std::ifstream in(argv[1]);
		if (!in) {
			std::cerr << "Error: could not open file.\n";
			return 1;
		}
		
		btc.process(in, std::cout);
		
		return 0;
		
	} catch (const std::exception& e) {
		std::cout << e.what() << '\n';
		return 1;
	}
}