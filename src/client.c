/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetya <hsetya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 18:17:16 by hsetyamu          #+#    #+#             */
/*   Updated: 2024/02/24 18:27:21 by hsetya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minitalk.h"

int main(int argc, char *argv[])
{
    printf("Argc:%d\n", argc);
    printf("Server PID:%s\n", argv[1]);
    printf("String to send:%s\n", argv[2]);
    return(0);
}

//Define a function `sig_confirm` that takes a signal, which is to be received from the server
    //If the signal is SIGUSR1 or SIGUSR2
        //Print "Message recieved"
    
//Define a funtion `send_bits` that takes in the server's PID, and a character
    //Declare an integer variable `bit` to iterate through each bit of the character
    //If the binary digit at the position `bit` is `1`, send to the server SIGUSR1
        //Otherwise send to the server SIGUSR2
    //Delay the program a bit before we look at the next bit of the character

//Write a program that takes in as arguments, the PID, and "message"
    //Handle command input errors
    //Check for the correct number of arguments
        //Since the main's argv parameters is of type char, and a PID is an integer, we need to convert this value to an integer
            //Call our `send_bits` function to send the bits to the server
            //If a signal is received from the server to acknowledge reciept, call our `sig_confirm` function