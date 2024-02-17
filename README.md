# INF224-TP: Yuri DE SENE ALVIZI


# Answered questions

## C++

### Step 1

Done.

### Step 2

Done.

### Step 3

Done.

### Step 4

1. This type of method is called pure virtual. They are declared with the keyword virtual in the beggining and "=0" in the end.

2. Because media doesn't have an implementation to the play method.

### Step 5

The oriented object caracteristic that allows this behavior is the polymorphism. In order to have it, the class needs to inherit from the parent class, and we can do that by putting *": public ClassParent* in the class declaration.

The array has pointers to these objects.

### Step 6

Done.

### Step 7

The Movie class needs to be changed to destroy the the pointers of the *chapters* array.

### Step 8

The object list has to be an object pointer list, since we want to take advantage of the polymorphism. In java is the same, but we don't need to care about the pointers, because the pointers are "hidden' from the developers.

### Step 9

Done. We can verify that they are destroyed by the printed message defined in ther destructors.

### Step 10

All these functionalities are performed by the *Manager.hh*.

In order to allow only Manager to create objects, we make the constructors private and make Manager be a friend class of the Media and Group classes.

Additional question has not been done.
### Step 11

The decided protocol is:

1. The client send a request in the form:

   'action type "Name"'

   where action can be *search* or *play* and type can be *media* or *group*. The name of the target has to be between quotes marks. For example, to search a video we send *search media "Video 1"*.

2. The server play the media, if it was a play request, or send all group or media info to the client, who prints it.

Additional questions have not been done.

### Step 12

The methods readAllMedia and saveAllMedia were added to Manager.hh. With them we can read all media saved in a file and put them in the map *medias*.

The additional questions have not been done.

### Step 13

Not done.

## Java Swing

### Step 1

When we click several times on the first two buttons, the printed text overflows the JTextArea and we need to increase its size to see the new printed texts.

As sugested, a JScrollPane was added to avoid this problem.

### Step 2

In order to have the same button in different places, a new class ButtonAction was created. It extends AbstractAction and it allows to determine the text in the button and its action when clicked.

### Step 3

The GUI developed can request to search a media or a group and to play a media. The "database" has:
- Medias: Photo 1, Photo 2, Video 1, Video 2, Movie 1, Movie 2;
- Groups: Vacation, Photos, Videos, Movies;
**The names are case sensitive!**

The client reads server answer line by line until receives a line equals to "|". This protocol communication was defined in order to receive "\n" caracters.

### Step 4:

As requested, to run the Java Swing GUI:
```console
   make run
```
**Attention:** It is necessary to run the server first.

## Doxygen

The generated **Doxygen** documentation for each part of this TP is in respective folders. For example, for the cpp documentation, open *cpp/doc/index.html*.
