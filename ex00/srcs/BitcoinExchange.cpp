/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo-mar <hugo-mar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 17:21:09 by hugo-mar          #+#    #+#             */
/*   Updated: 2025/10/05 14:38:59 by hugo-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <cstdlib>						// std::strtod std:atoi
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>						// std::ostringstream

/*----------------------------------------------------*/
/*  Constructors, destructor and assignmet opoerator  */
/*----------------------------------------------------*/
BitcoinExchange::BitcoinExchange() : _rates() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) : _rates(other._rates) {}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other) {
	if (this != &other)
		_rates = other._rates;
	return *this;
}

BitcoinExchange::~BitcoinExchange() {}

/*-----------*/
/*  Helpers  */
/*-----------*/
bool	BitcoinExchange::parseCsvLine(const std::string& line, std::string& date, double& rate) {
	
	std::string::size_type commaPos = line.find(',');
	if (commaPos == std::string::npos)
		return false;
		
	date = line.substr(0, commaPos);
	std::string	rateStr = line.substr(commaPos + 1);
	
	while (!date.empty() && (date[0] == ' ' || date[0] == '\t')) date.erase(0, 1);
	while (!date.empty() && (date[date.size() - 1] == ' ' || date[date.size() - 1] == '\t')) date.erase(date.size() - 1, 1);
	while (!rateStr.empty() && (rateStr[0] == ' ' || rateStr[0] == '\t'))rateStr.erase(0, 1);
	while (!rateStr.empty() && ((rateStr[rateStr.size() - 1] == ' ') || rateStr[rateStr.size() - 1] == '\t')) rateStr.erase(rateStr.size() - 1, 1);
	
	char* end = NULL;
	rate = std::strtod(rateStr.c_str(), &end);
	
	if (!isValidDate(date) || end == rateStr.c_str() || *end != '\0' || rate < 0.0)
		return false;
		
	return true;
}

bool	BitcoinExchange::parseInputLine(const std::string& line, std::string& date, double& value) {
	
	std::string::size_type barPos = line.find('|');
	if (barPos == std::string::npos) {
		std::cout << "Error: bad input => " << line << '\n';	
		return false;
	}
	
	date = line.substr(0, barPos);
	std::string valueStr = line.substr(barPos + 1);
	
	while (!date.empty() && (date[0] == ' ' || date[0] == '\t')) date.erase(0, 1);
	while (!date.empty() && (date[date.size() - 1] == ' ' || date[date.size() - 1] == '\t')) date.erase(date.size() - 1, 1);
	while (!valueStr.empty() && (valueStr[0] == ' ' || valueStr[0] == '\t')) valueStr.erase(0, 1);
	while (!valueStr.empty() && (valueStr[valueStr.size() - 1] == ' ' || valueStr[valueStr.size() - 1] == '\t')) valueStr.erase(valueStr.size() - 1, 1);

	char* end = NULL;
	value = std::strtod(valueStr.c_str(), &end);

	if (!isValidDate(date) || end == valueStr.c_str() || *end != '\0') {
		std::cout << "Error: bad input => " << line << '\n';
		return false;
	}

	if (!isValidValue(value))
		return false;
	
	return true;
}

bool	BitcoinExchange::isValidDate(const std::string& date) {

	if (date.size() != 10 || date[4] != '-' || date[7] != '-')
	return false;

	for (size_t i = 0; i < date.size(); ++i) {
		if (i == 4 || i == 7)
		continue;
		if (date[i] < '0' || date[i] > '9')
			return false;
		}

	int	year = std::atoi(date.substr(0, 4).c_str());
	int month = std::atoi(date.substr(5, 2).c_str());
	int day = std::atoi(date.substr(8, 2).c_str());

	if (year < 2009)
	return false;
	
	if (month < 1 || month > 12)
		return false;
		
	static const int MonthsMaxDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};		// Static for optimization (creation only at first call)
	int daysInMonth = MonthsMaxDays[month - 1];
	if (month == 2) {
		if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))		// If true, it's a leap year
			daysInMonth = 29;
		}
	
	if (day < 1 || day > daysInMonth)
		return false;
		
	return true;
}

bool	BitcoinExchange::isValidValue(double value) {
	
	if (value < 0.0) {
		std::cout << "Error: not a positive number.\n";
		return false;
	}
	if (value > 1000.0) {
		std::cout << "Error: too large a number.\n";
		return false;
	}
	
	return true;
}

bool	BitcoinExchange::getRateForDate(const std::string& date, double& outRate) const {
	
	if (_rates.empty())
		return false;
	
	std::map<std::string, double>::const_iterator it = _rates.lower_bound(date);			// iterator to first element with key >= given key
	
	if (it != _rates.end() && it->first == date) {
		outRate = it->second;
		return true;
	}
	
	if (it == _rates.begin())
		return false;
	
	--it;
	outRate = it->second;
	return true;
}

/*------------------*/
/*  Public methods  */
/*------------------*/
void	BitcoinExchange::loadDatabase(const char* csvPath) {

	std::ifstream in(csvPath, std::ios::in);
	if (!in)
		throw std::runtime_error("Error: could not open file.");
	
	std::string	line;
	
	if (!std::getline(in, line))						// Skip header line
		throw std::runtime_error("Error: database is empty or invalid.");

	std::size_t loaded = 0;
		
	while (std::getline(in, line)) {
		
		std::string date;
		double rate;
		
		if (parseCsvLine(line, date, rate)) {
			_rates[date] = rate;
			++loaded;
		}
		else
			std::cerr << "Warning: invalid line in CSV: " << line << std::endl; 
	}

	if (loaded == 0)
		throw std::runtime_error("Error: database is empty or invalid.");
}

std::string	BitcoinExchange::computeLine(const std::string& line) const {

	std::string	date;
	double		value;
	double		rate;

	if (!parseInputLine(line, date, value))
		return "";
		
	if (!getRateForDate(date, rate))
		return "Error: bad input => " + line;

	std::ostringstream oss;
	oss << date << " => " << value << " = " << (value * rate) << '\n';
	
	return oss.str();
}

void	BitcoinExchange::process(std::istream& in, std::ostream& out) const {

	std::string	line;
	
	if (!std::getline(in, line))		// Skip header
		return;
	
	while (std::getline(in, line)) {
		
		std::string result = computeLine(line);
		out << result;
	}
}