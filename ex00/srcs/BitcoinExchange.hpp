/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo-mar <hugo-mar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 23:29:00 by hugo-mar          #+#    #+#             */
/*   Updated: 2025/10/02 17:37:03 by hugo-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <map>
#include <string>
#include <iosfwd>

class BitcoinExchange
{
	
private:

	std::map<std::string, double> _rates;

	// Helpers
	static bool	parseCsvLine(const std::string& line, std::string& date, double& rate);
	static bool	parseInputLine(const std::string& line, std::string& date, double& value);
	static bool	isValidDate(const std::string& date);
	static bool	isValidValue(double value);
	bool		getRateForDate(const std::string& date, double& outRate) const;
	
public:

	// Constructors, destructor and assignmet opoerator
	BitcoinExchange();
	BitcoinExchange(const BitcoinExchange& other);
	BitcoinExchange& operator=(const BitcoinExchange& other);
	~BitcoinExchange();

	// Public methods
	void		loadDatabase(const char* csvPath);
	std::string	computeLine(const std::string& line) const;
	void		process(std::istream& in, std::ostream& out) const;
};

#endif
