/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo-mar <hugo-mar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 23:43:49 by hugo-mar          #+#    #+#             */
/*   Updated: 2025/10/11 00:08:00 by hugo-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <cstdlib>			// std::strtoul
#include <cerrno>			// errno, ERANGE
#include <climits>			// UINT_MAX
#include <stdexcept>		// std::runtime_error
#include <iostream>			// std::ostream
#include <vector>			// std::vector
#include <sys/time.h>		// gettimeofday
#include <algorithm>		// std::sort, std::lower_bound

// ----- Orthodox Canonical Form ------
PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe& other)
	: _input(other._input), _vec(other._vec), _lst(other._lst) {}
	
PmergeMe&	PmergeMe::operator=(const PmergeMe& other) {
	if (this != &other) {
		_input = other._input;
		_vec = other._vec;
		_lst = other._lst;
	}
	return *this;
}

PmergeMe::~PmergeMe() {}

// ----- Input loading -----
void	PmergeMe::loadFromArgs(int argc, char** argv) {
	
	// Reset containers before loading new input
	_input.clear();
	_vec.clear();
	_lst.clear();

	if (argc < 2)
		throw std::runtime_error("Error");

	for (int i = 1; i < argc; ++i) {
		
		unsigned int n;
		
		if (!parseUInt(argv[i], n))	
			throw std::runtime_error("Error");
			
		_input.push_back(n);
	}
}

// ----- Sorting - Execute merge-insert for each container and return elapsed time (µs) -----
static inline double nowMicroSecs() {			// Utility function to get the current system time in microseconds
	timeval tv;									// (inline tells the compiler it can replace the call with the function's tiny code directly)
	gettimeofday(&tv, NULL);
	return tv.tv_sec * 1e6 + tv.tv_usec;	
}

double	PmergeMe::sortVector() {
	
	requireNonEmpty();
	_vec = _input;
	
	if (_vec.size() < 2)
		return 0.0;
	
	double t0 = nowMicroSecs();
	mergeInsertVector();
	double t1 = nowMicroSecs();
	
	return t1 - t0;
}

double	PmergeMe::sortList() {
	
	requireNonEmpty();
	_lst.assign(_input.begin(), _input.end());

	if (_lst.size() < 2)
		return 0.0;

	double t0 = nowMicroSecs();
	mergeInsertList();
	double t1 = nowMicroSecs();

	return t1 - t0;
}

// ----- Output -----
void	PmergeMe::printBefore(std::ostream& os) const {
	os << "Before:\t";
	for (std::vector<unsigned int>::const_iterator it = _input.begin(); it != _input.end(); ++it) {
		if (it != _input.begin()) os << ' ';
		os << *it;
	}
	os << '\n';
}

void	PmergeMe::printAfterVector(std::ostream& os) const {
	os << "After:\t";
	for (std::vector<unsigned int>::const_iterator it = _vec.begin(); it != _vec.end(); ++it) {
		if (it != _vec.begin()) os << ' ';
		os << *it;
	}
	os << '\n';	
}

void	PmergeMe::printAfterList(std::ostream& os) const {
	os << "After:\t";
	for (std::list<unsigned int>::const_iterator it = _lst.begin(); it != _lst.end(); ++it) {
		if (it != _lst.begin()) os << ' ';
		os << *it;
	}
	os << '\n';
}

// Accessors
const std::vector<unsigned int>&	PmergeMe::getVector() const {
	
	return _vec;
}

const std::list<unsigned int>&		PmergeMe::getList() const {
	
	return _lst;
}

// ----- Merge-Insert algorithm for std::vector -----
void	PmergeMe::mergeInsertVector() {

	std::vector<unsigned int> smalls, bigs;

	smalls.reserve(_vec.size() / 2);
	bigs.reserve((_vec.size() + 1) / 2);
	
	makePairsVector(smalls, bigs);
	orderBigsVector(bigs);
	insertSmallsVector(bigs, smalls);

	_vec.swap(bigs);
}

void	PmergeMe::makePairsVector(std::vector<unsigned int>& smalls, std::vector<unsigned int>& bigs) const {

	const size_t vecSize = _vec.size();		// For optimization
	
	for (size_t i = 0; i + 1 < vecSize; i += 2) {
		
		const unsigned int a = _vec[i];
		const unsigned int b = _vec[i + 1];
		
		if (a < b) {
			smalls.push_back(a);
			bigs.push_back(b);
		} else {
			smalls.push_back(b);
			bigs.push_back(a);
		}
	}
	
	if (vecSize % 2)						// Handle last element in case of an odd-sized vector
		bigs.push_back(_vec.back());
}

void	PmergeMe::orderBigsVector(std::vector<unsigned int>& bigs) const {

	std::sort(bigs.begin(), bigs.end());
}

void	PmergeMe::insertSmallsVector(std::vector<unsigned int>& bigs, const std::vector<unsigned int>& smalls) const {
	
	for (std::vector<unsigned int>::const_iterator it = smalls.begin(); it != smalls.end(); ++it) {
	
		std::vector<unsigned int>::iterator pos = std::lower_bound(bigs.begin(), bigs.end(), *it);
		bigs.insert(pos, *it);
	}
}

// ----- Merge-Insert algorithm for std::list -----
void	PmergeMe::mergeInsertList() {
	
	std::list<unsigned int> smalls, bigs;

	makePairsList(smalls, bigs);
	orderBigsList(bigs);
	insertSmallsList(bigs, smalls);

	_lst.swap(bigs);
}

void	PmergeMe::makePairsList(std::list<unsigned int>& smalls, std::list<unsigned int>& bigs) const {
	
	std::list<unsigned int>::const_iterator it = _lst.begin();

	while (it != _lst.end()) {
		
		const unsigned int a = *it;
		++it;

		if (it == _lst.end()) {		// Handle last element in case of an odd-sized list
			bigs.push_back(a);
			break;
		}

		const unsigned int b = *it;
		++it;

		if (a < b) {
			smalls.push_back(a);
			bigs.push_back(b);
		} else {
			smalls.push_back(b);
			bigs.push_back(a);
		}
	}
}

void	PmergeMe::orderBigsList(std::list<unsigned int>& bigs) const {
	
	bigs.sort();
}

void	PmergeMe::insertSmallsList(std::list<unsigned int>& bigs, const std::list<unsigned int>& smalls) const {
	
	for (std::list<unsigned int>::const_iterator it = smalls.begin(); it != smalls.end(); ++it) {
		
		std::list<unsigned int>::iterator pos = std::lower_bound(bigs.begin(), bigs.end(), *it);
		bigs.insert(pos, *it);
	}
}

// ----- Utilities -----
bool	PmergeMe::parseUInt(const char* str, unsigned int& out) {
	
	 // Reject null, empty, leading sign/space: first char must be a digit
	if(!str || !*str || str[0] < '0' || str[0] > '9')
		return false;
		
	errno = 0;
	char* end = NULL;
	unsigned long tmp = strtoul(str, &end, 10);

	// Fail on: no conversion, trailing garbage, overflow, or > UINT_MAX
	if (end == str || *end != '\0' || errno == ERANGE || tmp > UINT_MAX)
		return false;
		
	out = static_cast<unsigned int>(tmp);
	return true;
}

void		PmergeMe::requireNonEmpty() const {
	if (_input.empty())
		throw std::runtime_error("Error");
}