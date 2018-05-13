---
layout: post
title: Proposal acceptance and community bonding period
tags:
  - post
  - gsoc
subtitle: Google Summer of Code Post #1
published: true
---
# Proposal acceptance and community bonding period

Two weeks into the summer break and the gsoc coding period is about to begin.
<br/><br/>
It all started in February when I started looking for organisations to contribute for the Google Summer of Code 2018. I knew the language was going to be Python, so straight I was into the PSF Sub Orgs. The next challenge was to select the sub org, I thought of going for core software development and not some specialised field. And what better than a Version Control System.
<br/><br/>
So now with the org finalised, I started with browsing through the codebase. The huge codebase was intimidating at first. Having written only programs, diving straight into a software's codebase was daunting. It was then I posted in the #mercurial on freenode that I was having this problem, and believe me that was the best thing that I did. Help came from a handle named JordiGH who pointed me to pudb, a graphical debuger that runs in the terminal.Little did I know that Jordi would eventually be mentoring me for the GSoC project. This was got me going, I could now run through the codebase the way I want, see the flow, see the function calls, see the obejct instatiations and it made my life a lot easier.
<br/><br/>
So there I was starting with issues. I started with a documentation fix. Then slowly moving into the core codebase. Honestly, I wasn't expectating that the doc fix would have such a long discussion on the channel, it taught me think from different angle and how the community would react to the change.
Then I got into adding features to histedit which would incorporate revsets in their ruleditor, I was really happy with this feature that I had added, because this was a problem that I faced, even my fellow gsocer from mercurial felt it's need. I then tried adding support for multiline commit messages from the command line itself, which is there in Git, but was missing mercurial, but my implementation wasn't actually great and it got rejected. Next I worked on a issue involing multiple carriage returns in hg annotate, I created a patch, but Yuya Nishihara had already solved this issue in a better way, so I just held that patch back.
<br/><br/>
Then as projects were announced, I chose to go with fixing grep's behaviour in mercurial. This was a thing that the community was rally interested. I started the documentation on this project. And made two significant contributions, while one fixed a five year old issue with grep, other which is still in progress is suppose to make hg work the way people would expect it to be.
Some of the merges came real close to the proposal submission deadline, and thanks to them my proposal looked better.
Here is a link my proposal : bit.ly/gsocprop
<br/><br/>
Came April 23rd as I was a bit anxious. I didn't even check the results, it was through my friends that I got to know that I was selected.  It really thrills me to know that the code that I have written / would be writing would be used by people all over the globe, at organisations such as Mozilla and Facebook.
<br/><br/>
It was my exams time and followed by vacations, I interacted with my mentor twice during this period. These were brief.
During these first two weeks I was mostly travelling and went to to my hometown as I would get busy once the coding period starts.
Now that I am back, it's time to get back to work.
