---
layout: post
title: "G.R.A.S.P. - Our ITSP Project"
subtitle: "A summer experience worth remembering!"
permalink: "/grasp-itsp"
tags: ["summers","image processing","itsp","python"]
---

Hey there! This is my first summers out of home, and it couldn't have been any better. With the monsoon rains coming and those 'stranded' moments in my hostel room, those 'Midnight Maggi moments' in my hostel, a couple of night-outs with my team-mates, and the summer projects that I did, everything was amazing. Apart from my WnCC SoC project and a website, I was also doing an ITSP project as well. After getting inspired by one of my senior's project and taking a little bit of inspiration from Iron Man's Jarvis, I decided to make a gesture recognition project. With the time constraints, I could not take it as far as I thought, but we still ended up with a decent project. So let me get to the project, what it is about, blah blah blah. 

## G.R.A.S.P.

### Introduction
We decided to make a simple hand recognizing and motion tracking tool, and use the movements to perform actions. Due to time constraints, we decided to fix to lateral, 8-direction movement, similar to what is found in a pattern lock in your smartphone. We are using color masks to isolate the hand, so wearing a glove gives the best results. Initially, the program accesses the webcam, and shows a window, and prompts the user to place his hand in the green rectangles shown in the window. It takes the colors and creates a color mask that separates out the hand from the rest of the frame. This image is then used to create the contours and the central point of the hand. This central point is tracked and the 'noticeable' lateral movements in the hand are recorded. A sequence of such movements is matched against some predefined data, and then if a match is found, the required command is executed and the recorded data is refreshed for new gestures to be recorded. 

### Working
Here comes the interesting part. This tool is written in python using numpy and openCV libraries. Numpy is a library which provides a powerful N-dimensional array object used for complex manipulations. OpenCV uses numpy to store and manipulate image data using numpy arrays (ndarrays). OpenCV is an image processing library built for python and some other different languages. We developed in an Ubuntu 14.04 LTS system. Here are the pre-requisites for the tool to work - 
<ul>
	<li>Python 2.7.x (We used Python 2.7.6)</li>
	<li>OpenCV 2.x.x (We used OpenCV 2.4.9)</li>
</ul>
<blockquote>
	<b>Warning:</b> Using Python 3.x and/or OpenCV 3.x.x may not work with this project. If you want to test it in a different (virtual) environment without disturbing your current python installation, we recommend you to use 'virtualenv' for setting up a virtual python environment. 
</blockquote>
<ul>
	<li>3. Numpy (We used v1.8.2)</li>
	<li>4. The following modules in python (although these modules are present by default in most or all python installations) – <i>os,math,subprocess,json,time,datetime</i>.</li>
</ul>

Once we have the tools ready, let us get started with reading and understanding the program. 
First, we capture the default WebCam using the 'VideoCapture' method of OpenCV. This method takes the default camera of the computer, and if it does not exist, or is used by another process, it will raise an error. A screen similar to the ones below opens up. You need to cover the rectangles entirely with the hand so that the program picks up the right colors.

