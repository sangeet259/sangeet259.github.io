# Demonstrating the problem with forward ordered grep `--``all`
So if you do a `hg grep "pattern" --all`
You would get all the lines along with revision numbers showing when this pattern appeared or disappeared from the repository. Cool, that’s what we want.

And by default, does a reverse revlog search. That is, it starts from the latest revision and goes all the way upto the oldest one. And accordingly show you the result.

All the demonstration are performed on this repository : https://bitbucket.org/sangeet259/hg_grep_all

*You can try to reproduce the following results by cloning*

Okay, now coming to the point.
This is the output of `hg grep "ruleid" --all` on that repo.

![](https://d2mxuefqeaa7sj.cloudfront.net/s_14728F58E2C2447B974FA1CEED8D87C4B844A7A44205FE637404A4BCC53C1097_1522070989071_image.png)


This is what we expect. Now if you do `hg grep -r 0:tip  "ruleid" --all`, what you want is that the older hits are shown first, that we start from the oldest revision and iterate upto the latest revision. But the result is unexpected :
Output of `**hg grep -r 0:tip "ruleid" --all**` on that repo.


![](https://d2mxuefqeaa7sj.cloudfront.net/s_14728F58E2C2447B974FA1CEED8D87C4B844A7A44205FE637404A4BCC53C1097_1522071187711_image.png)

![](https://d2mxuefqeaa7sj.cloudfront.net/s_14728F58E2C2447B974FA1CEED8D87C4B844A7A44205FE637404A4BCC53C1097_1522071203953_image.png)


Points to note:

1. There are no removals
2. Even in case of additions, they are just not correct

I realised this was due to the empty pstate dictionary that was being passed. And this dictionary was empty because at the end of each revision we are simply deleting the **matches[rev].**
So in the next revision it’s passing `[]` as pstate, as the computation of diff via difflib.SequenceMatcher requires comparing the previous state with this state, it’s simply showing that the previous state is empty and to get the current state, you just need to add everything from the current state to the pstate. This is the reason why there are no removals in the output and the discrepancy even in the additions.

To solve this we need to simply keep the matches and not delete it. But as Jordi told there will be a huge memory leak which we can not afford, so I came up with another solution of keeping the matches dictionary only till the end of this window and clearing it up once the window ends.
I do not make any changes to the line `del revfiles[rev]` . So we will know when a window ends when this revfiles dict gets empty.
Hence this :

    del revfiles[rev]
    if not revfiles:
      matches.clear()


Now see the result of `hg grep --all -r 0:tip "ruleid"`


![](https://d2mxuefqeaa7sj.cloudfront.net/s_14728F58E2C2447B974FA1CEED8D87C4B844A7A44205FE637404A4BCC53C1097_1522071934273_image.png)



🎉  We got the older hits first and the results are correct.

PS: There are other benifts of clear over dict.
1. Time: See the pastebin paste I created comparing the times
https://bpaste.net/show/fe79d2daae39
2. clear method apparently according to this SO answer is more memory efficient
https://stackoverflow.com/questions/10446839/does-dictionarys-clear-method-delete-all-the-item-related-objects-from-memory/30519908#30519908
