/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetya <hsetya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 18:17:21 by hsetyamu          #+#    #+#             */
/*   Updated: 2024/02/24 18:27:35 by hsetya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
//#define _XOPEN_SOURCE 700
#include <unistd.h>
#include <sys/types.h> //pid_t
/* #include <unistd.h>
#include <sys/syscall.h> */
#include "minitalk.h"

int main(void) 
{
    pid_t pid = getpid();
    printf("My process ID is %d.\n", pid);
    return (0);
}

//Define a function `sig_handler` to handle incoming signals
    //Declare a static integer variable used to iterate through the bits of a character
    //Declare a static integer variable to construct all the bits of the character 
        //Check if a character's 8 bits have been contructed
            //Print the character
            //Reset the static variables in order to process the next character
            //Send to the client, a signal to confirm a character was received

//Write a program that does not take in command line arguments other than the program name
    //Handle command input errors
    //Get the PID and print it 
    //Enter an infinate loop that continuously waits for signals to be processed
        //Call the `sig_handler` function to handle to signals
        //Wait for the next signal