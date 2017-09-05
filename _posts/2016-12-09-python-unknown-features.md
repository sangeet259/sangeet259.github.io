---
layout: post
title: "Into the unknown with Python"
permalink: "/py-unknown"
tags: [ "post", "python"]
subtitle: Lesser known features of Python and more!
---

Hello! As you may have noticed, my posts are slightly (read: very) irregular. Reason being I had a very hectic semester with really less time for anything. So after the semester, I decided to do some open source, and started with <a href="https://github.com/sympy/sympy">SymPy</a>. So after reading the code, I came to know that Python is capable of much larger things than expected. Though this is still a post for beginners, intermediate coders might find it helpful as well. In any case, let me know through the comments.

<blockquote><b>Note:</b>I'm still using Python 2.7. Some features may be slightly different in the Python 3.x versions. Please let me know the differences so that I can update the post regularly :)</blockquote>

Let me start with a few lesser known (and used features) of Python.

<h3>Generators and iterators:</h3>
To know what generators are, consider the following example-
{% highlight bash %}
	$ ulimit -v 131072
	$ python
{% endhighlight %} 
{% highlight python %}
	>>> a = (range(50000000))
{% endhighlight %}

This will most likely result in an error. This is because you set the user limit memory to 131072kB (128MB) and a list of 50000000 items cannot fit in. Now, try the following code. 
{% highlight python %}
	>>> a = (xrange(50000000))
{% endhighlight %}

This time, you won't see an error. Why? This is the fundamental difference between a list and a generator. Although `xrange` is not a generator by definition, the python doc say the following - 
<blockquote>
 |  Like range(), but instead of returning a list, returns an object that <br>
 |  generates the numbers in the range on demand.  For looping, this is <br>
 |  slightly faster than range() and more memory efficient. <br>
</blockquote>
Iterators and generators are much faster and memory efficient as compared to a list. This is a general idea of what generators and iterators are. This is not a tutorial and you will get excellent material to read online. 
<blockquote>
	<b>Note:</b> In Python3.x, range(&lt;num&gt;) returns an iterator instead of a list.
</blockquote>

<h3>Some useful functions: map, filter, any, all</h3>
While programming a tool, application, or whatever, using python, you might be tempted to write some "inner code" which will use (or abuse) the language. But chances are that the utility functions you are building might be a part of the standard library itself. I'm going to discuss some of them that were useful to me. There is a huge collection of functions and modules in the standard library, so at least skim through them the next time you are building something because chances are those functions exist already.
Here are some functions that can solve many problems with (almost) a single line of code.

<h4>map</h4>
In simple terms, this in-built function maps a function to every element of a list/iterator. This makes code much simpler to read and more compact. For example, consider the following code.
{% highlight python %}
>>> a = map(lambda x: x+1, xrange(5))
>>> a
[1, 2, 3, 4, 5]
{% endhighlight %}
Chances are you know what a lambda function is. If you do not, make a quick Google search :P . This code is certainly more compact than the for loop you would have written to get this done. In Python3.x, map returns an iterator, but to get an iterator in Python2.7, you can use the `itertools` module to use the `imap` function.
{% highlight python %}
>>> from itertools import imap
>>> a = imap(lambda x: x+1, xrange(5))
>>> a
<itertools.imap at 0x7fba9e9cca10>
{% endhighlight %}
For me, this function serves as a way to make code easier to read and more compact. Although excessive use of this can make code a little tricky to read if the code is too nested.

<h4>filter</h4>
As the name suggests, this function creates another list, after filtering through a function that returns `True` or `False` for each element. A simple example to demonstrate this - 
{% highlight python %}
>>> filter(lambda x: x%2 , xrange(10))
[1, 3, 5, 7, 9]
{% endhighlight %}
To get an iterator, you can use the `ifilter` function from the `itertools` module.

The point here is to understand the importance of iterators and the situations where they can be used, leading to faster code and lesser use of memory. In some other cases, where you may randomly need to access particular elements, lists or tuples are more favorable. The bottom line is, iterators and generators are useful, but you must know the limitations.

<h4>any, all</h4>
These 2 functions return a boolean `True` or `False` depending on whether any (or all) elements of an iterator/list/tuple are equivalent to `True`.
Here are some examples:
{% highlight py %}
>>> any(xrange(10))
True
>>> all(xrange(10))
False
{% endhighlight %}
Now, how do we use this? Instead of using some loop to check whether any(or all) elements satisfy some condition, we can simply use the one-liner code-
{% highlight py %}
>>> def some_condition(element):
	... some code here
	... 

>>> any(map(some_condition, mylist ))
{% endhighlight %}
Again, the point is to write concise and more 'Pythonic' code. The last function I want to mention here is slightly tricky for newbies, but is important nevertheless. 

<h3>Memoization and LRU</h3>
Memoization is a quick solution when you are solving a problem having optimal subproblems as part of the solution for the main problem (competitive coding guys can relate ;) ). In any case, if you want to save time by 'memoizing' the solution rather than calculating the solution, you can use the `lru_cache` decorator from the `functools` module. If you don't know what it is, stay hooked, I will discuss it in a while. LRU stands for 'least recently used' (self explanatory).
<blockquote>
	This works for Python 3.3+ only. I didn't find it in Python 2.7. If you find any such function as part of the standard library, please let me know.
</blockquote>
We use it in the following way - 
{% highlight py %}
>>> from functools import lru_cache
>>> @lru_cache(maxsize=10)
... def complex_calculation_function(x):
	... some code
	... 
>>>
{% endhighlight %}
The first time you put some value of the parameter, it calculates the value and returns it. The next time, if its stored in the cache, it returns the value without calculating it. Hence, you should be careful what function has to be used with it, if at all (do not use functions which have some side effects, or produce different answers based on the history of inputs). The `maxsize` attribute stores the max. number of recently used results that can be stored. There are some other cache statistics shown as well (like hits, misses, current cache size). Look it up for more details. 

In the above example, you are probably wondering what a decorator and what the weird `@` symbol means there, if you aren't familiar with decorators. Let's have a brief introduction to decorators.

<h3>Decorators</h3>
To understand decorators, let us use an example to memoize the functions in a `dict`:
{% highlight py %}
>>> _names = {}
>>> def memoize_function(f):
... 	global _names
... 	_names[f.__name__] = f
... 	return f

>>> @memoize_function
... def someFunc():
... 	# code here

>>>
{% endhighlight %}
The last line of code is equivalent to - 
{% highlight py %}
>>> def someFunc():
... 	# code here

>>> someFunc = memoize_function(someFunc)
{% endhighlight %}
In either of the cases, the name of the function and the function itself are stored in a dict `_names`. Although, decorators have a lot of details to look into, like maintaining the docstrings, and function name, etc. after applying the decorator, and others, but that is beyond the scope of this post. Decorators make the code look more beautiful and its purpose is distinguished from a regular function use due to its different syntax.

Thanks a lot for reading! Happy coding!! :)