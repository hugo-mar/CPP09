/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo-mar <hugo-mar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 10:15:28 by hugo-mar          #+#    #+#             */
/*   Updated: 2025/10/10 11:58:34 by hugo-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <iostream>
#include <iomanip>

static void	printTime(const char* tag, size_t size, double us) {
	
	std::cout << "Time to process a range of "
			  << size << " elements with " << tag <<" : "
			  << std::fixed << std::setprecision(3)
			  << us / 1000.0 << " ms"
			  << std::endl;
}

int main(int argc, char** argv) {
	
	try {
		PmergeMe pm;
		pm.loadFromArgs(argc, argv);
		
		pm.printBefore(std::cout);
		
		double vecTime = pm.sortVector();
		double lstTime = pm.sortList();

		pm.printAfterVector(std::cout);

		printTime("std::vector", pm.getVector().size(), vecTime);
		printTime("std::list", pm.getList().size(), lstTime);
	}
	catch (...) {
		std::cerr << "Error\n";
		return 1;
	}

	return 0;
}