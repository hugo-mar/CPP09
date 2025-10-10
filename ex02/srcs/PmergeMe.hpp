/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo-mar <hugo-mar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 18:57:56 by hugo-mar          #+#    #+#             */
/*   Updated: 2025/10/10 23:45:11 by hugo-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <vector>
# include <list>
# include <iosfwd>		// forward declaration of std::ostream

/*
 * Implements the Ford–Johnson merge-insert sort algorithm
 * using two different STL containers (vector and list).
 * 
 * The class:
 *	- Parses and validates input from command-line arguments.
 *	- Stores the original sequence (_input) for "Before" display.
 *	- Applies the merge-insert algorithm separately on a vector and a list.
 *	- Measures and returns the time taken for each container.
 */
class PmergeMe
{
	
private:
	// Original sequence (unchanged), and working copies for each container
	std::vector<unsigned int>	_input;
	std::vector<unsigned int>	_vec;
	std::list<unsigned int>		_lst;

	// Merge-Insert algorithm for std::vector
	void	mergeInsertVector();
	void	makePairsVector(std::vector<unsigned int>& smalls, std::vector<unsigned int>& bigs) const;
	void	orderBigsVector(std::vector<unsigned int>& bigs) const;
	void	insertSmallsVector(std::vector<unsigned int>& bigs, const std::vector<unsigned int>& smalls) const;

	// Merge-Insert algorithm for std::list
	void	mergeInsertList();
	void	makePairsList(std::list<unsigned int>& smalls, std::list<unsigned int>& bigs) const;
	void	orderBigsList(std::list<unsigned int>& bigs) const;
	void	insertSmallsList(std::list<unsigned int>& bigs, const std::list<unsigned int>& smalls) const;

	// Utilities
	static bool	parseUInt(const char* str, unsigned int& out);			// class-level helper, no instance
	void		requireNonEmpty() const;
	
public:
	// Orthodox Canonical Form
	PmergeMe();
	PmergeMe(const PmergeMe& other);
	PmergeMe& operator=(const PmergeMe& other);
	~PmergeMe();

	// Input loading
	void	loadFromArgs(int argc, char** argv);

	// Sorting - returns elapsed time (µs)
	double	sortVector();
	double	sortList();

	// Output
	void	printBefore(std::ostream& os) const;
	void	printAfterVector(std::ostream& os) const;
	void	printAfterList(std::ostream& os) const;

	// Accessors
	const std::vector<unsigned int>&	getVector() const;
	const std::list<unsigned int>&		getList() const;
};

#endif