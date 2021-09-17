# CleanPhotos
<hr>

## 1. Description 

The objective of this program is to automatically remove junk files when importing pictures form an iPhone or an iPad to
a Mac using the Screenshot App.

When an image that has been edited is imported, three files appear:
1. The original image
2. The edited image
3. An editing file

For example, suppose that we import the edited image IMG_0001.JPG. The files that will be generated are the following:
``IMG_0001.HEIC (original)``, ``IMG_E0001.HEIC (edited)`` and ``IMG_0001.AAE (editing file)``. Note that the extension
of the images can be different depending on the iPhone model that is being used. Modern iPhones use the .HEIC, however
older ones may use .JPG, for instance. This process applies for edited videos as well.

The same happens with an image taken with the live mode. In this case, there are only two files:
1. The picture that we can see in the phone by default
2. The video resulting from the live mode

For example, suppose that we import the live mode image IMG_0002.JPG. The files that will be generated are the following:
``IMG_0002.HEIC (original)`` and ``IMG_0002.MOV (video)``


<hr>

## 2. Operation

If the given directory can be opened correctly, all the files present in there are processed and stored in their
corresponding data structures. Editing files and .MOV files are stored separately from the rest of the files in the directory.
Then, depending on the options chosen by the user, the program will perform different actions.

- EDITED FILES to be removed: In this case the program iterates over all the .AAE files. For each of these files, it searches
for the original file and the editing file. If the search turns out to be successful then both the .AAE and the original 
file are deleted. Otherwise, just the original file is deleted.
  
- LIVE MODE pictures to be removed: In this case, the program iterates over all the .MOV files. For each one of these files,
it searches for its associated image. If this image is found, the .MOV file is removed. Otherwise, the .MOV file is preserved. 

<hr>

## 3. Usage

The first thing that has to be done is to compile the program and obtain the executable file.

The program can receive four different flags:
```
-e or --edited
-l or --live
-r or --recursive
-v or --verbose
```
To run the program:
```
./CleanPhotos (flags) (directory to be processed)
```
