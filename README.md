# CleanPhotos
<hr>

## 1. Description 

The objective of this program is to automatically remove junk files when importing pictures form an iPhone or an iPad to
a Mac using the Screenshot App.

When an image that has been edited is imported, three files appear:
1. The original image
2. The edited image
3. An editing file

For example, suppose that we import the edited image IMG_001.JPG. The files that will be generated are the following:
``IMG_001.JPG (original)``, ``IMG_E001.JPG (edited)`` and ``IMG_001.AAE (editing file)``

The same happens with an image taken with the live mode. In this case, there are only two files:
1. The picture that we can see in the phone by default
2. The video resulting from the live mode

For example, suppose that we import the live mode image IMG_002.JPG. The files that will be generated are the following:
``IMG_002.HEIC (original)`` and ``IMG_002.MOV (video)``

When executing the program, if an edited image is found, only the edited file will be preserved and the original image
in case a live mode image.

<hr>

## 2. Usage

The first thing that has to be done is to compile the program and obtain the executable file

The program can receive three different flags:
```
-e or --edited
-l or --live
-r or --recursive
```
To make the program run:
```
./CleanPhotos (flags) (directory that wants to be processed)
```
