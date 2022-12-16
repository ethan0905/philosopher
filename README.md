# philosopher 👥 [![esafar's 42 Philosophers Score](https://badge42.vercel.app/api/v2/cl6l739qg00490gialxmtgsrk/project/2464664)](https://github.com/JaeSeoKim/badge42)

<p align="left"> <img width="400" height="400" src="https://github.com/ethan0905/philosopher/blob/master/dinning_philosophers" </p>

## 📔 Summary

 - [📚 Subject](#-containersalgorithmiterators)
 - [❗️ Tricky tests](#%EF%B8%8F-potential-mistakes-)
 - [⚙️ How to run the project ?](#%EF%B8%8F-how-to-run-the-project-)
 - [🗃️ Data races](#%EF%B8%8F-usefull-documentation)
  
## 📚 Subject
One or more philosophers are sitting around a table where there is a large bowl of spaghetti. They alternatively eat, think, or sleep. While they are eating, they are not thinking nor sleeping; while thinking, they are not eating nor sleeping; and, of course, while sleeping, they are not eating nor thinking. In order to eat, each philosopher bring his fork with him at the beginning of the simulation. Because serving and eating spaghetti with only one fork is very inconvenient, a
philosopher takes their right and their left forks to eat, one in each hand. When a philosopher has finished eating, they put their forks back on the table and start sleeping. Once awake, they start thinking again. The simulation stops when a philosopher dies of starvation. Every philosopher needs to eat and should never starve. Philosophers don’t speak with each other. Philosophers don’t know if another philosopher is about to die.

###### Read more [here](https://cdn.intra.42.fr/pdf/pdf/41343/en.subject.pdf)

## ❗️ Tricky tests
| TEST | How philosopher should react |
| ------------- | ------------- |
| ./philo 1 800 200 200 | The philosopher should not eat and should die! |
| ./philo 5 800 200 200  | No one should die! |
| ./philo 5 800 200 200 7 | No one should die and the simulation should stop when all the philosophers has eaten at least 7 times each |
| ./philo 4 410 200 200 | No one should die! |
| ./philo 4 310 200 100  | A philosopher should die! |
| ./philo 5 800 200 150  | No one should die! |
| ./philo 3 610 200 80  | No one should die! |

## ⚙️ How to run the project ?
Compile using:
```
make
```
Then start a simulation using:
```
./philo <nb_philo> <time_to_die> <time_to_eat> <time_to_sleep> <nb_of_time_each_philo_must_eat> //last argument is facultative
```  

## 🗃️ Data races
To check data races, go into your Makefile and use *-fsanitize=thread* when you compile. You can either check them using:
```
valgrind --tool=helgrind ./philo arg1 arg2 arg3 arg4
```
