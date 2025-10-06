/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo-mar <hugo-mar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 19:45:43 by hugo-mar          #+#    #+#             */
/*   Updated: 2025/10/06 20:22:57 by hugo-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

# include <string>

class RPN
{
	
private:
	static bool			isOperator(char c);							// Static ft's because they dont depend on an intern state (dont need to access the this pointer)
	static long long	apply(long long a, long long b, char op);

public:
 	RPN();
	RPN(const RPN& other);
	RPN& operator=(const RPN& other);
	~RPN();

	long long evaluate(const std::string& expr);
};

#endif