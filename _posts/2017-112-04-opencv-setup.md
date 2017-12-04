I was trying to use the Tensorflow's newly released Object Detection API on my webcam.
I realised I couldn't open webcam, OpenCV which was bundled with ROS was throwing all sorts of errors, I Googled and tried many hacky solution but all in vain.


Now that my end sems were over I decided to install it fresh.

This site : https://www.learnopencv.com/install-opencv3-on-ubuntu/ is a great walktrough through the installation process.
It's absolutely complete.

There the author had used a virtualenv to work on.

Now I had done this for both Python2 and Python3 !
Now when I opened my webcam in Python2 it worked like charm, but as soon  as I changed the '2' to '3' it again crashed !!

Now I decided to follow the instructions exaclty and created a virtual env !
Then I followed the steps and it worked !!

Now why my normal installation wasn't working ??


Using
```bash
find /usr/local/lib/ -type f -name "cv2*.so"
```
I found that the installed OpenCV for Python3 was at 
```bash
/usr/local/lib/python3.5/dist-packages/cv2.cpython-35m-x86_64-linux-gnu.so
```

But when I inspected what `.so` file python was importing I found it was trying to use the `.so` file at
```bash
/home/sangeet/.local/lib/python3.5/site-packages/cv2/cv2.cpython-35m-x86_64-linux-gnu.so
```


Then I tried creating a symlink between the two, but since both the files had the same name it couldn't be done.

Then out of hope I copied the file from
```bash
/usr/local/lib/python3.5/dist-packages/cv2.cpython-35m-x86_64-linux-gnu.so
```
to 
```bash
/home/sangeet/.local/lib/python3.5/site-packages/cv2/cv2.cpython-35m-x86_64-linux-gnu.so
``` 
and simply overwrite it !!

Pheww.. It worked !!

