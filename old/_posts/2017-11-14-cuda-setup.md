## CUDA Set Up
---
The last time I tried to fiddle with CUDA I got stuck in a login loop and had to reinstall Ubuntu.
Last day again I was sitting in front of a fresh installation of Ubuntu and nightmares of last time's Tensorflow GPU setup were all but moments away.

Anyway I had to do it.

But surprisingly this time it was short and simple ( simpler would hae been a better choice ).
So decided to document it in case I or my friends ever need it.
Aim :: To install Tensrflow GPU version !

Bottleneck :: How to correctly install nvidia's CUDA Toolkit and cuDNN for that !
Few Pointers to keep in mind ::

1. Visit tensorflow's installation page and install only those version of dependencies that are mentioned. 
2. e.g. The latest version of cuDNN is 9 but as of the date of writing this post Tensoflow doesn't support cuDNN 9.
3. I am assuming you had no previous conflicting packages installed, like a previous version of tensoflow or nvidia CUDA toolkit.

## The steps ::

- Go to https://developer.nvidia.com/cuda-toolkit , but if you proceed it takes you to the cuda toolkit version 9's download page which we do not want as TF doesnt support it as of now.
- So go to CUDA Toolkit Archive and download the toolkit version 8 from the list. Proceed and download the `.deb (local)` file.
- Install the .deb package || At the end of the installation you will most probably get this error
    /sbin/ldconfig.real: /usr/lib/nvidia-375/libEGL.so.1 is not a symbolic link
- The fix to this is is simply renaming some files :::
```
$ sudo mv /usr/lib/nvidia-375/libEGL.so.1 /usr/lib/nvidia-375/libEGL.so.1.org
$ sudo mv /usr/lib32/nvidia-375/libEGL.so.1 /usr/lib32/nvidia-375/libEGL.so.1.org
$ sudo ln -s /usr/lib/nvidia-375/libEGL.so.375.39 /usr/lib/nvidia-375/libEGL.so.1
$ sudo ln -s /usr/lib32/nvidia-375/libEGL.so.375.39 /usr/lib32/nvidia-375/libEGL.so.1
```
- For sanity installation the .deb package again.
- Now you have to add the path variables to the .bashrc file
```
export PATH=/usr/local/cuda-8.0/bin${PATH:+:${PATH}}
export LD_LIBRARY_PATH=/usr/local/cuda-8.0/lib${LD_LIBRARY_PATH:+:${LD_LIBRARY_PATH}}
```
  Make sure that the installation was done in  `/usr/local/cuda-8.0`  only, if it were anywhere else accordingly change that.
- Now go to cuDNN downloads and sign up to download the appropriate version , note that cuDNN 7 is supported by TF as of now.
- Download the cuDNN v6.0 Library for Linux , even if there is a .deb versio nfor ubuntu go for this ! Why ? Because it worked for me !!



1.  Navigate to your <cudnnpath> directory containing the cuDNN Tar file.
2.  Unzip the cuDNN package.
    `$ tar -xzvf cudnn-9.0-linux-x64-v7.tgz`
3. Copy the following files into the CUDA Toolkit directory. Use these 👇 
```
$ sudo cp -P include/cudnn.h /usr/local/cuda-8.0/include/
$ sudo cp -P lib64/libcudnn* /usr/local/cuda-8.0/lib64/
$ sudo chmod a+r /usr/lib/x86_64-linux-gnu/libcudnn*
```
That’s it ! <br>
Do not meddle with your graphics driver, I did that twice once via `tty mode` and once via `additional drivers` option. Both the time I got stuck in a login loop.
