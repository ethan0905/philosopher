# philosopher 👥 [![esafar's 42 Philosophers Score](https://badge42.vercel.app/api/v2/cl6l739qg00490gialxmtgsrk/project/2464664)](https://github.com/JaeSeoKim/badge42)

<p align="center"> <img width="300" height="auto" src="https://github.com/ethan0905/philosopher/blob/master/dinning_philosophers" </p>

> Philosophers are sitting around a table where there is a large bowl of spaghetti in the middle. They all bring their own fork.
> **They can alternatively eat, sleep or think.** But in order to eat, they need to use 2 forks.
> 
> In a multi-threading manner, you gonna find a way to **prevent any philosopher from dying.**
> Read more [here](https://cdn.intra.42.fr/pdf/pdf/41343/en.subject.pdf)
  
## 📔 Summary

 - [❗️ Tricky tests](#%EF%B8%8F-tricky-tests)
 - [⚙️ How to run the project ?](#%EF%B8%8F-how-to-run-the-project-)
 - [🗃️ Data races](#%%EF%B8%8F-data-races)

## ❗️ Tricky tests
| TEST | How philosopher should react |
| ------------- | ------------- |
| `./philo 1 800 200 200` | The philosopher should not eat and should die! |
| `./philo 5 800 200 200`  | No one should die! |
| `./philo 5 800 200 200 7` | No one should die and the simulation should stop when all the philosophers has eaten at least 7 times each |
| `./philo 4 410 200 200` | No one should die! |
| `./philo 4 310 200 100`  | A philosopher should die! |
| `./philo 5 800 200 150`  | No one should die! |
| `./philo 3 610 200 80`  | No one should die! |

## ⚙️ How to run the project ?
Compile using:
````shell
make
````
Then start a simulation using:
````shell
./philo <nb_philo> <time_to_die> <time_to_eat> <time_to_sleep> <nb_of_time_each_philo_must_eat> //last argument is facultative
````  

## 🗃️ Data races
To check data races, go into your Makefile and use *-fsanitize=thread* when you compile. You can either check them using:
````shell
valgrind --tool=helgrind ./philo arg1 arg2 arg3 arg4
````
