
# Typed

Quick links:
1. [About](#about)
2. [Installation](#installation)
3. [Link to Documentation](https://ben-ezra.org/TYPED/html)

## About 
*TYPED* defines an *interface* for image processing that is based on explicity typed object. This means, for example, that the *compiler* knows that an object is an image of a specific color space and can *act* upon this knowledge. To lean more about typed objects and why you should care about them (or not, it depends on your application) please follow this link: (TO BE ADDDED)   

*TYPED* origins are small and simple C++ library named CLIP, (C++ Library for Image Processing) written at the Hebrew University of Jerusalem at the late 1990s to help wth research project.  

Type is an implementation of the CLIP interface over OpenCV, where ClipOCV is now mostly (but not entirely) a wrapper over OpenCV.
OpenCV can be used directly wherever ClipOCV interface is not (yet) available. 

ClipOCV has several features that make it (or so I believe), elegant and very comfortable to use
and with the use of move semantics it is in most cases as efficient using OpenCV directly. 
Some of these features include:

* ClipOCV is compact - ClipOCV programs tend to be very short.
* ClipOCV images are explicitly typed, the compiler "knows" the type of the image and can use to to automatically casting and color space
  transfromation. Likewise ClipOCV has explicit kernel types that are is different than image type. 
* Image origin can be anywhere within the image, image indeces can be float (interpolated) and can exceed the image bounderies (extrapolated).
* ClipOCV provides very useful map functions.  

## Installation 
1. Install OpenCV
2. Get ClipOCV: **git clone git@github.com:mbe2014/ClipOCV.git**
3. Create build dir in root folder: **mkdir build**
4. Change to build dir: **cd build**
5. Run cmake: **cmake ..**
6. Run make - this will create both library and examples: **make**
7. Optionally install library and include files: **make install**
8. Shell script **build.sh** will run steps 3 through 6 for Debug and Release setting.

---

CLIP    is copyright (c) 1997 - Hebrew University of Jerusalem<br>
ClipOCV is copyright (c) 2017 - Moshe Ben-Ezra<br>

