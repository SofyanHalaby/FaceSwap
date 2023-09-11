# FaceSwap
a seed for simple face swapping using C++, opencv and Haar cascade model
requirements:
- c++ compiler
- opencv
- cmake

how to build:
 - cv <FaceSwap directory>
 - cmake .
 - make
 - you should find FaceSwap binary file at the root of respository
before running you should have all of the following in the same directory:
 - FaceSwap: binary application file
 - haarcascade_frontalface_default.xml : a pre-built face detection model
 - in : directory contains images to be processed
 - out: directory to which the application sends its outputs
how to run:
 - cd to the the directory that contans the FaceSwap binary
 - run ./FaceSwap
 - you should find the output at "out" directory

