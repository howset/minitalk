# minitalk

Like the prev proj., 2 versions here. First one works very well on any input I tested, but rather complex to decipher.
The second one seems easier to understand.  
~Still working on it.~  
~Seems done. Now work on slides.~  
Done. Just eval now.  

Nothing particularly special here. I just picked this project because I didn't know that pipex may actually be more useful for the minishell project. The name minitalk led me to think that this is just a "small" project. Well, it might actually be. Just not for me. 

As usual, I went scouring for projects that seems understandable to me and try them out. Somehow most of them gave weird outputs when given a long string as an input (~2000 chars). So I looked for codes that would perform well. Found one, and tried to decipher it (v1). But I just couldn't get it in my head. Lost a lot of time going around the basics, which is probably good to expand my knowledge, but didn't really help in deciphering the lines of code I had in front of me. 

So then, again, dug around the internet. Found several hints, and composed my code accordingly (v2). This one worked quite fine. The design is robust enough with sending a signal back and forth between the client and server. The client sends one real signal to the server and holds back the next real signal until the server pings back a confirmation signal to the client to go forth. This way no (micro)adjustments of sleep/usleep is necessary. And most importantly, it is a lot easier to follow, with a more explicit syntax which is best suited to me.

The challenge is obviously playing around with the bitwise operations. Normal logical operations are ok, but doing it on the bit-level requires another step of effort. But basically, other than that, and avoiding non beginner-friendly syntaxes, the manuals of the functions would suffice. And of course getting a visual illustrations of bit shifting operations helps a lot.

The bonus is actually quite simple to achieve. ~I am not sure why or how, but as long as the signal is sent properly, emojis are displayed by the terminal without problem~ --> UTF-8. And the first bonus is already included in the design of the back and forth communication between client and server. The only exclamation mark here is the use of one global variable in the client side that serves as a flag to hold the firing of the next signal if the server has not pinged a confirmation signal. I suppose this can done in a different way by adding another function, but I am satisfied enough with this flow on my current level.

## Content
```
minitalk
├── mt_v1
│   ├── client.c
│   ├── minitalk.h
│   └── server.c
├── mt_v2
│   ├── lib
│   │   ├── src
│   │   │   ├── ft_printf
│   │   │   │   ├── ft_printf_c.c
│   │   │   │   ├── ft_printf_di.c
│   │   │   │   ├── ft_printf_hex.c
│   │   │   │   ├── ft_printf_p.c
│   │   │   │   ├── ft_printf_s.c
│   │   │   │   ├── ft_printf_u.c
│   │   │   │   ├── ft_printf.c
│   │   │   │   └── ft_printf.h
│   │   │   ├── get_next_line
│   │   │   │   ├── get_next_line_bonus.c
│   │   │   │   ├── get_next_line_bonus.h
│   │   │   │   ├── get_next_line_utils_bonus.c
│   │   │   │   ├── get_next_line_utils.c
│   │   │   │   ├── get_next_line.c
│   │   │   │   └── get_next_line.h
│   │   │   └── libft
│   │   │       ├── ft_atoi.c
│   │   │       ├── ft_[everything else].c
│   │   │       └── libft.h
│   │   └── Makefile
│   ├── slides
│   │   ├── minitalk1.svg
│   │   ├── minitalk2.svg
│   │   ├── minitalk3.svg
│   │   └── minitalk4.svg
│   ├── src
│   │   ├── client.c
│   │   ├── minitalk.h
│   │   └── server.c
│   ├── src_bonus
│   │   ├── client_bonus.c
│   │   ├── minitalk_bonus.h
│   │   └── server_bonus.c
│   ├── src_commented
│   │   ├── client.c
│   │   ├── minitalk.h
│   │   └── server.c
│   ├── txts
│   │   ├── 2000c.txt
│   │   ├── 8000c_emo.txt
│   │   └── 8000c.txt
│   ├── Makefile
│   └── README.md
├── .gitignore
└── README.md
```
