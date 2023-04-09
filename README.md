# asciidle-c
Previous asciidle bash script completly rewritten in C to optimize CPU load. The program now displays random ASCII art stored as .txt files in a terminal window when executed. The ascii art then scroll through your terminal window.

The new C program consume almost no CPU and maybe 1 or 2% of ram (on tested environnements)

To run directly, clone this repo, populate the txt folder with ascii art or run the bash script to automatically download some.

sudo chmod 774 asciidle

Run ./asciidle

.txt files are expected to be in /home/$USER/asciidle-c/txt

To compile the program from source :

Git clone this repo

cd asciidle-c

Compile with gcc -o asciidle asciidle.c -lncurses -lm

Put your ascii art in the txt folder or run the bash script to download some

run ./asciidle

![image](https://user-images.githubusercontent.com/114953576/230765145-0f76a3d4-03fe-48d6-85db-9c545e99cb7a.png)

Credit to BRANDON '65535' NIBLETT and the maintainers of asciipr0n.com for providing good quality old school ascii art.