<div class="row">
	<div class="col-sm-3"></div>
	<div class="col-sm-6">
		<figure class="figure">
		  <img src="/img/grasp-itsp/init.jpg" class="figure-img img-fluid img-rounded img-responsive" alt="init">
		  <figcaption class="figure-caption"><small>An initial window asking to put the hand to get the colors. (Yes, I'm wearing a glove there)</small></figcaption>
		</figure>
	</div>
	<div class="col-sm-3"></div>
</div>

If we are done with the correct placing of the hand, we can simply press 'q' to close the window or wait for some time, it will close automatically in that case. Now, we have the ROI (rectangles of interest) regions extracted from the image. But there is a catch, and that is colorspaces.
Colorspaces, now what are they?

### Colorspaces
A colorspace is simply a 3D coordinate system where each point is a different color. Aptly put by ArcSoft, 
<blockquote>
A range of colors can be created by the primary colors of pigment and these colors then define a specific color space. Color space, also known as the color model (or color system), is an abstract mathematical model which simply describes the range of colors as tuples of numbers, typically as 3 or 4 values or color components (e.g. RGB). Basically speaking, color space is an elaboration of the coordinate system and sub-space. Each color in the system is represented by a single dot.
</blockquote>
Below is an example of a graph depicting a colorspace. It's very complex and is not required to be fully understood. But there are some things which we should know about colorspaces. Like there are different representations of the 3D coordinate system (cartesian, cylindrical, and spherical), there are different representations of colorspaces as well (RGB,HSV,CMYK,etc.). 
<div class="row">
	<div class="col-sm-3"></div>
	<div class="col-sm-6">
		<figure class="figure">
		  <img src="/img/grasp-itsp/colorspaces.jpg" class="figure-img img-fluid img-rounded img-responsive" alt="colorspaces">
		  <figcaption class="figure-caption"><small>A graphical representation of a colorspace.</small></figcaption>
		</figure>
	</div>
	<div class="col-sm-3"></div>
</div>

Each colorspace has its own pros and cons. The RBGA colorspace is a common one. Any color can be represented as a sum of Red, Blue, and Green components. In addition to that, there is a alpha blending process of mixing the translucent foreground color with a background color, which is handled by the Alpha channel. This colorspace is useful if we want the Red, Green, and Blue components separately. But it is not so useful when we are comparing the same image in different lighting because the RGBA channels do not give us information about lighting. Hence, we must use another colorspace to get the information. Here comes the HSV colorspace.

### HSV colorspace- Hue,Saturation,Value
<div class="row">
	<div class="col-sm-3"></div>
	<div class="col-sm-6">
		<figure class="figure">
		  <img src="/img/grasp-itsp/HSV.png" class="figure-img img-fluid img-rounded img-responsive" alt="hsv">
		  <figcaption class="centraltext figure-caption"><small>HSV colorspace.</small></figcaption>
		</figure>
	</div>
	<div class="col-sm-3"></div>
</div>

RGB colorspace can be visualized as a cartesian colorspace, with values ranging from 0 to 255. In contrary, HSV is a cylindrical colorspace which separates the luma (intensity values) from the chroma (color values). That is the reason why HSV colorspace is used in many image processing applications. In our project, we are going to convert the image from an RGB to HSV image for further processing. 
	After getting the ROIs from the image, we convert into HSV and then separate the Hue values, which essentially stores the color information as seen from the above diagram. For best approximate results, we sort the ROI arrays and take the median Hue value. We do this for all the 5 ROIs. Then, we create color masks using those colors and an OpenCV method. Every frame taken from the camera is passed through these masks (after some other processing) and we create a sum of those images. Then they are thresholded. Here are some results of the final masked and thresholded image.

<div class="row">
	<div class="col-sm-6">
		<figure class="figure">
		  <img src="/img/grasp-itsp/mask1.jpg" class="figure-img img-fluid img-rounded img-responsive" alt="mask1">
		  <figcaption class="centraltext figure-caption"><small>Masked and thresholded image.</small></figcaption>
		</figure>
	</div>
	<div class="col-sm-6">
		<figure class="figure">
		  <img src="/img/grasp-itsp/mask2.jpg" class="figure-img img-fluid img-rounded img-responsive" alt="mask2">
		  <figcaption class="centraltext figure-caption"><small>Masked and thresholded image.</small></figcaption>
		</figure>
	</div>
</div>
At the time of testing, we used an orange glove. Orange values are similar to skin color in the HSV colorspace, hence a bit of my face is also taken. But we will remove it later. 

Before we proceed, we need to find the edges of the filtered image, and we do so with the Canny Edge detector.

### Canny Edge detector
The Canny edge detector is an edge detection operator that uses a multi-stage algorithm to detect a wide range of edges in images. It was developed by John F. Canny in 1986. Here is an example of the Canny Edge detector algorithm applied to the above images. 

<div class="row">
	<div class="col-sm-6">
		<figure class="figure">
		  <img src="/img/grasp-itsp/canny1.jpg" class="figure-img img-fluid img-rounded img-responsive" alt="canny1">
		  <figcaption class="centraltext figure-caption"><small>Image after applying Canny Edge detector.</small></figcaption>
		</figure>
	</div>
	<div class="col-sm-6">
		<figure class="figure">
		  <img src="/img/grasp-itsp/canny2.jpg" class="figure-img img-fluid img-rounded img-responsive" alt="canny2">
		  <figcaption class="centraltext figure-caption"><small>Image after applying Canny Edge detector.</small></figcaption>
		</figure>
	</div>
</div>

This helps us to visualize the contours very nicely. After that, we can use this image to find the contours and then select the biggest contour which will be the hand. To do this, we pass the frame into the in-built findContours function with <i>"RETR_TREE"</i> retrieval mode and <i>"CHAIN_APPROX_NONE"</i> method. <i>"RETR_TREE"</i> mode retrieves all of the contours and reconstructs a full hierarchy of nested contours. <i>"CHAIN_APPROX_NONE"</i> method takes absolutely all the contours without compressing horizontal, vertical or diagonal contours. As the name suggests, it does no approximation. After getting the contours, we use the <i>arcLength</i> of the contours to determine the biggest one. We could have used <i>contourArea</i> as well, but we found it good (since we are assuming that all other objects will be neglected during the masking stage). After finding the biggest contour, we find the convex Hull (the convex shape that covers the contour) and the bounding rectangle of the biggest contour. This will help us in finding the convexity defects, which can help us find the fingers. After finding the convexity defects, which contains 3 points – <i>start,end</i> and <i>far</i>. The points <i>start</i> and <i>end</i> are the points on the convex hull and <i>far</i> is the point of defect. We discard the defects which might be due to small foldings in the glove or the shape that brings in small defects. We remove them by using a small algorithm. The one line statement of the algorithm is that the minimum of <i>distance(start,far)</i> and <i>distance(end,far)</i> must be greater than 0.25 times the height of the bounding rectangle and the <i>angle SFE (start,far,end)</i> must be less than 80 degrees. These values are the just the results of hit and trial. Lets talk about tracking the center now.

### Tracking
After finding the contour, we can find the center using <i>moments</i> method of OpenCV. This gives us a 'dict' of values, which can be used to find the center. We can also just find the center of the bounding rectangle, but the former gives more accurate results. The final result is this (center is the yellow circle) - 

<div class="row">
	<div class="col-sm-6">
		<figure class="figure">
		  <img src="/img/grasp-itsp/final1.jpg" class="figure-img img-fluid img-rounded img-responsive" alt="final1">
		  <figcaption class="centraltext figure-caption"><small>Final result after detecting central point.</small></figcaption>
		</figure>
	</div>
	<div class="col-sm-6">
		<figure class="figure">
		  <img src="/img/grasp-itsp/final2.jpg" class="figure-img img-fluid img-rounded img-responsive" alt="final2">
		  <figcaption class="centraltext figure-caption"><small>Final result after detecting central point.</small></figcaption>
		</figure>
	</div>
</div>

See that tiny little red dot in the second dot? It is the defect that we filtered out. Now, we can just track this point and record the gestures. Now the question is, how do we record?

### <u>Lateral movements</u>

Given the time constraints, we decided not to use image templates for comparing gestures since it would involve things like resizing the templates, aligning to match with the recorded gesture, since the user can move his hand from anywhere, not just the center, and proper matching would be more than just a case of image subtraction (one of my friends just told me to subtract the template image from the recorded gesture, but that wasn't the case). So we decided to use 8-direction movement and got inspired from this common technique. 

This made our work a lot more simpler. Now all we had to do was track the relative movement of the hand from one frame to another and find out the direction in which the hand goes, then we approximate it with the closest direction and add it to a python list. But what if the user makes some casual hand movements, and they would be recorded by mistake? So we restricted the distance between the tracking point in consecutive frames to be greater than 80 pixels (again, a hit and trial). This makes the user perform relatively 'swift' hand movements for the gesture to register. And these movements were compared to some data we had in a file. The convention we used was as follows (the number denotes the direction) - 
<div class="row">
	<div class="col-sm-5">
		<figure class="figure">
		  <img src="/img/grasp-itsp/phone.jpg" class="figure-img img-fluid img-rounded img-responsive" alt="phoneLockScreen">
		  <figcaption class="centraltext figure-caption"><small>Pattern lock for a phone.</small></figcaption>
		</figure>
	</div>
	<div class="col-sm-7">
	<br>
		<ol>
			<li>North-West</li>
			<li>North</li>
			<li>North-East</li>
			<li>East</li>
			<li>South-East</li>
			<li>South</li>
			<li>South-West</li>
			<li>West</li>
		</ol>
	</div>
</div>


### <u>Storing new gestures</u>
If you look carefully at the source code, you will find a file called gesturedata.json . This file stores the gestures in a JSON format. The entries will look something like this - 

{% highlight python %}
{ 
  "gesture" : [2,4,6,7], 
  "command" : "rhythmbox", 
  "default" : "true" 
}
{% endhighlight %}

Every gesture stored has a <i>"gesture"</i> attribute to store the code of the gesture(more on it later), a <i>"command"</i> attribute, which displays the terminal command to perform, and a <i>"default"</i> attribute, which specifies whether the attribute is coded into the source code. It is recommended that any other gesture you might want to save must contain these three attributes and the <i>"default"</i> be set to <i>"false"</i>. This will tell the code that it is a user added script. Gestures having <i>"default"</i> value of <i>"true"</i> have been given special commands that can be executed, for example, Rhythmbox has full support for play/pause, Volume control, song control and so on. So unless you are a developer and are ready to make changes to the code, it is recommended to keep the <i>"default"</i> to <i>"false"</i>. Plus, the gestures are based on <i>"prefix-free code"</i>, i.e. the greediest one executes first. For example, if a gesture is [2,3,4] and another gesture is [2,3,4,5], the latter one will never be executed since the former one will come first and it will be compared. This behavior can be overcome by performing some action like closing the fist, but haar cascading techniques aren't that accurate (we will look at it in improvements, maybe). As of now, if you wish to add new gestures, make sure not to overlap them with the previous ones.  

With this, the working part comes to an end. This project was a fairly simple one we made, but we have plans to revamp it into a full-fledged gesture recognition app that can perform more complicated actions by incorporating machine learning and more sophisticated and accurate image processing techniques. 

### How to use 
As an end-user, all you need to do is, go to the <i>"main"</i> folder, and in the terminal, type <i>"python main.py"</i> to open the main process. Make sure there are at least the following files in the directory - <i>"main.py , functions.py, gestures.py, gesturedata.json"</i>. A small window will open with a text prompting you to place your hand to cover all the green rectangles. Once you are done, you can press 'q' to exit the window or wait for it to close itself after a few seconds. 
Then, a couple of windows open showing the final result in a window named <i>"frame"</i> and the mask named <i>"mask3"</i>. Keeping any window active, press 't' to go to <i>"track mode"</i>, 'i' to go to <i>"idle mode"</i>, and 's' to save a screenshot. The idle mode does no tracking, and in track mode, the terminal shows the movements you have made so far. Making some swift movements will show the new movement made along with the gesture recorded. In case you make the wrong gesture, simply press 't' to reset, or 'i' to go to idle mode. Once the gesture is recorded , the action will be performed and you will be informed of it via the terminal. Just to be safe, you are sent to the idle mode after the gesture is executed. Press 't' again and perform another gesture, and so on. If the keypresses do not work, make sure your Caps Lock is turned off. 
To exit the program, press the 'q' button. If you are still confused, you can check out the video under the "A demo?"  section below. 

Here is a list of gestures by default - 
<table>
	<tr>
		<th>Gesture</th>
		<th>Command</th>
	</tr>
	<tr>
		<td>[2,5,3,6]</td>
		<td>Opens firefox with 4 tabs by default – Google,Gmail,YouTube,Quora. URLs can be added, deleted, or modified by changing the "urls" property in "gesturedata.json"</td>
	</tr>
	<tr>
		<td>[2,6,2,6]</td>
		<td>Opens Google Chrome with 4 tabs by default – Google,Gmail,YouTube,Quora. URLs can be added, deleted, or modified by changing the "urls" property in "gesturedata.json"</td>
	</tr>
	<tr>
		<td>[2,4,6,7]</td>
		<td>Opens RhythmBox</td>
	</tr>
	<tr>
		<td>[3,2]</td>
		<td>Volume Up in rhythmbox, can also be mapped to other processes.</td>
	</tr>
	<tr>
		<td>[7,6]</td>
		<td>Volume Down in rhythmbox, can also be mapped to other processes.</td>
	</tr>
	<tr>
		<td>[3,5]</td>
		<td>Play next song in Rhythmbox.</td>
	</tr>
	<tr>
		<td>[1,7]</td>
		<td>Play previous song in Rhythmbox.</td>
	</tr>
	<tr>
		<td>[2,6,4]</td>
		<td>Play Rhythmbox (if paused).</td>
	</tr>
	<tr>
		<td>[2,6,8]</td>
		<td>PauseRhythmbox (if played).</td>
	</tr>
	<tr>
		<td>[5,2,7]</td>
		<td>Closes the current process.</td>
	</tr>
</table>

### Improvements
ITSP isn't the end of this project. It is just the beginning. What you just saw was a small attempt to recognizing gestures and performing small operations. Topics like image processing can be of great use in making our lives easier and designing new software and gadgets that can change the world altogether. We plan to dive more into the formal and conceptual topics of image processing to improve this project.

### A demo?
Here is a demonstration of the project.

<div style="text-align: center">
	<iframe width="560" height="315" src="https://www.youtube.com/embed/lZw4JClebbk" frameborder="0" allowfullscreen></iframe>
</div>

### Feedback / Suggestions
We are always ready for your feedback and suggestions. Feel free to contact us. As of now, the code is private, but we will release it as open source really soon. And what's more, we are now working on improving this project and taking it to the next level.

That's it for this month! Time for a coffee break! 
Thanks for reading. Happy Coding!! 