/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aen-naas <aen-naas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 13:17:02 by aen-naas          #+#    #+#             */
/*   Updated: 2023/05/30 13:17:28 by aen-naas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <limits.h>

bool checkOverflow(long arg) {
    if (arg > INT_MAX || arg < INT_MIN) {
        // Overflow occurred
        return true;
    } else {
        // No overflow
        return false;
    }
}

void yourFunction(int arg) {
    if (checkOverflow(arg)) {
        // Handle overflow
        // ...
    } else {
        // Proceed with normal execution
        // ...
    }
}

int main() {
    long yourArg = ...; // Argument value
    yourFunction(yourArg);
    return 0;
}
