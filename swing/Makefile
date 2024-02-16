##########################################
#
#  Exemple de Makefile
#  Eric Lecolinet - Reda Dehak - Telecom ParisTech 2015
#  INF224 - TP Java/Swing - http://www.telecom-paristech.fr/~elc/inf224
#
##########################################

#
# Nom du programme (doit correspondre au fichier qui contient main())
#
PROG = MainWindow

#
# Package name
#
PACKAGE = RemoteControl
BIN_DIR = bin

#
# Fichiers sources .java
#
SOURCES = $(SRC_DIR)/$(PACKAGE)/MainWindow.java  $(SRC_DIR)/$(PACKAGE)/ButtonAction.java $(SRC_DIR)/$(PACKAGE)/ClientSocket.java 

#
# Compilateur Java
#
JC = javac

#
# Options du compilateur Java
#
JFLAGS = -g

#
# Directory containing source files
#
SRC_DIR = src

##########################################
#
# Regles de construction/destruction des .class et de l'executable
#
 
all: classes

run: all
	java -cp $(BIN_DIR) $(PACKAGE).${PROG}

classes: $(SOURCES:.java=.class)

clean:
	-@$(RM) *.class 1>/dev/null 2>&1
  
tar:
	tar cvf ${PROG}.tar.gz ${SOURCES}


###########################################
#
# Regles implicites
#

.SUFFIXES: .java .class

# compile: $(BIN_DIR)
.java.class:
	$(JC) -d $(BIN_DIR) $(JFLAGS) $(SRC_DIR)/$(PACKAGE)/*.java

