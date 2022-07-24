

CPPND: Capstone Snake Game

The following project is an extension and improvemnets to the 
Snake game sample code provided by udacity .the additonal features are built and used 
to provide an entirely different game :

The following  7 total criteria  were used to demonstrate from the rubric :

1.Criteria 1 : project code must compile and run without errors.
2.Criteria 2 : A variety of control structures are used in the project.if you look at 
				the main.cpp for example , there are several subfunctions like (Output(),sortScores() etc)
				used to process the saved scores from the vector 
3.Criteria 3 : The project reads data from a file and process the data, or the program writes data to a file.
				new function called Input_Game() with in main() implemented to read in Input_Game from "saved.txt"
				
4.Criteria 4 : The project accepts user input and processes the input 
				the player has the option to choose and save new score to the existing score, if player agrees for
				saving new score logic would save the new score in to "saved.txt"
5.Criteria 5 : concepts of Concurrency - The project uses multithreading - The project uses multiple threads in the execution.
                two threads t1 and t2 are used to manage food and food2 in the game.cpp file 

6.Criteria 6 : A condition variable is used in the project.the concept of blocking a thread untill another thread  modifies a shared
				variable and then notify the _condition provate variable is implemeneted with in PlaceFood ()
				and PlaceFood1()
				
7.Criteria 7 : A mutex or lock is used in the project.
			   inorder for  multiple threads to never access the function at the same time PlaceFood (),a mutex is used to lock with lock_guard 
			   also the other thread PlaceFood1 uses  unique_lock to lock