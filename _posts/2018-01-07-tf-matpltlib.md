## Matplotlib Backened change during Training a DL Model

If you are training something on remote server where you dont have root access and get an error like your python is not configured for tkinter.
This is nothing but maybe somewhere in your pipe
Then you're options are :
* First install tkinter, note that since you do not have sudo priviledge, you have to install `tcl8.6-dev` and  `tk8.6-dev` from source too.
* Install Python from source again : [Here](https://passingcuriosity.com/2015/installing-python-from-source/) is a great link describing the process 
* In the last step you have to explicitly pass where your tkinter files are located during the `./configure`.

After this you should be fine. But there is another way to bypass this stuff.
I am assuming that you really isn't using GUI and sticking to terminal, in that case you don't need tkinter at all, why install it.
As I said, it's the matplotlib that's the culprit here, so what you can do is change it's backend from tkinter (TkAgg) to antigrain(Agg).
Then we won't need tkinter at all.
Here's how to do that :
* Find where is your matplotlib file is located :
```sh
>>> import matplotlib
>>> matplotlib.matplotlib_fname()
'/home/foo/.config/matplotlib/matplotlibrc'
```
* If there is no file create one in '/home/foo/.config/matplotlib/matplotlibrc'

In that file just change this (or if created enter just this) : `backend      : Agg`

Save it and run !

:tada:
You should be rolling !!
  









References:
* https://matplotlib.org/faq/usage_faq.html#what-is-a-backend
* https://gist.github.com/Nesffer/5fb3d6d4cd3e0cb65624
* https://stackoverflow.com/questions/4931376/generating-matplotlib-graphs-without-a-running-x-server/4935945#4935945
